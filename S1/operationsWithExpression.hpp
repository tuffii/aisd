#ifndef OPERATIONSWITHXPRESSION_HPP
#define OPERATIONSWITHXPRESSION_HPP
#include <string>
#include <iosfwd>
#include "queue.hpp"
#include "stack.hpp"
#include "priorityFuncs.hpp"
#include <MathOperations.hpp>
#include <readingCommands.hpp>

namespace surby
{
  template< typename T >
  std::string calcPostfixEpression(surby::Queue< T >& postfixExpression)
  {
    surby::Queue< surby::expressionElement > expression;
    surby::Stack< surby::expressionElement > stack;

    while (postfixExpression.getSize() != 0)
    {
      expression.pushFront(postfixExpression.getBack());
      postfixExpression.popBack();
    }

    if (expression.getSize() == 1)
    {
      return std::to_string(expression.getFront().getNumber());
    }

    else
    {
      while (expression.getSize() != 1)
      {
        if (expression.getFront().getType() != surby::TypeOfData::CHAR)
        {
          stack.pushBack(expression.getFront());
          expression.popFront();
        }
        else
        {
          char operation = expression.getFront().getOperation();
          expression.popFront();
          long long int a = stack.getBack().getNumber();
          stack.popBack();
          long long int b = stack.getBack().getNumber();
          stack.popBack();
          long long int answer = calc(operation, b, a);
          expression.pushFront(answer);
          while (!stack.isEmpty())
          {
            expression.pushFront(stack.getBack());
            stack.popBack();
          }
        }
      }
      if (expression.getFront().getType() == surby::TypeOfData::CHAR)
      {
        char operation = expression.getFront().getOperation();
        long long int a = stack.getBack().getNumber();
        stack.popBack();
        long long int b = stack.getBack().getNumber();
        stack.popBack();
        long long int answer = calc(operation, b, a);
        expression.pushFront(answer);
      }
    }
    postfixExpression.clear();
    return std::to_string(expression.getFront().getNumber());
  }

  template < typename T >
  void pushRemainingOperationFromStack(Stack< T >& stack, Queue< T >& queue)
  {
    if (!stack.isEmpty())
    {
      for (long long int i = stack.getSize() - 1; i >= 0; --i)
      {
        queue.pushBack(stack.getBack());
        stack.popBack();
      }
      stack.clear();
    }
  }

  template < typename T >
  void getPostfixExpression(const std::string& expression, surby::Queue< T >& postfixExpression)
  {
    surby::Queue< surby::expressionElement > queue;
    surby::Stack< surby::expressionElement > stack;
    for (size_t i = 0; i < expression.size(); i++)
    {
      char simv = expression[i];

      if (simv != '\n')
      {
        {
          if (isOperation(simv))
          {
            if (isMathOperation(simv))
            {
              checkPriorityInStack(stack, queue, simv);
              stack.pushBack(simv);
            }
            else
            {
              if (simv == '(')
              {
                stack.pushBack(simv);
              }
              else
              {
                if (simv == ')')
                {
                  long long int k = stack.getSize() - 1;
                  for (long long int i = k; stack.getBack().getOperation() != '('; i--)
                  {
                    queue.pushBack(stack.getBack());
                    stack.popBack();
                  }
                  stack.popBack();
                }
              }
            }
          }
          else if (std::isdigit(simv))
          {
            long long int value = strToLLInt(expression, i);
            while (std::isdigit(expression[i]))
            {
              i++;
            }
            i--;
            queue.pushBack(value);
          }
          if (expression[i + 1] == '\0')
          {
            pushRemainingOperationFromStack(stack, queue);
          }
        }
      }
    }
    while (!queue.isEmpty())
    {
      postfixExpression.pushFront(queue.getBack());
      queue.popBack();
    }
  }
}
#endif
