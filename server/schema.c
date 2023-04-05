
#include "include/schema.h"

struct schema* schema_create() {
    struct schema* new_1 =(struct schema*) malloc(sizeof(struct schema));
    new_1->count = 0;
    new_1->length = 0;
    new_1->start = NULL;
    new_1->end = NULL;
    return new_1;
}


void column_add(struct schema* schema, const char* name, enum data_type content_type) {
    struct column* new_1 = column_create(name, content_type);
    if (schema->end)
        schema->end->next = new_1;
    else schema->start = new_1;
    schema->end = new_1;
}

void column_add_varchar(struct schema* schema, const char* name, enum data_type content_type, uint16_t size) {
    struct column* new_1 = column_create_varchar(name, content_type, size);
    if (schema->end)
        schema->end->next = new_1;
    else schema->start = new_1;
    schema->end = new_1;
}




void column_list_delete(struct column* list) {
    struct column* current = list;
    struct column* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

void schema_close(struct schema* schema) {
    column_list_delete(schema->start);
    free(schema);
}

uint32_t column_presence_count(const struct column* list, const size_t length, const char* name) {
    int32_t idx = 0;
    const struct column* current = list;
    if (list) {
        while (idx < length) {
            if (strcmp(current->name, name) == 0) return current->size;
            idx++;
            current=current->next;
        }
        return 0;
    }
    else return 0;
}


struct schema* schema_add_column(struct schema* schema, const char* name, enum data_type data_type) {
    if (column_presence_count(schema->start, schema->count, name) == 0) {
        column_add(schema, name, data_type);
        schema->count++;
        schema->length += schema->end->size;
        return schema;
    } else {
        printf("Can't add two attributes with the same name");
        return schema;
    }
}

struct schema* schema_add_column_varchar(struct schema* schema, const char* name, enum data_type data_type, uint16_t size) {
    if (column_presence_count(schema->start, schema->count, name) == 0) {
        column_add_varchar(schema, name, data_type, size);
        schema->count++;
        schema->length += schema->end->size;
        return schema;
    } else {
        printf("Can't add two attributes with the same name");
        return schema;
    }
}

struct column* column_create(const char* name, enum data_type content_type ) {
    struct column* new_1 = (struct column*) malloc(sizeof (struct column));
    if (new_1 == NULL || content_type == VARCHAR) {
        return NULL;
    }
    strncpy(new_1->name, "", MAX_NAME_LENGTH);
    strncpy(new_1->name, name, strlen(name));
    new_1->data_type = content_type;
    switch (content_type) {
        case INTEGER:
            new_1->size = sizeof(int32_t);
            break;
        case BOOLEAN:
            new_1->size = sizeof(bool);
            break;
        case DOUBLE:
            new_1->size = sizeof(double);
            break;
    }
    new_1->next = NULL;
    return new_1;
}


struct column* column_create_varchar(const char* name, enum data_type content_type, uint16_t size) {
    if (content_type != VARCHAR)
        return NULL;

    struct column* new_1 =(struct column*) malloc(sizeof (struct column));
    if (!new_1) {
        return NULL;
    }
    strncpy(new_1->name, "", MAX_NAME_LENGTH);
    strncpy(new_1->name, name, strlen(name));

    new_1->next = NULL;
    new_1->size = sizeof(char) * size;
    new_1->data_type = content_type;
    return new_1;
}



struct column* column_delete(struct column* current, const char* name, struct schema* schema) {
    struct column* column;
    if (!current)
        return NULL;
    else if (strcmp(current->name, name) == 0) {
        column = current->next;
        free(current);
        return column;
    } else {
        current->next = column_delete(current->next, name, schema);
        if (current->next == NULL) {
            schema->end = current;
        }
        return current;
    }
}
