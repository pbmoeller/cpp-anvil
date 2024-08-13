// cpp-anvil
#include <cpp-anvil/util/compression.hpp>

// zlib
#include <zlib.h>

namespace anvil {

constexpr size_t GzipChunkSize = 32768;

CompressionType testCompression(const std::vector<unsigned char> &data) {
    if(isGzipCompressed(data)) {
        return CompressionType::Gzip;
    } else if(isZlibCompressed(data)) {
        return CompressionType::Zlib;
    } else {
        return CompressionType::Uncompressed;
    }
}

bool inflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data)
{
    if(!strm.is_open() || !strm.good()) {
        return false;
    }
    
    z_stream zstrm;
    memset(&zstrm, 0, sizeof(zstrm));
    if(inflateInit2(&zstrm, 16 + MAX_WBITS) != Z_OK) {
        return false;
    }

    data.clear();
    std::vector<char> inBuffer(GzipChunkSize);
    std::vector<unsigned char> outBuffer(GzipChunkSize);

    int ret;
    do {
        strm.read(inBuffer.data(), inBuffer.size());
        zstrm.next_in = reinterpret_cast<Bytef*>(inBuffer.data());
        zstrm.avail_in = strm.gcount();

        if(strm.bad()) {
            inflateEnd(&zstrm);
            return false;
        }

        do {
            zstrm.next_out = outBuffer.data();
            zstrm.avail_out = outBuffer.size();

            ret = inflate(&zstrm, 0);
            if(ret != Z_OK && ret != Z_STREAM_END) {
                inflateEnd(&zstrm);
                return false;
            }

            data.insert(data.end(),
                        outBuffer.data(), 
                        outBuffer.data() + (outBuffer.size() - zstrm.avail_out));
        } while(zstrm.avail_out == 0);
    } while(ret != Z_STREAM_END);

    inflateEnd(&zstrm);

    return ret == Z_STREAM_END;
}

bool inflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data)
{
    return false;
}

bool deflate_gzip(std::ifstream &strm, std::vector<unsigned char> &data)
{
    return false;
}

bool deflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data)
{
    return false;
}

} // namespace anvil
