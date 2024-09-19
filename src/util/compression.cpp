// cpp-anvil
#include <cpp-anvil/util/compression.hpp>

// zlib
#include <zlib.h>

namespace anvil {

constexpr size_t GzipChunkSize = 32768;
constexpr size_t ZlibChunkSize = 16384;

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
    
    z_stream zstrm{};
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

bool inflate_gzip(const std::vector<unsigned char> &in, std::vector<unsigned char> &out)
{
    // Just check that there is actually data
    if(in.size() == 0) {
        return true;
    }

    // Init zstream object
    z_stream zstrm{};
    zstrm.next_in   = const_cast<Bytef*>(in.data());
    zstrm.avail_in  = static_cast<uInt>(in.size());

    // Start with a guess for output size
    out.resize(in.size() * 2, 0);

    // 
    if(inflateInit2(&zstrm, (16 + MAX_WBITS)) != Z_OK) {
        return false;
    }

    int ret{0};
    do {
        // Set output buffer
        zstrm.next_out  = reinterpret_cast<Bytef*>(out.data() + zstrm.total_out);
        zstrm.avail_out = static_cast<uInt>(out.size()) - static_cast<uInt>(zstrm.total_out);

        // Decompress the data
        ret = inflate(&zstrm, Z_NO_FLUSH);
        if(ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&zstrm);
            return false;
        }

        if(ret == Z_BUF_ERROR || ret == Z_OK) {
            if(zstrm.avail_out == 0) {
                size_t old_size = out.size();
                out.resize(old_size * 2);
            }
        }
    } while(ret != Z_STREAM_END);

    out.resize(zstrm.total_out);

    // Clean up and free memory
    inflateEnd(&zstrm);

    return true;
}

bool inflate_zlib(std::ifstream &strm, std::vector<unsigned char> &data)
{
    if(!strm.is_open() || !strm.good()) {
        return false;
    }

    z_stream zstrm{};
    if(inflateInit(&zstrm) != Z_OK) {
        return false;
    }

    data.clear();
    std::vector<char> inBuffer(ZlibChunkSize);
    std::vector<unsigned char> outBuffer(ZlibChunkSize);

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

bool inflate_zlib(const std::vector<unsigned char> &in, std::vector<unsigned char> &out)
{
    // Just check that there is actually data
    if(in.size() == 0) {
        return true;
    }

    // Init zstream object
    z_stream zstrm{};
    if(inflateInit(&zstrm) != Z_OK) {
        return false;
    }

    zstrm.avail_in  = in.size();
    zstrm.next_in   = const_cast<Bytef*>(in.data());
    
    int ret{0};
    unsigned long prevOut{0};
    do {
        std::vector<unsigned char> buffer(ZlibChunkSize, 0);
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        zstrm.avail_out = ZlibChunkSize;

        ret = inflate(&zstrm, 0);
        out.insert(out.end(),
                   buffer.begin(),
                   buffer.begin() + (zstrm.total_out - prevOut));
        prevOut = zstrm.total_out;
    } while(ret == Z_OK);

    inflateEnd(&zstrm);
    if(ret != Z_STREAM_END) {
        return false;
    }

    out.resize(zstrm.total_out);
    return true;
}

bool deflate_gzip(std::ofstream &strm,
                  std::vector<unsigned char> &data,
                  const int compressionLevel)
{
    // Just check that there is actually data
    if(data.empty()) {
        return true;
    }

    // Initialize zstream object
    z_stream zstrm{};
    if(deflateInit2(&zstrm, compressionLevel, Z_DEFLATED,
                    16 + MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        return false;
    }
    zstrm.next_in = const_cast<Bytef*>(data.data());
    zstrm.avail_in = static_cast<uInt>(data.size());

    int ret{0};
    std::vector<unsigned char> buffer(GzipChunkSize, 0);
    do {
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        zstrm.avail_out = GzipChunkSize;

        ret = deflate(&zstrm, Z_FINISH);
        if(ret == Z_STREAM_ERROR) {
            deflateEnd(&zstrm);
            return false;
        }

        uInt bytes = GzipChunkSize - zstrm.avail_out;
        strm.write(reinterpret_cast<const char*>(buffer.data()), bytes);

        if(!strm.good()) {
            deflateEnd(&zstrm);
            return false;
        }

    } while(ret == Z_OK);

    deflateEnd(&zstrm);
    return ret == Z_STREAM_END;
}

bool deflate_gzip(const std::vector<unsigned char> &in,
                  std::vector<unsigned char> &out,
                  const int compressionLevel)
{
    // Just check that there is actually data
    if(in.empty()) {
        return true;
    }

    // Initialize zstream object
    z_stream zstrm{};
    if(deflateInit2(&zstrm, compressionLevel, Z_DEFLATED,
                    16 + MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        return false;
    }
    zstrm.next_in = const_cast<Bytef*>(in.data());
    zstrm.avail_in = static_cast<uInt>(in.size());

    out.clear();

    int ret{0};
    std::vector<unsigned char> buffer(GzipChunkSize, 0);
    do {
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        zstrm.avail_out = GzipChunkSize;

        ret = deflate(&zstrm, Z_FINISH);
        uInt bytes = GzipChunkSize - zstrm.avail_out;
        out.insert(out.end(),
                   buffer.begin(),
                   buffer.begin() + bytes);
    } while(ret == Z_OK);

    // Resize the output buffer to the actual compressed size
    out.resize(zstrm.total_out);

    deflateEnd(&zstrm);
    return true;
}

bool deflate_zlib(std::ofstream &strm,
                  std::vector<unsigned char> &data,
                  const int compressionLevel)
{
    // Just check that there is actually data
    if(data.size() == 0) {
        return true;
    }

    return false;
}

bool deflate_zlib(const std::vector<unsigned char> &in,
                  std::vector<unsigned char> &out,
                  const int compressionLevel)
{
    // Just check that there is actually data
    if(in.size() == 0) {
        return true;
    }

    // Initialize zstream object
    z_stream zstrm{};
    if(deflateInit(&zstrm, compressionLevel) != Z_OK) {
        return false;
    }
    zstrm.next_in = const_cast<Bytef*>(in.data());
    zstrm.avail_in = static_cast<uInt>(in.size());

    // Initial output buffer size, if we need more it can grow.
    out.clear();

    int ret{0};
    std::vector<unsigned char> buffer(ZlibChunkSize, 0);
    do {
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        zstrm.avail_out = ZlibChunkSize;

        ret = deflate(&zstrm, Z_FINISH);
        uInt bytes = ZlibChunkSize - zstrm.avail_out;
        out.insert(out.end(),
                   buffer.begin(),
                   buffer.begin() + bytes);
    } while(ret == Z_OK);

    // Resize the output buffer to the actual compressed size
    out.resize(zstrm.total_out);

    deflateEnd(&zstrm);
    return true;
}

} // namespace anvil
