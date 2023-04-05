//
// Created by KuPuK on 14.03.2023.
//

#ifndef LLP1_QUERY_H
#define LLP1_QUERY_H
#include <inttypes.h>
#include "table.h"
enum query_types {
    SELECT = 0,
    UPDATE,
    DELETE,
};

struct query {
    const char** name;
    enum query_types operation;
    int32_t number;
    const void** value;
    struct table* table;
};

struct query_join {
    struct table* left;
    struct table* right;
    const char* left_column;
    const char* right_column;
};

#endif //LLP1_QUERY_H
