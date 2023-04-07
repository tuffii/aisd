#ifndef BIDERECTIONALLIST_HPP
#define BIDERECTIONALLIST_HPP
#include <stdexcept>
#include <iterator>
#include <cassert>

namespace surby
{
  template < typename T >
  class BidirectionalList
  {
  public:
    class Iterator;
    class ConstIterator;

    BidirectionalList();
    ~BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);

    bool operator==(BidirectionalList&);
    bool operator!=(BidirectionalList&);

    void clear();
    void pushFront(const T&);
    void pushBack(const T&);
    void popFront();
    void popBack();
    bool isEmpty() const;
    size_t getSize() const;
    const T& getBack() const;
    const T& getFront() const;

    BidirectionalList& operator= (const BidirectionalList&);
    void swap(BidirectionalList&) noexcept;

    void insert(const T&, Iterator&);
    void erase(Iterator&);

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cend() const;
    ConstIterator cbegin() const;

  private:
    struct Node
    {
      T data_;
      Node* next_;
      Node* prev_;
    };
    size_t size_;
    Node* head_;
    Node* tail_;
  };

  template < typename T >
  BidirectionalList< T >::BidirectionalList():
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  BidirectionalList< T >::~BidirectionalList()
  {
    clear();
  }

  template< typename T >
  void surby::BidirectionalList< T >::clear()
  {
    while (!isEmpty())
    {
      popFront();
    }
  }

  template< typename T >
  BidirectionalList< T >& surby::BidirectionalList< T >::operator=(const BidirectionalList< T >& other)
  {
    if (this != std::addressof(other))
    {
      BidirectionalList< T > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  bool surby::BidirectionalList< T >::operator==(BidirectionalList& oter)
  {
    BidirectionalList< T >::Iterator firstIter = begin();
    BidirectionalList< T >::Iterator oterIter = oter.begin();
    if (size_ != oter.size_)
    {
      return false;
    }
    while (firstIter != end())
    {
      if (*firstIter != *oterIter)
      {
        return false;
      }
      ++firstIter;
      ++oterIter;
    }
    return true;
  }

  template< typename T >
  bool surby::BidirectionalList< T >::operator!=(BidirectionalList& oter)
  {
    return !(*this == oter);
  }

  template< typename T >
  void BidirectionalList< T >::swap(BidirectionalList& oter) noexcept
  {
    std::swap(head_, oter.head_);
    std::swap(tail_, oter.tail_);
    std::swap(size_, oter.size_);
  }

  template< typename T >
  void surby::BidirectionalList< T >::popFront()
  {
    Node* temp = head_;
    if (head_ != nullptr && head_->next_ != nullptr)
    {
      head_->next_->prev_ = nullptr;
      head_ = head_->next_;
    }
    delete temp;
    size_--;
    if (isEmpty())
    {
      tail_ = nullptr;
      head_ = nullptr;
    }
  }
  template< typename T >
  bool surby::BidirectionalList< T >::isEmpty() const
  {
    return (this->size_ == 0);
  }
  template< typename T >
  void surby::BidirectionalList< T >::pushBack(const T& data_)
  {
    if (isEmpty())
    {
      tail_ = new Node{ data_, nullptr, nullptr };
      head_ = tail_;
    }
    else
    {
      tail_->next_ = new Node{ data_, nullptr, tail_ };
      auto beforeTail = tail_;
      tail_ = tail_->next_;
      beforeTail->next_ = tail_;
    }
    size_++;
  }

  template< typename T >
  void surby::BidirectionalList< T >::pushFront(const T& data_)
  {
    head_ = new Node{ data_, head_, nullptr };
    if (isEmpty())
    {
      tail_ = head_;
    }
    else
    {
      head_->next_->prev_ = head_;
    }
    size_++;
  }

  template< typename T >
  void surby::BidirectionalList< T >::popBack()
  {
    Node* temp = tail_;
    if (tail_ != nullptr && tail_->prev_ != nullptr)
    {
      tail_->prev_->next_ = nullptr;
      tail_ = tail_->prev_;
    }
    delete temp;
    size_--;
    if (isEmpty())
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
  }
  template< typename T >
  size_t surby::BidirectionalList< T >::getSize() const
  {
    return size_;
  }

  template< typename T >
  const T& surby::BidirectionalList< T >::getBack() const
  {
    if (tail_ == nullptr)
    {
      throw std::out_of_range("getBack from empty List");
    }
    return tail_->data_;
  }
  template< typename T >
  const T& surby::BidirectionalList< T >::getFront() const
  {
    if (head_ == nullptr)
    {
      throw std::out_of_range("getBack from empty List");
    }
    return head_->data_;
  }

  template< typename T >
  BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other):
    size_(other.size_),
    head_(nullptr),
    tail_(nullptr)
  {
    if (!other.isEmpty())
    {
      if (other.size_ == 1)
      {
        size_ = 1;
        head_ = new Node{ other.head_->data_, nullptr , nullptr };
        tail_ = head_;
      }
      else
      {
        Node* otherNode = other.head_->next_;
        head_ = new Node{ other.head_->data_, nullptr , nullptr };
        Node* thisNode = head_;
        while (otherNode)
        {
          thisNode->next_ = new Node{ otherNode->data_, nullptr, thisNode };
          thisNode = thisNode->next_;
          otherNode = otherNode->next_;
        }
        tail_ = thisNode;
      }
    }
  }

  template< typename T >
  void surby::BidirectionalList< T >::insert(const T& value, Iterator& iter)
  {
    if (iter == begin())
    {
      this->pushFront(value);
    }
    else if (iter == end())
    {
      this->pushBack(value);
    }
    else
    {
      Iterator currentIter = begin();
      Node* currentNode = this->head_;
      while (++currentIter != iter)
      {
        currentNode = currentNode->next_;
      }
      currentNode->next_ = new Node{ value, currentNode->next_, currentNode };

      if (currentNode->next_->next_ != nullptr)
      {
        currentNode->next_->next_->prev_ = currentNode->next_;
      }
      this->size_++;
    }
  }

  template< typename T >
  void surby::BidirectionalList< T >::erase(Iterator& iter)
  {

    if (iter == end())
    {
      throw std::out_of_range("erase for end");
    }

    else if (iter == begin())
    {
      this->popFront();
      iter = this->begin();
    }
    else
    {
      Node* currentNode = this->head_;
      Iterator currentIter = begin();
      while (++currentIter != iter)
      {
        currentNode = currentNode->next_;
      }
      currentIter++;
      Node* nodeAfterDelete = currentNode->next_->next_;
      delete currentNode->next_;
      this->size_--;
      currentNode->next_ = nodeAfterDelete;
      if (nodeAfterDelete)
      {
        nodeAfterDelete->prev_ = currentNode;
      }
      else
      {
        tail_ = currentNode;
      }
      iter = currentIter;
    }
    if (size_ <= 1)
    {
      if (isEmpty())
      {
        head_ = nullptr;
      }
      tail_ = head_;
    }
  }

  template< typename T >
  class BidirectionalList< T >::Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class BidirectionalList< T >;

    Iterator();
    Iterator(const Iterator&) = default;
    Iterator(ConstIterator);
    ~Iterator() = default;

    Iterator& operator=(const Iterator&) = default;

    bool operator!=(const Iterator&) const;
    bool operator==(const Iterator&) const;

    Iterator& operator++();
    Iterator operator++(int);

    Iterator& operator--();
    Iterator operator--(int);


    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;

  private:
    ConstIterator iter_;
  };

  template < typename T >
  BidirectionalList< T >::Iterator::Iterator():
    iter_()
  {}

  template < typename T >
  BidirectionalList< T >::Iterator::Iterator(ConstIterator iter):
    iter_(iter)
  {}

  template < typename T >
  bool BidirectionalList< T >::Iterator::operator==(const Iterator& value) const
  {
    return iter_ == value.iter_;
  }

  template < typename T >
  bool BidirectionalList< T >::Iterator::operator!=(const Iterator& value) const
  {
    return !(value == *this);
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator& BidirectionalList< T >::Iterator::operator++()
  {
    ++iter_;
    return *this;
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::Iterator::operator++(int)
  {
    return Iterator(iter_++);
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator& BidirectionalList< T >::Iterator::operator--()
  {
    --iter_;
    return *this;
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::Iterator::operator--(int)
  {
    return Iterator(iter_--);
  }

  template < typename T >
  T& BidirectionalList< T >::Iterator::operator*()
  {
    return const_cast< T& >(*iter_);
  }

  template < typename T >
  T* BidirectionalList< T >::Iterator::operator->()
  {
    return std::addressof(const_cast< T& >(*iter_));
  }

  template < typename T >
  const T& BidirectionalList< T >::Iterator::operator*() const
  {
    return *iter_;
  }
  template < typename T >
  const T* BidirectionalList< T >::Iterator::operator->() const
  {
    return std::addressof(*iter_);
  }

  template< typename T >
  class BidirectionalList< T >::ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class BidirectionalList< T >;
    using Node = typename BidirectionalList< T >::Node;

    ConstIterator();
    ConstIterator(const ConstIterator&) = default;

    ~ConstIterator() = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const ConstIterator&) const;
    bool operator==(const ConstIterator&) const;

  private:
    Node* node_;
    const BidirectionalList< T >* list_;
    ConstIterator(Node*, const BidirectionalList< T >*);
  };

  template< typename T >
  BidirectionalList< T >::ConstIterator::ConstIterator():
    node_(nullptr),
    list_(nullptr)
  {}

  template < typename T >
  BidirectionalList< T >::ConstIterator::ConstIterator(Node* node, const BidirectionalList< T >* list):
    node_(node),
    list_(list)
  {}

  template < typename T >
  typename BidirectionalList< T >::ConstIterator& BidirectionalList< T >::ConstIterator::operator++()
  {
    assert(node_);
    this->node_ = this->node_->next_;
    return *this;
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::ConstIterator::operator++(int)
  {
    assert(node_);
    ConstIterator result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator& BidirectionalList< T >::ConstIterator::operator--()
  {
    assert(node_);
    this->node_ = this->node_->prev_;
    return *this;
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::ConstIterator::operator--(int)
  {
    assert(node_);
    ConstIterator result(*this);
    --(*this);
    return result;
  }

  template < typename T >
  bool BidirectionalList< T >::ConstIterator::operator==(const ConstIterator& iter) const
  {
    return (node_ == iter.node_ && list_ == iter.list_);
  }

  template < typename T >
  bool BidirectionalList< T >::ConstIterator::operator!=(const ConstIterator& iter) const
  {
    return !(iter == *this);
  }

  template < typename T >
  const T& BidirectionalList< T >::ConstIterator::operator*() const
  {
    assert(node_);
    return node_->data_;
  }

  template < typename T >
  const T* BidirectionalList< T >::ConstIterator::operator->() const
  {
    assert(node_);
    return std::addressof(node_->data_);
  }

  template< typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::begin()
  {
    return ConstIterator(this->head_, this);
  }

  template < typename T >
  typename BidirectionalList< T >::Iterator BidirectionalList< T >::end()
  {
    return ConstIterator(nullptr, this);
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::begin() const
  {
    return ConstIterator(this->head_, this);
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::end() const
  {
    return ConstIterator(nullptr, this);
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::cbegin() const
  {
    return begin();
  }

  template < typename T >
  typename BidirectionalList< T >::ConstIterator BidirectionalList< T >::cend() const
  {
    return end();
  }
}
#endif
