%{
#include <string>
#include <memory>
#include "expression.h"
#include "ids.h"
#include "lambdaparser.h"

extern "C" int yywrap() { return 1; }
extern Expression *parsedExpression;
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
   * If parsedExpression is null, we know that 
   * there was a parser error.
   */
  if (parsedExpression) {
    while (parsedExpression->willReduce()) {
      auto oldParsedExpression = parsedExpression;
      parsedExpression = parsedExpression->reduce();
      delete oldParsedExpression;
    }

    parsedExpression->print();
    std::cout << std::endl;
  }
}
