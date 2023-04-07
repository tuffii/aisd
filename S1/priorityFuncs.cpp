#include "priorityFuncs.hpp"
#include <string>

namespace surby
{
  bool isOperationPriorityFirstLvl(char operation);
  bool isOperationPrioritySecondLvl(char operation);
  bool isOperationPriorityThirdLvl(char operation);
  int priority(const surby::expressionElement& expressionElement);
  int priority(char operation);
}

bool surby::isOperationPriorityFirstLvl(const char operation)
{
  return (operation == '*' || operation == '/' || operation == '%');
}
bool surby::isOperationPrioritySecondLvl(const char operation)
{
  return (operation == '+' || operation == '-');
}
bool surby::isOperationPriorityThirdLvl(const char operation)
{
  return (operation == '(' || operation == ')');
}

int surby::priority(const surby::expressionElement& expressionElement)
{
  if (expressionElement.getType() != surby::TypeOfData::CHAR)
  {
    throw std::overflow_error("not operationt Priority\n");
  }
  char operation = expressionElement.getOperation();
  return priority(operation);
}
int surby::priority(const char operation)
{
  if (isOperationPriorityThirdLvl(operation))
  {
    return 2;
  }
  else if (isOperationPrioritySecondLvl(operation))
  {
    return 1;
  }
  else if (!isOperationPriorityFirstLvl(operation))
  {
    throw std::overflow_error("not operationt Priority\n");
  }
  return 0;
}

bool surby::isFirstMorePriority(const surby::expressionElement& first, const surby::expressionElement& second)
{
  return (priority(first) >= priority(second));
}
bool surby::isOperation(const char simv)
{
  return (isMathOperation(simv) || isOperationPriorityThirdLvl(simv));
}
bool surby::isMathOperation(const char simv)
{
  return (isOperationPriorityFirstLvl(simv) || isOperationPrioritySecondLvl(simv));
}
