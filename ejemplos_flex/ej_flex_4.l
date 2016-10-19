%{
#include <stdio.h>
#include "tokens.h"
%}
%option noyywrap
puntoycoma           ;
parentesisizquierdo  \(
parentesisderecho    \)
asterisco            \*
mas                  \+
menorigual           <=
%%
main                    {return TOK_MAIN;}
array                   {return TOK_ARRAY;}
int                     {return TOK_INT;}
if                      {return TOK_IF;}
else                    {return TOK_ELSE;}
while                   {return TOK_WHILE;}
{puntoycoma}            {return TOK_PUNTOYCOMA;}
{parentesisizquierdo}   {return TOK_PARENTESISIZQUIERDO;}
{parentesisderecho}     {return TOK_PARENTESISDERECHO;}
{asterisco}             {return TOK_ASTERISCO;}
{mas}                   {return TOK_MAS;}
{menorigual}            {return TOK_MENORIGUAL;}
%%
