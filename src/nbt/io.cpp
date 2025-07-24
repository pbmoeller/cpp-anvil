#include "cpp-anvil/nbt/io.hpp"
#include "cpp-anvil/util/compression.hpp"

// Internal headers
#include "util/nbt_byte_stream.hpp"

// STL
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <memory>
#include <vector>

namespace anvil {

bool readFile(std::ifstream& strm, std::vector<unsigned char>& data)
{
    strm.seekg(0, std::ios::end);
    size_t size = strm.tellg();
    strm.seekg(0);

    data.clear();
    data.resize(size, 0);
    strm.read(reinterpret_cast<char*>(&data[0]), size);

    if(strm.gcount() != size) {
        return false;
    }

    return true;
}

bool isNbtFile(const std::string& filename)
{
    if(!std::filesystem::exists(filename)) {
        return false;
    }

    std::ifstream file(filename, std::ios::binary);
    if(file.is_open()) {
        // Read first 2 bytes from binary data. These bytes indicate if the file is uncompressed or
        // either Zlib or Gzip compressed.
        std::vector<unsigned char> buffer(2, 0);
        file.read(reinterpret_cast<char*>(&buffer[0]), 2);
        if(!file || file.gcount() != 2) {
            return false;
        }
        CompressionType compressionType = testCompression(buffer);
        file.seekg(0);

        // Uncompress file if compression was found
        bool ret{true};
        std::vector<unsigned char> data;
        if(compressionType == CompressionType::Gzip) {
            ret = inflate_gzip(file, data);
        } else if(compressionType == CompressionType::Zlib) {
            ret = inflate_zlib(file, data);
        } else {
            ret = readFile(file, data);
        }

        file.close();

        // Check if uncompressing or reading file succeeded
        if(!ret) {
            return false;
        }

        // Check if the file starts with a CompoundTag
        if(data[0] != static_cast<unsigned char>(TagType::Compound)) {
            return false;
        }

        return true;
    }

    return false;
}

std::unique_ptr<CompoundTag> loadFromFile(const std::string& filename)
{
    CompressionType compressionType;
    return loadFromFile(filename, compressionType);
}

std::unique_ptr<CompoundTag> loadFromFile(const std::string& filename,
                                          CompressionType& compressionType)
{
    if(!std::filesystem::exists(filename)) {
        return {};
    }

    std::ifstream file(filename, std::ios::binary);
    if(file.is_open()) {
        // Read first 2 bytes from binary data. These bytes indicate if the file is uncompressed or
        // either Zlib or Gzip compressed.
        std::vector<unsigned char> buffer(2, 0);
        file.read(reinterpret_cast<char*>(&buffer[0]), 2);
        if(!file || file.gcount() != 2) {
            return {};
        }
        compressionType = testCompression(buffer);
        file.seekg(0);

        // Uncompress file if compression was found
        bool ret{true};
        std::vector<unsigned char> data;
        if(compressionType == CompressionType::Gzip) {
            ret = inflate_gzip(file, data);
        } else if(compressionType == CompressionType::Zlib) {
            ret = inflate_zlib(file, data);
        } else {
            ret = readFile(file, data);
        }

        file.close();

        // Check if uncompressing or reading file succeeded
        if(!ret) {
            return {};
        }

        // Check if the file starts with a CompoundTag
        if(data[0] != static_cast<unsigned char>(TagType::Compound)) {
            return {};
        }

        return readData(data);
    }

    return {};
}

bool saveToFile(const std::string& filename, std::vector<unsigned char>& data)
{
    return saveToFile(filename, data, CompressionType::Uncompressed, DefaultCompression);
}

bool saveToFile(const std::string& filename, std::vector<unsigned char>& data,
                CompressionType compressionType)
{
    return saveToFile(filename, data, compressionType, DefaultCompression);
}

bool saveToFile(const std::string& filename, std::vector<unsigned char>& data,
                CompressionType compressionType, int compressionLevel)
{
    std::ofstream ofs(filename, std::ios::binary);
    if(!ofs.is_open()) {
        return false;
    }

    int ret = true;
    switch(compressionType) {
        case CompressionType::Gzip:
            ret = deflate_gzip(ofs, data, compressionLevel);
            break;
        case CompressionType::Zlib:
            ret = deflate_zlib(ofs, data, compressionLevel);
            break;
        case CompressionType::Uncompressed:
            ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
            break;
    }

    ofs.close();

    return ret;
}

bool saveToFile(const std::string& filename, const CompoundTag* compoundTag)
{
    return saveToFile(filename, compoundTag, CompressionType::Uncompressed, DefaultCompression);
}

bool saveToFile(const std::string& filename, const CompoundTag* compoundTag,
                CompressionType compressionType)
{
    return saveToFile(filename, compoundTag, compressionType, DefaultCompression);
}

bool saveToFile(const std::string& filename, const CompoundTag* compoundTag,
                CompressionType compressionType, int compressionLevel)
{
    std::vector<unsigned char> data = writeData(compoundTag);

    return saveToFile(filename, data, compressionType, compressionLevel);
}

std::unique_ptr<BasicTag> readChildTag(NbtInputByteStream& byteStream, bool isListItem = false,
                                       TagType listTag = TagType::End)
{
    TagType tagType;
    StringType name;

    // ListItems do not have tag types and do not have names
    if(isListItem) {
        tagType = listTag;
    } else {
        tagType = byteStream.read<TagType>();

        // EndTags do not have names
        if(tagType != TagType::End) {
            name = byteStream.read<StringType>();
        }
    }

    // Read data from stream depending on the tag type
    std::unique_ptr<BasicTag> tag;
    switch(tagType) {
        case TagType::End:
            tag = std::make_unique<EndTag>();
            break;
        case TagType::Byte:
        {
            auto value = byteStream.read<ByteType>();
            tag        = std::make_unique<ByteTag>(name, value);
            break;
        }
        case TagType::Short:
        {
            auto value = byteStream.read<ShortType>();
            tag        = std::make_unique<ShortTag>(name, value);
            break;
        }
        case TagType::Int:
        {
            auto value = byteStream.read<IntType>();
            tag        = std::make_unique<IntTag>(name, value);
            break;
        }
        case TagType::Long:
        {
            auto value = byteStream.read<LongType>();
            tag        = std::make_unique<LongTag>(name, value);
            break;
        }
        case TagType::Float:
        {
            auto value = byteStream.read<FloatType>();
            tag        = std::make_unique<FloatTag>(name, value);
            break;
        }
        case TagType::Double:
        {
            auto value = byteStream.read<DoubleType>();
            tag        = std::make_unique<DoubleTag>(name, value);
            break;
        }
        case TagType::ByteArray:
        {
            auto value = byteStream.read<std::vector<ByteType>>();
            tag        = std::make_unique<ByteArrayTag>(name, value);
            break;
        }
        case TagType::String:
        {
            auto value = byteStream.read<StringType>();
            tag        = std::make_unique<StringTag>(name, value);
            break;
        }
        case TagType::List:
        {
            TagType listTagType = byteStream.read<TagType>();
            auto listTag        = std::make_unique<ListTag>(name, listTagType);
            std::unique_ptr<BasicTag> childTag;

            const int32_t size = byteStream.read<int32_t>();
            for(int32_t i = 0; i < size; ++i) {
                childTag = readChildTag(byteStream, true, listTagType);
                listTag->push_back(std::move(childTag));
            }
            tag = std::move(listTag);

            break;
        }
        case TagType::Compound:
        {
            auto compoundTag = std::make_unique<CompoundTag>(name);
            TagType childTagType{TagType::Unknown};
            do {
                std::unique_ptr<BasicTag> childTag = readChildTag(byteStream);
                if(!childTag) {
                    throw std::runtime_error("Failed to read child tag.");
                }
                childTagType = childTag->type();
                if(childTagType != TagType::End) {
                    compoundTag->push_back(std::move(childTag));
                }
            } while(childTagType != TagType::End);
            tag = std::move(compoundTag);
            break;
        }
        case TagType::IntArray:
        {
            auto value = byteStream.read<std::vector<IntType>>();
            tag        = std::make_unique<IntArrayTag>(name, value);
            break;
        }
        case TagType::LongArray:
        {
            auto value = byteStream.read<std::vector<LongType>>();
            tag        = std::make_unique<LongArrayTag>(name, value);
            break;
        }
        case TagType::Unknown:
        default:
            throw std::runtime_error("Invalid tag type.");
    }

    return tag;
}

std::unique_ptr<CompoundTag> readData(std::vector<unsigned char>& data)
{
    NbtInputByteStream byteStream(data);
    TagType tag = byteStream.read<TagType>();
    if(tag == TagType::Unknown) {
        throw std::runtime_error("Invalid tag type.");
    } else if(tag != TagType::Compound) {
        throw std::runtime_error("First tag must be of type CompoundTag.");
    } else {
        StringType name = byteStream.read<StringType>();

        std::unique_ptr<CompoundTag> root = std::make_unique<CompoundTag>(name);

        TagType childTagType{TagType::Unknown};
        std::unique_ptr<BasicTag> childTag;
        do {
            childTag = readChildTag(byteStream);
            if(!childTag) {
                throw std::runtime_error("Failed to read child tag.");
            }
            childTagType = childTag->type();
            if(childTagType != TagType::End) {
                root->push_back(std::move(childTag));
            }
        } while(childTagType != TagType::End);

        return root;
    }

    return {};
}

void writeTag(NbtOutputByteStream& byteStream, const BasicTag* basicTag, bool isListItem = false,
              TagType listTagType = TagType::End)
{
    TagType tagType = basicTag->type();

    // Check if Tag is EndTag
    if(tagType == TagType::End) {
        byteStream.write(tagType);
        return;
    }

    // ListItems do not have tag types and names
    if(!isListItem) {
        byteStream.write(tagType);
        byteStream.write(basicTag->name());
    }

    switch(tagType) {
        case TagType::Byte:
        {
            const auto* byteTag = static_cast<const ByteTag*>(basicTag);
            byteStream.write(byteTag->value());
            break;
        }
        case TagType::Short:
        {
            const auto* shortTag = static_cast<const ShortTag*>(basicTag);
            byteStream.write(shortTag->value());
            break;
        }
        case TagType::Int:
        {
            const auto* intTag = static_cast<const IntTag*>(basicTag);
            byteStream.write(intTag->value());
            break;
        }
        case TagType::Long:
        {
            const auto* longTag = static_cast<const LongTag*>(basicTag);
            byteStream.write(longTag->value());
            break;
        }
        case TagType::Float:
        {
            const auto* floatTag = static_cast<const FloatTag*>(basicTag);
            byteStream.write(floatTag->value());
            break;
        }
        case TagType::Double:
        {
            const auto* doubleTag = static_cast<const DoubleTag*>(basicTag);
            byteStream.write(doubleTag->value());
            break;
        }
        case TagType::ByteArray:
        {
            const auto* byteArrayTag = static_cast<const ByteArrayTag*>(basicTag);
            byteStream.write(static_cast<int32_t>(byteArrayTag->size()));
            for(const auto& value : byteArrayTag->value()) {
                byteStream.write(value);
            }
            break;
        }
        case TagType::String:
        {
            const auto* stringTag = static_cast<const StringTag*>(basicTag);
            byteStream.write(stringTag->value());
            break;
        }
        case TagType::List:
        {
            const auto* listTag = static_cast<const ListTag*>(basicTag);
            byteStream.write(listTag->listType());
            byteStream.write(static_cast<int32_t>(listTag->size()));
            for(const auto& value : listTag->value()) {
                writeTag(byteStream, value.get(), true, listTag->listType());
            }
            break;
        }
        case TagType::Compound:
        {
            const auto* compoundTag = static_cast<const CompoundTag*>(basicTag);
            for(const auto& value : compoundTag->value()) {
                writeTag(byteStream, value.get());
            }
            EndTag endTag;
            writeTag(byteStream, &endTag);
            break;
        }
        case TagType::IntArray:
        {
            const auto* intArrayTag = static_cast<const IntArrayTag*>(basicTag);
            byteStream.write(static_cast<int32_t>(intArrayTag->size()));
            for(const auto& value : intArrayTag->value()) {
                byteStream.write(value);
            }
            break;
        }
        case TagType::LongArray:
        {
            const auto* longArrayTag = static_cast<const LongArrayTag*>(basicTag);
            byteStream.write(static_cast<int32_t>(longArrayTag->size()));
            for(const auto& value : longArrayTag->value()) {
                byteStream.write(value);
            }
            break;
        }
        case TagType::End:
        case TagType::Unknown:
            // Oops, how could that happen.
            break;
    }
}

std::vector<unsigned char> writeData(const BasicTag* tag)
{
    std::vector<unsigned char> data;

    NbtOutputByteStream byteStream(data);

    writeTag(byteStream, tag);

    data.resize(byteStream.size());
    return data;
}

void printChildTag(std::stringstream& sstrm, const BasicTag* tag, int indent,
                   int current_indent = 0, bool printArrayContent = false)
{
    std::string indentStr = (indent > 0 ? std::string(current_indent, ' ') : "");

    TagType tagType = tag->type();
    if(tagType == TagType::End) {
        return;
    }

    sstrm << indentStr << "TAG_" << getTagTypeName(tagType) << "(\"" << tag->name() << "\"): ";

    switch(tagType) {
        case TagType::Byte:
        {
            const auto* t = tag_cast<const ByteTag*>(tag);
            sstrm << static_cast<int>(t->value()) << '\n';
            break;
        }
        case TagType::Short:
        {
            const auto* t = tag_cast<const ShortTag*>(tag);
            sstrm << static_cast<int>(t->value()) << '\n';
            break;
        }
        case TagType::Int:
        {
            const auto* t = tag_cast<const IntTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::Long:
        {
            const auto* t = tag_cast<const LongTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::Float:
        {
            const auto* t = tag_cast<const FloatTag*>(tag);
            sstrm << std::setprecision(8) << t->value() << '\n';
            break;
        }
        case TagType::Double:
        {
            const auto* t = tag_cast<const DoubleTag*>(tag);
            sstrm << std::setprecision(16) << t->value() << '\n';
            break;
        }
        case TagType::ByteArray:
        {
            const auto* t = tag_cast<const ByteArrayTag*>(tag);

            sstrm << t->size() << " entries";
            sstrm << '\n' << indentStr << "[\n";
            sstrm << indentStr;
            if(printArrayContent) {
                for(size_t i = 1; i < t->size(); ++i) {
                    sstrm << " " << static_cast<const IntType>((*t)[i]);
                }
            } else {
                sstrm << "  ...\n";
            }
            sstrm << indentStr << "]\n";

            break;
        }
        case TagType::String:
        {
            const auto* t = tag_cast<const StringTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::List:
        {
            const auto* t = tag_cast<const ListTag*>(tag);

            sstrm << t->size() << " entries of type " << getTagTypeName(t->listType());
            sstrm << '\n' << indentStr << "{\n";
            for(const auto& child : *t) {
                printChildTag(sstrm, child.get(), indent, current_indent + indent,
                              printArrayContent);
            }
            sstrm << indentStr << "}\n";
            break;
        }
        case TagType::Compound:
        {
            const auto* t = tag_cast<const CompoundTag*>(tag);

            sstrm << t->size() << " entries";
            sstrm << '\n' << indentStr << "{\n";
            for(const auto& child : *t) {
                printChildTag(sstrm, child.get(), indent, current_indent + indent,
                              printArrayContent);
            }
            sstrm << indentStr << "}\n";

            break;
        }
        case TagType::IntArray:
        {
            const auto* t = tag_cast<const IntArrayTag*>(tag);

            sstrm << t->size() << " entries";
            sstrm << '\n' << indentStr << "[\n";
            sstrm << indentStr;
            if(printArrayContent) {
                for(size_t i = 1; i < t->size(); ++i) {
                    sstrm << " " << static_cast<const IntType>((*t)[i]);
                }
            } else {
                sstrm << "  ...\n";
            }
            sstrm << indentStr << "]\n";

            break;
        }
        case TagType::LongArray:
        {
            const auto* t = tag_cast<const LongArrayTag*>(tag);

            sstrm << t->size() << " entries";
            sstrm << '\n' << indentStr << "[\n";
            sstrm << indentStr;
            if(printArrayContent) {
                for(size_t i = 1; i < t->size(); ++i) {
                    sstrm << " " << static_cast<const LongType>((*t)[i]);
                }
            } else {
                sstrm << "  ...\n";
            }
            sstrm << indentStr << "]\n";

            break;
        }
        case TagType::Unknown:
        {
            break;
        }
    }
}

std::string printTag(const BasicTag* tag, int indent, bool printArrayContent)
{
    std::stringstream sstrm;

    if(tag->type() != TagType::End && tag->type() != TagType::Unknown) {
        printChildTag(sstrm, tag, indent, printArrayContent);
    }

    return sstrm.str();
}

} // namespace anvil
