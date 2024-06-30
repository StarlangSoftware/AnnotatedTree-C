//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsProperNoun.h"
#include "IsLeafNode.h"

/**
 * Checks if the node is a leaf node and its parent has the tag NNP or NNPS.
 * @param parse_node Parse node to check.
 * @return True if the node is a leaf node and its parent has the tag NNP or NNPS, false otherwise.
 */
bool is_node_proper_noun(Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        char* parent_data = get_data2(parse_node->parent);
        return string_in_list(parent_data, (char*[]){"NNP", "NNPS"}, 2);
    }
    return false;
}
