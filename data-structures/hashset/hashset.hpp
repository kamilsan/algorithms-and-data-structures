#pragma once

#include <cstddef>
#include <functional>

template <typename T, typename Hash = std::hash<T>>
class Hashset
{
public:
  Hashset(size_t capacity);
  Hashset() : Hashset(7) {}
  Hashset(const Hashset& other);
  Hashset(Hashset&& other) noexcept;

  ~Hashset();

  void insert(const T& item);
  bool remove(const T& item);
  void resize(size_t capacity);

  bool contains(const T& item) const noexcept;
  bool isEmpty() const noexcept;
  size_t size() const noexcept;
  size_t capacity() const noexcept;

  Hashset& operator=(const Hashset& other);
  Hashset& operator=(Hashset&& other);

private:
  struct ChainNode
  {
    T value;
    ChainNode* next;
  };

  bool insert(const T& item, ChainNode** chains, size_t capacity);
  void adjustLoadFactor();

  ChainNode** chains_;
  size_t size_;
  size_t capacity_;
  float loadFactor_;

  static constexpr float MAX_LOAD_FACTOR = 1.25;
};

template <typename T, typename Hash>
Hashset<T, Hash>::Hashset(size_t capacity): size_(0), capacity_(capacity), loadFactor_(0)
{
  chains_ = new ChainNode*[capacity];
  for(size_t i = 0; i < capacity; ++i)
    chains_[i] = nullptr;
}

template <typename T, typename Hash>
Hashset<T, Hash>::Hashset(const Hashset& other)
{
  size_ = other.size_;
  capacity_ = other.capacity_;
  loadFactor_ = other.loadFactor_;
  chains_ = new ChainNode*[capacity_];
  for(size_t i = 0; i < capacity_; ++i)
  {
    ChainNode* otherCur = other.chains_[i];
    ChainNode* prev = nullptr;
    chains_[i] = nullptr;
    while(otherCur)
    {
      ChainNode* newNode = new ChainNode;
      newNode->value = otherCur->value;
      newNode->next = nullptr;
      if(prev)
        prev->next = newNode;
      else
        chains_[i] = newNode;

      otherCur = otherCur->next;
      prev = newNode; 
    }
  }
}

template <typename T, typename Hash>
Hashset<T, Hash>::Hashset(Hashset&& other) noexcept
{
  chains_ = other.chains_;
  size_ = other.size_;
  loadFactor_ = other.loadFactor_;
  capacity_ = other.capacity_;

  other.chains_ = nullptr;
  other.size_ = other.capacity_ = other.loadFactor_ = 0;
}

template <typename T, typename Hash>
Hashset<T, Hash>::~Hashset()
{
  for(size_t i = 0; i < capacity_; ++i)
  {
    ChainNode* node = chains_[i];
    while(node)
    {
      ChainNode* r = node;
      node = node->next;
      delete r;
    }
  }
  delete[] chains_;
}

template <typename T, typename Hash>
void Hashset<T, Hash>::insert(const T& item)
{
  bool inserted = insert(item, chains_, capacity_);
  if(inserted)
  {
    size_ += 1;

    loadFactor_ = static_cast<float>(size_) / capacity_;
    if(loadFactor_ > MAX_LOAD_FACTOR)
      resize(2.0f*capacity_);
  }
}

template <typename T, typename Hash>
bool Hashset<T, Hash>::remove(const T& item)
{
  size_t idx = Hash{}(item) % capacity_;
  ChainNode* node = chains_[idx];
  ChainNode* prev = nullptr;
  while(node)
  {
    if(node->value == item)
    {
      if(prev)
        prev->next = node->next;
      else
        chains_[idx] = node->next;

      delete node;

      size_ -= 1;
      loadFactor_ = static_cast<float>(size_) / capacity_;

      return true;
    }
    prev = node;
    node = node->next;
  }
  return false;
}

template <typename T, typename Hash>
void Hashset<T, Hash>::resize(size_t capacity)
{
  if(capacity <= capacity_) return;

  ChainNode** newChains = new ChainNode*[capacity];
  for(size_t i = 0; i < capacity; ++i)
  {
    newChains[i] = nullptr;
  }

  for(size_t i = 0; i < capacity_; ++i)
  {
    ChainNode* node = chains_[i];
    while(node)
    {
      insert(node->value, newChains, capacity);
      node = node->next;
    }
  }

  for(size_t i = 0; i < capacity_; ++i)
  {
    ChainNode* node = chains_[i];
    while(node)
    {
      ChainNode* r = node;
      node = node->next;
      delete r;
    }
  }
  delete[] chains_;

  chains_ = newChains;
  capacity_ = capacity;
  loadFactor_ = static_cast<float>(size_) / capacity_;
}

template <typename T, typename Hash>
bool Hashset<T, Hash>::contains(const T& item) const noexcept
{
  size_t idx = Hash{}(item) % capacity_;
  ChainNode* node = chains_[idx];
  while(node)
  {
    if(node->value == item)
      return true;
    node = node->next;
  }
  return false;
}

template <typename T, typename Hash>
bool Hashset<T, Hash>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <typename T, typename Hash>
size_t Hashset<T, Hash>::size() const noexcept
{
  return size_;
}

template <typename T, typename Hash>
size_t Hashset<T, Hash>::capacity() const noexcept
{
  return capacity_;
}

template <typename T, typename Hash>
Hashset<T, Hash>& Hashset<T, Hash>::operator=(const Hashset& other)
{
  if(this == &other) return *this;

  size_ = other.size_;
  capacity_ = other.capacity_;
  loadFactor_ = other.loadFactor_;
  chains_ = new ChainNode*[capacity_];
  for(size_t i = 0; i < capacity_; ++i)
  {
    ChainNode* otherCur = other.chains_[i];
    ChainNode* prev = nullptr;
    chains_[i] = nullptr;
    while(otherCur)
    {
      ChainNode* newNode = new ChainNode;
      newNode->value = otherCur->value;
      newNode->next = nullptr;
      if(prev)
        prev->next = newNode;
      else
        chains_[i] = newNode;

      otherCur = otherCur->next;
      prev = newNode; 
    }
  }

  return *this;
}

template <typename T, typename Hash>
Hashset<T, Hash>& Hashset<T, Hash>::operator=(Hashset&& other)
{
  chains_ = other.chains_;
  size_ = other.size_;
  loadFactor_ = other.loadFactor_;
  capacity_ = other.capacity_;

  other.chains_ = nullptr;
  other.size_ = other.capacity_ = other.loadFactor_ = 0;

  return *this;
}

template <typename T, typename Hash>
bool Hashset<T, Hash>::insert(const T& item, ChainNode** chains, size_t capacity)
{
  size_t idx = Hash{}(item) % capacity;
  ChainNode* node = chains[idx];
  ChainNode* prev = nullptr;
  while(node)
  {
    if(node->value == item) 
      return false;
    prev = node;
    node = node->next;
  }
  ChainNode* newNode = new ChainNode;
  newNode->value = item;
  newNode->next = nullptr;
  if(prev)
    prev->next = newNode;
  else
    chains[idx] = newNode;

  return true;
}
