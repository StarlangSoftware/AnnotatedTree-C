//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsLeafNode.h"

bool is_leaf_node(const Parse_node_drawable *parse_node) {
    return parse_node->children->size == 0;
}
