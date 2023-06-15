#pragma once

#include "core/BeAssert.h"
#include "core/Defines.h"
#include "platform/Platform.h"

namespace BE {
template<typename T>
class DynamicArray {
  static constexpr be_size c_DefaultCapacity = 8;
  static constexpr be_size c_GrowthFactor    = 2;

public:
  DynamicArray() :
      m_Data{(T*)PlatformAlloc(sizeof(T) * c_DefaultCapacity)},
      m_Size(0),
      m_Capacity{c_DefaultCapacity} {}

  DynamicArray(be_size capacity) :
      m_Data{(T*)PlatformAlloc(sizeof(T) * capacity)},
      m_Size(0),
      m_Capacity{capacity} {}

  ~DynamicArray() {
    for (be_size i = 0; i < m_Size; ++i) {
      m_Data[i].~T();
    }

    PlatformFree(m_Data);
  }

  void Resize(be_size newCapacity) {
    BE_ASSERT(newCapacity > m_Capacity);
    T* newData = (T*)PlatformAlloc(sizeof(T) * newCapacity);
    memcpy(newData, m_Data, sizeof(T) * m_Size);
    PlatformFree(m_Data);
    m_Data = newData;
  }

  void PushBack(const T& value) {
    if (m_Size == m_Capacity) {
      Resize(m_Capacity * c_GrowthFactor);
    }

    m_Data[m_Size++] = value;
  }

  void PushFront(const T& value) {
    if (m_Size == m_Capacity) {
      Resize(m_Capacity * c_GrowthFactor);
    }

    memmove(m_Data + 1, m_Data, sizeof(T) * m_Size);
    m_Data[0] = value;
    ++m_Size;
  }

  void PushAt(be_size index, const T& value) {
    BE_ASSERT(index < m_Size);
    if (index == m_Size) {
      PushBack(value);
      return;
    }

    if (m_Size == m_Capacity) {
      Resize(m_Capacity * c_GrowthFactor);
    }

    memmove(m_Data + index + 1, m_Data + index, sizeof(T) * (m_Size - index));
    m_Data[index] = value;
    ++m_Size;
  }

  T PopBack() {
    BE_ASSERT(m_Size > 0);
    return m_Data[--m_Size];
  }

  T PopFront() {
    BE_ASSERT(m_Size > 0);
    T value = m_Data[0];
    memmove(m_Data, m_Data + 1, sizeof(T) * (m_Size - 1));
    --m_Size;
    return value;
  }

  T PopAt(be_size index) {
    BE_ASSERT(index < m_Size);
    if (index == m_Size - 1) {
      return PopBack();
    }

    T value = m_Data[index];
    memmove(m_Data + index, m_Data + index + 1, sizeof(T) * (m_Size - index - 1));
    --m_Size;
    return value;
  }

  void RemoveBack() {
    BE_ASSERT(m_Size > 0);
    --m_Size;
  }

  void RemoveFront() {
    BE_ASSERT(m_Size > 0);
    memmove(m_Data, m_Data + 1, sizeof(T) * (m_Size - 1));
    --m_Size;
  }

  void RemoveAt(be_size index) {
    BE_ASSERT(index < m_Size);
    if (index == m_Size - 1) {
      RemoveBack();
      return;
    }

    memmove(m_Data + index, m_Data + index + 1, sizeof(T) * (m_Size - index - 1));
    --m_Size;
  }

  T& operator[](be_size index) {
    BE_ASSERT(index < m_Size);
    return m_Data[index];
  }

  const T& operator[](be_size index) const {
    BE_ASSERT(index < m_Size);
    return m_Data[index];
  }

  T* Data() { return m_Data; }

  const T* Data() const { return m_Data; }

  be_size Size() const { return m_Size; }

  be_size Capacity() const { return m_Capacity; }

private:
  T* m_Data;
  be_size m_Size;
  be_size m_Capacity;
};

} // namespace BE
