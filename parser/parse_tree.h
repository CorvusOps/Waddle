/* 
* File        : parsetree.h
* Description : This file contains functions related to organised a Parse tree. 
*               The functions implemented are:
*               create_tree(), create_entry(), free_parse_tree(), display() 
*/


#include "../lexer/tok_char.h"
#include "../lexer/symbol_table.h"

struct parse_tree {
    char* token;
    int type;
    int line;
    struct parse_tree* child;
    struct parse_tree* sibling;
};


#define PARSING_ERROR -1
#define SUBTREE_OK 0
#define MEMORY_ERROR 1
#define STILL_CHILD 3

typedef struct parse_tree p_tree;


/* Create a new ParseTree. */
p_tree* create_tree(){
    
    p_tree* tree = NULL; // declare a pointer
	
	return tree;

}

/* Create a Entry for a token. */
p_tree* create_tree_entry(char* token, int type, int line) {
    p_tree* entry;

    /* Allocate space for entry */
	if( ( entry =(p_tree*) malloc( sizeof( p_tree ) ) ) == NULL ) {
		free(entry);
		return NULL;
	}

    if( ( entry->token = strdup( token ) ) == NULL ) {
		return NULL;
	}
	
	entry->type = type;
    entry->line = line;
	entry->child = NULL;
    entry->sibling = NULL;

	return entry;
}


/* Print the Parse Tree recursively. */
void print_PT(p_tree* tree, int indent) {
    if (tree == NULL)
        return;
    
    // This is a Depth-First print
    if (indent > 0) {
        indent += 1;
        char space[indent];
        memset(space, ' ', indent * sizeof(char));
        memset(space+indent, '\0', sizeof(char));
        printf("%s", space);
    }
    
    // Handler for Line Tokens and Program tokens
    if (tree->type) {
        printf("<%s, %d>\n", tree->token, tree->type);
    } else {
        printf("<%s>\n", tree->token);
    }

    p_tree* sibling;
    p_tree* child;
    sibling = tree->sibling;
    child = tree->child;
    print_PT(child, indent + 2);
    print_PT(sibling, indent);
}

/* Print the Parse Tree from the indent. */
void print_parse_tree(p_tree* tree) {
    print_PT(tree, 0);
}

/* Print syntax table file */
void display_syntax_table(t_table* table)
{
	t_table* traverser;
    int line = 1, is_valid =1;
    char *messageAgg, *tokenAgg, *token ;
	
    traverser = table;
    tokenAgg = "";

    FILE *syntax;
    syntax = fopen("syntaxTable.txt","w"); 
	fprintf(syntax,"lineNo token\tvalidity\t\tmessage\n");
    
    messageAgg = (char *) malloc(10);
    strcpy(messageAgg, "");
    fclose(syntax);
	while( traverser != NULL )
	{   
        syntax = fopen("syntaxTable.txt","a+"); 
        fprintf(syntax,"\t%d\t%s\n",traverser->line, traverser->lexeme);
        fclose(syntax);
        if (traverser->valid == 0) {
            is_valid = 0;
            messageAgg = (char *) realloc(messageAgg, 200);
            strcat(messageAgg, traverser->message);
        }
        
        if (traverser->next_tok->line > line || traverser->next_tok == NULL)  {
            if (is_valid == 1) {
                syntax = fopen("syntaxTable.txt","a+");
                fprintf(syntax,"%d\t%s\t\t%s\t%s\n",traverser->line, traverser->lexeme,"valid", "No Errors.");
                fclose(syntax);
            } else {
                syntax = fopen("syntaxTable.txt","a+");
                fprintf(syntax,"\t%d\t%s\t\t%s\t%s\n",traverser->line, traverser->lexeme,"invalid", messageAgg);
                fclose(syntax);
            }
            line++;
            is_valid = 1;
        }
        

		traverser = traverser->next_tok;
	}
    
   
}


/* Free memory for the ParseTree and all its internal data, including children and siblings. */
void free_parse_tree(p_tree* tree) {
    p_tree* sibling;
    p_tree* child;
    sibling = tree->sibling;
    child = tree->child;
    free(tree);

    if (sibling != NULL)
        free_parse_tree(sibling);
    if (child != NULL)
        free_parse_tree(child);
}
