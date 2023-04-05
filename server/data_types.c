
#include "include/data_types.h"

bool integer_compare(char* row_ptr,const void* value, uint32_t offset) {
    int32_t comparing = (int32_t) *(row_ptr + offset);
    int32_t expecting = *((int32_t*) value);
    if (comparing == expecting) {
        return true;
    }
    return false;
}

bool boolean_compare(char* row_ptr, const void* value, uint32_t offset) {
    bool comparing = (bool) *(row_ptr + offset);
    bool expecting = *((bool*) value);
    if (comparing == expecting) {
        return true;
    }
    return false;
}


bool double_compare(char* row_ptr, const void* value, uint32_t offset) {
    double* comparing = (double*) (row_ptr + offset);
    double expecting = *((double*) value);
    if (*comparing == expecting) {
        return true;
    }
    return false;
}

bool varchar_compare(char* row_ptr,const void* value, uint32_t offset, uint16_t column_size) {
    char* comparing = (char*) (row_ptr + offset);
    char* expecting = *((char**) value);
    if (strcmp(comparing, expecting) == 0) {
        return true;
    }
    return false;
}

void integer_update(char* row_ptr,const void* value, uint32_t offset) {
    int32_t* original = (int32_t*) (row_ptr + offset);
    int32_t expecting = *((int32_t*) value);
    *original = expecting;
}

void boolean_update(char* row_ptr,const void* value, uint32_t offset) {
    bool* original = (bool*) (row_ptr + offset);
    bool expecting = *((bool*) value);
    *original = expecting;
}

void double_update(char* row_ptr,const void* value, uint32_t offset) {
    double* original = (double*) (row_ptr + offset);
    double expecting = *((double*) value);
    *original = expecting;
}

void varchar_update(char* row_ptr,const void* value, uint32_t offset, uint16_t column_size) {
    char* original = (char*) row_ptr + offset;
    char* expecting = *((char**) value);
    strcpy(original, expecting);
}


char * integer_output(char *begin, uint32_t offset, char *buf) {
    int32_t* value = (int32_t*) (begin + offset);
    printf("%" PRId32 " ", *value);
    char buffer[128];
    sprintf(buffer, "%d", *value);
    if (buf) {
        safe_string_concatenation(&buf, buffer);
    }
    return buf;
}

char * boolean_output(char *begin, uint32_t offset, char *buf) {
    bool* value = (bool*) (begin + offset);
    printf("%s ", *value ? "T" : "F");
    char buffer[128];
    sprintf(buffer, "%s ", *value ? "T" : "F");
    if (buf) {
        safe_string_concatenation(&buf, buffer);
    }
    return buf;
}

char * double_output(char *begin, uint32_t offset, char *buf) {
    double* value = (double*) (begin + offset);
    printf("%f ", *value);
    char buffer[128];
    sprintf(buffer, "%f ", *value);
    if (buf) {
        safe_string_concatenation(&buf, buffer);
    }
    return buf;
}

char * varchar_output(char *begin, uint32_t offset, char *buf) {
    char* value = (char*) (begin + offset);
    printf("%s ", value);
    char buffer[128];
    sprintf(buffer, "%s ", value);
    if (buf) {
        safe_string_concatenation(&buf, buffer);
    }
    return buf;
}

char * data_output(char *begin, struct column *columns, uint16_t length, char *buf) {
    uint16_t cursor = 0;

    for (size_t i = 0; i < length; i++) {
        switch (columns[i].data_type) {
            case INTEGER:
                buf = integer_output(begin, cursor, buf);
                break;
            case BOOLEAN:
                buf = boolean_output(begin, cursor, buf);
                break;
            case VARCHAR:
                buf = varchar_output(begin, cursor, buf);
                break;
            case DOUBLE:
                buf = double_output(begin, cursor, buf);
                break;
        }
        cursor += columns[i].size;
    }
    safe_string_concatenation(&buf, "\n");
    printf("\n");
    return buf;
}


char* safe_string_copy (const char* from) {
    int count = strlen(from);
    char* ret =(char*) malloc(sizeof(char) * (count + 1));
    strcpy(ret, from);
    return ret;
}

void safe_string_concatenation (char** str, const char * str2) {
    char* str1 = *str;
    int first_len = strlen(str1), second_len = strlen(str2);
    char * new_str = (char*)malloc(sizeof(char) * (first_len + second_len + 1));
    strcat(new_str, str1);
    strcat(new_str, " ");
    strcat(new_str, str2);
    *str = new_str;
}

