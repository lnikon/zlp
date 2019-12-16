#ifndef GENERIGenericValue_H
#define GENERIGenericValue_H

#include "extension_defs.hpp"
#include "type_defs.hpp"

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
    GenericValue(std::string arr, std::size_t nSize);

    GenericValue(const GenericValue& o);
    GenericValue(GenericValue&& o) noexcept;

    ~GenericValue() noexcept;

    GenericValue& operator=(const GenericValue&);
    GenericValue& operator=(GenericValue&&) noexcept;

    inline Extension type() const noexcept;
    inline std::size_t count() const noexcept; // returns number of contained elements
    inline std::size_t size() const noexcept;	// returns total size of allocated memory
    inline std::size_t unitSize() const noexcept;	// returns size of single element (size of type)

    inline bool null() const noexcept;
    inline bool valid() const noexcept;
    inline bool string() const noexcept;

    inline operator BYTE const&() const noexcept;
    inline operator WORD const&() const noexcept;
    inline operator DWORD const&() const noexcept;
    inline operator QWORD const&() const noexcept;
    inline operator CHAR const&() const noexcept;
//    inline operator () const noexcept;
    inline operator bool() const noexcept;

    inline operator void const*() const noexcept;

    template <typename DataType>
    inline DataType const& operator[](t_index idx) const noexcept;

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
};

#endif // GENERIGenericValue_H
