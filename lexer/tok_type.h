/* 
* Compiler Design Project 1 : Lexical Analyser
*
* File        : tokentype.h
* Description : This file defines tokens and the values associated to them.
*                  
*/
#ifndef TOKENTYPE_H
#define _TOKENTYPE_H

enum TokenType {
  Char,
  Str,  
  Int,
  Float,
  Bool,
  LOGICAL_AND=5,
  LOGICAL_OR,
  LOGICAL_NOT,
  Print=8,
  Hey,
  If,
  Elif,
  Else,
  For,
  While,
  Do,
  BLOCK_COMMENT,
  LINE_COMMENT,
  Break,
  Continue,
  True=50,
  False,
  ASSIGN=100,
  MINUS,
  PLUS,
  MUL,
  DIV,
  MODULO,
  LS_THAN,
  GR_THAN,
  MINUSCREMENT,
  PLUSCREMENT,
  MULTICREMENT,
  DIVCREMENT,
  LS_THAN_EQ,
  GR_THAN_EQ,
  EQ,
  NOT_EQ,
  DOT,
  DELIMITER=300,
  COMMA,
  OPEN_PAR,
  CLOSE_PAR,
  OPEN_CURL,
  CLOSE_CURL,
  FW_SLASH,
  HEX_CONSTANT=400,
  INT_CONSTANT,
  DEC_CONSTANT,
  STR_CONSTANT,
  CHAR_CONSTANT,
  Null,
  IDENTIFIER=500,
  INVALID,
  PROG=600,
  LINE,
  OBJECT,
  BASE_EXP,
  TERM,
  PREDICATE,
  EXPR,
  STRING_CON,
  ASSIGN_CON,
  INPUT_CON,
  OUTPUT_CON,
  ENDLINE
};

#endif