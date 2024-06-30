//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsEnglishLeafNode.h"
#include "IsLeafNode.h"
#include "IsNullElement.h"

/**
 * Checks if the parse node is a leaf node and contains a valid English word in its data.
 * @param parse_node Parse node to check.
 * @return True if the parse node is a leaf node and contains a valid English word in its data; false otherwise.
 */
bool is_english_leaf_node(const Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        return !is_null_element(parse_node);
    }
    return false;
}
