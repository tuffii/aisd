#include "errorMessage.hpp"
#include <iostream>
std::ostream& surby::emptyMessage(std::ostream& out)
{
  if (out.good())
  {
    out << "<EMPTY>";
  }
  return out;
}

std::ostream& surby::invalidCommandMessage(std::ostream& out)
{
  if (out.good())
  {
    out << "<INVALID COMMAND>";
  }
  return out;
}
