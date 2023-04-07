#ifndef EXPRESSIONELEMENT_HPP
#define EXPRESSIONELEMENT_HPP

namespace surby
{
  enum class TypeOfData
  {
    CHAR,
    LLINT,
    UNDEF
  };
  class expressionElement
  {
  public:
    expressionElement(char);
    expressionElement();
    expressionElement(long long int);
    TypeOfData getType() const;
    char getOperation() const;
    long long int getNumber() const;
  private:
    union
    {
      char operation_;
      long long int number_;
    };
    TypeOfData type_;
  };
}
#endif
