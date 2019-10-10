#pragma once

#include <cstddef>
#include <functional>

template <typename T>
class DoublyLinkedList
{
public:
  DoublyLinkedList();
  DoublyLinkedList(const DoublyLinkedList& other);
  DoublyLinkedList(DoublyLinkedList&& other) noexcept;

  ~DoublyLinkedList();

  void add_front(const T& item);
  void add_back(const T& item);
  T remove_front();
  T remove_back();
  bool remove(const T& item);
  void for_each(std::function<void(const T&)> func) const noexcept;

  size_t size() const noexcept;
  bool isEmpty() const noexcept;
  const T& get_front() const noexcept;
  const T& get_back() const noexcept;
  bool contains(T item) const noexcept;

  DoublyLinkedList& operator=(const DoublyLinkedList& other);
  DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;
private:
  struct Node
  {
    T value;
    Node* next;
    Node* prev;
  };
  Node* head_;
  Node* tail_;
  size_t size_;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(): head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
{
  size_ = other.size_;
  if(other.size_ == 0) return;
  head_ = tail_ = new Node;
  head_->value = other.head_->value;
  head_->next = head_->prev = nullptr;

  Node* cur = head_;
  Node* curOther = other.head_->next;
  while(curOther)
  {
    Node* newNode = new Node;
    newNode->value = curOther->value;
    cur->next = newNode;
    newNode->prev = cur;

    cur = newNode;
    curOther = curOther->next;
    tail_ = newNode;
  }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
{
  size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
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
void DoublyLinkedList<T>::add_front(const T& item)
{
  Node* newNode = new Node;
  newNode->value = item;
  newNode->next = head_;
  newNode->prev = nullptr;
  if(head_)
  {
    head_->prev = newNode;
  }
  else 
  {
    // If there is no head, then there is no tail
    tail_ = newNode;
  }
  head_ = newNode;
  size_++;
}

template <typename T>
void DoublyLinkedList<T>::add_back(const T& item)
{
  Node* newNode = new Node;
  newNode->value = item;
  newNode->next = nullptr;
  newNode->prev = tail_;
  if(tail_)
  {
    tail_->next = newNode;
  }
  else
  {
    // If there is no tail, then there is no head
    head_ = newNode;
  }
  tail_ = newNode;
  size_++;
}

template <typename T>
bool DoublyLinkedList<T>::remove(const T& item)
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
        head_ = r->next;

      if(r->next)
        r->next->prev = prev;
      else
        tail_ = prev;

      delete r;
      size_--;

      return true;
    }

    prev = cur;
    cur = cur->next;
  }

  return false;
}

template <typename T>
T DoublyLinkedList<T>::remove_front()
{
  T val = head_->value;

  Node* r = head_;
  head_ = head_->next;
  if(head_)
  {
    head_->prev = nullptr;
  }
  else
  {
    tail_ = nullptr;
  }
  size_--;
  delete r;

  return val;
}

template <typename T>
T DoublyLinkedList<T>::remove_back()
{
  T val = tail_->value;

  Node* r = tail_;
  tail_ = tail_->prev;
  if(tail_)
  {
    tail_->next = nullptr;
  }
  else
  {
    head_ = nullptr;
  }
  size_--;
  delete r;

  return val;
}

template <typename T>
void DoublyLinkedList<T>::for_each(std::function<void(const T&)> func) const noexcept
{
  Node* cur = head_;
  while(cur)
  {
    func(cur->value);
    cur = cur->next;
  }
}

template <typename T>
size_t DoublyLinkedList<T>::size() const noexcept
{
  return size_;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <typename T>
const T& DoublyLinkedList<T>::get_front() const noexcept
{
  return head_->value;
}

template <typename T>
const T& DoublyLinkedList<T>::get_back() const noexcept
{
  return tail_->value;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const noexcept
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
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
  if(this == &other) return *this;

  Node* cur = head_;
  while(cur)
  {
    Node* r = cur;
    cur = cur->next;
    delete r;
  }

  size_ = other.size_;
  if(other.size_ == 0) return *this;
  head_ = tail_ = new Node;
  head_->value = other.head_->value;
  head_->next = head_->prev = nullptr;

  cur = head_;
  Node* curOther = other.head_->next;
  while(curOther)
  {
    Node* newNode = new Node;
    newNode->value = curOther->value;
    newNode->prev = cur;
    cur->next = newNode;
    
    tail_ = newNode;
    cur = newNode;
    curOther = curOther->next;
  }

  return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) noexcept
{
  size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;
  other.head_ = nullptr;
  other.tail_ = nullptr;

  return *this;
}
