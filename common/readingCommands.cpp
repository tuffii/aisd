#include "readingCommands.hpp"

std::string surby::getArgFromStr(std::string& line)
{
  std::string word;
  size_t i = 0;
  while (i < line.size() && (line[i] == ' '))
  {
    i++;
  }
  while (i < line.size() && line[i] != ' ')
  {
    word += line[i];
    i++;
  }
  if (line[i] == '\0' || i == line.size())
  {
    line = '\0';
  }
  else
  {
    line = line.substr(i + 1, line.size());
  }
  return word;
}

int surby::strToInt(const std::string& str, const size_t startNumber)
{
  std::string intStr = str.substr(startNumber, str.find(' ', startNumber));
  return std::stoi(intStr);
}

long long int surby::strToLLInt(const std::string& str, const size_t startNumber)
{
  std::string intStr = str.substr(startNumber, str.find(' ', startNumber));
  return std::stoll(intStr);
}

bool surby::isNumber(const std::string& str)
{
  size_t a = 0;
  if (str[a] == '-' || str[a] == '+')
  {
    a++;
  }
  while (a < str.size())
  {
    if (!std::isdigit(str[a]))
    {
      return 0;
    }
    a++;
  }
  return 1;
}
