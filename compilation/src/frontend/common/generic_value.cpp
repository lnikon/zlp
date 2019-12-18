#include "generic_value.h"

#include <cstring>
#include <exception>

GenericValue::GenericValue(Extension ext) noexcept
    : type_{ext}, count_{0}
{
    data_.qw = 0;
}

GenericValue::GenericValue(Extension ext, std::size_t count, const void* pData)
    : type_{ext}, count_{count}
{
    data_.qw = 0;
    if (count > 1)
    {
        std::size_t sz = 0;
        if (type_ == Extension::EXT_BYTE)
        {
            data_.pb = new BYTE[count_];
            sz = count_ * sizeof(BYTE);
        }
        else if (type_ == Extension::EXT_WORD)
        {
            data_.pw = new WORD[count_];
            sz = count_ * sizeof(WORD);
        }
        else if (type_ == Extension::EXT_DWORD)
        {
            data_.pdw = new DWORD[count_];
            sz = count_ * sizeof(DWORD);
        }
        else if (type_ == Extension::EXT_QWORD)
        {
            data_.pqw = new QWORD[count_];
            sz = count_ * sizeof(QWORD);
        }
        else
        {
            throw std::terminate;
        }

        if (pData == nullptr)
        {
            std::memset((void *)data_.pb, 0, sz);
        }
        else
        {
            std::memcpy((void *)data_.pb, (void *)pData, sz);
        }
    }
    else if(count == 1 && pData != nullptr)
    {
        if (type_ == Extension::EXT_BYTE)
        {
            data_.b = *((const uint8_t*)pData);
        }
        else if (type_ == Extension::EXT_WORD)
        {
            data_.w = *((const uint16_t*)pData);
        }
        else if (type_ == Extension::EXT_DWORD)
        {
            data_.dw = *((const uint32_t*)pData);
        }
        else if (type_ == Extension::EXT_QWORD)
        {
            data_.qw = *((const uint64_t*)pData);
        }
        else
        {
            throw std::terminate;
        }
    }
    else
    {
        throw std::terminate;
    }
}

GenericValue::GenericValue(BYTE byte) noexcept
    : type_{Extension::EXT_BYTE}, count_{1}
{
    data_.qw = 0;
    data_.b = byte;
}

GenericValue::GenericValue(WORD word) noexcept
    : type_{Extension::EXT_WORD}, count_{1}
{
    data_.qw = 0;
    data_.w = word;
}

GenericValue::GenericValue(DWORD dword) noexcept
    : type_{Extension::EXT_DWORD}, count_{1}
{
    data_.qw = 0;
    data_.dw = dword;
}

GenericValue::GenericValue(QWORD qword) noexcept
    : type_{Extension::EXT_QWORD}, count_{1}
{
    data_.qw = qword;
}

GenericValue::GenericValue(CHAR chr) noexcept
    : type_{Extension::EXT_CHAR}, count_{1}
{
    data_.qw = 0;
    data_.ch = chr;
}

GenericValue::GenericValue(BYTE_ARRAY bytes)
    : type_{Extension::EXT_BYTE}, count_{bytes.size()}
{
    data_.qw = 0;
    if (count_ == 1)
    {
        data_.b = bytes.at(0);
    }
    else if (count_ > 1)
    {
        data_.pb = new BYTE[count_];
        std::memcpy((void *)data_.pb, (void*)bytes.data(), count_);
    }
}

GenericValue::GenericValue(WORD_ARRAY words)
    : type_{Extension::EXT_WORD}, count_{words.size()}
{
    data_.qw = 0;
    if (count_ == 1)
    {
        data_.w = words.at(0);
    }
    else if (count_ > 1)
    {
        data_.pw = new WORD[count_];
        std::memcpy((void *)data_.pw, (void*)words.data(), count_);
    }
}

GenericValue::GenericValue(DWORD_ARRAY dwords)
    : type_{Extension::EXT_DWORD}, count_{dwords.size()}
{
    data_.qw = 0;
    if (count_ == 1)
    {
        data_.dw = dwords.at(0);
    }
    else if (count_ > 1)
    {
        data_.pdw = new DWORD[count_];
        std::memcpy((void *)data_.pdw, (void*)dwords.data(), count_);
    }
}

GenericValue::GenericValue(QWORD_ARRAY qwords)
    : type_{Extension::EXT_QWORD}, count_{qwords.size()}
{
    if (count_ == 1)
    {
        data_.qw = qwords.at(0);
    }
    else if (count_ > 1)
    {
        data_.pqw = new QWORD[count_];
        std::memcpy((void *)data_.pqw, (void*)qwords.data(), count_);
    }
}

GenericValue::GenericValue(std::string str)
    : GenericValue(str.data(), str.size())
{

}

GenericValue::GenericValue(const char* cstr, std::size_t size)
    : type_{Extension::EXT_CHAR}, count_{0}
{
    data_.qw = 0;
    if (cstr != nullptr && size > 0)
    {
        count_ = (cstr[size - 1] == char(0)) ? size : size + 1;
        data_.psz = new char[count_];
        std::memcpy((void *)data_.psz, (void *)cstr, size * sizeof(char));
        data_.psz[count_ - 1] = char(0);
    }
}

GenericValue::GenericValue(const GenericValue &other)
    : GenericValue(other.type_, other.count_, static_cast<const void*>(other))
{

}

GenericValue::GenericValue(GenericValue &&other) noexcept
    : type_{other.type_},
      count_{other.count_}
{
    data_.qw = other.data_.qw;

    other.count_ = 0;
    other.data_.qw = 0;
}

GenericValue::~GenericValue() noexcept
{
    if (count_ > 1)
    {
        delete[] data_.pb;
    }

    data_.qw = 0;
    count_ = 0;
}

GenericValue &GenericValue::operator=(const GenericValue &other)
{
    if (this == &other)
    {
        return *this;
    }

    GenericValue temp(other.type_, other.count_, static_cast<const void*>(other));
    operator=(std::move(temp));

    return *this;
}

GenericValue &GenericValue::operator=(GenericValue && other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    if (count_ > 1)
    {
        delete[] data_.pb;
    }

    type_ = other.type_;
    count_ = other.count_;
    data_.qw = other.data_.qw;

    other.count_ = 0;
    other.data_.qw = 0;

    return *this;
}

Extension GenericValue::type() const noexcept
{
return type_;
}

std::size_t GenericValue::count() const noexcept
{
return count_;
}

std::size_t GenericValue::size() const noexcept
{
    return count_ * unitSize();
}

std::size_t GenericValue::unitSize() const noexcept
{
    std::size_t unitsz = 0;
    if (type_ == Extension::EXT_BYTE)
    {
        unitsz = sizeof(uint8_t);
    }
    else if(type_ == Extension::EXT_WORD)
    {
        unitsz = sizeof(uint16_t);
    }
    else if(type_ == Extension::EXT_DWORD)
    {
        unitsz = sizeof(uint32_t);
    }
    else if(type_ == Extension::EXT_QWORD)
    {
        unitsz = sizeof(uint64_t);
    }

    return unitsz;
}

bool GenericValue::null() const noexcept
{
    return (count() == 0);
}

bool GenericValue::valid() const noexcept
{
    return (type() != Extension::EXT_NULL);
}

bool GenericValue::string() const noexcept
{
    return type() == Extension::EXT_CHAR && count() > 1;
}

GenericValue::operator const char*() const noexcept
{
    return (string() ? data_.psz : nullptr);
}

GenericValue::operator const void*() const noexcept
{
    const void* p = nullptr;
    if (count_ == 1)
    {
        p = reinterpret_cast<const void*>(&data_.b);
    }
    else
    {
        p = reinterpret_cast<const void*>(data_.pb);
    }
    return p;
}

GenericValue::operator const BYTE&() const noexcept
{
    return (count_ > 1) ? *data_.pb : data_.b;
}

GenericValue::operator bool() const noexcept
{
    return (count_ > 1) ? bool(*data_.pqw) : bool(data_.qw);
}

GenericValue::operator const CHAR &() const noexcept
{
    return (count_ > 1) ? *data_.psz : data_.ch;
}

GenericValue::operator const QWORD &() const noexcept
{
    return (count_ > 1) ? *data_.pqw : data_.qw;
}

GenericValue::operator const DWORD &() const noexcept
{
    return (count_ > 1) ? *data_.pdw : data_.dw;
}

GenericValue::operator const WORD &() const noexcept
{
    return (count_ > 1) ? *data_.pw : data_.w;
}

uint8_t valueTypeSize(Extension e)
{
    return (e == Extension::EXT_CHAR) ? sizeof(char) : sizeof(e);
}
