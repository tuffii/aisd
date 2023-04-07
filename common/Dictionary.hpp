#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include "ForwardList.hpp"

namespace surby
{
  template < typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
    struct Data
    {
      Key key_;
      Value value_;
    };

    using Iterator = typename ForwardList< Data >::Iterator;
    using ConstIterator = typename ForwardList< Data >::ConstIterator;

    Dictionary() = default;
    ~Dictionary() = default;
    Dictionary(std::initializer_list< std::pair< Key, Value > >);

    void push(const Key&, const Value&);
    const Value& get(const Key&) const;
    void drop(const Key&);
    bool isEmpty() const;
    Iterator find(const Key&) const;
    Value at(const Key&) const;

    Iterator begin();
    Iterator end();
    ConstIterator cend() const;
    ConstIterator cbegin() const;
  private:
    ForwardList< Data > dataList_;
    Compare comparator_;
  };

  template< typename Key, typename Value, typename Compare >
  using Iterator = typename ForwardList< typename Dictionary< Key, Value, Compare >::Data >::Iterator;

  template< typename Key, typename Value, typename Compare >
  using ConstIterator = typename ForwardList< typename Dictionary< Key, Value, Compare >::Data >::ConstIterator;

  template< typename Key, typename Value, typename Compare >
  Iterator< Key, Value, Compare > surby::Dictionary< Key, Value, Compare >::begin()
  {
    return this->dataList_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  Iterator< Key, Value, Compare > surby::Dictionary< Key, Value, Compare >::end()
  {
    return this->dataList_.end();
  }

  template< typename Key, typename Value, typename Compare >
  ConstIterator< Key, Value, Compare > surby::Dictionary< Key, Value, Compare >::cend() const
  {
    return this->dataList_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  ConstIterator< Key, Value, Compare > surby::Dictionary< Key, Value, Compare >::cbegin() const
  {
    return this->dataList_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  Iterator< Key, Value, Compare > surby::Dictionary< Key, Value, Compare >::find(const Key& key) const
  {
    for (auto it = this->dataList_.begin(); it != this->dataList_.end(); it++)
    {
      if (it->key_ == key)
      {
        return it;
      }
    }
    return dataList_.end();
  }

  template< typename Key, typename Value, typename Compare >
  Value surby::Dictionary< Key, Value, Compare >::at(const Key& key) const
  {
    auto it = this->find(key);
    if (it == this->cend())
    {
      throw std::out_of_range("at: key is not exist");
    }
    return it->value_;
  }

  template < typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(const Key& key, const Value& value)
  {
    if (dataList_.isEmpty())
    {
      dataList_.push(Data{ key, value });
      return;
    }
    else
    {
      for (auto it = dataList_.begin(); it != dataList_.end(); it++)
      {
        if (it->key_ == key)
        {
          throw std::out_of_range("key is already exist");
        }

        if (!comparator_(it->key_, key))
        {
          dataList_.insert(Data{key, value}, it);
          return;
        }
      }
    }
    dataList_.insert(Data{ key, value }, end());
  }

  template< typename Key, typename Value, typename Compare >
  const Value& Dictionary< Key, Value, Compare >::get(const Key& key) const
  {
    for (auto it = dataList_.begin(); it != dataList_.end(); it++)
    {
      if (it->key_ == key)
      {
        return it->value_;
      }
    }
    throw std::out_of_range("key is not exist");
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::drop(const Key& key)
  {
    for (auto it = dataList_.begin(); it != dataList_.end(); it++)
    {
      if (it->key_ == key)
      {
        dataList_.erase(it);
        return;
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::isEmpty() const
  {
    return dataList_.isEmpty();
  }

  template< typename Key, typename Value, typename Compare >
  surby::Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< std::pair < Key, Value > > list)
  {
    for (auto&& pair: list)
    {
      push(pair.first, pair.second);
    }
  }
}
#endif
