#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <bidirectionalList.hpp>

namespace surby
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;

    void clear();
    void pushFront(const T&);
    void pushBack(const T&);
    void popFront();
    void popBack();

    bool isEmpty() const;
    size_t getSize() const;
    const T& getBack() const;
    const T& getFront() const;

  private:
    surby::BidirectionalList< T > list_;
  };

  template< typename T >
  bool surby::Queue< T >::isEmpty() const
  {
    return this->list_.isEmpty();
  }

  template< typename T >
  size_t Queue < T >::getSize() const
  {
    return this->list_.getSize();
  }

  template< typename T >
  void Queue< T >::clear()
  {
    this->list_.clear();
  }

  template< typename T >
  void Queue< T >::pushBack(const T& data)
  {
    this->list_.pushBack(data);
  }

  template< typename T >
  void Queue< T >::pushFront(const T& data)
  {
    this->list_.pushFront(data);
  }

  template< typename T >
  void Queue< T >::popBack()
  {
    this->list_.popBack();
  }

  template< typename T >
  void Queue< T >::popFront()
  {
    this->list_.popFront();
  }

  template< typename T >
  const T& Queue< T >::getBack() const
  {
    return this->list_.getBack();
  }

  template< typename T >
  const T& Queue< T >::getFront() const
  {
    return this->list_.getFront();
  }
}
#endif
