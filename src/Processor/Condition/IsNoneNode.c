//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <stddef.h>
#include <string.h>
#include "IsNoneNode.h"
#include "IsLeafNode.h"

/**
 * Checks if the data of the parse node is '*NONE*'.
 * @param parse_node Parse node to check.
 * @return True if the data of the parse node is '*NONE*', false otherwise.
 */
bool is_none_node(Parse_node_drawable *parse_node, View_layer_type second_language) {
    if (is_leaf_node(parse_node)){
        char* data = get_parse_node_layer_data(parse_node, second_language);
        return data != NULL && strcmp(data, "*NONE*") == 0;
    }
    return false;
}
