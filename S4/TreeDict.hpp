#ifndef TREEDICT_HPP
#define TREEDICT_HPP
#include "BinarySearchTree.hpp"
#include <stdexcept>

namespace surby
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class TreeDict
  {
  private:
    struct Data
    {
      Key key_;
      Value value_;
    };
  public:
    using Iterator = typename BinarySearchTree< Key, Value, Compare >::Iterator;
    using ConstIterator = typename BinarySearchTree< Key, Value, Compare >::ConstIterator;

    TreeDict() = default;
    TreeDict(const TreeDict&) = default;
    TreeDict(TreeDict&&) = default;
    ~TreeDict() = default;

    TreeDict(std::initializer_list< std::pair< Key, Value > > initList):
      tree_()
    {
      for (auto&& element: initList)
      {
        push(element.first, element.second);
      }
    }

    void push(const Key& key, const Value& value)
    {
      tree_.push(key, value);
    }

    Value& get(const Key& key)
    {
      Iterator result = find(key);
      return result->value_;
    }

    void drop(const Key& key)
    {
      tree_.erase(key);
    }

    bool isEmpty() const
    {
      return this->tree_.isEmpty();
    }

    void clear()
    {
      this->tree_.clear();
    }

    Iterator find(const Key& key) const
    {
      return this->tree_.find(key);
    }

    Value& at(const Key& key)
    {
      auto it = this->find(key);
      if (it == this->end())
      {
        throw std::overflow_error("at: key is not exist");
      }
      return it->value_;
    }

    Value at(const Key& key) const
    {
      auto it = find(key);
      if (it == cend())
      {
        throw std::out_of_range("at: key is not exist");
      }
      return it->value_;
    }

    Iterator begin()
    {
      return this->tree_.begin();
    }
    Iterator end()
    {
      return this->tree_.end();
    }
    ConstIterator cend() const
    {
      return this->tree_.cend();
    }
    ConstIterator cbegin() const
    {
      return this->tree_.cbegin();
    }
  private:
    BinarySearchTree< Key, Value, Compare > tree_;
  };
}
#endif
