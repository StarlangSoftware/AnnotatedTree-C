//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsPredicateVerbNode.h"
#include "IsVerbNode.h"

/**
 * Checks if the node is a leaf node and at least one of the semantic ids of the parse node belong to a verb synset,
 * and the semantic role of the node is PREDICATE.
 * @param parse_node Parse node to check.
 * @param word_Net Wordnet used for checking the pos tag of the synset.
 * @return True if the node is a leaf node and at least one of the semantic ids of the parse node belong to a verb
 *          synset and the semantic role of the node is PREDICATE, false otherwise.
 */
bool is_predicate_verb_node(Parse_node_drawable *parse_node, Word_net_ptr word_Net) {
    Layer_info_ptr layer_info = parse_node->layers;
    return is_verb_node(parse_node, word_Net) && layer_info != NULL && strcmp(get_layer_argument(layer_info)->argument_type, "PREDICATE") == 0;
}
