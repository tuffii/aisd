#include "calcExpression.hpp"
#include "ExpressionElement.hpp"
#include "operationsWithExpression.hpp"
#include "queue.hpp"
#include <string>
#include <iostream>

std::ostream& surby::calcExpressions(std::istream& stream, std::ostream& out)
{
  std::string answer;
  std::string expression;
  while (std::getline(stream, expression))
  {
    surby::Queue< surby::expressionElement > postfixExpression;
    surby::getPostfixExpression< surby::expressionElement >(expression, postfixExpression);
    if (!postfixExpression.isEmpty())
    {
      if (answer.empty())
      {
        answer = surby::calcPostfixEpression(postfixExpression);
      }
      else
      {
        answer = surby::calcPostfixEpression(postfixExpression) + " " + answer;
      }
    }
  }
  out << answer << std::endl;
  return out;
}
