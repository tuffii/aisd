#include "Commands.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <readingCommands.hpp>
#include <errorMessage.hpp>

void surby::readAllLists(dictOfLists_t& lists, std::ifstream& in)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (!line.empty())
    {
      std::string name = surby::getArgFromStr(line);
      surby::bidirList list;
      while (line[0] != '\0')
      {
        std::string arg = surby::getArgFromStr(line);
        int key = surby::strToInt(arg, 0);
        list.pushBack(key);
      }
      lists.push(name, list);
    }
  }
}

std::ostream& surby::print(std::string& str, const dictOfLists_t& lists, std::ostream& out)
{
  std::string name = surby::getArgFromStr(str);
  surby::doPrint(out, lists, name);
  return out;
}
std::ostream& surby::doPrint(std::ostream& out, const dictOfLists_t& lists, cString& name)
{
  auto list = lists.at(name);
  if (list.isEmpty())
  {
    surby::emptyMessage(out);
    out << '\n';
    return out;
  }
  out << name;
  for (auto it = list.begin(); it != list.end(); it++)
  {
    out << ' ' << *it;
  }
  out << '\n';
  return out;
}

void surby::replace(std::string& line, dictOfLists_t& lists)
{
  std::string nameOfList = surby::getArgFromStr(line);
  long long int secondIntArg = std::stoll(surby::getArgFromStr(line));
  std::string thirdArg = surby::getArgFromStr(line);
  surby::doReplace(nameOfList, secondIntArg, thirdArg, lists);
}
void surby::doReplace(cString& firstArg, const long long secondArg, cString& thirdArg, dictOfLists_t& lists)
{
  auto listIter = lists.find(firstArg);

  if (listIter == lists.end())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  if (surby::isNumber(thirdArg))
  {
    long long int thirdIntArg = std::stoll(thirdArg);
    for (auto it = listIter->value_.begin(); it != listIter->value_.end(); it++)
    {
      if (*it == secondArg)
      {
        *it = thirdIntArg;
      }
    }
  }
  else
  {
    auto changeListIter = lists.find(thirdArg);
    if (changeListIter == lists.end())
    {
      throw std::overflow_error("<INVALID COMMAND>");
    }
    auto it = listIter->value_.begin();
    while (it != listIter->value_.end())
    {
      if (*it == secondArg)
      {
        listIter->value_.erase(it);
        for (auto iter = changeListIter->value_.begin(); iter != changeListIter->value_.end(); iter++)
        {
          listIter->value_.insert(*iter, it);
        }
      }
      else if (it != listIter->value_.end())
      {
        it++;
      }
    }
  }
}

void surby::remove(std::string& line, dictOfLists_t& lists)
{
  std::string firstArg = surby::getArgFromStr(line);
  std::string secondArg = surby::getArgFromStr(line);
  surby::doRemove(firstArg, secondArg, lists);
}
void surby::doRemove(cString& firstArg, cString& secondArg, dictOfLists_t& lists)
{
  auto listIter = lists.find(firstArg);

  if (listIter == lists.end())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  if (surby::isNumber(secondArg))
  {
    long long int secondIntArg = std::stoll(secondArg);
    auto it = listIter->value_.begin();
    while (it != listIter->value_.end())
    {
      if (*it == secondIntArg)
      {
        listIter->value_.erase(it);
      }
      else if (it != listIter->value_.end())
      {
        it++;
      }
    }
  }
  else
  {
    auto toDeliteListIter = lists.find(secondArg);
    if (toDeliteListIter == lists.end())
    {
      throw std::overflow_error("<INVALID COMMAND>");
    }
    auto it = listIter->value_.begin();
    while (it != listIter->value_.end())
    {
      bool fl = 0;
      for (auto iter = toDeliteListIter->value_.begin(); iter != toDeliteListIter->value_.end(); iter++)
      {
        if (*iter == *it)
        {
          listIter->value_.erase(it);
          fl = 1;
        }
      }
      if (!fl && it != listIter->value_.end())
      {
        it++;
      }
    }
  }
}

void surby::concat(std::string& line, dictOfLists_t& lists)
{
  std::string name = surby::getArgFromStr(line);
  surby::bidirList list;
  size_t count = 0;
  while (line[0] != '\0')
  {
    std::string nameConcatList = surby::getArgFromStr(line);
    list = surby::doConcatList(list, lists.at(nameConcatList));
    count++;
  }
  if (count < 2)
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  lists.push(name, list);
}
surby::bidirList surby::doConcatList(const surby::bidirList& first, const surby::bidirList& second)
{
  surby::bidirList result(first);

  for (auto it = second.begin(); it != second.end(); it++)
  {
    result.pushBack(*it);
  }
  return result;
}

std::ostream& surby::equal(std::string& line, const dictOfLists_t& lists, std::ostream& out)
{
  auto firstlistIter = lists.find(surby::getArgFromStr(line));
  if (firstlistIter == lists.cend())
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  size_t count = 0;
  while (line[0] != '\0')
  {
    count++;
    auto otherlistIter = lists.find(surby::getArgFromStr(line));
    if (firstlistIter->value_ != otherlistIter->value_)
    {
      out << "<FALSE>\n";
      return out;
    }
  }
  if (!count)
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
  out << "<TRUE>\n";
  return out;
}
