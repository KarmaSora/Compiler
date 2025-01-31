%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%

"+"                     {if(USE_LEX_ONLY) {printf("PLUSOP ");} else {return yy::parser::make_PLUSOP(yytext);}}
"-"                     {if(USE_LEX_ONLY) {printf("SUBOP ");} else {return yy::parser::make_MINUSOP(yytext);}}
"*"                     {if(USE_LEX_ONLY) {printf("MULTOP ");} else {return yy::parser::make_MULTOP(yytext);}}
"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext);}}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext);}}
"/"                     {if(USE_LEX_ONLY) {printf("DIVOP ");} else {return yy::parser::make_DIVOP(yytext);}}

"!"                     {if(USE_LEX_ONLY) {printf("EXCLAMATION MARK ");} else {return yy::parser::make_EXCLAMATION_MARK(yytext);}}
"="                     {if(USE_LEX_ONLY) {printf("EQUAL ");} else {return yy::parser::make_ASSIGN(yytext);}}
"&& "                     {if(USE_LEX_ONLY) {printf("AND ");} else {return yy::parser::make_AND(yytext);}}
"|| "                     {if(USE_LEX_ONLY) {printf("OR ");} else {return yy::parser::make_OR(yytext);}}
"<"                     {if(USE_LEX_ONLY) {printf("LESS THAN ");} else {return yy::parser::make_GREATER_THAN(yytext);}}
">"                     {if(USE_LEX_ONLY) {printf("GREATER THAN ");} else {return yy::parser::make_LESS_THAN(yytext);}}
"<="                     {if(USE_LEX_ONLY) {printf("LESS EQUAL ");} else {return yy::parser::make_GREATER_EQUAL(yytext);}}
">="                     {if(USE_LEX_ONLY) {printf("GREATER EQUAL ");} else {return yy::parser::make_LESS_EQUAL(yytext);}}
"=="                     {if(USE_LEX_ONLY) {printf("Equality Operator ");} else {return yy::parser::make_EQUAL(yytext);}}

"["                   {if(USE_LEX_ONLY) {printf("Left SQR Brac ");} else {return yy::parser::make_RSQB(yytext);}}
"]"                   {if(USE_LEX_ONLY) {printf("Right SQR Brac ");} else {return yy::parser::make_LSQB(yytext);}}
";"                   {if(USE_LEX_ONLY) {printf("SemiColon ");} else {return yy::parser::make_SEMICOLON(yytext);}}
","                   {if(USE_LEX_ONLY) {printf("COMMA ");} else {return yy::parser::make_COMMA(yytext);}}
"_"                   {if(USE_LEX_ONLY) {printf("UnderScore ");} else {return yy::parser::make_UNDERSCORE(yytext);}}
"."                   {if(USE_LEX_ONLY) {printf("DOT ");} else {return yy::parser::make_DOT(yytext);}}
":"                   {if(USE_LEX_ONLY) {printf("COLON ");} else {return yy::parser::make_COLON(yytext);}}
"{"                   {if(USE_LEX_ONLY) {printf("Left Brac ");} else {return yy::parser::make_LB(yytext);}}
"}"                   {if(USE_LEX_ONLY) {printf("right Brac ");} else {return yy::parser::make_RB(yytext);}}


"public"                   {if(USE_LEX_ONLY) {printf("public ");} else {return yy::parser::make_RP(yytext);}}
"class"                   {if(USE_LEX_ONLY) {printf("class ");} else {return yy::parser::make_RP(yytext);}}
"static"                   {if(USE_LEX_ONLY) {printf("Static ");} else {return yy::parser::make_RP(yytext);}}
"void"                   {if(USE_LEX_ONLY) {printf("void ");} else {return yy::parser::make_RP(yytext);}}
"main"                   {if(USE_LEX_ONLY) {printf("main ");} else {return yy::parser::make_RP(yytext);}}
"return"                   {if(USE_LEX_ONLY) {printf("RETURN ");} else {return yy::parser::make_RP(yytext);}}
"int"                   {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}
"boolean"                   {if(USE_LEX_ONLY) {printf("BOOLEAN ");} else {return yy::parser::make_RP(yytext);}}
"String"                   {if(USE_LEX_ONLY) {printf("STRING ");} else {return yy::parser::make_RP(yytext);}}
"if"                   {if(USE_LEX_ONLY) {printf("IF ");} else {return yy::parser::make_RP(yytext);}}
"else"                   {if(USE_LEX_ONLY) {printf("ELSE ");} else {return yy::parser::make_RP(yytext);}}
"while"                   {if(USE_LEX_ONLY) {printf("WHILE ");} else {return yy::parser::make_RP(yytext);}}
"System.out.println"                   {if(USE_LEX_ONLY) {printf("SYSTEM:OUT:PRINTLN ");} else {return yy::parser::make_RP(yytext);}}



0|[1-9][0-9]*           {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}
[a-zA-Z]*           {if(USE_LEX_ONLY) {printf("Char ");} else {return yy::parser::make_INT(yytext);}}

[ \t\n\r]+              {printf("%s", yytext);}
"//"[^\n]*              {printf("%s", yytext);}

.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}
%%