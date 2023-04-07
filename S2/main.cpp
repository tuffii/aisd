#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "Commands.hpp"
#include <errorMessage.hpp>
#include <readingCommands.hpp>

using string_dict_funcs = std::function< void(std::string&, surby::dictOfDicts_t&) >;
using string_const_dict_funcs = std::function< void(std::string&, const surby::dictOfDicts_t&) >;

int main(int argc, char** argv)
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Incorrect number of arguments");
    }
    std::ifstream in(argv[1]);
    if (!in)
    {
      throw std::invalid_argument("Incorrect number of arguments");
    }
    surby::dictOfDicts_t dictionaries;
    std::string line;
    while (std::getline(in, line))
    {
      if (!line.empty())
      {
        std::string name = surby::getArgFromStr(line);
        surby::dict_t dictionary;
        while (line[0] != '\0')
        {
          std::string arg = surby::getArgFromStr(line);
          int key = surby::strToInt(arg, 0);
          arg = surby::getArgFromStr(line);
          dictionary.push(key, arg);
        }
        dictionaries.push(name, dictionary);
      }
    }
    surby::Dictionary< std::string, string_dict_funcs, std::less < std::string > > commands
    {
      {"complement", surby::Complement},
      {"intersect", surby::Intersect},
      {"union", surby::UnionF}
    };
    surby::Dictionary< std::string, string_const_dict_funcs, std::less < std::string > > constCommands
    {
      {"print", surby::Print}
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
          catch (std::out_of_range&)
          {
            constCommands.at(commandName)(line, dictionaries);
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
  catch (std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (std::out_of_range& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
