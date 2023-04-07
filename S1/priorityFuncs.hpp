#ifndef PRIORITYFUNCS_HPP
#define PRIORITYFUNCS_HPP
#include "queue.hpp"
#include "stack.hpp"
#include "ExpressionElement.hpp"
namespace surby
{
  bool isFirstMorePriority(const expressionElement&, const expressionElement&);

  bool isOperation(char simv);
  bool isMathOperation(char simv);

  template < typename T >
  void checkPriorityInStack(Stack< T >& stack, Queue< T >& queue, const char simv)
  {
    expressionElement exprSimv(simv);
    while (stack.getSize() >= 1 && isFirstMorePriority(exprSimv, (stack.getBack())))
    {
      queue.pushBack(stack.getBack());
      stack.popBack();
    }
  }
}
#endif
