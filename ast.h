
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

struct _Var{
  int type;
  char *name;
};

struct _VarList{
  struct _Var *var;
  struct _VarList *next;
};

struct _Cmd {
  enum {
    E_Attrib,
    E_If,
    E_For,
    E_While,
    E_Printf,
    E_Scanf
  }type;
  union {
    struct _Attrib *cmdattr;
    struct _If *cmdif;
    struct _For *cmdfor;
    struct _While *cmdwhile;
    struct _Printf *cmdprintf;
    struct _Scanf *cmdscanf;
  }attr;
};

struct _CmdList{
  struct _Cmd *value;
  struct _CmdList *next;
};

struct _Attrib{
  struct _Var *var;
  struct _Expr *value;
};

struct _If{
  enum {IF, IFELSE, ELSE} type;
  struct _BoolExpr *boolexpr;
  struct _CmdList *cmdlist;
  struct _If *next;
};

struct _For{
  struct _Attrib *init;
  struct _BoolExpr *boolexpr;
  struct _Attrib *inc;
  struct _CmdList *cmdlist;
};

struct _While{
  struct _BoolExpr *boolexpr;
  struct _CmdList *cmdlist;
};

struct _Printf{
  char *s;
  struct _VarList *varlist;
};

struct _Scanf{
  char *s;
  struct _VarList *varlist;
};


typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr; // Convenience typedef
typedef struct _Var Var;
typedef struct _VarList VarList;
typedef struct _Attrib Attrib;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;
typedef struct _Attrib Attrib;
typedef struct _If If;
typedef struct _For For;
typedef struct _While While;
typedef struct _Printf Printf;
typedef struct _Scanf Scanf;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);

BoolExpr* ast_boolexpr_leaf(Expr* exp);
BoolExpr* ast_boolexpr(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolexpr_complex(int operator, BoolExpr* left, BoolExpr* right);

Var* ast_var(int type, char *name);
VarList* ast_varlist(Var *var, VarList *next);

Cmd* ast_cmd_attr(Attrib *cmdattrib);
Cmd* ast_cmd_if(If *cmdif);
Cmd* ast_cmd_for(For *cmdfor);
Cmd* ast_cmd_while(While *cmdwhile);
Cmd* ast_cmd_printf(Printf *cmdprintf);
Cmd* ast_cmd_scanf(Scanf *cmdscanf);

CmdList* ast_cmdlist(Cmd *cmd, CmdList *next);

Attrib* ast_attrib(Var *var, Expr *value);

If* ast_if_first(BoolExpr* boolexpr, CmdList *cmdlist, If *next);
If* ast_if_elseif(BoolExpr* boolexpr, CmdList *cmdlist, If *next);
If* ast_if_else(CmdList *cmdlist);

For* ast_for(Attrib *init, BoolExpr *boolexpr, Attrib *inc, CmdList *cmdlist);

While* ast_while(BoolExpr* boolexpr, CmdList *cmdlist);

Printf* ast_printf(char* s, VarList *varlist);

Scanf* ast_scanf(char* s, VarList *varlist);

#endif
