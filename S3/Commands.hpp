#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <Dictionary.hpp>
#include <bidirectionalList.hpp>
#include <string>
#include <iosfwd>
namespace surby
{
  using lessString = std::less< std::string >;
  using bidirList = BidirectionalList< long long >;
  using dictOfLists_t = Dictionary< std::string, bidirList, lessString >;
  using cString = const std::string;

  void readAllLists(dictOfLists_t& dictionaries, std::ifstream& in);

  surby::bidirList doConcatList(const surby::bidirList&, const surby::bidirList&);

  std::ostream& print(std::string&, const dictOfLists_t&, std::ostream&);
  void replace(std::string&, dictOfLists_t&);
  void remove(std::string&, dictOfLists_t&);
  void concat(std::string&, dictOfLists_t&);
  std::ostream& equal(std::string&, const dictOfLists_t&, std::ostream&);

  std::ostream& doPrint(std::ostream&, const dictOfLists_t&, cString&);
  void doReplace(cString&, long long, cString&, dictOfLists_t&);
  void doRemove(cString&, cString&, dictOfLists_t&);
}
#endif
