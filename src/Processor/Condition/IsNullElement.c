//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsNullElement.h"
#include "IsLeafNode.h"

/**
 * Checks if the parse node is a leaf node and its data is '*' and its parent's data is '-NONE-'.
 * @param parse_node Parse node to check.
 * @return True if the parse node is a leaf node and its data is '*' and its parent's data is '-NONE-', false
 * otherwise.
 */
bool is_null_element(const Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        char* data = get_layer_data(parse_node->layers, ENGLISH_WORD);
        char* parent_data = parse_node->parent->data;
        return str_contains_c(data, '*') || (strcmp(data, "0") == 0 && strcmp(parent_data, "-NONE-") == 0);
    }
    return false;
}
