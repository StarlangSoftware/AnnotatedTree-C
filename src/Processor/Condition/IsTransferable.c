//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsTransferable.h"
#include "IsLeafNode.h"
#include "IsNoneNode.h"
#include "IsNullElement.h"

bool is_transferable(Parse_node_drawable *parse_node, View_layer_type second_language) {
    if (is_leaf_node(parse_node)){
        if (is_none_node(parse_node, second_language)){
            return false;
        }
        return !is_null_element(parse_node);
    }
    return false;
}
