%{
#include <string>
#include "expression.h"
#include <memory>

Expression* parsedExpression = nullptr;

extern int yylex();

extern void yyterminate();

void yyerror(const char *s) { 
  printf("Parse error: %s\n", s);
}

%}

%union {
  Expression *expr;
  Application *application;
  Function *function;
  std::string *id;
  int token;
}


%token <token> LAMBDA
%token <token> DOT
%token <id> ID
%token <token> OPENPAREN
%token <token> CLOSEPAREN

%type <expr> expression
%type <application> application
%type <function> function

%start start

%%

start      : expression { parsedExpression = $1; };

expression : ID { $$ = new Id($1); delete $1;}
           | function { $$ = $1; }
           | application { $$ = $1; }
           | OPENPAREN expression CLOSEPAREN { $$ = $2; }
           ;

function   : OPENPAREN LAMBDA ID DOT expression CLOSEPAREN 
             { $$ = new Function(new Id($3), $5); delete $3; }
           ;

application: OPENPAREN expression expression CLOSEPAREN
             { $$ = new Application($2, $3); }
           ;
%%
