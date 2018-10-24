#include <stdio.h>
#include "parser.h"

void printTab(int n){
  for(int i=0;i<n-1;i++) printf("  ");
  printf("|");
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
  else if(expr->kind == E_Expr){
    printExpr(expr->attr.value,tabs);
  }
  else if(expr->kind == E_Bool){
    printTab(tabs);
    switch (expr->attr.op.operator) {
      case EQUALS: 
        printf("==\n");
        break;
      default: yyerror("Unknown operator!");
    }
    printExpr(expr->attr.op.left, tabs+2);
    printExpr(expr->attr.op.right, tabs+2);
  }
}

int evalexpr(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_OPERATION) {
    int vLeft = evalexpr(expr->attr.op.left);
    int vRight = evalexpr(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS: 
        result = vLeft + vRight; 
        break;
      case MINUS:
        result = vLeft - vRight;
        break;
      case MULT:
        result = vLeft * vRight;
        break;
      case DIV:
        result = vLeft / vRight;
        break;
      case MOD:
        result = vLeft % vRight;
        break;   
      default: yyerror("Unknown operator!");
    }
  }
  return result;
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
    printBoolExpr(root,0);
    //printf("Result = %d\n", eval(root));
  }
  return 0;


}
