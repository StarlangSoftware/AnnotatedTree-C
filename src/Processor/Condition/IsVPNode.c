//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <Symbol.h>
#include "IsVPNode.h"

/**
 * Checks if the node is not a leaf node and its tag is VP.
 * @param parse_node Parse node to check.
 * @return True if the node is not a leaf node and its tag is VP, false otherwise.
 */
bool is_vp_node(Parse_node_drawable *parse_node) {
    return parse_node->children->size > 0 && is_VP(get_data2(parse_node));
}
