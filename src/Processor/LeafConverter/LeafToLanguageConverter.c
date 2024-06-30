//
// Created by Olcay Taner YILDIZ on 17.12.2023.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "LeafToLanguageConverter.h"

/**
 * Converts the data in the leaf node to string, except shortcuts to parentheses are converted to its normal forms,
 * '*', '0', '-NONE-' are converted to empty string.
 * @param leaf_node Node to be converted to string.
 * @param layer_type Layer for which conversion done.
 * @return String form of the data, except shortcuts to parentheses are converted to its normal forms,
 * '*', '0', '-NONE-' are converted to empty string.
 */
char *leaf_converter(Parse_node_drawable_ptr leaf_node, View_layer_type layer_type) {
    char* layerData = get_parse_node_layer_data(leaf_node, layer_type);
    char* parentLayerData = get_parse_node_layer_data(leaf_node->parent, layer_type);
    if (layerData != NULL){
        if (str_contains_c(layerData, '*') || (strcmp(layerData, "0") == 0 && strcmp(parentLayerData, "-NONE-") == 0)){
            return "";
        } else {
            char tmp[MAX_WORD_LENGTH];
            sprintf(tmp, " %s", layerData);
            return clone_string(tmp);
        }
    } else {
        return "";
    }
}
