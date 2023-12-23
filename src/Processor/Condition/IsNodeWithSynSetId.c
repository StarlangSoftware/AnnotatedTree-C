//
// Created by Olcay Taner YILDIZ on 16.12.2023.
//

#include <string.h>
#include "IsNodeWithSynSetId.h"
#include "IsLeafNode.h"

bool is_node_with_syn_set_id(const Parse_node_drawable *parse_node, const char *id) {
    if (is_leaf_node(parse_node)){
        Layer_info_ptr layer_info = parse_node->layers;
        for (int i = 0; i < get_number_of_meanings(layer_info); i++){
            char* syn_set_id = get_semantic_at(layer_info, i);
            if (strcmp(syn_set_id, id) == 0){
                return true;
            }
        }
    }
    return false;
}
