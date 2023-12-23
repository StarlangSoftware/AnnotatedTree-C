//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <stddef.h>
#include <string.h>
#include "IsNodeWithPredicate.h"
#include "IsNodeWithSynSetId.h"

bool is_node_with_predicate(const Parse_node_drawable *parse_node, const char* id) {
    Layer_info_ptr layer_info = parse_node->layers;
    return is_node_with_syn_set_id(parse_node, id)
    && layer_info != NULL
    && get_layer_data(layer_info, PROPBANK) != NULL
    && strcmp(get_layer_data(layer_info, PROPBANK), "PREDICATE") == 0;
}
