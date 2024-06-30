//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <stddef.h>
#include <string.h>
#include "IsNodeWithPredicate.h"
#include "IsNodeWithSynSetId.h"

/**
 * Checks if at least one of the semantic ids of the parse node is equal to the given id and also the node is
 * annotated as PREDICATE with semantic role.
 * @param parse_node Parse node to check.
 * @param id Synset id to check
 * @return True if at least one of the semantic ids of the parse node is equal to the given id and also the node is
 * annotated as PREDICATE with semantic role, false otherwise.
 */
bool is_node_with_predicate(const Parse_node_drawable *parse_node, const char* id) {
    Layer_info_ptr layer_info = parse_node->layers;
    return is_node_with_syn_set_id(parse_node, id)
    && layer_info != NULL
    && get_layer_data(layer_info, PROPBANK) != NULL
    && strcmp(get_layer_data(layer_info, PROPBANK), "PREDICATE") == 0;
}
