%{
#include "Lexer.hpp"

%}

%option noyywrap
%option nounput
%option noinput
%%

[ \t]                       ;
[\n]                        return EOL;
int8\([0-9]+\)              return INT8;
int16\([0-9]+\)             return INT16;
int32\([0-9]+\)             return INT32;
float\([0-9]+\.[0-9]*\)     return FLOAT;
double\([0-9]+[.]*[0-9]*\)  return DOUBLE;

"push"                  return PUSH;
"pop"                   return POP;
"dump"                  return DUMP;
"assert"                return ASSERT;
"add"                   return ADD;
"sub"                   return SUB;
"mul"                   return MUL;
"div"                   return DIV;
"mod"                   return MOD;
"print"                 return PRINT;
"exit"                  return EXIT;
";;"                    return END;
;.*                     return COMMENT;
.                       return ERROR;

%%
