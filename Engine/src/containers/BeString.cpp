#include "BeString.h"

#include "core/BeAssert.h"

#include <cstring>

namespace BE {
String::String() : m_Data(nullptr), m_Size(0) {}

String::~String() {
  delete[] m_Data;
  m_Data = nullptr;
}

String::String(const String& other) {
  m_Size = other.m_Size;
  m_Data = new char[m_Size + 1];
  memcpy(m_Data, other.m_Data, m_Size + 1);
}

String::String(String&& other) noexcept {
  m_Size       = other.m_Size;
  m_Data       = other.m_Data;
  other.m_Size = 0;
  other.m_Data = nullptr;
}

String String::operator=(const String& other) {
  if (this != &other) {
    delete[] m_Data;
    m_Size = other.m_Size;
    m_Data = new char[m_Size + 1];
    memcpy(m_Data, other.m_Data, m_Size + 1);
  }
  return *this;
}

String String::operator=(String&& other) noexcept {
  if (this != &other) {
    delete[] m_Data;
    m_Size       = other.m_Size;
    m_Data       = other.m_Data;
    other.m_Size = 0;
    other.m_Data = nullptr;
  }
  return *this;
}

String::String(const char* str) {
  m_Size = strlen(str);
  m_Data = new char[m_Size + 1];
  memcpy(m_Data, str, m_Size + 1);
}

String::String(const char* str, be_size size) {
  m_Size = size;
  m_Data = new char[m_Size + 1];
  memcpy(m_Data, str, m_Size);
  m_Data[m_Size] = '\0';
}

String::String(const char* begin, const char* end) {
  m_Size = end - begin;
  m_Data = new char[m_Size + 1];
  memcpy(m_Data, begin, m_Size);
  m_Data[m_Size] = '\0';
}

String String::operator+(const String& other) const {
  String result;
  result.m_Size = m_Size + other.m_Size;
  result.m_Data = new char[result.m_Size + 1];
  memcpy(result.m_Data, m_Data, m_Size);
  memcpy(result.m_Data + m_Size, other.m_Data, other.m_Size + 1);
  return result;
}

String String::operator+(const char* str) const {
  String result;
  be_size size  = strlen(str);
  result.m_Size = m_Size + size;
  result.m_Data = new char[result.m_Size + 1];
  memcpy(result.m_Data, m_Data, m_Size);
  memcpy(result.m_Data + m_Size, str, size + 1);
  return result;
}

String String::operator+(char c) const {
  String result;
  result.m_Size = m_Size + 1;
  result.m_Data = new char[result.m_Size + 1];
  memcpy(result.m_Data, m_Data, m_Size);
  result.m_Data[m_Size]        = c;
  result.m_Data[result.m_Size] = '\0';
  return result;
}

String& String::operator+=(const String& other) {
  be_size size = m_Size + other.m_Size;
  char* data   = new char[size + 1];
  memcpy(data, m_Data, m_Size);
  memcpy(data + m_Size, other.m_Data, other.m_Size + 1);
  delete[] m_Data;
  m_Data = data;
  m_Size = size;
  return *this;
}

String& String::operator+=(const char* str) {
  be_size size = m_Size + strlen(str);
  char* data   = new char[size + 1];
  memcpy(data, m_Data, m_Size);
  memcpy(data + m_Size, str, size + 1);
  delete[] m_Data;
  m_Data = data;
  m_Size = size;
  return *this;
}

String& String::operator+=(const char c) {
  char* data = new char[m_Size + 2];
  memcpy(data, m_Data, m_Size);
  data[m_Size]     = c;
  data[m_Size + 1] = '\0';
  delete[] m_Data;
  m_Data = data;
  m_Size++;
  return *this;
}

bool String::operator==(const String& other) const {
  if (m_Size != other.m_Size) {
    return false;
  }
  return memcmp(m_Data, other.m_Data, m_Size) == 0;
}

bool String::operator==(const char* str) const {
  be_size size = strlen(str);
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
  BE_ASSERT(index < m_Size);
  return m_Data[index];
}

const char& String::operator[](be_size index) const {
  BE_ASSERT(index < m_Size);
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

} // namespace BE
