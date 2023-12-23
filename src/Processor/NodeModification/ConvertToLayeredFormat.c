//
// Created by Olcay Taner YILDIZ on 23.12.2023.
//

#include "ConvertToLayeredFormat.h"

void convert_to_layered_format(Parse_node_drawable_ptr parse_node) {
    if (parse_node->children->size == 0){
        char* name = parse_node->data;
        clear_layers(parse_node);
        set_layer_data(parse_node->layers, ENGLISH_WORD, name);
        clear_data(parse_node);
    }
}
