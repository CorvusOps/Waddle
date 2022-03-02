#include "./token.h"


//Match Compound operations
/* matches operator type */
int match_operator_type (enum TokenType type) {
    return (match_arithmetic_type(type) ||
            match_logical_type(type));
}

// Expressions Functionalities
/* Function that Checks if the expression is compound */
int is_base_expr (t_table** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    p_tree *lpar, *rpar, *subexpr, *obj;
    
    if (( *tree = create_tree_entry("BASE_EXP", BASE_EXP, 0) ) == NULL ) {
        printf("MEMORY ERR: base_expr container not created.\n");
        return MEMORY_ERROR;
    }

    // if a multiple expression
    if ((*tok)->type == OPEN_PAR) {
        // is a sub expression
        
        lpar = create_tree();
        status = is_open_par(tok, &lpar);
        if (status != SUBTREE_OK){
            return status;
        }
        (*tree)->child = lpar;

        
        subexpr = create_tree();
        status = is_expression(tok, &subexpr);
        if (status != SUBTREE_OK){
            return status;
        }
        lpar->sibling = subexpr;

        
        rpar = create_tree();
        status = is_close_par(tok, &rpar);
        if (status != SUBTREE_OK){
            return status;
        }
        subexpr->sibling = rpar;
    }
    else {
        // if the expression is just an Obj
        // An object is any type of value that a user inputs 
        // (e.g.) x -> object-> identifier 
        //        54.5 -> object -> number -> real
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            return status;
        }
        (*tree)->child = obj;
    }
    return status;
}

/* Checker of Operators  within an expression*/
int is_term (t_table** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    enum TokenType type;
    p_tree *base, *op, *term;

    if (( *tree = create_tree_entry("TERM", TERM, 0) ) == NULL ) {
        printf("MEMORY ERR: term container not created.\n");
        return MEMORY_ERROR;
    }

    base = create_tree();
    status = is_base_expr(tok, &base);
    if (status != SUBTREE_OK){
        return status;
    }
    (*tree)->child = base;

    // The remainder of a Term is optional
    type = (*tok)->type;

    if (match_term_type(type)){
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            return status;
        }
        base->sibling = op;

        term = create_tree();
        status = is_term(tok, &term);
        if (status != SUBTREE_OK){
            return status;
        }
        op->sibling = term;
    }
    return status;
}

/* Another Checker of Operators with extended (+,-)  within an expression*/
int is_predicate (t_table** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *term, *op, *pred;
    enum TokenType type;
    int status;

    if (( *tree = create_tree_entry("PREDICATE", PREDICATE, 0) ) == NULL ) {
        printf("MEMORY ERR: predicate container not created.\n");
        return MEMORY_ERROR;
    }
    term = create_tree();
    status = is_term(tok, &term);
    if (status != SUBTREE_OK){
        return status;
    }
    (*tree)->child = term;

    // The remainder of Pred is optional
    // (only if there is '+' | '-')
    type = (*tok)->type;
    if (match_arithmetic_type(type) &&
        !match_term_type(type)) {
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            return status;
        }
        term->sibling = op;

        pred = create_tree();
        status = is_predicate(tok, &pred);
        if (status != SUBTREE_OK){
            return status;
        }
        op->sibling = pred;
    }

    return status;
}

/* Checker of the whole expression */
int is_expression (t_table** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *pred, *op, *expr;
    enum TokenType type;
    int status;

    if (( *tree = create_tree_entry("EXPR", EXPR, 0) ) == NULL ) {
        printf("MEMORY ERR: expression container not created.\n");
        return MEMORY_ERROR;
    }

    pred = create_tree();
    status = is_predicate(tok, &pred);
    if (status != SUBTREE_OK){
        return status;
    }
    (*tree)->child = pred;

    //  if there is a conditional operator
    type = (*tok)->type;
    
    if (match_operator_type(type)){
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            return status;
        }
        pred->sibling = op;
        

        expr = create_tree();
        status = is_expression(tok, &expr);
        if (status != SUBTREE_OK){
            return status;
        }
        op->sibling = expr;
    }

     return status;
}