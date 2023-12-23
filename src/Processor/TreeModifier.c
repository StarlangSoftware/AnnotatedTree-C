//
// Created by Olcay Taner YILDIZ on 23.12.2023.
//

#include "TreeModifier.h"

void node_modify(Parse_node_drawable_ptr parse_node, void (*modifier_function)(Parse_node_drawable_ptr)) {
    modifier_function(parse_node);
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
        node_modify(child, modifier_function);
    }
}

void modify(Parse_tree_drawable_ptr parse_tree, void (*modifier_function)(Parse_node_drawable_ptr)) {
    node_modify(parse_tree->root, modifier_function);
}
