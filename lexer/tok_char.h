#ifndef TOKENCHAR_H
#define _TOKENCHAR_H

#include "./tok_type.h"

const char* type2char (enum TokenType t) {
    switch (t)
    {
        case Char: return "Char";
        case Str: return "Str";
        case Int: return "Int";
        case Float: return "Float";
        case Bool: return "Bool";
        case Null: return "Null";
        case LOGICAL_AND: return "AND";
        case LOGICAL_OR: return "OR";
        case LOGICAL_NOT: return "NOT";
        case Print: return "Print";
        case Hey: return "Hey";
        case If: return "if";
        case Elif: return "Elif";
        case Else: return "Else";
        case For: return "For";
        case While: return "While";
        case Do: return "Do";
        case BLOCK_COMMENT: return "##";
        case LINE_COMMENT: return "#";
        case Break: return "Break";
        case Continue: return "Continue";
        case True: return "True";
        case False: return "False";
        case ASSIGN: return "=";
        case MINUS: return "-";
        case PLUS: return "+";
        case MUL: return "*";
        case DIV: return "/";
        case MODULO: return "%";
        case LS_THAN: return "<";
        case GR_THAN: return ">";
        case MINUSCREMENT: return "-=";
        case PLUSCREMENT: return "+=";
        case DIVCREMENT: return "/=";
        case MULTICREMENT: return "*=";
        case LS_THAN_EQ: return "<=";
        case GR_THAN_EQ: return ">=";
        case EQ: return "==";
        case NOT_EQ: return "!=";
        case DOT: return ".";
        case DELIMITER: return ";";
        case COMMA: return "COMMA";
        case OPEN_PAR: return "(";
        case CLOSE_PAR: return ")";
        case OPEN_CURL: return "{";
        case CLOSE_CURL: return "}";
        case HEX_CONSTANT: return "HEX";
        case INT_CONSTANT: return "Integer";
        case DEC_CONSTANT: return "Float Number";
        case STR_CONSTANT: return "String";
        case CHAR_CONSTANT: return "Character";
        case IDENTIFIER: return "IDENTIFIER";
        case INVALID: return "INVALID";
        case PROG: return "PROG";
        case LINE: return "LINE";
        case OBJECT: return "OBJECT";
        case BASE_EXP: return "BASE_EXP";
        case TERM: return "TERM";
        case PREDICATE: return  "PREDICATE";
        case EXPR: return "EXPR";
        case ASSIGN_CON: return "ASSIGN_CON";
        case INPUT_CON: return "INPUT_CON";
        case OUTPUT_CON: return "OUTPUT_CON";
        case ENDLINE: return "ENDLINE";
        default: return "UNKNOWN";
    }
}

#endif