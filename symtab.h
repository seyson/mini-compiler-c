#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Implementation of a symbol table, i.e., an array (hash table) of linked lists.
Each record stores information about a unique symbol (identifier) that occurs in the program
(each scope in the program?).
Symbols with the same starting character are stored together, i.e., hash to the same value.

(key -> value)
a -> symbols that start with 'a'
b -> symbols that start with 'b'
...
z -> symbols that start with 'z'
_ -> symbols that start with '_'

Identifiers in general might be
- programs (maybe not if we don't allow '#' through the tokenizer)
- variables
- subroutines/functions (parameters, return type, etc., stored)
- subroutine/function parameters (must be available when processing a call)
- user-defined data types (structs, unions, typedef?)
- instruction labels
- constants too?

* when a new scope is created, we can push a new symbol table onto a stack of symbol tables, and store local data on the topmost table
* when a scope is closed, we pop the top symbol table off
* 

Information stored includes
- the type of identifier
- the type of variable/object (char, string, int, float, etc.)
- the value of the id (values assigned to variables or returned by function calls,
including intermediate ones generated by the compiler itself)
- size of the id (how many bytes? e.g., int: 4, float: 4)
- dimensions/length of the object (e.g., a 2D array of n*m elements?)
- 
*/

#define STACK_SIZE 100

typedef struct Node Node;
typedef struct List List;
typedef struct SymbolTableStack SymbolTableStack;

/* Stack of symbol tables */
struct SymbolTableStack {
    List* table[STACK_SIZE];
    int top;
};

struct Node {
    char* name; /* name of the symbol */
    char type; /* type of the symbol: int, real, char, array, or func */
    char elt_type; /* element type (for arrays) or return type (for functions) */
    int size; /* number of bytes that should be allocated */
    int addr; /* data location */
    int line; /* line declared */
    char params[12]; /* list of parameter types (for functions) */
    int num_of_params;
    int arrlength; /* length (1 for non-arrays, n for arrays) */
/*    union {*/
/*        int i;*/
/*        float f;*/
/*        char *s;*/
/*    };*/
    Node *next;
};

struct List {
    Node* head;
};

int h(char*);

/* Create a symbol table */
List* create_table(void);

void free_table(List*);

/* Return a pointer to a symbol's node if it exists in the symbol table (or NULL if it doesn't) */
Node* search_id(List*, char*);

/* Place the id in the symbol table if it doesn't exist, and return a pointer to the node */
Node* install_id(List*, char*);

void print_table(List*);

/* Add a symbol table to the top of the stack */
void push_symtab(List*, SymbolTableStack*);

/* Remove the topmost symbol table from stack */
void remove_symtab(SymbolTableStack*);

/* Return a pointer to (the first occurrence of) a symbol if it exists in the symtab stack (or return NULL if it doesn't) */
Node* search_symtabs(SymbolTableStack*, char*);

void print_stack(SymbolTableStack);

#endif