%{
#include "Lexer.hpp"

%}

%option noyywrap
%option nounput
%option noinput
%x STATE_INT8 STATE_INT16 STATE_INT32 STATE_FLOAT STATE_DOUBLE QUIT
%%


[ \t]                       							;
[\n]                        							return EOL;
"int8("													BEGIN(STATE_INT8);
"int16("												BEGIN(STATE_INT16);
"int32("												BEGIN(STATE_INT32);
"float("												BEGIN(STATE_FLOAT);
"double("												BEGIN(STATE_DOUBLE);

<STATE_INT8>[-+]?[0-9]+										{ BEGIN(QUIT); return INT8; }
<STATE_INT16>[-+]?[0-9]+          	  						{ BEGIN(QUIT); return INT16; }  
<STATE_INT32>[-+]?[0-9]+             						{ BEGIN(QUIT); return INT32; }  
<STATE_FLOAT>[-+]?[0-9]*\.?[0-9]*[f]?([eE][+-]?[0-9]+)?		{ BEGIN(QUIT); return FLOAT; }
<STATE_DOUBLE>[-+]?[0-9]*\.?[0-9]*[f]?([eE][+-]?[0-9]+)?	{ BEGIN(QUIT); return DOUBLE; }
<QUIT>")"													BEGIN(INITIAL);

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
^;;$                    return END;
;.*                     return COMMENT;
<*>.                    return ERROR;

%%
