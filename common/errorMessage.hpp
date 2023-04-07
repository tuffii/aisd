#ifndef ERRORMESSAGE_HPP
#define ERRORMESSAGE_HPP
#include <iosfwd>
namespace
  surby
{
  std::ostream& emptyMessage(std::ostream& out);
  std::ostream& invalidCommandMessage(std::ostream& out);
}
#endif
