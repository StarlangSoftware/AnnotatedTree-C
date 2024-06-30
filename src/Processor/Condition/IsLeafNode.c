//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsLeafNode.h"

/**
 * Checks if the parse node is a leaf node, i.e., it has no child.
 * @param parse_node Parse node to check.
 * @return True if the parse node is a leaf node, false otherwise.
 */
bool is_leaf_node(const Parse_node_drawable *parse_node) {
    return parse_node->children->size == 0;
}
