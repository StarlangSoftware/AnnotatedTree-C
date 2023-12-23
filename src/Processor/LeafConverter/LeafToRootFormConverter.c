//
// Created by Olcay Taner YILDIZ on 17.12.2023.
//

#include <stddef.h>
#include <stdio.h>
#include "LeafToRootFormConverter.h"

char *leaf_to_root_form_converter(Parse_node_drawable_ptr parse_node) {
    Layer_info_ptr layer_info = parse_node->layers;
    char root_words[MAX_WORD_LENGTH] = "";
    for (int i = 0; i < get_number_of_words(layer_info); i++) {
        char* root = get_morphological_parse_at(layer_info, i)->root;
        if (root != NULL){
            sprintf(root_words, "%s %s", root_words, root);
        }
    }
    return clone_string(root_words);
}
