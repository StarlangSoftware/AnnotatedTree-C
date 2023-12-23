//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include "IsVerbNode.h"
#include "IsLeafNode.h"

bool is_verb_node(Parse_node_drawable *parse_node, Word_net_ptr word_net) {
    Layer_info_ptr layer_info = parse_node->layers;
    if (is_leaf_node(parse_node) && layer_info != NULL && get_layer_data(layer_info, SEMANTICS) != NULL){
        for (int i = 0; i < get_number_of_meanings(layer_info); i++){
            char* syn_set_id = get_semantic_at(layer_info, i);
            if (get_syn_set_with_id(word_net, syn_set_id) != NULL && get_syn_set_with_id(word_net, syn_set_id)->pos == VERB_POS){
                return true;
            }
        }
    }
    return false;
}
