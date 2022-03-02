%option yylineno

%{

  #include "./parser/validators/stmt.h"
  // #include "./structs/parse/grammar_validator.h"
  #include <stdlib.h>
  #include <stdio.h>

  t_table* symbol_table;
  t_table* display_table;
  int cmnt_strt = 0;

%}

/* Exclusive states */
%x CMNT

letter [a-zA-Z_]
digit [0-9]+
ws  [ \t\r\f\v]+
identifier [a-zA-Z][a-zA-Z0-9]*
hex [a-fA-F0-9]

E			[Ee][+-]?{digit}+
FS			(f|F|l|letter)
IS			(u|U|l|letter)*

%%
  /* Keywords Dictionary */
Char                            {insert_to_symbol_table(&symbol_table,yytext,"DATATYPE",Char, yylineno, NULL);}
Str                             {insert_to_symbol_table(&symbol_table,yytext,"DATATYPE",Str, yylineno, NULL);}
Int                             {insert_to_symbol_table(&symbol_table,yytext,"DATATYPE",Int, yylineno, NULL);}
Float                           {insert_to_symbol_table(&symbol_table,yytext,"DATATYPE",Float, yylineno, NULL);}
Bool                            {insert_to_symbol_table(&symbol_table,yytext,"DATATYPE",Bool,yylineno, NULL);}
Null                            {insert_to_symbol_table(&symbol_table,yytext,"Null",Null,yylineno, NULL);}
Print                           {insert_to_symbol_table(&symbol_table,yytext,"IOKEYWORD",Print,yylineno, NULL);}
Hey                             {insert_to_symbol_table(&symbol_table,yytext,"IOKEYWORD",Hey,yylineno, NULL);}
AND                             {insert_to_symbol_table(&symbol_table,yytext,"LOGDKEYWORD",LOGICAL_AND,yylineno, NULL);}
OR                              {insert_to_symbol_table(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_OR,yylineno, NULL);}
NOT                             {insert_to_symbol_table(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_NOT,yylineno, NULL);}
if                              {insert_to_symbol_table(&symbol_table,yytext,"CONDKEYWORD",If,yylineno, NULL);}
elif                            {insert_to_symbol_table(&symbol_table,yytext,"CONDKEYWORD",Elif,yylineno, NULL);}
else                            {insert_to_symbol_table(&symbol_table,yytext,"CONDKEYWORD",Else,yylineno, NULL);}
For                             {insert_to_symbol_table(&symbol_table,yytext,"LOOPKEYWORD",For,yylineno, NULL);}
While                           {insert_to_symbol_table(&symbol_table,yytext,"LOOPKEYWORD",While,yylineno, NULL);}
Do                              {insert_to_symbol_table(&symbol_table,yytext,"LOOPKEYWORD",Do,yylineno, NULL);}
Break                           {insert_to_symbol_table(&symbol_table,yytext,"JUMPKEYWORD",Break,yylineno, NULL);}
Continue                        {insert_to_symbol_table(&symbol_table,yytext,"JUMPKEYWORD",Continue,yylineno, NULL);}
True                            {insert_to_symbol_table(&symbol_table,yytext,"BOOLKEYWORD",True,yylineno, NULL);}
False                           {insert_to_symbol_table(&symbol_table,yytext,"BOOLKEYWORD",False,yylineno, NULL);}

  /* Comment Section */
##                          {cmnt_strt = yylineno; BEGIN CMNT; insert_to_symbol_table(&symbol_table,yytext,"BLOCK_COMMENT",BLOCK_COMMENT,yylineno, NULL);}
<CMNT>.|{ws}                      ;
<CMNT>\n                          {}
<CMNT>##                    {BEGIN INITIAL; insert_to_symbol_table(&symbol_table,yytext,"BLOCK_COMMENT",BLOCK_COMMENT,yylineno, NULL);}
<CMNT><<EOF>>                     {insert_to_symbol_table(&symbol_table,yytext,"INVALID",INVALID,yylineno,"No closing comment statement before termination");BEGIN INITIAL;}

  /* Identfier section */
{identifier}                      {insert_to_symbol_table(&symbol_table,yytext,"IDENTIFIER",IDENTIFIER,yylineno, NULL);}
{ws}                              ;
{digit}+({letter}|_)+	            {insert_to_symbol_table(&symbol_table,yytext,"INVALID",INVALID,yylineno,"Invalid identifier. did not follow rules");}


{letter}?'(\\.|[^\\'])+'		      {insert_to_symbol_table(&symbol_table,yytext,"CHAR_CONSTANT",CHAR_CONSTANT,yylineno, NULL);}
{digit}+{E}{FS}?			            {insert_to_symbol_table(&symbol_table,yytext,"DEC_CONSTANT",DEC_CONSTANT,yylineno, NULL);}
{digit}*"."{digit}+({E})?{FS}?		{insert_to_symbol_table(&symbol_table,yytext,"DEC_CONSTANT",DEC_CONSTANT,yylineno, NULL);}
{digit}+"."{digit}*({E})?{FS}?		{insert_to_symbol_table(&symbol_table,yytext,"DEC_CONSTANT",DEC_CONSTANT,yylineno, NULL);}
{digit}                           {insert_to_symbol_table(&symbol_table,yytext,"INT_CONSTANT",INT_CONSTANT,yylineno, NULL);}

  /* Quotations Section */
\"[^\"\n]*\"     {

if(yytext[yyleng-2]=='\\')        /* check if it was an escaped quote */
{
  yyless(yyleng-1);               /* push the quote back if it was escaped */
  yymore();
}
else 
insert_to_symbol_table(&symbol_table,yytext,"STR_CONSTANT",STR_CONSTANT,yylineno, NULL);
}

\"[^\"\n]*$                       {insert_to_symbol_table(&symbol_table,yytext,"INVALID",INVALID ,yylineno,"No closing quotations");}
\n                                {}

  /* Operators Dictionary */
";"                               {insert_to_symbol_table(&symbol_table,yytext,"ENDLINE",ENDLINE ,yylineno, NULL); }
"-="                              {insert_to_symbol_table(&symbol_table,yytext,"DECREMENT",MINUSCREMENT,yylineno, NULL);}
"+="                              {insert_to_symbol_table(&symbol_table,yytext,"INCREMENT",PLUSCREMENT,yylineno, NULL);}
"*="                              {insert_to_symbol_table(&symbol_table,yytext,"INCREMENT",MULTICREMENT,yylineno, NULL);}
"/="                              {insert_to_symbol_table(&symbol_table,yytext,"INCREMENT",DIVCREMENT,yylineno, NULL);}
"<="                              {insert_to_symbol_table(&symbol_table,yytext,"LS_THAN_EQ",LS_THAN_EQ,yylineno, NULL);}
">="                              {insert_to_symbol_table(&symbol_table,yytext,"GR_THAN_EQ",GR_THAN_EQ,yylineno, NULL);}
"=="                              {insert_to_symbol_table(&symbol_table,yytext,"EQ",EQ,yylineno, NULL);}
"!="                              {insert_to_symbol_table(&symbol_table,yytext,"NOT_EQ",NOT_EQ,yylineno, NULL);}
","			                          {insert_to_symbol_table(&symbol_table,yytext,"COMMA",COMMA,yylineno, NULL);}
"="			                          {insert_to_symbol_table(&symbol_table,yytext,"ASSIGN",ASSIGN,yylineno, NULL);}
"("			                          {insert_to_symbol_table(&symbol_table,yytext,"OPEN_PAR",OPEN_PAR,yylineno, NULL);}
")"			                          {insert_to_symbol_table(&symbol_table,yytext,"CLOSE_PAR",CLOSE_PAR,yylineno, NULL);}
"{"			                          {insert_to_symbol_table(&symbol_table,yytext,"OPEN_CURL",OPEN_CURL,yylineno, NULL);}
"}"			                          {insert_to_symbol_table(&symbol_table,yytext,"CLOSE_CURL",CLOSE_CURL,yylineno, NULL);}
"-"			                          {insert_to_symbol_table(&symbol_table,yytext,"MINUS",MINUS,yylineno, NULL);}
"+"			                          {insert_to_symbol_table(&symbol_table,yytext,"PLUS",PLUS,yylineno, NULL);}
"*"			                          {insert_to_symbol_table(&symbol_table,yytext,"MUL",MUL,yylineno, NULL);}
"/"		                            {insert_to_symbol_table(&symbol_table,yytext,"DIV",DIV,yylineno, NULL);}
"%"			                          {insert_to_symbol_table(&symbol_table,yytext,"MODULO",MODULO,yylineno, NULL);}
"<"			                          {insert_to_symbol_table(&symbol_table,yytext,"LS_THAN",LS_THAN,yylineno, NULL);}
">"			                          {insert_to_symbol_table(&symbol_table,yytext,"GR_THAN",GR_THAN,yylineno, NULL);}
.                                 {insert_to_symbol_table(&symbol_table,yytext,"INVALID",INVALID,yylineno, NULL);}


%%


int main(int argc, char **argv)
{
  char filename[200];
  printf("Enter the path filename:");
  scanf("%[^\n]s", filename);
  printf("%s %d",filename, ends_with(filename, "caroline", 8));
  
  if(ends_with(filename, "wdl", 3)) {
    yyin=fopen(filename,"r");
    symbol_table=create_symbol_table();
    yylex();
    display_table=symbol_table;
    display_symbol_table(display_table);
    run_with_stat(symbol_table);

  } else {
    printf("Invalid extension. Please input files only with .wdl extension");
  }
  
}
int yywrap()
{
  return(1);
}