#ifndef GENERIGenericValue_H
#define GENERIGenericValue_H

#include "extension_defs.hpp"
#include "type_defs.hpp"

#include <cassert>

using namespace Extensions;

class GenericValue
{
public:
    explicit GenericValue(Extension ext = Extension::EXT_NULL) noexcept;
    GenericValue(Extension ext, std::size_t count, const void* pData = nullptr);

    GenericValue(BYTE byte) noexcept;
    GenericValue(WORD word) noexcept;
    GenericValue(DWORD dword) noexcept;
    GenericValue(QWORD qword) noexcept;
    GenericValue(CHAR chr) noexcept;

    GenericValue(BYTE_ARRAY bytes);
    GenericValue(WORD_ARRAY words);
    GenericValue(DWORD_ARRAY dwords);
    GenericValue(QWORD_ARRAY qwords);

    GenericValue(std::string str);
    GenericValue(const char* cstr, std::size_t size);

    GenericValue(const GenericValue& o);
    GenericValue(GenericValue&& o) noexcept;

    ~GenericValue() noexcept;

    GenericValue& operator=(const GenericValue&);
    GenericValue& operator=(GenericValue&&) noexcept;

    Extension type() const noexcept;
    std::size_t count() const noexcept; // returns number of contained elements
    std::size_t size() const noexcept;	// returns total size of allocated memory
    std::size_t unitSize() const noexcept;	// returns size of single element (size of type)

    bool null() const noexcept;
    bool valid() const noexcept;
    bool string() const noexcept;

    operator BYTE const&() const noexcept;
    operator WORD const&() const noexcept;
    operator DWORD const&() const noexcept;
    operator QWORD const&() const noexcept;
    operator CHAR const&() const noexcept;
    operator bool() const noexcept;
    operator const char*() const noexcept;
    operator void const*() const noexcept;

    template <typename DataType>
    inline DataType const& operator[](std::size_t) const noexcept;

private:
    union GenericData
    {
            BYTE b;
            WORD w;
            DWORD dw;
            QWORD qw;
            CHAR ch;

            BYTE* pb;
            WORD* pw;
            DWORD* pdw;
            QWORD* pqw;
            CHAR* psz;

    };

    Extension type_{Extension::EXT_NULL};
    std::size_t count_;
    GenericData data_;
};

template<typename DataType>
inline const DataType& GenericValue::operator[](std::size_t idx) const noexcept
{
    return DataType();
}

template<>
inline const uint8_t& GenericValue::operator[]<uint8_t>(std::size_t idx) const noexcept
{
    assert(type_ == Extension::EXT_BYTE && count_ > 1);
    return data_.pb[idx];
}

template<>
inline const uint16_t& GenericValue::operator[]<uint16_t>(std::size_t idx) const noexcept
{
    assert(type_ == Extension::EXT_WORD && count_ > 1);
    return data_.pw[idx];
}

template<>
inline const uint32_t& GenericValue::operator[]<uint32_t>(std::size_t idx) const noexcept
{
    assert(type_ == Extension::EXT_DWORD && count_ > 1);
    return data_.pdw[idx];
}

template<>
inline const uint64_t& GenericValue::operator[]<uint64_t>(std::size_t idx) const noexcept
{
    assert(type_ == Extension::EXT_QWORD && count_ > 1);
    return data_.pqw[idx];
}

template <>
inline const char& GenericValue::operator[]<char>(std::size_t idx) const noexcept
{
    assert(type_ == Extension::EXT_CHAR && count_ > 1);
    return data_.psz[idx];
}

using namespace Extensions;

template <typename DataType>
inline Extension valueType()
{
    return Extension::EXT_NULL;
}

template <>
inline Extension valueType<uint8_t>()
{
    return Extension::EXT_BYTE;
}

template <>
inline Extension valueType<uint16_t>()
{
    return Extension::EXT_WORD;
}

template <>
inline Extension valueType<uint32_t>()
{
    return Extension::EXT_DWORD;
}

template <>
inline Extension valueType<uint64_t>()
{
    return Extension::EXT_QWORD;
}

template <>
inline Extension valueType<char>()
{
    return Extension::EXT_CHAR;
}

uint8_t valueTypeSize(Extension e);

#endif // GENERIGenericValue_H
