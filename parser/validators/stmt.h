#include "./expr.h"

/* ASSIGNMENT AND I/O STATEMENTS */
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
        return PARSING_ERROR;
    }
    (*tree)->sibling = assign;

    input = create_tree();
    status = is_input(tok, &input);
    if (status != SUBTREE_OK) {
        return status;
    }
    assign->child = input;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        return PARSING_ERROR;
    }
    input->sibling = open_par;

    if (match_obj((*tok)->type)) {
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        open_par->sibling = obj;
    }

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        return PARSING_ERROR;
    }
    open_par->sibling = close_par;

    /*
    endline = create_tree();
    status = is_endline(tok, &endline);
    close_par->sibling = endline;
    */
    
    return SUBTREE_OK;
}

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
            return PARSING_ERROR;
        }
        (*tree)->child = datatype;
    }
    

    
    var1 = create_tree();
    status = is_identifier(tok, &var1);
    if (status != SUBTREE_OK) {
        return PARSING_ERROR;
    }
    datatype->sibling = var1;

    if((*tok)->type == ENDLINE) {
        status = is_endline(tok, &endline);
        return status;
    }

    if((*tok)->type == ASSIGN && (*tok)->next_tok->type == Hey) {
        is_input_stmt(tok, &eq);
    }

    curr = *tok;
    if (curr->type == ASSIGN) {
        eq = create_tree();
        status = is_assign(tok, &eq);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        var1->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        eq->sibling = expression;

        endline = create_tree();
        status = is_endline(tok, &endline);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        expression->sibling = endline;

        return status;
    }

    if (match_crement_type(curr->type)) {
        eq = create_tree();
        status = is_crement(tok, &eq);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        var1->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        eq->sibling = expression;
    }
    
    if (curr->type == COMMA) {
        while (curr->type != ENDLINE) {
            comma = create_tree();
            status = is_comma(tok, &comma);
            if (status != SUBTREE_OK) {
                return PARSING_ERROR;
            }
            var1->sibling = comma;

            var1 = create_tree();
            status = is_identifier(tok, &var1);
            if (status != SUBTREE_OK) {
                return PARSING_ERROR;
            }
            comma->sibling = var1;
            curr = *tok;
        }
        endline = create_tree();
        status = is_endline(tok, &endline);
        if (status != SUBTREE_OK) {
            return PARSING_ERROR;
        }
        var1->sibling = endline;

        return status;
    }

    
    endline = create_tree();
    status = is_endline(tok, &endline);
    var1->sibling = endline;
    return status;

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
        return status;
    }
    (*tree)->child = print;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    print->child = open_par;

    
    if ((*tok)->type == STR_CONSTANT) {
        obj = create_tree();
        status = is_str_concat(tok, &obj);
        if (status != SUBTREE_OK) {
            return status;
        }
        print->sibling = obj;

       
    } else {
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            return status;
        }
        print->sibling = obj;
    }

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_par->child = close_par;

    endline = create_tree();
    status = is_endline(tok, &endline);
    close_par->sibling = endline;
    
    return status;
}

int is_if_stmt(t_table** tok, p_tree** tree){
    p_tree *if_kywrd, *open_par, *expression, *close_par, *open_curl, *endline, *body, *close_curl;
    int status;

    if (( *tree = create_tree_entry("IF_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: if condition container not created.\n");
        return MEMORY_ERROR;
    }

    if_kywrd = create_tree();
    status = is_if(tok, &if_kywrd);
    if (status != SUBTREE_OK) {
        return status;
    }
    (*tree)->child = if_kywrd;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    if_kywrd->sibling = open_par;

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_par->sibling = expression;

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    expression->sibling = close_par;

    open_curl = create_tree();
    status = is_open_curl(tok, &open_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    close_par->sibling = open_curl;

    /*
    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_curl->sibling = endline;
    */

    body = create_tree();
    status = is_block(tok, &body, CLOSE_CURL);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_curl->sibling = body;

    close_curl = create_tree();
    status = is_close_curl(tok, &close_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    body->sibling = close_curl;
}

int is_elif_stmt(t_table** tok, p_tree** tree) {
    p_tree *elif, *open_par, *expression, *close_par, *open_curl, *endline, *body, *close_curl;
    int status;

    if (( *tree = create_tree_entry("ELSEIF_CON", OUTPUT_CON, 0) ) == NULL) {
        //printf("MEMORY ERR: elseif container not created.\n");
        return MEMORY_ERROR;
    }

    elif = create_tree();
    status = is_elif(tok, &elif);
    if (status != SUBTREE_OK) {
        return status;
    }
    (*tree)->child = elif;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    elif->sibling = open_par;

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_par->sibling = expression;

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    expression->sibling = close_par;

    open_curl = create_tree();
    status = is_open_curl(tok, &open_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    close_par->sibling = open_curl;

    /*
    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_curl->sibling = endline;
    */

    body = create_tree();
    status = is_block(tok, &body, CLOSE_CURL);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_curl->sibling = body;

    close_curl = create_tree();
    status = is_close_curl(tok, &close_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    body->sibling = close_curl;
}

int is_else_stmt(t_table** tok, p_tree** tree) {
    p_tree *else_kywrd, *open_curl, *endline, *body, *close_curl;
    int status;
    
    if (( *tree = create_tree_entry("ELSE CON", OUTPUT_CON, 0) ) == NULL) {
        printf("MEMORY ERR: else statement contatiner not created.\n");
        return MEMORY_ERROR;
    }

    else_kywrd = create_tree();
    status = is_else(tok, &else_kywrd);
    if (status != SUBTREE_OK) {
        return status;
    }
    (*tree)->child = else_kywrd;
    
    /*
    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        return status;
    }
    else_kywrd->sibling = endline;
    */

    open_curl = create_tree();
    status = is_open_curl(tok, &open_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    body->sibling = open_curl;
    
    body = create_tree();
    status = is_block(tok, &body, CLOSE_CURL);
    if (status != SUBTREE_OK) {
        return status;
    }
    else_kywrd->sibling = body;

    close_curl = create_tree();
    status = is_close_curl(tok, &close_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    body->sibling = close_curl;

}

int is_while_loop(t_table** tok, p_tree** tree) {
    p_tree *while_kywrd, *open_par, *expression, *close_par, *open_curl, *endline, *body, *close_curl;
    int status;

    if (( *tree = create_tree_entry("WHILE_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: while loop container not created.\n");
        return MEMORY_ERROR;
    }

    while_kywrd = create_tree();
    status = is_while(tok, &while_kywrd);
    if (status != SUBTREE_OK) {
        return status;
    }
    (*tree)->child = while_kywrd;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    while_kywrd->sibling = open_par;

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_par->sibling = expression;

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        return status;
    }
    expression->sibling = close_par;

    open_curl = create_tree();
    status = is_open_curl(tok, &open_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    close_par->sibling = open_curl;

    /*endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }
    open_curl->sibling = endline;*/

    body = create_tree();
    status = is_block(tok, &body, CLOSE_CURL);
    if (status != SUBTREE_OK) {
        return status;
    }
    open_curl->sibling = body;

    close_curl = create_tree();
    status = is_close_curl(tok, &close_curl);
    if (status != SUBTREE_OK) {
        return status;
    }
    body->sibling = close_curl;
}

int is_for_loop(t_table** tok, p_tree** tree){
    p_tree *for_keyword, *open_par, *expression, *close_par, *open_curl, *body, *close_curl;

    t_table *curr;
    
    int status;
    
    if (( *tree = create_tree_entry("For", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: for loop container not created.\n");
        return MEMORY_ERROR;
    }
    for_keyword = create_tree();
    status = is_for(tok, &for_keyword);
    if (status != SUBTREE_OK){
        return status;
    }

    (*tree)->child = for_keyword;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK)
    {
        return status;
    }

    for_keyword->sibling = open_par;
    
    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK)
    {
        return status;
    }
    
    open_par->sibling = expression;
    
    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK)
    {
        return status;
    }
    
    expression->sibling = close_par;  

    open_curl = create_tree();
    status = is_open_curl(tok, &open_curl);
    if (status != SUBTREE_OK)
    {
        return status;
    }
    
    close_par->sibling = open_curl; 

    body = create_tree();
    status = is_block(tok, &body, CLOSE_CURL);//replace with is_block
    if (status != SUBTREE_OK)
    {
        return status;
    }
    open_curl->sibling = body; 

    close_curl = create_tree();
    status = is_close_curl(tok, &close_curl);
    if (status != SUBTREE_OK)
    {
        return status;
    }
    
    body->sibling = close_curl; 
  
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
    } else if (curr->type == If){
        status = is_if_stmt(tok,&subtree);
    } else if (curr->type == Elif){
        status = is_elif_stmt(tok,&subtree);
    } else if (curr->type == Else){
        status = is_else_stmt(tok,&subtree);
    } else if (curr->type == While) {
        status = is_while_loop(tok, &subtree);
    } else if (curr->type == For){
        status = is_for_loop(tok, &subtree);
    } else if (curr->type == BLOCK_COMMENT) {
        *tok = curr->next_tok;
        status = SUBTREE_OK;
    } else {
        printf("SYNTAX ERROR: No grammar match rule.\n");
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
    
            if (status == PARSING_ERROR) {
                lineNo = temp_list->line;
                while (temp_list->line == lineNo) {
                    temp_list = temp_list->next_tok;
                }
            }
        }
        printf("Does it enter here?");
        return SUBTREE_OK;
    }
    printf("OR  enter here?");
    return MEMORY_ERROR;
    
}

int is_block(t_table** tok, p_tree** tree, int terminator){
    int status;
    t_table *curr;
    
    if (( *tree = create_tree_entry("BLOCK_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: block container not created.\n");
        return MEMORY_ERROR;
    }

    curr = *tok;

    while (curr->type != terminator){
        p_tree *line, *end_line;

        line = create_tree();

        if ((*tok)->next_tok == NULL){
            return status;
        }

        status = is_line(tok, &line);

        if (status != SUBTREE_OK) {
            if ((*tok)->next_tok == NULL){
                char *terminator_str = "";
                switch (terminator)
                {
                    case CLOSE_CURL:
                        terminator_str = "}";
                        break;
                    case DELIMITER:
                        terminator_str = "DELIMITER";
                        break; 
                }
                printf(" Expected %s.", terminator_str);
            }
            //free_parse_tree(line);
            
            return status;
        }

        (*tree)->child = line;

        if ((*tok)->next_tok == NULL){
            return status;
        }
        
        /*
        end_line = create_tree();
        status = is_endline(tok, &end_line);
        if (status != SUBTREE_OK) {
            free_parse_tree(end_line);
            return status;
        }
        line->sibling = end_line;
        */
        curr = *tok;

    }

    return status;
}


void run_with_stat(t_table* head) {
    p_tree* tree;
    int status;

    tree = create_tree();
    t_table* prog_tb = head;

    status = is_program(&head, &tree);
    printf("STATUS RETURNED HERE: %d\n", status);
    display_syntax_table(prog_tb);
    
}
