#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include "ast.h"
#include "mm_malloc.h"

#include "stdio.h"
char* safe_string_copy (const char* from);
void safe_string_concatenation(char** str, const char * str2);
void indent(int indentation, char** src);
char* to_string_general(ast_node* node, int indentation);
void output(ast_node* root);
#endif
