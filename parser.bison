// Tokens
%token 
  INT  
  PLUS
  MINUS
  MULT
  DIV
  MOD

%token
  EQUALS
  DIFF
  LESS
  GREAT
  LESSEQUAL
  GREATEQUAL

// Operator associativity & precedence
%left EQUALS DIFF LESS GREAT LESSEQUAL GREATEQUAL
%left PLUS MINUS
%left MULT DIV MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue; 
  BoolExpr* boolValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <boolValue> boolexpr

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
BoolExpr* root;

}

%%
program: boolexpr { root = $1; }

boolexpr:
  expr {
    $$ = ast_boolexpr_leaf($1);
  }
  |
  expr EQUALS expr {
    $$ = ast_boolexpr(EQUALS,$1,$3);
  }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  } 
  |
  expr MINUS expr { 
    $$ = ast_operation(MINUS, $1, $3); 
  } 
  |
  expr MULT expr { 
    $$ = ast_operation(MULT, $1, $3); 
  } 
  |
  expr DIV expr { 
    $$ = ast_operation(DIV, $1, $3); 
  } 
  |
  expr MOD expr { 
    $$ = ast_operation(MOD, $1, $3); 
  } 
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

