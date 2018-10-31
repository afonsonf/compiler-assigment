// Tokens
%token
  VARNAME
  VARINT
  SEMICOLON
  ATTR
  NOTYPE

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

%token
  ANDLOGIC
  ORLOGIC

// Operator associativity & precedence
%left ANDLOGIC ORLOGIC
%left EQUALS DIFF LESS GREAT LESSEQUAL GREATEQUAL
%left PLUS MINUS
%left MULT DIV MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* varname;
  Expr* exprValue;
  BoolExpr* boolValue;
  Var* varvalue;
  Attrib *attribvalue;
  Cmd *cmdvalue;

}

%type <intValue> INT
%type <exprValue> expr
%type <boolValue> boolexpr
%type <varvalue> VAR
%type <attribvalue> attrib
%type <varname> VARNAME
%type <cmdvalue> cmd


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
Cmd* root;

}

%%
program: cmd { root = $1; }

cmd:
  attrib {
    $$ = ast_cmd_attr($1);
  }

attrib:
  VAR ATTR expr SEMICOLON{
    $$ = ast_attrib($1,$3);
  }

VAR:
  VARINT VARNAME{
    $$ = ast_var(VARINT,$2);
  }
  |
  VARNAME{
    $$ = ast_var(NOTYPE, $1);
  }

boolexpr:
  expr {
    $$ = ast_boolexpr_leaf($1);
  }
  |
  expr EQUALS expr {
    $$ = ast_boolexpr(EQUALS,$1,$3);
  }
  |
  expr DIFF expr {
    $$ = ast_boolexpr(DIFF,$1,$3);
  }
  |
  expr LESS expr {
    $$ = ast_boolexpr(LESS,$1,$3);
  }
  |
  expr GREAT expr {
    $$ = ast_boolexpr(GREAT,$1,$3);
  }
  |
  expr LESSEQUAL expr {
    $$ = ast_boolexpr(LESSEQUAL,$1,$3);
  }
  |
  expr GREATEQUAL expr {
    $$ = ast_boolexpr(GREATEQUAL,$1,$3);
  }
  |
  boolexpr ANDLOGIC boolexpr {
    $$ = ast_boolexpr_complex(ANDLOGIC, $1, $3);
  }
  |
  boolexpr ORLOGIC boolexpr {
    $$ = ast_boolexpr_complex(ORLOGIC, $1, $3);
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
