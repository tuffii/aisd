#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>

namespace surby
{
  namespace detail
  {
    template < typename T >
    class List
    {
    public:
      List();
      ~List();
      List(const List< T >&);

      void clear();
      void push(const T&);
      void pop();
      bool isEmpty() const;
      size_t getSize() const;
      const T& get() const;

    protected:
      struct node
      {
        T data_;
        node* pNext_;
      };
      size_t size_;
      node* head_;
    };

    template < typename T >
    List< T >::List():
      size_(0),
      head_(nullptr)
    {
    }

    template < typename T >
    List< T >::~List()
    {
      clear();
    }

    template< typename T >
    void List< T >::push(const T& data_)
    {
      head_ = new node{ data_, head_ };
      size_++;
    }

    template< typename T >
    void List< T >::pop()
    {
      if (isEmpty())
      {
        throw std::out_of_range("pop from empty List");
      }
      node* temp = head_;
      head_ = head_->pNext_;
      delete temp;
      size_--;
    }

    template< typename T >
    void List< T >::clear()
    {
      while (size_)
      {
        pop();
      }
    }

    template< typename T >
    size_t List< T >::getSize() const
    {
      return this->size_;
    }

    template< typename T >
    bool List< T >::isEmpty() const
    {
      return (this->size_ == 0);
    }

    template< typename T >
    const T& List< T >::get() const
    {
      if (head_ == nullptr)
      {
        throw std::out_of_range("getBack from empty List");
      }
      return this->head_->data_;
    }

    template< typename T >
    List < T >::List(const List < T >& other):
      size_(other.size_),
      head_(nullptr)
    {
      if (!other.isEmpty())
      {
        node* otherNode = other.head_->pNext_;
        head_ = new node{ other.head_->data_, nullptr };
        node* thisNode = head_;
        while (otherNode)
        {
          thisNode->pNext_ = new node{ otherNode->data_, nullptr };
          thisNode = thisNode->pNext_;
          otherNode = otherNode->pNext_;
        }
      }
    }
  }
}
#endif
