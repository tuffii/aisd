#ifndef READINGCOMMANDS_HPP
#define READINGCOMMANDS_HPP
#include <string>

namespace surby
{
  std::string getArgFromStr(std::string&);
  long long int strToLLInt(const std::string&, size_t);
  int strToInt(const std::string&, size_t);
  bool isNumber(const std::string& str);
}
#endif
