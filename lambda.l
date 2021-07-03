%{
#include <string>
#include "expression.h"
#include "freevariables.h"
#include "lambdaparser.h"

extern "C" int yywrap() { return 1; }
extern Expression *rootExpression;
%}

%%

[ \t\n] { ; }
"\\"    { return LAMBDA; }
"."     { return DOT; }
[a-z]   { yylval.id = new std::string(yytext, yyleng); return ID; }
"("     { return OPENPAREN; }
")"     { return CLOSEPAREN; }
.       { printf("Unknown token.\n"); yyterminate(); }

%%

int main() {
  yyparse();
  /*
   * If rootExpression is null, we know that 
   * there was a parser error.
   */
  if (rootExpression) {
    rootExpression->print();
    std::cout << std::endl;
    std::cout << rootExpression->free() << std::endl;

    const auto x = new std::string("x");
    const auto y = new std::string("y");
    const auto z = new std::string("z");
    const auto a = new std::string("a");
    const auto b = new std::string("b");
    const auto idB = new Id(b);

    std::cout << "Is x free? " << rootExpression->free().isFree(Id(x)) << std::endl;
    std::cout << "Is y free? " << rootExpression->free().isFree(Id(y)) << std::endl;
    std::cout << "Is z free? " << rootExpression->free().isFree(Id(z)) << std::endl;

    /*
    const auto oldRootExpression = rootExpression;
    rootExpression = rootExpression->rename(Id(a), idB);
    delete oldRootExpression;
    */

    auto reducedRoot = rootExpression->reduce();
    while (reducedRoot) {
      std::cout << "Reduced: " << std::endl;
      reducedRoot->print();
      std::cout << std::endl;
      reducedRoot = reducedRoot->reduce();
    }

    //rootExpression->firstFree();

    delete a;
    delete b;
    delete x;
    delete y;
    delete z;
    delete idB;
  }
}
