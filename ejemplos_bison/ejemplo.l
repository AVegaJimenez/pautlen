%{
#include <stdio.h>
#include "y.tab.h"
int morf_err=0;
%}
%option noyywrap
constante_entera    	[0-9]+
constante_real			[0-9]+\.[0-9]+
%%
[\n\t ]+				{/* Whitespace*/}
"+"						{printf("TOKEN: %s\n", yytext); return yytext[0];}
"-"						{printf("TOKEN: %s\n", yytext); return yytext[0];}
"*"						{printf("TOKEN: %s\n", yytext); return yytext[0];}
"\/"					{printf("TOKEN: %s\n", yytext); return yytext[0];}
"\("					{printf("TOKEN: %s\n", yytext); return yytext[0];}
"\)"					{printf("TOKEN: %s\n", yytext); return yytext[0];}
{constante_entera}    	{printf("TOKEN: %s\n", yytext); return  TOK_CONSTANTE_ENTERA;}
{constante_real}    	{printf("TOKEN: %s\n", yytext); return  TOK_CONSTANTE_REAL;}
.						{morf_err=1;printf("ERROR MORFOLOGICO: %s\n",yytext); return TOK_ERROR;}
%%
