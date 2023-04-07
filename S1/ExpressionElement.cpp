#include "ExpressionElement.hpp"
#include <stdexcept>

surby::expressionElement::expressionElement(const char simv)
{
  type_ = TypeOfData::CHAR;
  operation_ = simv;
}

surby::expressionElement::expressionElement(const long long int value)
{
  type_ = TypeOfData::LLINT;
  number_ = value;
}

surby::expressionElement::expressionElement()
{
  type_ = TypeOfData::UNDEF;
}

surby::TypeOfData surby::expressionElement::getType() const
{
  return type_;
}

char surby::expressionElement::getOperation() const
{
  if (getType() != TypeOfData::CHAR)
  {
    throw std::overflow_error("getOperation not CHAR");
  }
  return operation_;
}

long long int surby::expressionElement::getNumber() const
{
  if (getType() != TypeOfData::LLINT)
  {
    throw std::overflow_error("getNumber not INT");
  }
  return number_;
}
