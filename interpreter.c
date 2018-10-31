#include <stdio.h>
#include "parser.h"

void printTab(int n){
  for(int i=0;i<n-1;i++) printf("  ");
}

void printExpr(Expr* expr, int tabs){
  if(expr == 0){
    printf("!!!!ERROR!!!!\n");
  }
  else if(expr->kind == E_INTEGER){
    printTab(tabs);
    printf("%d\n",expr->attr.value);
  }
  else if(expr->kind == E_OPERATION){
    printTab(tabs);
    switch (expr->attr.op.operator) {
      case PLUS:
        printf("+\n");
        break;
      case MINUS:
        printf("-\n");
        break;
      case MULT:
        printf("*\n");
        break;
      case DIV:
        printf("/\n");
        break;
      case MOD:
        printf("%c\n",'%');
        break;
      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.left, tabs+2);
    printExpr(expr->attr.op.right, tabs+2);
  }
}

void printBoolExpr(BoolExpr* expr, int tabs){
  if(expr == 0){
    printf("!!!!ERROR!!!!\n");
  }
  else if(expr->kind == E_Bool){
    printExpr(expr->attr.value,tabs);
  }
  else if(expr->kind == E_BoolOp){
    printTab(tabs);
    switch (expr->attr.op.operator) {
      case EQUALS:
        printf("==\n");
        break;
      case DIFF:
        printf("!=\n");
        break;
      case LESS:
        printf("<\n");
        break;
      case GREAT:
        printf(">\n");
        break;
      case LESSEQUAL:
        printf("<=\n");
        break;
      case GREATEQUAL:
        printf(">=\n");
        break;
      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.left, tabs+2);
    printExpr(expr->attr.op.right, tabs+2);
  }
  else if(expr->kind == E_Complex){
    printTab(tabs);
    switch(expr->attr.complex.operator) {
      case ANDLOGIC:
        printf("&&\n");
        break;
      case ORLOGIC:
        printf("||\n");
        break;
      default: yyerror("Unknown operator!");
    }
    printBoolExpr(expr->attr.complex.left,tabs+2);
    printBoolExpr(expr->attr.complex.right,tabs+2);
  }
}

void printVar(Var *var, int tabs){
  if(var->type == VARINT){
    printTab(tabs);
    printf("int\n");
  }
  printTab(tabs);
  printf("%s\n", var->name);
}

void printAttr(Attrib *attrib, int tabs){
  printTab(tabs);
  printf("=\n");
  printVar(attrib->var, tabs+2);
  printf("\n");
  printExpr(attrib->value,tabs+2);
}

void printCmd(Cmd *cmd, int tabs){
  if(cmd->type == E_Attrib){
    printAttr(cmd->attr.cmdattr,tabs);
  }
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    printCmd(root,0);
  }
  return 0;


}
