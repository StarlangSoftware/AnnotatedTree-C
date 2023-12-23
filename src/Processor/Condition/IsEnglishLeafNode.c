//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsEnglishLeafNode.h"
#include "IsLeafNode.h"
#include "IsNullElement.h"

bool is_english_leaf_node(const Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        return !is_null_element(parse_node);
    }
    return false;
}
