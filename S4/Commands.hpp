#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "TreeDict.hpp"

namespace surby
{
  using lessString = std::less< std::string >;
  using dict_t = TreeDict< int, std::string, std::less< int > >;
  using dictOfDicts_t = TreeDict< std::string, dict_t, lessString >;

  std::ostream& doPrint(std::ostream&, const dictOfDicts_t&, const std::string&);
  void doComplement(const std::string&, const std::string&, const std::string&, dictOfDicts_t&);
  void doIntersect(const std::string&, const std::string&, const std::string&, dictOfDicts_t&);
  void doUnion(const std::string&, const std::string&, const std::string&, dictOfDicts_t&);

  void Print(std::string&, const dictOfDicts_t&, std::ostream&);
  void Complement(std::string&, dictOfDicts_t&);
  void Intersect(std::string&, dictOfDicts_t&);
  void UnionF(std::string&, dictOfDicts_t&);
}
#endif
