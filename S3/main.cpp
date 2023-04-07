#include <iostream>
#include <fstream>
#include <functional>
#include "Commands.hpp"
#include <Dictionary.hpp>
#include <readingCommands.hpp>
#include <errorMessage.hpp>

int main(int argc, char** argv)
{
  using string_dict_funcs = std::function< void(std::string&, surby::dictOfLists_t&) >;
  using string_const_dict_funcs = std::function< std::ostream& (std::string&, const surby::dictOfLists_t&, std::ostream&) >;
  try
  {
    if (argc != 2)
    {
      std::cerr << "Incorrect number of arguments";
      return 1;
    }
    std::ifstream fInput(argv[1]);
    if (!fInput)
    {
      std::cerr << "File open error";
      return 1;
    }
    surby::dictOfLists_t dictionaries;
    std::ifstream in(argv[1]);
    try
    {
      if (!in.is_open())
      {
        throw std::overflow_error("file is not open");
      }
      surby::readAllLists(dictionaries, in);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what();
      return -1;
    }
    surby::Dictionary< std::string, string_dict_funcs, surby::lessString > commands
    {
      {"replace", surby::replace},
      {"remove", surby::remove},
      {"concat", surby::concat},
    };
    surby::Dictionary< std::string, string_const_dict_funcs, surby::lessString > constCommands
    {
      {"print", surby::print},
      {"equal", surby::equal}
    };
    while (!std::cin.eof())
    {
      try
      {
        std::string line;
        std::getline(std::cin, line, '\n');

        std::string commandName = surby::getArgFromStr(line);
        if (!commandName.empty())
        {
          try
          {
            commands.at(commandName)(line, dictionaries);
          }
          catch (const std::out_of_range&)
          {
            constCommands.at(commandName)(line, dictionaries, std::cout);
          }
        }
      }
      catch (const std::exception&)
      {
        surby::invalidCommandMessage(std::cout);
        std::cout << '\n';
      }
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
