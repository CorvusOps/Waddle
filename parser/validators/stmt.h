#include "./expr.h"

/* ASSIGNMENT AND I/O STATEMENTS */

/* Function checker to see if the line statement is following the rules of assignment statement*/
int is_assignment_stmt(t_table** tok, p_tree** tree) {
    t_table * curr;
    p_tree *datatype, *var1, *eq, *expression, *comma, *other, *endline;
    
    int status;

    if (( *tree = create_tree_entry("ASSIGN_CON", ASSIGN_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: assign container not created.\n");
        return MEMORY_ERROR;
    }

    if (match_datatype((*tok)->type)) {
        datatype = create_tree();
        status = is_datatype(tok, &datatype);
        if (status != SUBTREE_OK) {
            free_parse_tree(datatype);
            return PARSING_ERROR;
        }
        (*tree)->child = datatype;
    }
    

    
    var1 = create_tree();
    status = is_identifier(tok, &var1);
    if (status != SUBTREE_OK) {
        free_parse_tree(var1);
        return PARSING_ERROR;
    }
    datatype->sibling = var1;

    if((*tok)->type == ENDLINE) {
        status = is_endline(tok, &endline);
        return status;
    }

    if(curr->type == ASSIGN && curr->next_tok->type == Hey) {
        is_input_stmt(tok, &eq);
    }

    curr = *tok;
    if (curr->type == ASSIGN) {
        eq = create_tree();
        status = is_assign(tok, &eq);
        if (status != SUBTREE_OK) {
            free_parse_tree(eq);
            return PARSING_ERROR;
        }
        var1->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            free_parse_tree(expression);
            return PARSING_ERROR;
        }
        eq->sibling = expression;

        return status;
    }

    if (match_crement_type(curr->type)) {
        eq = create_tree();
        status = is_crement(tok, &eq);
        if (status != SUBTREE_OK) {
            free_parse_tree(eq);
            return PARSING_ERROR;
        }
        var1->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            free_parse_tree(expression);
            return PARSING_ERROR;
        }
        eq->sibling = expression;
    }
    
    if (curr->type == COMMA) {
        while (curr->type != ENDLINE) {
            comma = create_tree();
            status = is_comma(tok, &comma);
            if (status != SUBTREE_OK) {
                free_parse_tree(var1);
                return PARSING_ERROR;
            }
            var1->sibling = comma;

            var1 = create_tree();
            status = is_identifier(tok, &var1);
            if (status != SUBTREE_OK) {
                free_parse_tree(var1);
                return PARSING_ERROR;
            }
            comma->sibling = var1;
            curr = *tok;
        }
        return status;
    }

    
    endline = create_tree();
    status = is_endline(tok, &endline);
    var1->sibling = endline;
    return status;

}

/* Function checker to see if the line statement is following the rules of input statement*/
int is_input_stmt(t_table** tok, p_tree** tree) {
    // Create subtree
    p_tree *assign, *input,  *open_par, *close_par, *obj, *endline;
    int status;
   
    if (( *tree = create_tree_entry("INPUT_CON", INPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: assign container not created.\n");
        return MEMORY_ERROR;
    }

    assign = create_tree();
    status = is_assign(tok, &assign);
    if (status != SUBTREE_OK) {
        free_parse_tree(assign);
        return PARSING_ERROR;
    }
    (*tree)->sibling = assign;

    input = create_tree();
    status = is_input(tok, &input);
    if (status != SUBTREE_OK) {
        free_parse_tree(input);
        return status;
    }
    assign->child = input;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(open_par);
        return PARSING_ERROR;
    }
    input->sibling = open_par;

    if (match_obj((*tok)->type)) {
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(open_par);
            return PARSING_ERROR;
        }
        open_par->sibling = obj;
    }

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(close_par);
        return PARSING_ERROR;
    }
    open_par->sibling = close_par;

    endline = create_tree();
    status = is_endline(tok, &endline);
    close_par->sibling = endline;

    return SUBTREE_OK;
}

/* Function checker to see if the line statement is following the rules of input statement*/
int is_output_stmt(t_table** tok, p_tree** tree) {
    // Create subtree
    p_tree *print, *open_par, *close_par, *obj, *endline;
    int status;
    
    if (( *tree = create_tree_entry("OUTPUT_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }

    print = create_tree();
    status = is_print(tok, &print);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    (*tree)->child = print;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    print->child = open_par;

    
    if ((*tok)->type == STR_CONSTANT) {
        obj = create_tree();
        status = is_str_concat(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;

       
    } else {
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;
    }

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    open_par->child = close_par;

    endline = create_tree();
    status = is_endline(tok, &endline);
    close_par->sibling = endline;
    
    return status;
}

// Check which type of line should we check the grammar.
int is_line(t_table** tok, p_tree** line) {
    
    p_tree* subtree;
    t_table* newTok;
    int status;
    t_table* curr;

    // Check if entry is created successfully 
    if (( *line = create_tree_entry("Line", LINE, 0) ) == NULL ) {
        printf("MEMORY ERROR:line container not created");
        return MEMORY_ERROR;
    }
    
    curr = *tok;

    if(curr->type == IDENTIFIER && (curr->next_tok == NULL || curr->next_tok->type != ASSIGN)){
        printf("SYNTAX ERROR: No grammar match rule.");
        status = PARSING_ERROR;
    }
    else if(is_var_binding(curr->type, curr->next_tok->type) ||
        (curr-> type == IDENTIFIER)) {
        status = is_assignment_stmt(tok, &subtree);
    } else if(curr->type == Hey) {
        status = is_input_stmt(tok, &subtree);
    } else if (curr->type == Print) {
        status = is_output_stmt(tok, &subtree);
    } else if (curr->type == BLOCK_COMMENT) {
        *tok = curr->next_tok;
        status = SUBTREE_OK;
    } else {
        printf("SYNTAX ERROR: No grammar match rule.");
        status = PARSING_ERROR;
    }

    (*line)->child = subtree;
    return status;
}

int is_program(t_table** head, p_tree** tree) {
    t_table* tok, *temp_list;
    int status, child, lineNo;
    p_tree *current, *temp;
    p_tree *line, *endline;

    temp = create_tree_entry("PROG", PROG, 0);
    if (temp  == NULL ) {
        printf("MEMORY ERROR: program container not created");
        return MEMORY_ERROR;
    }

    if (*tree == NULL) {
        *tree = temp;

        current = *tree;
        temp_list = *head;

        //
        // Nested call to identify grammar tokens return pointer to subtree(s)
        // or NULL is parsing/memory error happened.
        //
        
        child = 1; // true - the first line is always a child of Program
        // A program is a (possibly empty) sequence of 'line' 'end<token>'
        while ((temp_list) != NULL) {
            status = is_line(&temp_list, &line);
            if (child) {
                current->child = line;
                child = !child;
            } else {
                current->sibling = line;
            }

            if (status == MEMORY_ERROR) {
                printf("Program Out of Memory.\n");
                return MEMORY_ERROR;
            }
    
            if (status == PARSING_ERROR) {
                lineNo = temp_list->line;
                while (temp_list->line == lineNo) {
                    temp_list = temp_list->next_tok;
                }
            }
        }
        
        return SUBTREE_OK;
    }
    
    return MEMORY_ERROR;
    
}


void run_with_stat(t_table* head) {
    p_tree* tree;
    int status;

    tree = create_tree();
    t_table* prog_tb = head;

    status = is_program(&head, &tree);
    printf("STATUS RETURNED HERE: %d\n", status);
    
}
