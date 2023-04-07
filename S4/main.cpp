#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "Commands.hpp"
#include <errorMessage.hpp>
#include <readingCommands.hpp>

int main(int argc, char** argv)
{
  using string_dict_funcs = std::function< void(std::string&, surby::dictOfDicts_t&) >;
  using string_dict_const_funcs = std::function< void(std::string&, const surby::dictOfDicts_t&, std::ostream&) >;
  try
  {
    if (argc != 2)
    {
      throw std::overflow_error("Incorrect number of arguments\n");
    }
    std::ifstream in(argv[1]);
    if (!in)
    {
      throw std::overflow_error("file is not open\n");
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
    surby::TreeDict< std::string, string_dict_funcs, std::less < std::string > > commands
    {
      {"complement", surby::Complement},
      {"intersect", surby::Intersect},
      {"union", surby::UnionF}
    };
    surby::TreeDict< std::string, string_dict_const_funcs, std::less < std::string > > constcommands
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
          catch (const std::exception&)
          {
            constcommands.at(commandName)(line, dictionaries, std::cout);
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
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
