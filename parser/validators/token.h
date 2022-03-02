/* 
* File        : token_validator.h
* Description : This file contains functions related to validate tokens. 
*               The functions implemented are:
*               tok_validator(), is_<token>(), match_<operation>(), is_var_binding()
*/

#include "../parse_tree.h"

//MATCHER FUNTIONS:
/* Validate if belonging to category of Datatypes */
int match_datatype(int toktype) {
    return 
    toktype == Char ||
    toktype == Str ||
    toktype == Int ||
    toktype == Bool ||
    toktype == Float;
}

int is_negative(t_table* tok) {
    return tok->type == MINUS && 
    (tok->next_tok->type == INT_CONSTANT ||
    tok->next_tok->type == DEC_CONSTANT);
}

int match_constants(int type) {
    return (
        type == INT_CONSTANT ||
        type == DEC_CONSTANT ||
        type == STR_CONSTANT ||
        type == True || type == False
    );
}

int match_identifier(int type) {
    return type == IDENTIFIER;
}

/* match which logical operator is used*/
int match_logical_type (int type) {
    return (type == EQ ||
            type == NOT_EQ ||
            type == GR_THAN ||
            type == GR_THAN_EQ ||
            type == LS_THAN ||
            type == LS_THAN_EQ ||
            type == LOGICAL_AND ||
            type == LOGICAL_OR);
}



/* match which arithmetic operator is used*/
int match_arithmetic_type (int type) {
    return (type == PLUS ||
            type == MINUS ||
            type == MUL ||
            type == DIV ||
            type == MODULO);
}

/* match which term operator is used */
int match_term_type (int type) {
    return (type == MUL ||
            type == DIV ||
            type == MODULO);
}

/* match which term operator is used */
int match_crement_type (int type) {
    return (type == PLUSCREMENT ||
            type == MINUSCREMENT ||
            type == MULTICREMENT ||
            type == DIVCREMENT);
}

/* match which term operator is used */
int match_obj (int type) {
    return (type == STR_CONSTANT ||
            type == INT_CONSTANT ||
            type == DEC_CONSTANT ||
            type == IDENTIFIER);
}

// SINGLE TOKEN FUNCTIONS
/* Template function for Checking token succession types */
int tok_validator (t_table** tok, p_tree** tree, int type, char* lexeme) {
    char message[150];
    // First Condition checking if tok is null
    if (*tok == NULL)
        return PARSING_ERROR;
    
    t_table *current = *tok;
    
    // Condition checking syntax rules set to token
    printf("Sa Validator: %d, %d\n", current->type, type);

    if (current->type == INVALID) {
        snprintf(message, sizeof(message), "PARSER ERROR: In line %d, %s\n", current->line, current->message);
        current->message = message;
        *tok = current->next_tok;
        return PARSING_ERROR;
    }
    if (current->type != type) {
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d. Expecting <%s>, Found <%s>\n", current->line, type2char(type), type2char(current->type));
        current->message = message;
        printf("THE message: %s\n", current->message);
        return PARSING_ERROR;
    }

    if (lexeme != NULL)
        if(strcmp(current->lexeme, lexeme) != 0) {
            snprintf(message, sizeof(message),"Expecting %s, Found %s\n", lexeme, current->lexeme);
            current->message = message;
            return PARSING_ERROR;
        }
    
    *tree = create_tree_entry(current->lexeme, current->type, current->line);
    current->message = "";
    *tok = current->next_tok;
    
    return SUBTREE_OK;
}



int is_char(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Char, NULL);
}

int is_string(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Str, NULL);
}

int is_int(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Int, NULL);
}

int is_float(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Float, NULL);
}

int is_bool(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Bool, NULL);
}

int is_null(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Null, NULL);
}

int is_and(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_AND, NULL);
}

int is_or(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_OR, NULL);
}

int is_not(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_NOT, NULL);
}

int is_print(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Print, NULL);
}

int is_input(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Hey, NULL);
}

int is_if(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, If, NULL);
}

int is_elif(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Elif, NULL);
}

int is_else(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Else, NULL);
}

int is_for(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, For, NULL);
}

int is_while(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, While, NULL);
}

int is_do(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Do, NULL);
}

int is_break(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Break, NULL);
}

int is_continue(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, Continue, NULL);
}

int is_true(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, True, NULL);
}

int is_false(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, False, NULL);
}

int is_assign(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, ASSIGN, NULL);
}

int is_minus(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, MINUS, NULL);
}

int is_plus(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, PLUS, NULL);
}

int is_mul(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, MUL, NULL);
}

int is_div(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, DIV, NULL);
}

int is_modulo(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, MODULO, NULL);
}

int is_ls_than(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, LS_THAN, NULL);
}

int is_gt_than(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, GR_THAN, NULL);
}

int is_ls_than_eq(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, LS_THAN_EQ, NULL);
}

int is_minuscrement(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, MINUSCREMENT, NULL);
}

int is_pluscrement(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, PLUSCREMENT, NULL);
}

int is_multicrement(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, MULTICREMENT, NULL);
}

int is_divcrement(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, DIVCREMENT, NULL);
}

int is_gt_than_eq(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, GR_THAN_EQ, NULL);
}

int is_eq(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, EQ, NULL);
}

int is_not_eq(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, NOT_EQ, NULL);
}

int is_dot(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, DOT, NULL);
}

int is_delimeter(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, DELIMITER, NULL);
}

int is_comma(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, COMMA, NULL);
}

int is_open_par(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, OPEN_PAR, NULL);
}

int is_close_par(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, CLOSE_PAR, NULL);
}

int is_open_curl(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, OPEN_CURL, NULL);
}

int is_close_curl(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, CLOSE_CURL, NULL);
}

int is_hex_const(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, HEX_CONSTANT, NULL);
}

int is_dec_const(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, DEC_CONSTANT, NULL);
}

int is_int_const(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, INT_CONSTANT, NULL);
}

int is_char_const(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, CHAR_CONSTANT, NULL);
}

int is_identifier(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, IDENTIFIER, NULL);
}

int is_endline(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDLINE, NULL);
}

int is_char_seq(t_table** tok, p_tree** tree) {
    return tok_validator(tok, tree, STR_CONSTANT, NULL);
}




/* COPOUND TOKENS VALIDATION */
/* Function checker if it is under logical operator (is_CondOp)*/
int is_logical_op (t_table** tok, p_tree** tree) {
    int type;
    char message[150];

    type = (*tok)->type;
    if (type == LOGICAL_AND)
        return is_and(tok, tree);
    else if (type == LOGICAL_OR)
        return is_or(tok, tree);
    else if (type == EQ)
        return is_eq(tok, tree);
    else if (type == NOT_EQ)
        return is_not_eq(tok, tree);
    else if (type == GR_THAN)
        return is_gt_than(tok, tree);
    else if (type == GR_THAN_EQ)
        return is_gt_than_eq(tok, tree);
    else if (type == LS_THAN)
        return is_ls_than(tok, tree);
    else if (type == LS_THAN_EQ)
        return is_ls_than_eq(tok, tree);
    else
        snprintf(message, sizeof(message),"PARSING ERROR: In line %d, Expected object of type <Operator> found %s", 
        (*tok)->line, type2char((*tok)->type));
        (*tok)->message = message;
        return SUBTREE_OK;
}

/* Function checker if it is under datatype */
int is_datatype (t_table** tok, p_tree** tree) {
    int type;
    char message[150];

    type = (*tok)->type;
    if (type == Char)
        return is_char(tok, tree);
    else if (type == Str)
        return is_string(tok, tree);
    else if (type == Int)
        return is_int(tok, tree);
    else if (type == Float)
        return is_float(tok, tree);
    else if (type == Bool)
        return is_bool(tok, tree);
    else
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d, Expected type of object <DATAYPE> found <%s>", (*tok)->line, type2char((*tok)->type));
        (*tok)->message = message;
        return PARSING_ERROR;
}

/* Function Checker to check crement operators */
int is_crement (t_table** tok, p_tree** tree) {
    int type;
    char message[150];

    type = (*tok)->type;
    if (type == PLUSCREMENT)
        return is_pluscrement(tok, tree);
    else if (type == MINUSCREMENT)
        return is_minuscrement(tok, tree);
    else if (type == MULTICREMENT)
        return is_multicrement(tok, tree);
    else if (type == DIVCREMENT)
        return is_divcrement(tok, tree);
    else {
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d, where lexeme=<%s>. Expected any type of <CREMENT> found <%s>", 
        (*tok)->line, (*tok)->lexeme, type2char((*tok)->type));
        (*tok)->message = message;
        return PARSING_ERROR;
    }
}

/* Function Checker to check operators */
int is_operator (t_table** tok, p_tree** tree) {
    int type;

    type = (*tok)->type;
    if (type == PLUS)
        return is_plus(tok, tree);
    else if (type == MINUS)
        return is_minus(tok, tree);
    else if (type == MUL)
        return is_mul(tok, tree);
    else if (type == DIV)
        return is_div(tok, tree);
    else if (type == MODULO)
        return is_modulo(tok, tree);
    else
        return is_logical_op(tok, tree);
}

int is_var_binding(int type1, int type2) {
    if (Char == type1 || type1 == Str || type1 == Int || type1 == Float || type1 == Bool) {
       return type2 == IDENTIFIER;
    }
    return 0;
}


/* Function checker to check expressions with/out signs and the precedence of what number(pow)*/
int is_number(t_table** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *sign, *numeric;
    int status, has_sign;

    if (( *tree = create_tree_entry("NUMBER", OBJECT, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }

    status = SUBTREE_OK;
    has_sign = 1;
    
    // Checking if expression has sign 
    sign = create_tree();
    
    if ((*tok)->type == PLUS)
        status = is_plus(tok, &sign);
    else if ((*tok)->type == MINUS)
        status = is_minus(tok, &sign);
    else
        has_sign = 0;

    if (status != SUBTREE_OK) {
        return status;
    }

    if (has_sign)
        (*tree)->child = sign;

    // Checking if expression type it has containing it 
    numeric = create_tree();

    if ((*tok)->type == INT_CONSTANT)
        status = is_int_const(tok, &numeric);
    else if ((*tok)->type == DEC_CONSTANT)
        status = is_dec_const(tok, &numeric);
    
    if (status != SUBTREE_OK)
        return PARSING_ERROR;
    else {
        if (has_sign)
            sign->sibling = numeric;
        else
            (*tree)->child = numeric;
    }
    return status;
}


/* Determine which obj is involved with an expression */
int is_obj(t_table** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;
    
    p_tree* subtree;
    int status;
    char message[150];

    if (( *tree = create_tree_entry("OBJ", OBJECT, 0) ) == NULL ) {
        printf("MEMORY ERR: object container not created.\n");
        return MEMORY_ERROR;
    }

    subtree = create_tree();

    // use LL(1) FOLLOW Sets
    t_table* curr;
    curr = *tok;

    if (curr->type == IDENTIFIER)
        status = is_identifier(tok, &subtree);
    else if (curr->type == Null)
        status = is_null(tok, &subtree);
    else if (curr->type == STR_CONSTANT)
        status = is_char_seq(tok, &subtree);
    else if (curr->type == Bool)
        status = is_bool(tok, &subtree);
    else if (curr->type == INT_CONSTANT ||
             curr->type == DEC_CONSTANT) {
        status = is_number(tok, &subtree);
    } else if (curr->type == True)
        status = is_true(tok, &subtree);
    else if (curr->type == False)
        status = is_false(tok, &subtree);
    else if (curr->type == ENDLINE) {
        snprintf(message, sizeof(message),"PARSING ERROR: In line %d, where lexeme=;, missing type <OBJ> FOUND <ENDLINE> within the statement", curr->line);
        curr->message = message;
        status = PARSING_ERROR;
    } else if (curr->type == OPEN_PAR) {
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d, where lexeme=( .Expecting data of type <Obj> found <OPEN_PAR>", curr->line);
        curr->message = message;
        status = PARSING_ERROR;
    } else if (curr->type == CLOSE_PAR) {
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d, where lexeme=). Expecting data of Type <Obj> found <CLOSE_PAR>", curr->line);
        curr->message = message;
        status = PARSING_ERROR;
    } else if (match_arithmetic_type(curr->type)) {
        snprintf(message, sizeof(message),"PARSER ERROR: In line %d, where lexeme=%s. Expecting data of type <Obj> found <%s>", 
        curr->line, curr->lexeme, type2char(curr->type));
        curr->message = message;
        status = PARSING_ERROR;
    }

    else   
        status = PARSING_ERROR;

    if (status == SUBTREE_OK)
        (*tree)->child = subtree;

    return status;
}

/* Function Checker if string has values to format */ 
int is_quoted_string(t_table** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;
    
    p_tree *char_seq, *comma, *obj, *last;
    int status, nVar, nObj;
    char message[150];

    status = SUBTREE_OK;
    nVar = nObj = 0;

    //Initial Tree declaring we are in a String Container
    if (( *tree = create_tree_entry("STRING_CON", STRING_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: string container not created.\n");
        return MEMORY_ERROR;
    }
    
    char_seq = create_tree();
    
    // Set the Char Seq as the initial child
    status = is_char_seq(tok, &char_seq);
    if (status != SUBTREE_OK) {
        return status;
    }

    (*tree)->child = char_seq;
    last = char_seq;


    // IF there are variables needed to interpolate, count them
    int i = 0;
    while (char_seq->token[i] != '\0') {
        if (char_seq->token[i] == '%') {
            if (char_seq->token[i+1] == '%') // escape char
                i += 2;
            else if (char_seq->token[i+1] == 's') {
                nVar += 1;
                i += 2;
            }
            else i++;
        }
        else i++;
    }

    if ((*tok)->type == ENDLINE) {
        if (nVar > 0) {
            return PARSING_ERROR;
        }
        else 
            return SUBTREE_OK;
    }

    while ((*tok)->type == COMMA) {
        comma = create_tree();
        status = is_comma(tok, &comma);
        if (status != SUBTREE_OK) {
            break;
        }

        last->sibling = comma;
        last = comma;
        
        // Now there must be a Obj
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            break;
        }
        
        last->sibling = obj;
        last = obj;
        nObj++;
    }

    // Raise Error if assignment of obj is not equal to its intermpolation
    if (nObj != nVar) {
        snprintf(message, sizeof(message),"PARSER ERROR: QuotedStr with #obj != #interpolation (%d != %d)\n", nObj, nVar);
        (*tok)->message = message;
        return PARSING_ERROR;
    }
    return status;
}

/* Function checker if string is concatenated*/
int is_str_concat (t_table** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *quotedstr, *plus, *last, *obj, *endline;
    int status;

    if (( *tree = create_tree_entry("CONCAT", CONCAT, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }
    status = SUBTREE_OK;

    quotedstr = create_tree();
    status = is_quoted_string(tok, &quotedstr);
    if (status != SUBTREE_OK) {
        return status;
    }
    (*tree)->child = quotedstr;
    last = quotedstr;

    if ((*tok)->type == ENDLINE)
        status = is_endline(tok, &endline);
        if (status != SUBTREE_OK) {
            return status;
        }
        last->sibling = endline;
        last = endline;


    while((*tok)->type == PLUS) {
        plus = create_tree();
        status = is_plus(tok, &plus);
        if (status != SUBTREE_OK) {
            return status;
        }
        last->sibling = plus;
        last = plus;

        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            return status;
        }
        last->sibling = obj;
        last = obj;
        
    }

    if ((*tok)->type == ENDLINE)
        status = is_endline(tok, &endline);
        if (status != SUBTREE_OK) {
            return status;
        }
        last->sibling = endline;
        last = endline;
    
    return status;
}



