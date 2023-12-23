//
// Created by Olcay Taner YILDIZ on 17.12.2023.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "LeafToLanguageConverter.h"

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
