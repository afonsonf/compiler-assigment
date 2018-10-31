// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_expr_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_expr_var(Var *var){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = var;
  return node;
}

Expr* ast_expr_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}


BoolExpr* ast_boolexpr_leaf(Expr* exp){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_Bool;
  node->attr.value = exp;
  return node;
}

BoolExpr* ast_boolexpr(int operator, Expr* left, Expr* right){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BoolOp;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr* ast_boolexpr_complex(int operator, BoolExpr* left, BoolExpr* right){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_Complex;
  node->attr.complex.operator = operator;
  node->attr.complex.left = left;
  node->attr.complex.right = right;
  return node;
}

Attrib* ast_attrib(Var *var, Expr *value){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->var = var;
  node->value = value;
  return node;
}

Cmd* ast_cmd_attr(Attrib *cmdattrib){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->type = E_Attrib;
  node->attr.cmdattr = cmdattrib;
  return node;
}

Var* ast_var(int type, char *name){
  Var* node = (Var*) malloc(sizeof(Var));
  node->name = name;
  node->type = type;
  return node;
}
