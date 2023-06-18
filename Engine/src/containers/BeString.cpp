#include "BeString.h"

#include "core/BeAssert.h"
#include "StringView.h"
#include "utils/StringUtils.h"

#include <cstring>

namespace BE {
String::String() : m_Data(nullptr), m_Size(0), m_Capacity(0) {}

String::~String() {
  delete[] m_Data;
  m_Data = nullptr;
}

String::String(const String& other) {
  m_Size     = other.m_Size;
  m_Capacity = other.m_Capacity;
  m_Data     = new char[m_Size + 1];
  memcpy(m_Data, other.m_Data, m_Size + 1);
}

String::String(String&& other) noexcept {
  m_Size           = other.m_Size;
  m_Capacity       = other.m_Capacity;
  m_Data           = other.m_Data;
  other.m_Size     = 0;
  other.m_Capacity = 0;
  other.m_Data     = nullptr;
}

String String::operator=(const String& other) {
  if (this != &other) {
    delete[] m_Data;
    m_Size     = other.m_Size;
    m_Capacity = other.m_Capacity;
    m_Data     = new char[m_Size + 1];
    memcpy(m_Data, other.m_Data, m_Size + 1);
  }
  return *this;
}

String String::operator=(String&& other) noexcept {
  if (this != &other) {
    delete[] m_Data;
    m_Size           = other.m_Size;
    m_Capacity       = other.m_Capacity;
    m_Data           = other.m_Data;
    other.m_Size     = 0;
    other.m_Capacity = 0;
    other.m_Data     = nullptr;
  }
  return *this;
}

String::String(const char* str) {
  m_Size     = strlen(str);
  m_Capacity = m_Size;
  m_Data     = new char[m_Size + 1];
  memcpy(m_Data, str, m_Size + 1);
}

String::String(const char* str, be_size size) {
  m_Size     = size;
  m_Capacity = size;
  m_Data     = new char[m_Size + 1];
  memcpy(m_Data, str, m_Size);
  m_Data[m_Size] = '\0';
}

String::String(const char* begin, const char* end) {
  m_Size     = end - begin;
  m_Capacity = m_Size;
  m_Data     = new char[m_Size + 1];
  memcpy(m_Data, begin, m_Size);
  m_Data[m_Size] = '\0';
}

String::String(be_size size) : m_Size(0), m_Capacity(size) {
  m_Data = new char[m_Capacity + 1];
  memset(m_Data, 0, m_Capacity + 1);
}

String String::operator+(const String& other) const {
  be_size capacity = m_Size + other.m_Size;
  String result(capacity);
  memcpy(result.m_Data, m_Data, m_Size);
  memcpy(result.m_Data + m_Size, other.m_Data, other.m_Size + 1);
  return result;
}

String String::operator+(const char* str) const {
  be_size size = StrLen(str);
  String result(m_Size + size);
  memcpy(result.m_Data, m_Data, m_Size);
  memcpy(result.m_Data + m_Size, str, size + 1);
  return result;
}

String String::operator+(char c) const {
  String result(m_Size + 1);
  memcpy(result.m_Data, m_Data, m_Size);
  result.m_Data[m_Size]        = c;
  result.m_Data[result.m_Size] = '\0';
  return result;
}

String& String::operator+=(const String& other) {
  if (m_Capacity < m_Size + other.m_Size) {
    m_Capacity = m_Size + other.m_Size;
    char* data = new char[m_Capacity + 1];
    memcpy(data, m_Data, m_Size);
    memcpy(data + m_Size, other.m_Data, other.m_Size + 1);
    delete[] m_Data;
    m_Size = m_Capacity;
    m_Data = data;
  } else {
    memcpy(m_Data + m_Size, other.m_Data, other.m_Size + 1);
    m_Size += other.m_Size;
  }
  return *this;
}

String& String::operator+=(const char* str) {
  be_size size = StrLen(str);
  if (m_Capacity < m_Size + size) {
    m_Capacity = m_Size + size;
    m_Size     = m_Capacity;
    char* data = new char[m_Capacity + 1];
    memcpy(data, m_Data, m_Size);
    memcpy(data + m_Size, str, size + 1);
    m_Data[m_Size] = '\0';
    delete[] m_Data;
    m_Data = data;
  } else {
    memcpy(m_Data + m_Size, str, size + 1);
    m_Size += size;
  }
  return *this;
}

String& String::operator+=(const char c) {
  if (m_Capacity < m_Size + 1) {
    char* data = new char[m_Size + 2];
    memcpy(data, m_Data, m_Size);
    data[m_Size]     = c;
    data[m_Size + 1] = '\0';
    delete[] m_Data;
    m_Data = data;
    m_Size++;
    m_Capacity = m_Size;
  } else {
    m_Data[m_Size]     = c;
    m_Data[m_Size + 1] = '\0';
    m_Size++;
  }
  return *this;
}

String& String::operator+=(const StringView& str) {
  if (m_Capacity < m_Size + str.Size()) {
    be_size size = m_Size + str.Size();
    char* data   = new char[size + 1];
    memcpy(data, m_Data, m_Size);
    memcpy(data + m_Size, str.Data(), str.Size());
    delete[] m_Data;
    m_Data     = data;
    m_Size     = size;
    m_Capacity = size;
  } else {
    memcpy(m_Data + m_Size, str.Data(), str.Size());
    m_Size         += str.Size();
    m_Data[m_Size]  = '\0';
  }
  return *this;
}

bool String::operator==(const String& other) const {
  if (m_Size != other.m_Size) {
    return false;
  }
  return memcmp(m_Data, other.m_Data, m_Size) == 0;
}

bool String::operator==(const char* str) const {
  be_size size = StrLen(str);
  if (m_Size != size) {
    return false;
  }
  return memcmp(m_Data, str, m_Size) == 0;
}

bool String::operator!=(const String& other) const {
  return !(*this == other);
}

bool String::operator!=(const char* str) const {
  return !(*this == str);
}

char& String::operator[](be_size index) {
  BE_ASSERT(index < m_Capacity);
  return m_Data[index];
}

const char& String::operator[](be_size index) const {
  BE_ASSERT(index < m_Capacity);
  return m_Data[index];
}

char& String::Front() {
  BE_ASSERT(m_Size > 0);
  return m_Data[0];
}

const char& String::Front() const {
  BE_ASSERT(m_Size > 0);
  return m_Data[0];
}

char& String::Back() {
  BE_ASSERT(m_Size > 0);
  return m_Data[m_Size - 1];
}

const char& String::Back() const {
  BE_ASSERT(m_Size > 0);
  return m_Data[m_Size - 1];
}

const char* String::Data() const {
  return m_Data;
}

be_size String::Size() const {
  return m_Size;
}

bool String::Empty() const {
  return m_Size == 0;
}

be_size String::Find(be_size pos, char c) const {
  for (be_size i = pos; i < m_Size; i++) {
    if (m_Data[i] == c) {
      return i;
    }
  }
  return NPos;
}

String String::SubString(be_size pos, be_size count) const {
  BE_ASSERT(pos < m_Size);
  BE_ASSERT(pos + count <= m_Size);

  return String(m_Data + pos, count);
}

void String::Resize(be_size size) {
  BE_ASSERT(size > 0);
  if (m_Capacity < size) {
    m_Capacity = size;
    char* data = new char[m_Capacity + 1];
    memset(data, 0, m_Capacity + 1);
    memcpy(data, m_Data, m_Size);
    delete[] m_Data;
    m_Size = size;
    m_Data = data;
  }
  m_Size = size;
}

void String::Reserve(be_size size) {
  BE_ASSERT(size >= m_Capacity);
  if (m_Capacity < size) {
    m_Capacity = size;
    char* data = new char[m_Capacity + 1];
    memset(data, 0, m_Capacity + 1);
    memcpy(data, m_Data, m_Size);
    delete[] m_Data;
    m_Data = data;
  }
}

} // namespace BE
