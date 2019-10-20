#pragma once

#include <cstddef>
#include <functional>
#include <exception>

template <typename T, typename C = std::less<T>>
class Heap
{
public:
  Heap(size_t capacity);
  Heap(): Heap(4) {}
  Heap(const Heap& other);
  Heap(Heap&& other) noexcept;

  ~Heap();

  T peek() const noexcept;
  const T& get(size_t index) const;
  bool contains(const T& item) const noexcept;
  bool isEmpty() const noexcept;
  size_t size() const noexcept;
  size_t capacity() const noexcept;

  T pop();
  T get(size_t index);
  bool removeMinMax();
  void insert(const T& item);
  bool remove(const T& item);

  Heap& operator=(const Heap& other);
  Heap& operator=(Heap&& other) noexcept;
  const T& operator[](size_t index) const;
  T operator[](size_t index);

private:
  T* buffer_;
  size_t size_;
  size_t capacity_;

  void resize();

  size_t parent(size_t idx) const noexcept;
  size_t leftChild(size_t idx) const noexcept;
  size_t rightChild(size_t idx) const noexcept;

  void bubbleUp(size_t idx);
  void bubbleDown(size_t idx);
};

template <typename T, typename C>
Heap<T, C>::Heap(size_t capacity)
{
  capacity_ = capacity;
  buffer_ = new T[capacity_];
  size_ = 0;
}

template <typename T, typename C>
Heap<T, C>::Heap(const Heap& other)
{
  capacity_ = other.capacity_;
  size_ = other.size_;
  buffer_ = new T[capacity_];
  for(size_t i = 0; i < size_; ++i)
  {
    buffer_[i] = other.buffer_[i];
  }
}

template <typename T, typename C>
Heap<T, C>::Heap(Heap&& other) noexcept
{
  buffer_ = other.buffer_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.buffer_ = nullptr;
}

template <typename T, typename C>
Heap<T, C>::~Heap()
{
  delete[] buffer_;
}

template <typename T, typename C>
T Heap<T, C>::peek() const noexcept
{
  return buffer_[0];
}

template <typename T, typename C>
const T& Heap<T, C>::get(size_t index) const
{
  if(index < 0 || index >= size_) throw std::out_of_range("Index out of range!");
  return buffer_[index];
}

template <typename T, typename C>
bool Heap<T, C>::contains(const T& item) const noexcept
{
  for(size_t i = 0; i < size_; ++i)
  {
    if(buffer_[i] == item) return true;
  }
  return false;
}

template <typename T, typename C>
bool Heap<T, C>::isEmpty() const noexcept 
{
  return size_ == 0;
}

template <typename T, typename C>
size_t Heap<T, C>::size() const noexcept
{
  return size_;
}

template <typename T, typename C>
size_t Heap<T, C>::capacity() const noexcept
{
  return capacity_;
}

template <typename T, typename C>
T Heap<T, C>::pop()
{
  T val = buffer_[0];
  removeMinMax();
  return val;
}

template <typename T, typename C>
T Heap<T, C>::get(size_t index)
{
  if(index < 0 || index >= size_) throw std::out_of_range("Index out of range!");
  return buffer_[index];
}

template <typename T, typename C>
bool Heap<T, C>::removeMinMax()
{
  if(size_ == 0) return false;
  buffer_[0] = buffer_[size_ - 1];
  size_--;
  bubbleDown(0);
  return true;
}

template <typename T, typename C>
void Heap<T, C>::insert(const T& item)
{
  if(size_ == capacity_) resize();
  buffer_[size_] = item;
  bubbleUp(size_);
  size_++;
}

template <typename T, typename C>
bool Heap<T, C>::remove(const T& item)
{
  for(size_t i = 0; i < size_; ++i)
  {
    if(buffer_[i] == item)
    {
      buffer_[i] = buffer_[size_ - 1];
      size_--;
      bubbleUp(i);
      bubbleDown(i);
      return true;
    }
  }
  return false;
}

template <typename T, typename C>
Heap<T, C>& Heap<T, C>::operator=(const Heap& other)
{
  if(this == &other) return *this;

  if(buffer_) delete[] buffer_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  buffer_ = new T[capacity_];
  for(size_t i = 0; i < size_; ++i)
  {
    buffer_[i] = other.buffer_[i];
  }

  return *this;
}

template <typename T, typename C>
Heap<T, C>& Heap<T, C>::operator=(Heap&& other) noexcept
{
  buffer_ = other.buffer_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.buffer_ = nullptr;
  return *this;
}

template <typename T, typename C>
const T& Heap<T, C>::operator[](size_t index) const
{
  return buffer_[index];
}

template <typename T, typename C>
T Heap<T, C>::operator[](size_t index)
{
  return buffer_[index];
}


template <typename T, typename C>
void Heap<T, C>::resize()
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

template <typename T, typename C>
inline size_t Heap<T, C>::parent(size_t idx) const noexcept
{
  return (idx - 1) / 2; 
}

template <typename T, typename C>
inline size_t Heap<T, C>::leftChild(size_t idx) const noexcept
{
  return 2*idx + 1;
}

template <typename T, typename C>
inline size_t Heap<T, C>::rightChild(size_t idx) const noexcept
{
  return 2*idx + 2;
}

template <typename T, typename C>
void Heap<T, C>::bubbleUp(size_t idx)
{
  size_t curIdx = idx;
  size_t parentIdx = parent(curIdx);
  while(parentIdx >= 0)
  {
    if(C()(buffer_[curIdx], buffer_[parentIdx]))
    {
      std::swap(buffer_[curIdx], buffer_[parentIdx]);
      curIdx = parentIdx;
      parentIdx = parent(curIdx);
    }
    else break;
  }
}

template <typename T, typename C>
void Heap<T, C>::bubbleDown(size_t idx)
{
  size_t curIdx = idx;
  size_t leftChildIdx = leftChild(curIdx);
  size_t rightChildIdx = rightChild(curIdx);
  while(leftChildIdx < size_)
  {
    size_t nextIdx = leftChildIdx;
    if(rightChildIdx < size_ && C()(buffer_[rightChildIdx], buffer_[nextIdx]))
      nextIdx = rightChildIdx;
    
    if(C()(buffer_[nextIdx], buffer_[curIdx]))
    {
      std::swap(buffer_[nextIdx], buffer_[curIdx]);
      curIdx = nextIdx;
      leftChildIdx = leftChild(curIdx);
      rightChildIdx = rightChild(curIdx);
    }
    else break;
  }
}
