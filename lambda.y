%{
#include <string>
#include "expression.h"

Expression *rootExpression = nullptr;

extern int yylex();

void yyerror(const char *s) { 
  printf("Parse error: %s\n", s);
}

%}

%union {
  Expression *expr;
  Ids *ids;
  std::string *id;
  int token;
}


%token <token> LAMBDA
%token <token> DOT
%token <id> ID
%token <token> OPENPAREN
%token <token> CLOSEPAREN

%type <ids> ids
%type <expr> expression

%start sexpression

%%

sexpression: expression { rootExpression = $1; };

expression : { $$ = new Expression(); }
           | ids { $$ = $1; }
           | LAMBDA ids DOT expression { $$ = new Function($2, $4); }
           | OPENPAREN expression CLOSEPAREN expression { $$ = new Application($2, $4); }
     ;

ids  : ID { $$ = new Ids($1); }
     | ids ID { $1->add($2); }
     ;
%%
