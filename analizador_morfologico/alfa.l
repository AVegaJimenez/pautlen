%{
#include <stdio.h>
#include "tokens.h"
long yylin = 1;
long yycol = 0;
%}
%option noyywrap
whitespace              [ \t]+
newline                 \n|\n\r|\r
comentario              "//".*
main                	"main"
int                 	"int"
boolean             	"boolean"
array               	"array"
function            	"function"
if                  	"if"
else                	"else"
while               	"while"
scanf               	"scanf"
printf              	"printf"
return              	"return"
puntoycoma          	";"
coma                	","
parentesisizquierdo 	"("
parentesisderecho   	")"
corcheteizquierdo   	"["
corchetederecho     	"]"
llaveizquierda      	"{"
llavederecha        	"}"
asignacion          	"="
mas                 	"+"
menos               	"-"
division            	"/"
asterisco           	"*"
and                 	"&&"
or                  	"||"
not                 	"!"
igual               	"=="
distinto            	"!="
menorigual          	"<="
mayorigual          	">="
menor               	"<"
mayor               	">"
constante_entera    	[0-9]+
true                	"true"
false               	"false"
identificador       	[a-zA-Z][a-zA-Z0-9]{0,99}
identificadorlargo      [a-zA-Z][a-zA-Z0-9]*
error               	.
%%
{comentario}          	{/* COMENTARIO */}
{whitespace}            {/* WHITESPACE */}
{newline}               {yylin++; yycol = 0;}
{main}                	{return  TOK_MAIN;}
{int}                 	{return  TOK_INT;}
{boolean}             	{return  TOK_BOOLEAN;}
{array}               	{return  TOK_ARRAY;}
{function}            	{return  TOK_FUNCTION;}
{if}                  	{return  TOK_IF;}
{else}                	{return  TOK_ELSE;}
{while}               	{return  TOK_WHILE;}
{scanf}               	{return  TOK_SCANF;}
{printf}              	{return  TOK_PRINTF;}
{return}              	{return  TOK_RETURN;}
{puntoycoma}          	{return  TOK_PUNTOYCOMA;}
{coma}                	{return  TOK_COMA;}
{parentesisizquierdo} 	{return  TOK_PARENTESISIZQUIERDO;}
{parentesisderecho}   	{return  TOK_PARENTESISDERECHO;}
{corcheteizquierdo}   	{return  TOK_CORCHETEIZQUIERDO;}
{corchetederecho}     	{return  TOK_CORCHETEDERECHO;}
{llaveizquierda}      	{return  TOK_LLAVEIZQUIERDA;}
{llavederecha}        	{return  TOK_LLAVEDERECHA;}
{asignacion}          	{return  TOK_ASIGNACION;}
{mas}                 	{return  TOK_MAS;}
{menos}               	{return  TOK_MENOS;}
{division}            	{return  TOK_DIVISION;}
{asterisco}           	{return  TOK_ASTERISCO;}
{and}                 	{return  TOK_AND;}
{or}                  	{return  TOK_OR;}
{not}                 	{return  TOK_NOT;}
{igual}               	{return  TOK_IGUAL;}
{distinto}            	{return  TOK_DISTINTO;}
{menorigual}          	{return  TOK_MENORIGUAL;}
{mayorigual}          	{return  TOK_MAYORIGUAL;}
{menor}               	{return  TOK_MENOR;}
{mayor}               	{return  TOK_MAYOR;}
{constante_entera}    	{return  TOK_CONSTANTE_ENTERA;}
{true}                	{return  TOK_TRUE;}
{false}               	{return  TOK_FALSE;}
{identificador}       	{return  TOK_IDENTIFICADOR;}
{identificadorlargo}    {return  TOK_ERROR;}
{error}               	{return  TOK_ERROR;}
%%
