#pragma once

#include <cstddef>
#include <functional>

#include "../queue/queue.hpp"

template <typename T, typename compare = std::less<T>>
class BST
{
public:
  enum class TraversalOrder { PreOrder, InOrder, PostOrder, LevelOrder };

  BST();
  BST(const BST& other);
  BST(BST&& other) noexcept;

  ~BST();

  void insert(const T& item);
  bool remove(const T& item);

  void traverse(std::function<void(T&)> fun, 
    TraversalOrder order = TraversalOrder::InOrder);
  void traverse(std::function<void(const T&)> fun, 
    TraversalOrder order = TraversalOrder::InOrder) const;

  bool contains(const T& item) const noexcept;
  bool isEmpty() const noexcept;
  size_t size() const noexcept;

  BST& operator=(const BST& other);
  BST& operator=(BST&& other) noexcept;
private:
  struct Node
  {
    T value;
    Node* left;
    Node* right;
  };
  Node* root_;
  size_t size_;

  void copy(Node*& dst, Node* src);
  void destroy(Node*& node);
  void traverse(Node* node, std::function<void(T&)> fun, TraversalOrder order);
  void remove(Node*& node, Node* parent);
};

template <typename T, typename C>
BST<T, C>::BST(): root_(nullptr), size_(0) {}

template <typename T, typename C>
BST<T, C>::BST(const BST& other)
{
  size_ = other.size_;
  copy(root_, other.root_);
}

template <typename T, typename C>
BST<T, C>::BST(BST&& other) noexcept
{
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename C>
BST<T, C>::~BST()
{
  destroy(root_);
}

template <typename T, typename C>
void BST<T, C>::insert(const T& item)
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
  Node* newNode = new Node();
  newNode->value = item;
  newNode->left = nullptr;
  newNode->right = nullptr;
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
}

template <typename T, typename C>
bool BST<T, C>::remove(const T& item)
{
  Node* cur = root_;
  Node* parent = nullptr;
  while(cur)
  {
    if(cur->value == item)
    {
      remove(cur, parent);
      return true;
    }
    else if(C{}(item, cur->value))
    {
      parent = cur;
      cur = cur->left;
    }
    else
    {
      parent = cur;
      cur = cur->right;
    }
  }

  return false;
}

template <typename T, typename C>
void BST<T, C>::traverse(std::function<void(T&)> fun, TraversalOrder order)
{
  traverse(root_, fun, order);
}

template <typename T, typename C>
void BST<T, C>::traverse(std::function<void(const T&)> fun, TraversalOrder order) const
{
  const_cast<BST<T, C>*>(this)->traverse(root_, fun, order);
}

template <typename T, typename C>
bool BST<T, C>::contains(const T& item) const noexcept
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
bool BST<T, C>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <typename T, typename C>
size_t BST<T, C>::size() const noexcept
{
  return size_;
}

template <typename T, typename C>
BST<T, C>& BST<T, C>::operator=(const BST& other)
{
  if(this == &other) return *this;
  if(root_) destroy(root_);
  size_ = other.size_;
  copy(root_, other.root_);
  return *this;
}

template <typename T, typename C>
BST<T, C>& BST<T, C>::operator=(BST&& other) noexcept
{
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
  return *this;
}

template <typename T, typename C>
void BST<T, C>::traverse(Node* node, std::function<void(T&)> fun, TraversalOrder order)
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
void BST<T, C>::destroy(Node*& node)
{
    if(!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T, typename C>
void BST<T, C>::copy(Node*& dst, Node* src)
{
  if(!src) return;
  Node* newNode = new Node;
  newNode->value = src->value;
  newNode->left = nullptr;
  newNode->right = nullptr;
  dst = newNode;
  copy(newNode->left, src->left);
  copy(newNode->right, src->right);
}

template <typename T, typename C>
void BST<T, C>::remove(Node*& node, Node* parent)
{
  if(node->left && node->right)
  {
    Node* smallestNode = node->right;
    Node* smallestNodeParent = node;
    while(smallestNode->left)
    {
      smallestNodeParent = smallestNode;
      smallestNode = smallestNode->left;
    }
    
    // Note: Smallest node must be removed BEFORE setting current node's value
    //       in order to be able to determine if the node to be deleted 
    //       is parent's left or right child.
    auto value = smallestNode->value;
    remove(smallestNode, smallestNodeParent);
    node->value = value;
  }
  else
  {
    Node* newChild = nullptr;
    if(node->left) newChild = node->left;
    else newChild = node->right;

    if(C{}(node->value, parent->value))
      parent->left = newChild;
    else
      parent->right = newChild;

    delete node;
  }
}