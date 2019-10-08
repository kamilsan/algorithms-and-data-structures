#pragma once

#include <cstddef>
#include <exception>

template <typename T>
class DynamicArray
{
public:
  DynamicArray();
  DynamicArray(size_t capacity);
  DynamicArray(DynamicArray& other);
  DynamicArray(DynamicArray&& other) noexcept;

  ~DynamicArray();

  const T& get(int index) const;
  bool isEmpty() const;
  size_t size() const;
  size_t capacity() const;

  T get(int index);
  void insert(const T& item);
  void clear();

  DynamicArray& operator=(DynamicArray& other);
  DynamicArray& operator=(DynamicArray&& other) noexcept;
  const T& operator[](size_t index) const;
  T operator[](size_t index);

private:
  size_t size_;
  size_t capacity_;
  T* buffer_;

  void resize();
};

template <typename T>
DynamicArray<T>::DynamicArray(): size_(0), capacity_(4), buffer_(new T[capacity_]) {}

template <typename T>
DynamicArray<T>::DynamicArray(size_t capacity): size_(0), capacity_(capacity), buffer_(new T[capacity]) {}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray& other)
{
  buffer_ = new T[other.capacity_];
  capacity_ = other.capacity_;
  size_ = other.size_;
  for(size_t i = 0; i < size_; ++i)
  {
    buffer_[i] = other.buffer_[i];
  }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
{
  buffer_ = other.buffer_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.buffer_ = nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
  delete[] buffer_;
}

template <typename T>
const T& DynamicArray<T>::get(int index) const
{
  if(index < 0 || index >= size_) throw std::out_of_range("Index out of range!");
  return buffer_[index];
}

template <typename T>
bool DynamicArray<T>::isEmpty() const
{
  return size_ == 0;
}

template <typename T>
size_t DynamicArray<T>::size() const
{
  return size_;
}

template <typename T>
size_t DynamicArray<T>::capacity() const
{
  return capacity_;
}

template <typename T>
T DynamicArray<T>::get(int index)
{
  if(index < 0 || index >= size_) throw std::out_of_range("Index out of range!");
  return buffer_[index];
}

template <typename T>
void DynamicArray<T>::insert(const T& item)
{
  if(size_ == capacity_) resize();
  buffer_[size_] = item;
  size_++;
}

template <typename T>
void DynamicArray<T>::clear()
{
  delete[] buffer_;
  capacity_ = 0;
  size_ = 0;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>& other)
{
  if(this == &other) return *this;
  if(buffer_) delete[] buffer_;
  buffer_ = new T[other.capacity_];
  capacity_ = other.capacity_;
  size_ = other.size_;
  for(size_t i = 0; i < size_; ++i)
  {
    buffer_[i] = other.buffer_[i];
  }
  return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept
{
  if(buffer_) delete[] buffer_;
  buffer_ = other.buffer_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.buffer_ = nullptr;
  return *this;
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const
{
  return buffer_[index];
}

template <typename T>
T DynamicArray<T>::operator[](size_t index)
{
  return buffer_[index];
}

template <typename T>
void DynamicArray<T>::resize()
{
  size_t newCapacity = 2*capacity_;
  T* newBuffer = new T[newCapacity];
  for(size_t i = 0; i < size_; ++i)
  {
    newBuffer[i] = buffer_[i];
  }
  delete[] buffer_;
  buffer_ = newBuffer;
  capacity_ = newCapacity;
}