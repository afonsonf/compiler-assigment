// Tokens

%token
  SEMICOLON
  COMMA
  OPENPAR
  CLOSEPAR
  OPENCHAV
  CLOSECHAV

%token
  WHILE
  FOR
  PRINTF
  SCANF

%token
  VARNAME
  STRING
  VARINT
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
%left SEMICOLON
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
  char* strvalue;

  Expr* exprValue;
  BoolExpr* boolValue;
  Var* varvalue;
  VarList *varlistvalue;

  Attrib *attribvalue;
  While *whilevalue;
  For *forvalue;
  Printf *printfvalue;
  Scanf *scanfvalue;

  Cmd *cmdvalue;
  CmdList *cmdlistvalue;
}

%type <intValue> INT
%type <strvalue> STRING
%type <varname> VARNAME
%type <varvalue> VARTYPE
%type <varvalue> VARNOTYPE
%type <varlistvalue> varlist

%type <exprValue> expr
%type <boolValue> boolexpr

%type <attribvalue> attrib
%type <whilevalue> while
%type <forvalue> for
%type <printfvalue> printf
%type <scanfvalue> scanf

%type <cmdvalue> cmd
%type <cmdlistvalue> cmdlist

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
CmdList* root;

}

%%
program: cmdlist { root = $1; }

cmdlist:
  cmd cmdlist {
    $$ = ast_cmdlist($1,$2);
  }
  |
  cmd {
    $$ = ast_cmdlist($1,NULL);
  }

cmd:
  attrib {
    $$ = ast_cmd_attr($1);
  }
  |
  while {
    $$ = ast_cmd_while($1);
  }
  |
  for{
    $$ = ast_cmd_for($1);
  }
  |
  printf {
    $$ = ast_cmd_printf($1);
  }
  |
  scanf {
    $$ = ast_cmd_scanf($1);
  }

while:
  WHILE OPENPAR boolexpr CLOSEPAR OPENCHAV cmdlist CLOSECHAV {
    $$ = ast_while($3,$6);
  }
  |
  WHILE OPENPAR boolexpr CLOSEPAR cmd {
    $$ = ast_while($3,ast_cmdlist($5,NULL));
  }

printf:
  PRINTF OPENPAR STRING COMMA varlist CLOSEPAR SEMICOLON {
    $$ = ast_printf($3, $5);
  }
  |
  PRINTF OPENPAR STRING CLOSEPAR SEMICOLON {
    $$ = ast_printf($3, NULL);
  }


scanf:
  SCANF OPENPAR STRING COMMA varlist CLOSEPAR SEMICOLON {
    $$ = ast_scanf($3, $5);
  }
  |
  SCANF OPENPAR STRING CLOSEPAR SEMICOLON {
    $$ = ast_scanf($3, NULL);
  }

attrib:
  VARTYPE ATTR expr SEMICOLON{
    $$ = ast_attrib($1,$3);
  }
  |
  VARNOTYPE ATTR expr SEMICOLON{
    $$ = ast_attrib($1,$3);
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
    $$ = ast_expr_integer($1);
  }
  |
  VARNOTYPE {
    $$ = ast_expr_var($1);
  }
  |
  expr PLUS expr {
    $$ = ast_expr_operation(PLUS, $1, $3);
  }
  |
  expr MINUS expr {
    $$ = ast_expr_operation(MINUS, $1, $3);
  }
  |
  expr MULT expr {
    $$ = ast_expr_operation(MULT, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_expr_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_expr_operation(MOD, $1, $3);
  }

varlist:
  VARNOTYPE COMMA varlist {
    $$ = ast_varlist($1,$3);
  }
  |
  VARNOTYPE{
    $$ = ast_varlist($1, NULL);
  }

VARTYPE:
  VARINT VARNAME{
    $$ = ast_var(VARINT,$2);
  }

VARNOTYPE:
  VARNAME{
    $$ = ast_var(NOTYPE, $1);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
