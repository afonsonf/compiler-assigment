%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}

"==" { return EQUALS; }
"!=" { return DIFF; }
"<"  { return LESS; }
">"  { return GREAT; }
"<=" { return LESSEQUAL; }
">=" { return GREATEQUAL; }

"&&" { return ANDLOGIC; }
"||" { return ORLOGIC; }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }

"=" { return ATTR; }

"int" { 
    yylval.vartype = yytext; 
    return VARINT;
}
";"   { return SEMICOLON; }

[a-z]+[a-zA-z0-9_]* {
    yylval.varname = yytext;
    return VARNAME;
}



.  { yyerror("unexpected character"); }
%%

