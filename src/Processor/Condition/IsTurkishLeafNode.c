//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <stddef.h>
#include <string.h>
#include "IsTurkishLeafNode.h"
#include "IsLeafNode.h"

bool is_turkish_leaf_node(const Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        char* data = get_layer_data(parse_node->layers, TURKISH_WORD);
        char* parent_data = parse_node->parent->data;
        return (data != NULL && !str_contains_c(data, '*') && !(strcmp(data, "0") == 0 && strcmp(parent_data, "-NONE-") == 0));
    }
    return false;
}
