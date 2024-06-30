//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsPunctuationNode.h"
#include "IsLeafNode.h"

/**
 * Checks if the node is a leaf node and contains punctuation as the data.
 * @param parse_node Parse node to check.
 * @return True if the node is a leaf node and contains punctuation as the data, false otherwise.
 */
bool is_punctuation_node(Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        char* data = get_parse_node_layer_data(parse_node, ENGLISH_WORD);
        return is_punctuation(data) && strcmp(data, "$") != 0;
    }
    return false;
}
