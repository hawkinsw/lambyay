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
  }

}
