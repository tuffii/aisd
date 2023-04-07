#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <iterator>
#include "List.hpp"
#include <cassert>

namespace surby
{
  template < typename T >
  class ForwardList: protected detail::List< T >
  {
  public:
    using list = typename detail::List< T >;
    using node = typename list::node;

    class Iterator;
    class ConstIterator;

    ForwardList() = default;

    void push(const T&);
    void insert(const T&, Iterator);
    void erase(Iterator);
    bool isEmpty() const;
    void clear();

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;
  };

  template< typename T >
  void ForwardList< T >::push(const T& value)
  {
    list::push(value);
  }

  template< typename T >
  void surby::ForwardList< T >::clear()
  {
    list::clear();
  }

  template < typename T >
  void ForwardList< T >::insert(const T& value, Iterator iter)
  {
    if (iter == begin())
    {
      push(value);
    }
    else
    {
      Iterator currentIter = begin();
      node* currentNode = this->head_;
      while (++currentIter != iter)
      {
        currentNode = currentNode->pNext_;
      }
      currentNode->pNext_ = new node{ value, currentNode->pNext_ };

      this->size_++;
    }
  }

  template < typename T >
  void ForwardList< T >::erase(Iterator iter)
  {
    if (iter == end())
    {
      throw std::out_of_range("erase for end");
    }
    else if (iter == begin())
    {
      list::pop();
      iter = begin();
    }
    else
    {
      node* currentNode = this->head_;
      Iterator currentIter = begin();
      while (++currentIter != iter)
      {
        currentNode = currentNode->pNext_;
      }
      currentIter++;
      node* nodeAfterDelete = currentNode->pNext_->pNext_;
      delete currentNode->pNext_;
      this->size_--;
      currentNode->pNext_ = nodeAfterDelete;
      iter = currentIter;
    }
  }

  template < typename T >
  bool ForwardList< T >::isEmpty() const
  {
    return list::isEmpty();
  }

  template< typename T >
  class ForwardList < T >::Iterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class ForwardList < T >;

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
  ForwardList < T >::Iterator::Iterator():
    iter_()
  {
  }

  template < typename T >
  ForwardList < T >::Iterator::Iterator(ConstIterator iter):
    iter_(iter)
  {
  }

  template < typename T >
  bool ForwardList < T >::Iterator::operator==(const Iterator& value) const
  {
    return iter_ == value.iter_;
  }

  template < typename T >
  bool ForwardList < T >::Iterator::operator!=(const Iterator& value) const
  {
    return !(value == *this);
  }

  template < typename T >
  typename ForwardList < T >::Iterator& ForwardList < T >::Iterator::operator++()
  {
    ++iter_;
    return *this;
  }

  template < typename T >
  typename ForwardList < T >::Iterator ForwardList < T >::Iterator::operator++(int)
  {
    return Iterator(iter_++);
  }

  template < typename T >
  typename ForwardList < T >::Iterator& ForwardList < T >::Iterator::operator--()
  {
    --iter_;
    return *this;
  }

  template < typename T >
  typename ForwardList < T >::Iterator ForwardList < T >::Iterator::operator--(int)
  {
    return Iterator(iter_--);
  }

  template < typename T >
  T& ForwardList < T >::Iterator::operator*()
  {
    return const_cast< T& >(*iter_);
  }

  template < typename T >
  T* ForwardList < T >::Iterator::operator->()
  {
    return std::addressof(const_cast< T& >(*iter_));
  }

  template < typename T >
  const T& ForwardList < T >::Iterator::operator*() const
  {
    return *iter_;
  }
  template < typename T >
  const T* ForwardList < T >::Iterator::operator->() const
  {
    return std::addressof(*iter_);
  }

  template< typename T >
  class ForwardList < T >::ConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class ForwardList< T >;
    using Node = typename ForwardList < T >::node;

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
    const ForwardList< T >* list_;
    ConstIterator(Node*, const ForwardList< T >*);
  };

  template< typename T >
  ForwardList < T >::ConstIterator::ConstIterator():
    node_(nullptr),
    list_(nullptr)
  {
  }

  template < typename T >
  ForwardList < T >::ConstIterator::ConstIterator(Node* node, const ForwardList < T >* list):
    node_(node),
    list_(list)
  {
  }

  template < typename T >
  typename ForwardList < T >::ConstIterator& ForwardList < T >::ConstIterator::operator++()
  {
    assert(node_);
    this->node_ = this->node_->pNext_;
    return *this;
  }

  template < typename T >
  typename ForwardList < T >::ConstIterator ForwardList < T >::ConstIterator::operator++(int)
  {
    assert(node_);
    ConstIterator result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  typename ForwardList < T >::ConstIterator& ForwardList < T >::ConstIterator::operator--()
  {
    assert(node_);
    this->node_ = this->node_->prev_;
    return *this;
  }

  template < typename T >
  typename ForwardList < T >::ConstIterator ForwardList < T >::ConstIterator::operator--(int)
  {
    assert(node_);
    ConstIterator result(*this);
    --(*this);
    return result;
  }

  template < typename T >
  bool ForwardList < T >::ConstIterator::operator==(const ConstIterator& iter) const
  {
    return (node_ == iter.node_ && list_ == iter.list_);
  }

  template < typename T >
  bool ForwardList < T >::ConstIterator::operator!=(const ConstIterator& iter) const
  {
    return !(iter == *this);
  }

  template < typename T >
  const T& ForwardList< T >::ConstIterator::operator*() const
  {
    assert(node_);
    return node_->data_;
  }

  template < typename T >
  const T* ForwardList < T >::ConstIterator::operator->() const
  {
    assert(node_);
    return std::addressof(node_->data_);
  }

  template< typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::begin()
  {
    return ConstIterator(this->head_, this);
  }

  template < typename T >
  typename ForwardList< T >::Iterator ForwardList< T >::end()
  {
    return ConstIterator(nullptr, this);
  }

  template < typename T >
  typename ForwardList< T >::ConstIterator ForwardList< T >::begin() const
  {
    return ConstIterator(this->head_, this);
  }

  template < typename T >
  typename ForwardList< T >::ConstIterator ForwardList< T >::end() const
  {
    return ConstIterator(nullptr, this);
  }

  template < typename T >
  typename ForwardList< T >::ConstIterator ForwardList< T >::cbegin() const
  {
    return begin();
  }

  template < typename T >
  typename ForwardList< T >::ConstIterator ForwardList< T >::cend() const
  {
    return end();
  }
}
#endif
