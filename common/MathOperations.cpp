#include "MathOperations.hpp"
#include <limits>
#include <stdexcept>

const constexpr long long int min_int = std::numeric_limits< long long int >::min();
const constexpr long long int max_int = std::numeric_limits< long long >::max();

long long int surby::calc(const char operation, const long long int a, const long long int b)
{
  long long int result = 0;
  if (operation == '+')
  {
    result = summ(a, b);
  }
  else if (operation == '-')
  {
    result = sub(a, b);
  }
  else if (operation == '*')
  {
    result = multipl(a, b);
  }
  else if (operation == '/')
  {
    result = division(a, b);
  }
  else if (operation == '%')
  {
    result = mod(a, b);
  }
  return result;
}

long long int surby::sub(const long long int a, const long long int b)
{
  if ((b > 0 && a < min_int + b) || (b < 0 && a > min_int + b))
  {
    throw std::overflow_error("owerflow!");
  }
  return a - b;
}

long long int surby::summ(const long long int a, const long long int b)
{
  if (a > 0 && b > 0)
  {
    if (a > max_int - b)
    {
      throw std::overflow_error("owerflow!");
    }
  }
  else if (a < 0 && b < 0)
  {
    if (a < min_int - b)
    {
      throw std::overflow_error("owerflow!");
    }
  }
  return a + b;
}

long long int surby::multipl(const long long int a, const long long int b)
{
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
  {
    if (a > max_int / b)
    {
      throw std::overflow_error("overflow!");
    }
  }

  else if ((a < 0 && b > 0) || (a > 0 && b < 0))
  {
    if (a < min_int / b)
    {
      throw std::overflow_error("Overflow!");
    }
  }
  return a * b;
}

long long int surby::division(const long long int a, const long long int b)
{
  if (b == 0)
  {
    throw std::overflow_error("Divide by zero exception");
  }
  return a / b;
}

long long int surby::mod(const long long int a, const long long int b)
{
  if (b == 0)
  {
    throw std::overflow_error("Divide by zero exception");
  }
  if (a > 0)
  {
    return a % b;
  }
  else
  {
    return (a + b * (std::abs(a) / b + 1));
  }
}
