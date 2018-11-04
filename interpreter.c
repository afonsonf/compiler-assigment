#include <stdio.h>
#include "parser.h"

void printTab(int n);

void printVar(Var *var, int tabs);
void printVarList(VarList *varlist, int tabs);
void printString(char *str, int tabs);
void printExpr(Expr* expr, int tabs);
void printBoolExpr(BoolExpr* expr, int tabs);

void printAttr(Attrib *attrib, int tabs);
void printIf(If *cmdif, int tabs);
void printWhile(While *cmdwhile, int tabs);
void printFor(For *cmdfor, int tabs);
void printPrintf(Printf *cmdprintf, int tabs);
void printScanf(Scanf *cmdscanf, int tabs);

void printCmd(Cmd *cmd, int tabs);
void printCmdList(CmdList *cmdlist, int tabs);

void printfFunction(Function *function, int tabs);

void printTab(int n){
  for(int i=0;i<n-1;i++) printf("  ");
}

void printVar(Var *var, int tabs){
  if(var->type == VARINT){
    printTab(tabs);
    printf("int\n");
  }
  printTab(tabs);
  printf("%s\n", var->name);
}

void printVarList(VarList *varlist, int tabs){
  while(varlist){
    printVar(varlist->var,tabs);
    varlist = varlist->next;
  }
}

void printString(char *str, int tabs){
  printTab(tabs);
  printf("%s\n", str);
}

void printExpr(Expr* expr, int tabs){
  if(expr->kind == E_VAR){
    printVar(expr->attr.var,tabs);
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
  if(expr->kind == E_Bool){
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

void printAttr(Attrib *attrib, int tabs){
  printTab(tabs);
  printf("attrib\n");
  printVar(attrib->var, tabs+2);
  if(attrib->value){
    printf("\n");
    printExpr(attrib->value,tabs+2);
  }
}

void printIf(If *cmdif, int tabs){
  printTab(tabs);
  printf("if\n");
  printBoolExpr(cmdif->boolexpr,tabs+2);
  printf("\n");
  printCmdList(cmdif->cmdlist,tabs+2);
  if(cmdif->type == ELSETYPE){
    printTab(tabs);
    printf("else\n");
    printCmdList(cmdif->cmdlist_pos,tabs+2);
  }
}

void printWhile(While *cmdwhile, int tabs){
  printTab(tabs);
  printf("while\n");
  printBoolExpr(cmdwhile->boolexpr, tabs+2);
  printf("\n");
  printCmdList(cmdwhile->cmdlist,tabs+2);
}

void printFor(For* cmdfor, int tabs){
  printTab(tabs);
  printf("For\n");
  printAttr(cmdfor->init,tabs+2);
  printf("\n");
  printBoolExpr(cmdfor->boolexpr,tabs+2);
  printf("\n");
  printAttr(cmdfor->inc,tabs+2);
  printf("\n");
  printCmdList(cmdfor->cmdlist,tabs+2);
}

void printPrintf(Printf *cmdprintf, int tabs){
  printTab(tabs);
  printf("printf\n");
  printString(cmdprintf->s, tabs+2);
  if(cmdprintf->varlist){
    printf("\n");
    printVarList(cmdprintf->varlist,tabs+2);
  }
}

void printScanf(Scanf* cmdscanf, int tabs){
  printTab(tabs);
  printf("scanf\n");
  printString(cmdscanf->s, tabs+2);
  if(cmdscanf->varlist){
    printf("\n");
    printVarList(cmdscanf->varlist,tabs+2);
  }
}

void printCmd(Cmd *cmd, int tabs){
  if(cmd->type == E_Attrib){
    printAttr(cmd->attr.cmdattr,tabs);
  }
  else if(cmd->type == E_If){
    printIf(cmd->attr.cmdif,tabs);
  }
  else if(cmd->type == E_While){
    printWhile(cmd->attr.cmdwhile,tabs);
  }
  else if(cmd->type == E_Printf){
    printPrintf(cmd->attr.cmdprintf,tabs);
  }
  else if(cmd->type == E_Scanf){
    printScanf(cmd->attr.cmdscanf,tabs);
  }else if(cmd->type == E_For){
    printFor(cmd->attr.cmdfor,tabs);
  }
}

void printCmdList(CmdList *cmdlist, int tabs){
  while(cmdlist){
    printCmd(cmdlist->value,tabs);
    cmdlist = cmdlist->next;
    if(cmdlist){
      printTab(tabs);
      printf("---\n");
    }
  }
}

void printFunction(Function *function, int tabs){
  printTab(tabs);printf("+++++++++++++++++\n");
  printTab(tabs);printf("+ %s\n",function->name);
  printTab(tabs);printf("+++++++++++++++++\n");
  printf("\n");
  printCmdList(function->cmdlist,tabs);
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
      printFunction(root,0);
  }
  return 0;
}
