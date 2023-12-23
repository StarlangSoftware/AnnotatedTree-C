//
// Created by Olcay Taner YILDIZ on 23.12.2023.
//

#include <stddef.h>
#include "DestroyLayers.h"

void destroy_layers(Parse_node_drawable_ptr parse_node) {
    Layer_info_ptr layer_info = parse_node->layers;
    if (layer_info != NULL){
        english_clear(layer_info);
        dependency_clear(layer_info);
        meta_morphemes_moved_clear(layer_info);
    }
}
