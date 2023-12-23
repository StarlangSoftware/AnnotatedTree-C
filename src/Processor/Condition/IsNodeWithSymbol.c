//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsNodeWithSymbol.h"

bool is_node_with_symbol(Parse_node_drawable *parse_node, const char *symbol) {
    if (parse_node->children->size > 0){
        return strcmp(get_data2(parse_node), symbol) == 0;
    } else {
        return false;
    }
}
