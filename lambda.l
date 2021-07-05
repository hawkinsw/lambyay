%{
#include <string>
#include "expression.h"
#include "ids.h"
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
    std::cout << "Parsed expression: ";
    rootExpression->print();
    std::cout << std::endl;

    std::cout << "Bound variables: ";
    auto boundIds = rootExpression->bound();
    std::cout << boundIds << std::endl;
    std::cout << "First not in: ";
    boundIds.firstNotIn().print();
    std::cout << std::endl;

    Expression *reducedRoot = rootExpression->reduce();
    std::cout << "Reduced expression: ";
    reducedRoot->print();
    std::cout << std::endl;

    if (rootExpression != reducedRoot)
      delete reducedRoot;
    delete rootExpression;

  }
}
