#include "Commands.hpp"
#include <errorMessage.hpp>
#include <readingCommands.hpp>
#include <iostream>

using cString = const std::string;

void surby::Print(std::string& line, const dictOfDicts_t& dict)
{
  std::string name = surby::getArgFromStr(line);
  doPrint(std::cout, dict, name);
}

std::ostream& surby::doPrint(std::ostream& out, const dictOfDicts_t& dict, cString& name)
{
  auto list = dict.at(name);
  if (list.isEmpty())
  {
    surby::emptyMessage(out);
  }
  else
  {
    out << name;
    for (auto data: list)
    {
      out << " " << data.key_ << " " << data.value_;
    }
  }
  out << '\n';
  return out;
}

void surby::Complement(std::string& line, dictOfDicts_t& dict)
{
  std::string newDataset = surby::getArgFromStr(line);
  std::string firstDataset = surby::getArgFromStr(line);
  std::string secondDataset = surby::getArgFromStr(line);
  surby::doComplement(newDataset, firstDataset, secondDataset, dict);
}
void surby::doComplement(cString& name, cString& dat1, cString& dat2, dictOfDicts_t& dict)
{
  surby::dictOfDicts_t::Iterator it1 = dict.find(dat1);
  surby::dictOfDicts_t::Iterator it2 = dict.find(dat2);
  if ((it1 == dict.cend()) || it2 == dict.cend())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  dict_t result = dict_t(it1->value_);
  dict_t::ConstIterator dat2ListIter = it2->value_.cbegin();
  while (dat2ListIter != it2->value_.cend())
  {
    int key = dat2ListIter->key_;
    if (result.find(key) != result.end())
    {
      result.drop(key);
    }
    dat2ListIter++;
  }
  if (dict.find(name) != dict.end())
  {
    dict.drop(name);
  }
  dict.push(name, result);
}

void surby::Intersect(std::string& line, dictOfDicts_t& dict)
{
  std::string newDataset = surby::getArgFromStr(line);
  std::string firstDataset = surby::getArgFromStr(line);
  std::string secondDataset = surby::getArgFromStr(line);
  surby::doIntersect(newDataset, firstDataset, secondDataset, dict);
}
void surby::doIntersect(cString& name, cString& dat1, cString& dat2, dictOfDicts_t& dict)
{
  surby::dictOfDicts_t::Iterator it1 = dict.find(dat1);
  surby::dictOfDicts_t::Iterator it2 = dict.find(dat2);
  if ((it1 == dict.cend()) || it2 == dict.cend())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  dict_t result;
  dict_t dat1List = dict_t(it1->value_);
  auto dat1ListIter = dat1List.begin();
  dict_t dat2List = dict_t(it2->value_);
  while (dat1ListIter != dat1List.end())
  {
    if (dat2List.find(dat1ListIter->key_) != dat2List.end())
    {
      result.push(dat1ListIter->key_, dat1ListIter->value_);
    }
    dat1ListIter++;
  }
  if (dict.find(name) != dict.end())
  {
    dict.drop(name);
  }
  dict.push(name, result);
}

void surby::UnionF(std::string& line, dictOfDicts_t& dict)
{
  std::string newDataset = surby::getArgFromStr(line);
  std::string firstDataset = surby::getArgFromStr(line);
  std::string secondDataset = surby::getArgFromStr(line);
  surby::doUnion(newDataset, firstDataset, secondDataset, dict);
}
void surby::doUnion(cString& name, cString& dat1, cString& dat2, dictOfDicts_t& dict)
{
  surby::dictOfDicts_t::Iterator it1 = dict.find(dat1);
  surby::dictOfDicts_t::Iterator it2 = dict.find(dat2);
  if ((it1 == dict.cend()) || it2 == dict.cend())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  dict_t result = dict.get(dat1);
  dict_t dat2List = dict_t(it2->value_);
  auto dat2ListIter = dat2List.begin();
  while (dat2ListIter != dat2List.end())
  {
    if (result.find(dat2ListIter->key_) == result.end())
    {
      result.push(dat2ListIter->key_, dat2ListIter->value_);
    }
    dat2ListIter++;
  }
  if (dict.find(name) != dict.end())
  {
    dict.drop(name);
  }
  dict.push(name, result);
}
