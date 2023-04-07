#include <iostream>
#include <string>
#include <fstream>
#include "calcExpression.hpp"

int main(int argc, char** argv)
{
  std::ifstream in;
  try
  {
    if (argc == 2)
    {
      std::string fileName = argv[1];
      in.open(fileName);
      surby::calcExpressions(in, std::cout);
    }
    else if (argc < 2)
    {
      surby::calcExpressions(std::cin, std::cout);
    }
    else if (argc > 2)
    {
      std::cerr << "too many argc" << std::endl;
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 2;
  }
  return 0;
}
