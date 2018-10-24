
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};


struct _BoolExpr{
  enum { 
    E_Bool,
    E_BoolOp,
    E_Complex
  } kind;
  union {
    struct _Expr* value; // expr
    struct { 
      int operator; // ==,<,>,<=,>=,!= 
      struct _Expr* left;
      struct _Expr* right;
    } op; 
    struct {
      int operator; // &&, ||
      struct _BoolExpr* left;
      struct _BoolExpr* right;
    } complex; 
  } attr;
};


typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr; // Convenience typedef

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolexpr_leaf(Expr* exp);
BoolExpr* ast_boolexpr(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolexpr_complex(int operator, BoolExpr* left, BoolExpr* right);
#endif
