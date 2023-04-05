

#ifndef LLP1_TABLE_INCLUDE_H
#define LLP1_TABLE_INCLUDE_H

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "../struct/table.h"
#include "../struct/query.h"
#include "file.h"

#define MAX_NAME_LENGTH 20

#ifdef __cplusplus
extern "C" {
#endif
void attribute_add(struct row* row,const char* name, enum data_type content_type,const void* value);

int32_t column_get_offset(const struct column *list,const char *name, const size_t length);

struct row* row_create(struct table* table);


void row_close(struct row* row);
void row_insert(struct row* row);
char* row_select(struct query *query, bool show_output, char *buf);
char* row_update(struct query *query, bool show_output, char *buf);
char* row_delete(struct query *query, bool show_output, char *buf);


void integer_add(struct row* row, int32_t value, uint32_t offset);
void boolean_add(struct row* row, bool value, uint32_t offset);
void varchar_add(struct row* row, char* value, uint32_t offset, uint32_t length);
void double_add(struct row* row, double value, uint32_t offset);

#ifdef __cplusplus
}
#endif
#endif //LLP1_TABLE_INCLUDE_H
