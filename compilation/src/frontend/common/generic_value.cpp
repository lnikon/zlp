#include "generic_value.h"

GenericValue::GenericValue(Extension ext) noexcept
{

}

GenericValue::GenericValue(Extension ext, std::size_t count, const void *pData)
{

}

GenericValue::GenericValue(BYTE byte)
{

}

GenericValue::GenericValue(WORD word)
{

}

GenericValue::GenericValue(DWORD dword)
{

}

GenericValue::GenericValue(QWORD qword)
{

}

GenericValue::GenericValue(CHAR chr)
{

}

GenericValue::GenericValue(BYTE_ARRAY bytes)
{

}

GenericValue::GenericValue(WORD_ARRAY words)
{

}

GenericValue::GenericValue(DWORD_ARRAY dwords)
{

}

GenericValue::GenericValue(QWORD_ARRAY qwords)
{

}

GenericValue::GenericValue(std::string str)
{

}

GenericValue::GenericValue(std::string arr, std::size_t nSize)
{

}

GenericValue::GenericValue(const GenericValue &o)
{

}

GenericValue::GenericValue(GenericValue &&o) noexcept
{

}

GenericValue::~GenericValue()
{

}

GenericValue &GenericValue::operator=(const GenericValue &)
{

}

GenericValue &GenericValue::operator=(GenericValue &&) noexcept
{

}

Extension GenericValue::type() const noexcept
{

}

std::size_t GenericValue::count() const noexcept
{

}

std::size_t GenericValue::size() const noexcept
{

}

std::size_t GenericValue::unitSize() const noexcept
{

}

bool GenericValue::null() const noexcept
{

}

bool GenericValue::valid() const noexcept
{

}

bool GenericValue::string() const noexcept
{

}

GenericValue::operator bool() const noexcept
{

}

GenericValue::operator const CHAR &() const noexcept
{

}

GenericValue::operator const QWORD &() const noexcept
{

}

GenericValue::operator const DWORD &() const noexcept
{

}

GenericValue::operator const WORD &() const noexcept
{

}

GenericValue::operator const BYTE &() const noexcept
{

}
