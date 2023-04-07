#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <functional>
#include <cassert>
#include <stdexcept>
#include <cmath>

namespace surby
{
  template < typename Key, typename Value >
  struct data_t
  {
    Key key_;
    Value value_;
  };

  template< class T >
  struct NodeTree
  {
    T data_;
    NodeTree* parent_;
    NodeTree* left_;
    NodeTree* right_;
  };

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree
  {
  public:
    using Data = data_t < Key, Value >;
    using Node = NodeTree < Data >;

    class ConstIterator;
    class Iterator;

    BinarySearchTree():
      root_(nullptr),
      size_(0)
    {}
    BinarySearchTree(const BinarySearchTree& other):
      root_(nullptr),
      size_(other.size_),
      comp_(other.comp_)
    {
      root_ = copy(other.root_);
    }
    BinarySearchTree(BinarySearchTree&& other) noexcept:
      root_(other.root_),
      size_(other.size_),
      comp_(other.comp_)
    {
      other.root_ = nullptr;
    }
    ~BinarySearchTree()
    {
      clear();
    }
    void clear()
    {
      clearNode(root_);
      root_ = nullptr;
    }
    bool isEmpty() const noexcept
    {
      return (size_ == 0);
    }
    size_t getSize() const noexcept
    {
      return size_;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
      if (this != &other)
      {
        BinarySearchTree copy(other);
        swap(copy);
      }
      return *this;
    }
    BinarySearchTree& operator=(BinarySearchTree&& other)
    {
      if (this != &other)
      {
        BinarySearchTree copy(std::move(other));
        swap(copy);
      }
      return *this;
    }
    void swap(BinarySearchTree& other) noexcept
    {
      std::swap(size_, other.size_);
      std::swap(comp_, other.comp_);
      std::swap(root_, other.root_);
    }

    ConstIterator cfind(const Key& key) const
    {
      if (!root_)
      {
        return end();
      }

      Node* current = root_;
      while (current)
      {
        if (comp_(current->data_.key_, key))
        {
          current = current->right_;
        }
        else if (comp_(key, current->data_.key_))
        {
          current = current->left_;
        }
        else
        {
          break;
        }
      }
      return ConstIterator(current, this);
    }

    Iterator find(const Key& key) const
    {
      return Iterator(cfind(key));
    }

    Iterator begin()
    {
      return Iterator(cbegin());
    }
    Iterator end()
    {
      return Iterator(cend());
    }

    ConstIterator begin() const
    {
      return cbegin();
    }
    ConstIterator end() const
    {
      return cend();
    }

    ConstIterator cbegin() const
    {
      return ConstIterator(min(root_), this);
    }
    ConstIterator cend() const
    {
      return ConstIterator(nullptr, this);
    }

    ConstIterator crbegin() const
    {
      return ConstIterator(max(root_), this);
    }
    ConstIterator rbegin() const
    {
      return crbegin();
    }
    Iterator rbegin()
    {
      return Iterator(crbegin);
    }

    void erase(const Key& key)
    {
      Node* toDelete = find(key).it_.node_;
      balanceBranch(eraseNode(toDelete));
    }
    Node* erase(Iterator it)
    {
      return balanceBranch(eraseNode(it.it_.node_));
    }

    void push(const Key& key, const Value& value)
    {
      this->insert(key, value);
    }

  private:
    Node* root_;
    size_t size_;
    Compare comp_;

    Node* insert(const Key& key, const Value& value)
    {
      Node* node = new Node{Data{ key, value }};
      insertNode(node);
      balanceBranch(node);
      return node;
    }

    Node* copy(const Node* node)
    {
      if (node != nullptr)
      {
        Node* newNode = new Node{node->data_, nullptr, nullptr, nullptr};
        newNode->left_ = copy(node->left_);
        if (newNode->left_)
        {
          newNode->left_->parent_ = newNode;
        }
        newNode->right_ = copy(node->right_);
        if (newNode->right_)
        {
          newNode->right_->parent_ = newNode;
        }
        return newNode;
      }
      return nullptr;
    }

    void clearNode(Node* node)
    {
      if (node == nullptr)
      {
        return;
      }
      size_--;

      if (node->left_)
      {
        clearNode(node->left_);
      }
      if (node->right_)
      {
        clearNode(node->right_);
      }
      delete node;
    }

    Node* insertNode(Node* node)
    {
      if (isEmpty())
      {
        root_ = node;
        size_++;
        return root_;
      }

      Node* current = root_;
      Node* parent = root_;

      while (current != nullptr)
      {
        if (compare(node, current))
        {
          current = current->left_;
        }
        else if (compare(current, node))
        {
          current = current->right_;
        }
        else
        {
          node->parent_ = current->parent_;

          if (current->left_ != nullptr)
          {
            node->left_ = current->left_;
            node->left_->parent_ = node;
          }
          if (current->right_ != nullptr)
          {
            node->right_ = current->right_;
            node->right_->parent_ = node;
          }

          if (current == root_)
          {
            root_ = node;
            delete current;
            return node;
          }
          if (compare(node, current->parent_))
          {
            current->parent_->left_ = node;
          }
          else
          {
            current->parent_->right_ = node;
          }
          delete current;
          return node;
        }
        if (current != nullptr) {
          parent = current;
        }
      }

      if (parent != nullptr)
      {
        if (compare(node, parent))
        {
          parent->left_ = node;
        }
        else {
          parent->right_ = node;
        }
      }

      node->parent_ = parent;
      size_++;
      return node;
    }

    bool compare(Node* lhs, Node* rhs) const
    {
      return (comp_(lhs->data_.key_, rhs->data_.key_));
    }

    bool isBalancedNode(Node* node)
    {
      long long change = getHeight(node->right_) - getHeight(node->left_);
      return (change <= 1 && change >= -1);
    }

    void balanceBranch(Node* node)
    {
      if (!node)
      {
        return;
      }
      Node* current = node;
      while (current != nullptr)
      {
        if (!isBalancedNode(current))
        {
          balanceNode(current);
        }
        current = current->parent_;
      }
    }
    void balanceNode(Node* node)
    {
      size_t rightHeight = getHeight(node->right_);
      size_t leftHeight = getHeight(node->left_);
      if (rightHeight - leftHeight == 2)
      {
        if (getHeight(node->right_->left_) <= getHeight(node->right_->right_))
        {
          smallLeftRotate(node);
          return;
        }
        else
        {
          bigLeftRotate(node);
          return;
        }
      }
      if (leftHeight - rightHeight == 2)
      {
        if (getHeight(node->left_->right_) <= getHeight(node->left_->left_))
        {
          smallRightRotate(node);
          return;
        }
        else
        {
          bigRightRotate(node);
          return;
        }
      }
    }

    size_t getHeight(Node* node)
    {
      if (!node)
      {
        return 0;
      }
      return std::fmax(getHeight(node->left_), getHeight(node->right_)) + 1;
    }

    Node* bigRightRotate(Node* node)
    {
      if (!node || !node->left_ || !node->left_->right_)
      {
        return nullptr;
      }

      Node* leftNode = node->left_;
      Node* newRoot = node->left_->right_;

      if (node == root_)
      {
        root_ = newRoot;
        newRoot->parent_ = nullptr;
      }
      else
      {
        if (compare(node, node->parent_))
        {
          node->parent_->left_ = newRoot;
        }
        else
        {
          node->parent_->right_ = newRoot;
        }
        newRoot->parent_ = node->parent_;
      }

      node->parent_ = newRoot;
      node->left_ = newRoot->right_;
      if (node->left_)
      {
        node->left_->parent_ = node;
      }
      leftNode->parent_ = newRoot;
      leftNode->right_ = newRoot->left_;
      if (leftNode->right_)
      {
        leftNode->right_->parent_ = leftNode;
      }

      newRoot->left_ = leftNode;
      newRoot->right_ = node;
      return newRoot;
    }
    Node* bigLeftRotate(Node* node)
    {
      if (!node || !node->right_ || !node->right_->left_)
      {
        return nullptr;
      }

      Node* rightNode = node->right_;
      Node* newRoot = node->right_->left_;

      if (node == root_)
      {
        root_ = newRoot;
        newRoot->parent_ = nullptr;
      }
      else
      {
        if (compare(node, node->parent_))
        {
          node->parent_->left_ = newRoot;
        }
        else
        {
          node->parent_->right_ = newRoot;
        }
        newRoot->parent_ = node->parent_;
      }

      node->parent_ = newRoot;
      node->right_ = newRoot->left_;
      if (node->right_)
      {
        node->right_->parent_ = node;
      }
      rightNode->parent_ = newRoot;
      rightNode->left_ = newRoot->right_;
      if (rightNode->left_)
      {
        rightNode->left_->parent_ = rightNode;
      }
      newRoot->right_ = rightNode;
      newRoot->left_ = node;
      return newRoot;
    }

    Node* smallLeftRotate(Node* node)
    {
      if (!node || !node->right_)
      {
        return nullptr;
      }
      Node* rightNode = node->right_;
      if (node == root_)
      {
        rightNode->parent_ = nullptr;
        root_ = rightNode;
      }
      else
      {
        if (compare(node, node->parent_))
        {
          node->parent_->left_ = rightNode;
        }
        else
        {
          node->parent_->right_ = rightNode;
        }
        rightNode->parent_ = node->parent_;
      }
      node->parent_ = rightNode;

      node->right_ = rightNode->left_;
      if (rightNode->left_)
      {
        rightNode->left_->parent_ = node;
      }
      rightNode->left_ = node;
      return rightNode;
    }
    Node* smallRightRotate(Node* node)

    {
      if (!node || !node->left_)
      {
        return nullptr;
      }

      Node* leftNode = node->left_;

      if (node == root_)
      {
        leftNode->parent_ = nullptr;
        root_ = leftNode;
      }
      else
      {
        if (compare(node, node->parent_))
        {
          node->parent_->left_ = leftNode;
        }
        else
        {
          node->parent_->right_ = leftNode;
        }

        leftNode->parent_ = node->parent_;
      }
      node->parent_ = leftNode;

      node->left_ = leftNode->right_;

      if (leftNode->right_)
      {
        leftNode->right_->parent_ = node;
      }
      leftNode->right_ = node;
      return leftNode;
    }

    Node* eraseNode(Node* node)
    {
      if (!node)
      {
        return nullptr;
      }
      if (node->right_)
      {
        if (node->left_)
        {
          return eraseIfTwoChildren(node);
        }
        return eraseIfRightChildren(node);
      }
      if (node->left_)
      {
        return eraseIfLeftChildren(node);
      }
      return eraseIfNoChildren(node);
    }

    Node* eraseIfTwoChildren(Node* node)
    {
      Node* change = max(node->left_);
      change->parent_->right_ = nullptr;
      change->right_ = node->right_;
      change->left_ = node->left_;
      if (node == root_)
      {
        root_ = change;
        change->parent_ = nullptr;
      }
      else
      {
        change->parent_ = node->parent_;
      }
      node->left_->parent_ = change;
      delete node;
      return change;
    }
    Node* eraseIfNoChildren(Node* node)
    {
      --size_;
      if (node == root_)
      {
        delete root_;
        return nullptr;
      }
      if (compare(node, node->parent_))
      {
        node->parent_->left_ = nullptr;
      }
      else
      {
        node->parent_->right_ = nullptr;
      }
      Node* data = node->parent_;
      delete node;
      return data;
    }
    Node* eraseIfLeftChildren(Node* node)
    {
      --size_;
      if (node == root_)
      {
        root_ = root_->left_;
        root_->parent_ = nullptr;
        delete node;
        return root_;
      }
      if (compare(node, node->parent_))
      {
        node->parent_->left_ = node->left_;
      }
      else
      {
        node->parent_->right_ = node->left_;
      }
      node->left_->parent_ = node->parent_;
      Node* left = node->left_;
      delete node;
      return left;
    }
    Node* eraseIfRightChildren(Node* node)
    {
      --size_;
      if (node == root_)
      {
        root_ = root_->right_;
        root_->parent_ = nullptr;
        delete node;
        return root_;
      }
      if (compare(node, node->parent_))
      {
        node->parent_->left_ = node->right_;
      }
      else
      {
        node->parent_->right_ = node->right_;
      }
      node->right_->parent_ = node->parent_;
      Node* right = node->right_;
      delete node;
      return right;
    }

    Node* min(Node* node) const
    {
      if (node)
      {
        while (node->left_)
        {
          node = node->left_;
        }
      }
      return node;
    }
    Node* max(Node* node) const
    {
      if (node)
      {
        while (node->right_)
        {
          node = node->right_;
        }
      }
      return node;
    }

    Node* next(Node* node) const
    {
      if (!node)
      {
        return nullptr;
      }
      Node* current = node;
      if (current->right_)
      {
        current = current->right_;
        while (current->left_)
        {
          current = current->left_;
        }
        return current;
      }
      if (current->parent_ && compare(current, current->parent_))
      {
        return current->parent_;
      }
      while (current->parent_ && compare(current->parent_, current))
      {
        current = current->parent_;
      }
      return current->parent_;
    }
    Node* prev(Node* node) const
    {
      if (!node)
      {
        return nullptr;
      }
      Node* current = node;

      if (current->left_)
      {
        current = current->left_;
        while (current->right_)
        {
          current = current->right_;
        }
        return current;
      }
      if (current->parent_ && compare(current->parent_, current))
      {
        return current->parent_;
      }
      while (current->parent_ && compare(current, current->parent_))
      {
        current = current->parent_;
      }
      return current->parent_;
    }
  };

  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree< Key, Value, Compare >::ConstIterator
  {
  public:
    using Data = data_t < Key, Value >;
    using Node = NodeTree < Data >;
    friend BinarySearchTree;

    bool operator==(const ConstIterator& other) const noexcept
    {
      return node_ == other.node_ && tree_ == other.tree_;
    }
    bool operator!=(const ConstIterator& other) const noexcept
    {
      return !(*this == other);
    }
    ConstIterator& operator++()
    {
      assert(node_);
      node_ = tree_->next(node_);
      return *this;
    }

    ConstIterator operator++(int)
    {
      assert(node_);
      ConstIterator result(*this);
      ++(*this);
      return result;
    }

    ConstIterator& operator--()
    {
      assert(node_);
      node_ = tree_->prev(node_);
      return *this;
    }
    ConstIterator operator--(int)
    {
      assert(node_);
      ConstIterator it(*this);
      --(*this);
      return it;
    }
    const Data& operator*() const
    {
      assert(node_);
      return node_->data_;
    }
    const Data* operator->() const
    {
      assert(node_);
      return std::addressof(node_->data_);
    }

  private:
    const BinarySearchTree* tree_;
    Node* node_;

    ConstIterator(Node* node, const BinarySearchTree* tree) noexcept:
      tree_(tree),
      node_(node)
    {}
  };

  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree< Key, Value, Compare >::Iterator
  {
  public:
    using Data = data_t < Key, Value >;
    using Node = NodeTree < Data >;
    friend BinarySearchTree;

    Iterator(ConstIterator it):
      it_(it)
    {}
    bool operator==(const Iterator& other) const
    {
      return it_ == other.it_;
    }
    bool operator!=(const Iterator& other) const
    {
      return !(*this == other);
    }
    Iterator& operator++()
    {
      ++it_;
      return *this;
    }
    Iterator operator++(int)
    {
      Iterator it(*this);
      ++(*this);
      return it;
    }
    Iterator operator--()
    {
      --it_;
      return *this;
    }
    Iterator operator--(int)
    {
      Iterator it(*this);
      --(*this);
      return it;
    }

    Data& operator*()
    {
      return const_cast < Data& >(*it_);
    }
    Data* operator->()
    {
      return const_cast< Data* >(std::addressof(*it_));
    }
    const Data& operator*() const
    {
      return *it_;
    }
    Data* operator->() const
    {
      return std::addressof(*it_);
    }

  private:
    ConstIterator it_;

    explicit Iterator(Node* node, const BinarySearchTree* tree):
      it_(node, tree)
    {}
  };
}
#endif
