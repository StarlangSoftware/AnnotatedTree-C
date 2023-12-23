//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsPredicateVerbNode.h"
#include "IsVerbNode.h"

bool is_predicate_verb_node(Parse_node_drawable *parse_node, Word_net_ptr word_Net) {
    Layer_info_ptr layer_info = parse_node->layers;
    return is_verb_node(parse_node, word_Net) && layer_info != NULL && strcmp(get_layer_argument(layer_info)->argument_type, "PREDICATE") == 0;
}
