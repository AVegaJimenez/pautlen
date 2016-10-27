%{
#include <stdio.h>
#include "tokens.h"
#define _ERROR_HEAD "****Error en [lin %ld, col %ld]: "
#define _ERROR_SYM  "simbolo no permitido (%s)\n"
#define _ERROR_ID   "identificador demasiado largo (%s)\n"
long yylin = 1;
long yycol = 1;
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
erroridentificador      [a-zA-Z][a-zA-Z0-9]*
error               	.
%%
{comentario}          	{/* COMENTARIO */}
{whitespace}            {yycol += yyleng;}
{newline}               {yylin++; yycol = 0;}
{main}                	{yycol += yyleng; return  TOK_MAIN;}
{int}                 	{yycol += yyleng; return  TOK_INT;}
{boolean}             	{yycol += yyleng; return  TOK_BOOLEAN;}
{array}               	{yycol += yyleng; return  TOK_ARRAY;}
{function}            	{yycol += yyleng; return  TOK_FUNCTION;}
{if}                  	{yycol += yyleng; return  TOK_IF;}
{else}                	{yycol += yyleng; return  TOK_ELSE;}
{while}               	{yycol += yyleng; return  TOK_WHILE;}
{scanf}               	{yycol += yyleng; return  TOK_SCANF;}
{printf}              	{yycol += yyleng; return  TOK_PRINTF;}
{return}              	{yycol += yyleng; return  TOK_RETURN;}
{puntoycoma}          	{yycol += yyleng; return  TOK_PUNTOYCOMA;}
{coma}                	{yycol += yyleng; return  TOK_COMA;}
{parentesisizquierdo} 	{yycol += yyleng; return  TOK_PARENTESISIZQUIERDO;}
{parentesisderecho}   	{yycol += yyleng; return  TOK_PARENTESISDERECHO;}
{corcheteizquierdo}   	{yycol += yyleng; return  TOK_CORCHETEIZQUIERDO;}
{corchetederecho}     	{yycol += yyleng; return  TOK_CORCHETEDERECHO;}
{llaveizquierda}      	{yycol += yyleng; return  TOK_LLAVEIZQUIERDA;}
{llavederecha}        	{yycol += yyleng; return  TOK_LLAVEDERECHA;}
{asignacion}          	{yycol += yyleng; return  TOK_ASIGNACION;}
{mas}                 	{yycol += yyleng; return  TOK_MAS;}
{menos}               	{yycol += yyleng; return  TOK_MENOS;}
{division}            	{yycol += yyleng; return  TOK_DIVISION;}
{asterisco}           	{yycol += yyleng; return  TOK_ASTERISCO;}
{and}                 	{yycol += yyleng; return  TOK_AND;}
{or}                  	{yycol += yyleng; return  TOK_OR;}
{not}                 	{yycol += yyleng; return  TOK_NOT;}
{igual}               	{yycol += yyleng; return  TOK_IGUAL;}
{distinto}            	{yycol += yyleng; return  TOK_DISTINTO;}
{menorigual}          	{yycol += yyleng; return  TOK_MENORIGUAL;}
{mayorigual}          	{yycol += yyleng; return  TOK_MAYORIGUAL;}
{menor}               	{yycol += yyleng; return  TOK_MENOR;}
{mayor}               	{yycol += yyleng; return  TOK_MAYOR;}
{constante_entera}    	{yycol += yyleng; return  TOK_CONSTANTE_ENTERA;}
{true}                	{yycol += yyleng; return  TOK_TRUE;}
{false}               	{yycol += yyleng; return  TOK_FALSE;}
{identificador}       	{yycol += yyleng; return  TOK_IDENTIFICADOR;}
{erroridentificador}    {yycol += yyleng; return  TOK_ERROR;}
{error}               	{yycol += yyleng; return  TOK_ERROR;}
%%
