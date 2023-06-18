#pragma once

#include "core/Defines.h"

namespace BE {
class StringView;

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
  String(be_size size);

  String operator+(const String& other) const;
  String operator+(const char* str) const;
  String operator+(char c) const;
  String& operator+=(const String& other);
  String& operator+=(const char* str);
  String& operator+=(char c);
  String& operator+=(const StringView& strView);

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

  be_size Find(be_size pos, char c) const;
  String SubString(be_size pos, be_size size) const;

  void Reserve(be_size size);
  void Resize(be_size size);

  static constexpr be_size NPos = -1;

private:
  c8* m_Data;

  /// Accupied size of the string. (null terminator is not included)
  be_size m_Size;

  /// Allocated size of the string. (null terminator is not included)
  be_size m_Capacity;
};

} // namespace BE
