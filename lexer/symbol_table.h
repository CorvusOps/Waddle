/* 
* File        : symboltable.h
* Description : This file contains functions related to organised a symbol table. 
*               The functions implemented are:
*               create_symbol_table(), create_entry_for_symbol_table(), insert_to_symbol_table(), search_symbol_table(), display_symbol_table() 
*/


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* struct to hold each entry */
struct token_table
{
	char* lexeme; 
	int type;
	char* tok_name;
	int line;
	char * message;
	int valid;
	struct token_table* next_tok;
};

typedef struct token_table t_table;

/* Creates a new symbol table. */
t_table* create_symbol_table()
{
	t_table* table_ptr = NULL; // declare a pointer
	
	return table_ptr;
}

/* Create an entry for a lexeme, token pair. This will be called from the insert function */
t_table *create_entry_for_symbol_table( char *lexeme, int type, char*tok_name, int line)
{
	t_table *new_entry;

	/* Allocate space for new_entry */
	if( ( new_entry =(t_table*) malloc( sizeof( t_table ) ) ) == NULL ) {
		free(new_entry);
		return NULL;
	}
	
	/* Copy lexeme to new_entry location using strdup (string-duplicate). Return NULL if it fails */
	if( ( new_entry->lexeme = strdup( lexeme ) ) == NULL ) {
		return NULL;
	}
	
	new_entry->type = type;
	new_entry->tok_name = tok_name;
	new_entry->line = line;
	new_entry->next_tok = NULL;

	return new_entry;
}

/* search for an entry given a lexeme. Return a pointer to the entry of the lexeme exists, else return NULL */
t_table* search_symbol_table( t_table* hash_table_ptr, char* lexeme )
{
	t_table* myentry;
	
	while( myentry != NULL && strcmp( lexeme, myentry->lexeme ) != 0 )
	{
		myentry = myentry->next_tok;
	}

	if(myentry == NULL) // lexeme is not found
		return NULL;
	
	else // lexeme found
		return myentry;
}

// Traverse the hash table and print all the entries in file
void display_symbol_table(t_table* table_ptr)
{
	t_table* traverser;
	FILE *writeParsed=fopen("symbolTable.txt","w");
    
	fprintf(writeParsed,"\t\tlexeme\t\ttoken-type\t\ttoken-name\n");

	traverser = table_ptr;

	while( traverser != NULL)
	{
		fprintf(writeParsed,"%15s\t\t%3d\t\t%10s\n", traverser->lexeme, traverser->type, traverser->tok_name);
		traverser = traverser->next_tok;
	}
   
	fclose(writeParsed);
}

/* Insert an entry into a linked list. */
void insert_to_symbol_table( t_table** table_ptr, char* lexeme, char*tok_name, int type, int line, char* message)
{
	t_table* new_entry = NULL;

	new_entry = create_entry_for_symbol_table(lexeme, type, tok_name, line); // Create an entry using the <lexeme, token> pair

	if(new_entry == NULL) // In case there was some error while executing create_entry_for_symbol_table()
	{
		free(new_entry);
		printf("Insert failed. New entry could not be created.");
		exit(1);
	}

	if (message != NULL) {
		new_entry->message = message;
	}


	if (*table_ptr == NULL){
		*table_ptr = new_entry;
		return;
	}
	
	t_table* temp = *table_ptr;
	while (temp->next_tok != NULL)
		temp = temp->next_tok;
	temp->next_tok = new_entry;
	
}


int ends_with(const char* name, const char* extension, size_t length)
{
  const char* ldot = strrchr(name, '.');
  if (ldot != NULL)
  {
    if (length == 0)
      length = strlen(extension);
    return strncmp(ldot + 1, extension, length) == 0;
  }
  return 0;
}


