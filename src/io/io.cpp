// cpp-anvil
#include <cpp-anvil/io/io.hpp>
#include <cpp-anvil/io/compression.hpp>
#include <cpp-anvil/io/nbt_byte_stream.hpp>

// STL
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <memory>
#include <vector>

namespace nbt {
namespace io {

bool readFile(std::ifstream &strm, std::vector<unsigned char> &data)
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

std::unique_ptr<CompoundTag> loadFile(const std::string &filename)
{
    CompressionType compressionType;
    return loadFile(filename, compressionType);
}

std::unique_ptr<CompoundTag> loadFile(const std::string &filename,
                                      CompressionType &compressionType)
{
    if(!std::filesystem::exists(filename)) {
        return std::unique_ptr<CompoundTag>();
    }

    std::ifstream file(filename, std::ios::binary);
    if(file.is_open())
    {
        // Read first 2 bytes in binary data. These bytes indicate if the file is uncompressed or
        // either Zlib or Gzip compressed.
        std::vector<unsigned char> buffer(2, 0);
        file.read(reinterpret_cast<char*>(&buffer[0]), 2);
        if(!file || file.gcount() != 2) {
            return std::unique_ptr<CompoundTag>();
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

        // Check if uncompressing or reading file succeeded
        if(!ret) {
            return std::unique_ptr<CompoundTag>();
        }

        // Check if the file starts with a CompoundTag
        if(data[0] != static_cast<unsigned char>(TagType::Compound)) {
            return std::unique_ptr<CompoundTag>();
        }

        return loadData(data);
    }

    return std::unique_ptr<CompoundTag>();
}

std::unique_ptr<BasicTag> readChildTag(NbtByteStream &byteStream,
                                       bool isListItem = false,
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
            ByteType value = byteStream.read<ByteType>();
            tag = std::make_unique<ByteTag>(name, value);
            break;
        }
        case TagType::Short:
        {
            ShortType value = byteStream.read<ShortType>();
            tag = std::make_unique<ShortTag>(name, value);
            break;
        }
        case TagType::Int:
        {
            IntType value = byteStream.read<IntType>();
            tag = std::make_unique<IntTag>(name, value);
            break;
        }
        case TagType::Long:
        {
            LongType value = byteStream.read<LongType>();
            tag = std::make_unique<LongTag>(name, value);
            break;
        }
        case TagType::Float:
        {
            FloatType value = byteStream.read<FloatType>();
            tag = std::make_unique<FloatTag>(name, value);
            break;
        }
        case TagType::Double:
        {
            DoubleType value = byteStream.read<DoubleType>();
            tag = std::make_unique<DoubleTag>(name, value);
            break;
        }
        case TagType::ByteArray:
        {
            std::vector<ByteType> value = byteStream.read<std::vector<ByteType>>();
            tag = std::make_unique<ByteArrayTag>(name, value);
            break;
        }
        case TagType::String:
        {
            StringType value = byteStream.read<StringType>();
            tag = std::make_unique<StringTag>(name, value);
            break;
        }
        case TagType::List:
        {
            TagType listTagType = byteStream.read<TagType>();
            std::unique_ptr<ListTag> listTag = std::make_unique<ListTag>(name, listTagType);
            std::unique_ptr<BasicTag> childTag;
            
            int32_t size = byteStream.read<int32_t>();
            for(int32_t i = 0; i < size; ++i) {
                childTag = readChildTag(byteStream, true, listTagType);
                listTag->push_back(std::move(childTag));
            }
            tag = std::move(listTag);

            break;
        }
        case TagType::Compound:
        {
            std::unique_ptr<CompoundTag> compoundTag = std::make_unique<CompoundTag>(name);
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
            std::vector<IntType> value = byteStream.read<std::vector<IntType>>();
            tag = std::make_unique<IntArrayTag>(name, value);
            break;
        }
        case TagType::LongArray:
        {
            std::vector<LongType> value = byteStream.read<std::vector<LongType>>();
            tag = std::make_unique<LongArrayTag>(name, value);
            break;
        }
        case TagType::Unknown:
        default:
            throw std::runtime_error("Invalid tag type.");
    }

    return tag;
}

std::unique_ptr<CompoundTag> loadData(std::vector<unsigned char> &data)
{
    NbtByteStream byteStream(data);
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

    return std::unique_ptr<CompoundTag>();
}

void printChildTag(std::stringstream &sstrm,
                   const BasicTag *tag,
                   int indent,
                   int current_indent = 0,
                   bool printArrayContent = false)
{
    std::string indentStr = (indent > 0 ? std::string(current_indent, ' ') : "");

    TagType tagType = tag->type();
    if(tagType == TagType::End) {
        return;
    }
    const NamedTag *namedTag = tag_cast<const NamedTag*>(tag);

    sstrm << indentStr << "TAG_" << getTagTypeName(tagType) << "(\"" << namedTag->name() << "\"): ";

    switch(tagType) {
        case TagType::Byte:
        {
            const ByteTag *t = tag_cast<const ByteTag*>(tag);
            sstrm << static_cast<int>(t->value()) << '\n';
            break;
        }
        case TagType::Short:
        {
            const ShortTag *t = tag_cast<const ShortTag*>(tag);
            sstrm << static_cast<int>(t->value()) << '\n';
            break;
        }
        case TagType::Int:
        {
            const IntTag *t = tag_cast<const IntTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::Long:
        {
            const LongTag *t = tag_cast<const LongTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::Float:
        {
            const FloatTag *t = tag_cast<const FloatTag*>(tag);
            sstrm << std::setprecision(8) << t->value() << '\n';
            break;
        }
        case TagType::Double:
        {
            const DoubleTag *t = tag_cast<const DoubleTag*>(tag);
            sstrm << std::setprecision(16) << t->value() << '\n';
            break;
        }
        case TagType::ByteArray:
        {
            const ByteArrayTag *t = tag_cast<const ByteArrayTag*>(tag);

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
            const StringTag *t = tag_cast<const StringTag*>(tag);
            sstrm << t->value() << '\n';
            break;
        }
        case TagType::List:
        {
            const ListTag *t = tag_cast<const ListTag*>(tag);

            sstrm << t->size() << " entries of type " << getTagTypeName(t->listType());
            sstrm << '\n' << indentStr << "{\n";
            for(const auto &child : *t) {
                printChildTag(sstrm, child.get(), indent, current_indent + indent, printArrayContent);
            }
            sstrm << indentStr << "}\n";
            break;
        }
        case TagType::Compound:
        {
            const CompoundTag *t = tag_cast<const CompoundTag*>(tag);

            sstrm << t->size() << " entries";
            sstrm << '\n' << indentStr << "{\n";
            for(const auto &child : *t) {
                printChildTag(sstrm, child.get(), indent, current_indent + indent, printArrayContent);
            }
            sstrm << indentStr << "}\n";

            break;
        }
        case TagType::IntArray:
        {
            const IntArrayTag *t = tag_cast<const IntArrayTag*>(tag);

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
            const LongArrayTag *t = tag_cast<const LongArrayTag*>(tag);

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

std::string printTag(const BasicTag *tag, int indent, bool printArrayContent)
{
    std::stringstream sstrm;

    if(tag->type() != TagType::End && tag->type() != TagType::Unknown) {
        printChildTag(sstrm, tag, indent, printArrayContent);
    }

    return sstrm.str();
}

} // namespace io
} // namespace nbt
