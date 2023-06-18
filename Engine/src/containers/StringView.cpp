#include "StringView.h"

#include "core/BeAssert.h"
#include "utils/StringUtils.h"

namespace BE {
StringView::StringView() : m_Data(nullptr), m_Size(0) {}

StringView::StringView(const String& str) : m_Data(str.Data()), m_Size(str.Size()) {}

StringView::StringView(const char* str) : m_Data(str), m_Size(StrLen(str)) {}

StringView::StringView(const char* str, be_size size) : m_Data(str), m_Size(size) {}

const char* StringView::Data() const {
  return m_Data;
}

be_size StringView::Size() const {
  return m_Size;
}

bool StringView::Empty() const {
  return m_Size == 0;
}

be_size StringView::Find(be_size pos, char c) const {
  BE_ASSERT(pos < m_Size);
  for (be_size i = pos; i < m_Size; ++i) {
    if (m_Data[i] == c) {
      return i;
    }
  }
  return NPos;
}

StringView StringView::SubString(be_size pos, be_size size) const {
  BE_ASSERT(pos < m_Size);
  if (size == NPos) {
    size = m_Size - pos;
  }
  return StringView(m_Data + pos, size);
}

} // namespace BE
