
#ifndef LLP1_DATA_TYPES_H
#define LLP1_DATA_TYPES_H


#include <stdbool.h>
#include <inttypes.h>
#include "../struct/database.h"
#include "../struct/table.h"
#include "file.h"
#ifdef __cplusplus
extern "C" {
#endif
void integer_update(char* row_ptr,const void* value, uint32_t offset);
void boolean_update(char* row_ptr,const void* value, uint32_t offset);
void varchar_update(char* row_ptr,const void* value, uint32_t offset, uint16_t column_size);
void double_update(char* row_ptr,const void* value, uint32_t offset);


char * integer_output(char *begin, uint32_t offset, char *buf);
char * boolean_output(char *begin, uint32_t offset, char *buf);
char * varchar_output(char *begin, uint32_t offset, char *buf);
char * double_output(char *begin, uint32_t offset, char *buf);
char * data_output(char *begin, struct column *columns, uint16_t length, char *buf);

bool integer_compare(char* row_ptr,const void* value, uint32_t offset);
bool boolean_compare(char* row_ptr,const void* value, uint32_t offset);
bool varchar_compare(char* row_ptr,const void* value, uint32_t offset, uint16_t column_size);
bool double_compare(char* row_ptr, const void* value, uint32_t offset);

char* safe_string_copy (const char* from);
void safe_string_concatenation(char** str, const char * str2);
#ifdef __cplusplus
}
#endif

#endif //LLP1_DATA_TYPES_H
