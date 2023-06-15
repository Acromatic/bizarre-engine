#pragma once

#include "core/Defines.h"

namespace BE {
class String {
public:
  String();
  ~String();

  String(const String& other);
  String(String&& other) noexcept;
  String operator=(const String& other);
  String operator=(String&& other) noexcept;

  String(const char* str);
  String(const char* str, be_size size);
  String(const char* begin, const char* end);

  String operator+(const String& other) const;
  String operator+(const char* str) const;
  String operator+(char c) const;
  String& operator+=(const String& other);
  String& operator+=(const char* str);
  String& operator+=(char c);

  bool operator==(const String& other) const;
  bool operator==(const char* str) const;
  bool operator!=(const String& other) const;
  bool operator!=(const char* str) const;

  char& operator[](be_size index);
  const char& operator[](be_size index) const;

  char& Front();
  const char& Front() const;

  char& Back();
  const char& Back() const;

  const char* Data() const;
  be_size Size() const;
  bool Empty() const;

private:
  c8* m_Data;
  be_size m_Size;
};

} // namespace BE
