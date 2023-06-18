#pragma once

#include "containers/BeString.h"
#include "core/Defines.h"

namespace BE {

class StringView {
public:
  StringView();
  StringView(const String& str);
  StringView(const char* str);
  StringView(const char* str, be_size size);

  const char* Data() const;
  be_size Size() const;
  bool Empty() const;

  be_size Find(be_size pos, char c) const;
  StringView SubString(be_size pos = 0, be_size size = NPos) const;

  static constexpr be_size NPos = String::NPos;

private:
  const char* m_Data;
  be_size m_Size;
};

} // namespace BE
