%{
#include <string>
#include "expression.h"
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
  rootExpression->print();
  std::cout << std::endl;
}
