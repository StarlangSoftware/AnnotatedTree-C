//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include <RegularExpression.h>
#include "IsNumber.h"
#include "IsLeafNode.h"

bool is_number_node(const Parse_node_drawable *parse_node) {
    if (is_leaf_node(parse_node)){
        char* data = get_layer_data(parse_node->layers, ENGLISH_WORD);
        char* parent_data = parse_node->parent->data;
        Regular_expression_ptr regex = create_regular_expression("[0-9,\\.]+");
        bool result = strcmp(parent_data, "CD") == 0 && full_matches(regex, data);
        free_regular_expression(regex);
        return result;
    }
    return false;
}
