#pragma once

#include <cstddef>
#include <functional>

template <typename T>
class LinkedList
{
public:
  LinkedList();
  LinkedList(const LinkedList& other);
  LinkedList(LinkedList&& other) noexcept;

  ~LinkedList();

  void add_front(const T& item);
  bool remove(const T& item);
  T remove_front();
  void for_each(std::function<void(const T&)> func) const;

  size_t size() const;
  const T& get_front() const;
  bool contains(T item) const;

  LinkedList& operator=(const LinkedList& other);
  LinkedList& operator=(LinkedList&& other) noexcept;
private:
  struct Node
  {
    T value;
    Node* next;
  };
  Node* head_;
  size_t size_;
};

template <typename T>
LinkedList<T>::LinkedList(): head_(nullptr), size_(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
  size_ = other.size;
  if(other.size == 0) return;
  head_ = new Node;
  head_->value = other.head_->value;

  Node* cur = head_;
  Node* curOther = other->head_->next;
  while(curOther)
  {
    Node* newNode = new Node;
    newNode = curOther->value;
    cur->next = newNode;

    cur = newNode;
    curOther = curOther->next;
  }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
{
  head_ = other.head_;
  size_ = other.size;
  other.head_ = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  Node* cur = head_;
  while(cur)
  {
    Node* r = cur;
    cur = cur->next;
    delete r;
  }
}

template <typename T>
void LinkedList<T>::add_front(const T& item)
{
  Node* newNode = new Node;
  newNode->value = item;
  newNode->next = head_;
  head_ = newNode;
}

template <typename T>
bool LinkedList<T>::remove(const T& item)
{
  Node* prev = nullptr;
  Node* cur = head_;
  while(cur)
  {
    if(cur->value == item)
    {
      Node* r = cur;
      if(prev)
        prev->next = r->next;
      else
      {
        head_ = r->next;
      }
      delete r;

      return true;
    }

    prev = cur;
    cur = cur->next;
  }

  return false;
}

template <typename T>
T LinkedList<T>::remove_front()
{
  T val = head_->value;

  Node* r = head_;
  head_ = head_->next;
  size_--;
  delete r;

  return val;
}

template <typename T>
void LinkedList<T>::for_each(std::function<void(const T&)> func) const
{
  Node* cur = head_;
  while(cur)
  {
    func(cur->value);
    cur = cur->next;
  }
}

template <typename T>
size_t LinkedList<T>::size() const
{
  return size_;
}

template <typename T>
const T& LinkedList<T>::get_front() const
{
  return head_->value;
}

template <typename T>
bool LinkedList<T>::contains(T item) const
{
  Node* cur = head_;
  while(cur)
  {
    if(cur->value == item)
      return true;

    cur = cur->next;
  }

  return false;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
  if(*other == this) return *this;

  Node* cur = head_;
  while(cur)
  {
    Node* r = cur;
    cur = cur->next;
    delete r;
  }

  size_ = other.size;
  if(other.size == 0) return *this;
  head_ = new Node;
  head_->value = other.head_->value;

  cur = head_;
  Node* curOther = other->head_->next;
  while(curOther)
  {
    Node* newNode = new Node;
    newNode = curOther->value;
    cur->next = newNode;
    
    cur = newNode;
    curOther = curOther->next;
  }

  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept
{
  head_ = other.head_;
  size_ = other.size;
  other.head_ = nullptr;

  return *this;
}
