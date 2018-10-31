cmds:
if/else
for
while
printf
scanf

struct lstCmds{
  lstCmds
  lstNext
}

struct atribuição{
  type;
  var;
  expr;
}

struct if{
  boolExp
  lstCmds
  next  
}

struct for{
  Atrib
  bool
  Atrib
  lstCmds;
}

struct while{
  bool
  lstCmds
}

struct printf{
  mystring
  lstVar
}

struct scanf{
  mystring
  lstVar
}

struct var{
  mystring
}

struct expr{
  ja feito
}

struct boolExp{
  quase feito :D
}
