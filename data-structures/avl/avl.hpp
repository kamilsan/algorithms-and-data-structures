#pragma once

#include <cstddef>
#include <functional>

#include "../queue/queue.hpp"

template <typename T, typename compare = std::less<T>>
class AVL
{
public:
  enum class TraversalOrder { PreOrder, InOrder, PostOrder, LevelOrder };

  AVL();
  AVL(const AVL& other);
  AVL(AVL&& other) noexcept;

  ~AVL();

  void insert(const T& item);
  bool remove(const T& item);

  void traverse(std::function<void(T&)> fun, 
    TraversalOrder order = TraversalOrder::InOrder);
  void traverse(std::function<void(const T&)> fun, 
    TraversalOrder order = TraversalOrder::InOrder) const;

  bool contains(const T& item) const noexcept;
  bool isEmpty() const noexcept;
  size_t size() const noexcept;

  AVL& operator=(const AVL& other);
  AVL& operator=(AVL&& other) noexcept;
private:
  struct Node
  {
    Node(const T& val): value(val), left(nullptr), 
      right(nullptr), parent(nullptr), height(0) {}

    T value;
    Node* left;
    Node* right;
    Node* parent;
    size_t height;
  };

  Node* root_;
  size_t size_;

  long height(Node* node) const noexcept;
  void balance(Node* node);
  void updateHeight(Node* node);
  void rotateRight(Node* node);
  void rotateLeft(Node* node);

  void copy(Node*& dst, Node* src, Node* parent);
  void destroy(Node*& node);
  void traverse(Node* node, std::function<void(T&)> fun, TraversalOrder order);
  void removeImpl(Node*& node);
};

template <typename T, typename C>
AVL<T, C>::AVL(): root_(nullptr), size_(0) {}

template <typename T, typename C>
AVL<T, C>::AVL(const AVL& other)
{
  size_ = other.size_;
  copy(root_, other.root_, nullptr);
}

template <typename T, typename C>
AVL<T, C>::AVL(AVL&& other) noexcept
{
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename C>
AVL<T, C>::~AVL()
{
  destroy(root_);
}

template <typename T, typename C>
void AVL<T, C>::insert(const T& item)
{
  Node* cur = root_;
  Node* parent = nullptr;
  while(cur)
  {
    parent = cur;
    if(C{}(item, cur->value))
      cur = cur->left;
    else
      cur = cur->right;
  }
  Node* newNode = new Node(item);
  newNode->parent = parent;
  if(parent)
  {
    if(C{}(item, parent->value))
      parent->left = newNode;
    else 
      parent->right = newNode;
  }
  else
    root_ = newNode;

  size_++;

  balance(parent);
}

template <typename T, typename C>
bool AVL<T, C>::remove(const T& item)
{
  Node* cur = root_;
  while(cur)
  {
    if(cur->value == item)
    {
      removeImpl(cur);
      size_ -= 1;
      return true;
    }
    else if(C{}(item, cur->value))
      cur = cur->left;
    else
      cur = cur->right;
  }

  return false;
}

template <typename T, typename C>
void AVL<T, C>::traverse(std::function<void(T&)> fun, TraversalOrder order)
{
  traverse(root_, fun, order);
}

template <typename T, typename C>
void AVL<T, C>::traverse(std::function<void(const T&)> fun, TraversalOrder order) const
{
  const_cast<AVL<T, C>*>(this)->traverse(root_, fun, order);
}

template <typename T, typename C>
bool AVL<T, C>::contains(const T& item) const noexcept
{
  Node* cur = root_;
  while(cur)
  {
    if(cur->value == item)
      return true;
    else if(C{}(item, cur->value))
      cur = cur->left;
    else
      cur = cur->right;
  }
  return false;
}

template <typename T, typename C>
bool AVL<T, C>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <typename T, typename C>
size_t AVL<T, C>::size() const noexcept
{
  return size_;
}

template <typename T, typename C>
AVL<T, C>& AVL<T, C>::operator=(const AVL& other)
{
  if(this == &other) return *this;
  if(root_) destroy(root_);
  size_ = other.size_;
  copy(root_, other.root_, nullptr);
  return *this;
}

template <typename T, typename C>
AVL<T, C>& AVL<T, C>::operator=(AVL&& other) noexcept
{
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
  return *this;
}

template <typename T, typename C>
long AVL<T, C>::height(Node* node) const noexcept
{
  if(!node) return -1;
  else return node->height;
}

template <typename T, typename C>
void AVL<T, C>::balance(Node* node)
{
  while(node)
  {
    updateHeight(node);
    if(height(node->right) >= height(node->left) + 2)
    {
      if(height(node->right->right) >= height(node->right->left))
        rotateLeft(node);
      else
      {
        rotateRight(node->right);
        rotateLeft(node);
      }
    }
    else if(height(node->left) >= height(node->right) + 2)
    {
      if(height(node->left->left) >= height(node->left->right))
        rotateRight(node);
      else
      {
        rotateLeft(node->left);
        rotateRight(node);
      }
    }
    node = node->parent;
  }
}

template <typename T, typename C>
void AVL<T, C>::updateHeight(Node* node)
{  
  node->height = 1 + std::max(height(node->right), height(node->left));
}

template <typename T, typename C>
void AVL<T, C>::rotateRight(Node* node)
{
  Node* y = node->left;
  y->parent = node->parent;
  if(!y->parent)
    root_ = y;
  else
  {
    if(y->parent->right == node)
      y->parent->right = y;
    else
      y->parent->left = y;
  }
  node->left = y->right;
  node->parent = y;
  if(y->right)
    y->right->parent = node;
  y->right = node;
  updateHeight(node);
  updateHeight(y);
}

template <typename T, typename C>
void AVL<T, C>::rotateLeft(Node* node)
{
  Node* y = node->right;
  y->parent = node->parent;
  if(!y->parent)
    root_ = y;
  else
  {
    if(y->parent->right == node)
      y->parent->right = y;
    else
      y->parent->left = y;
  }
  node->right = y->left;
  node->parent = y;
  if(y->left)
    y->left->parent = node;
  y->left = node;
  updateHeight(node);
  updateHeight(y);
}

template <typename T, typename C>
void AVL<T, C>::traverse(Node* node, std::function<void(T&)> fun, TraversalOrder order)
{
  if(!node) return;
  switch(order)
  {
    case TraversalOrder::LevelOrder:
    {
      Queue<Node*> queue;
      queue.enqueue(root_);
      while(!queue.isEmpty())
      {
        auto cur = queue.dequeue();
        fun(cur->value);
        if(cur->left)
          queue.enqueue(cur->left);
        if(cur->right)
          queue.enqueue(cur->right);
      }
      break;
    }
    case TraversalOrder::PreOrder:
    {
      fun(node->value);
      traverse(node->left, fun, order);
      traverse(node->right, fun, order);
      break;
    }
    case TraversalOrder::InOrder:
    {
      traverse(node->left, fun, order);
      fun(node->value);
      traverse(node->right, fun, order);
      break;
    }
    case TraversalOrder::PostOrder:
    {
      traverse(node->left, fun, order);
      traverse(node->right, fun, order);
      fun(node->value);
      break;
    }
  }
}

template <typename T, typename C>
void AVL<T, C>::destroy(Node*& node)
{
    if(!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T, typename C>
void AVL<T, C>::copy(Node*& dst, Node* src, Node* parent)
{
  if(!src) return;
  Node* newNode = new Node(src->value);
  newNode->height = src->height;
  newNode->parent = parent;
  dst = newNode;
  copy(newNode->left, src->left, newNode);
  copy(newNode->right, src->right, newNode);
}

template <typename T, typename C>
void AVL<T, C>::removeImpl(Node*& node)
{
  if(node->left && node->right)
  {
    Node* smallestNode = node->right;
    while(smallestNode->left)
      smallestNode = smallestNode->left;
    
    node->value = smallestNode->value;
    removeImpl(smallestNode);
  }
  else
  {
    Node* newChild = nullptr;
    Node* parent = node->parent;
    if(node->left) newChild = node->left;
    else newChild = node->right;

    if(parent)
    {
      if(parent->left == node)
        parent->left = newChild;
      else
        parent->right = newChild;
    }
    else
      root_ = newChild;

    if(newChild)
      newChild->parent = parent;

    delete node;

    balance(parent);
  }
}