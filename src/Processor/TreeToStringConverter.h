//
// Created by Olcay Taner YILDIZ on 22.12.2023.
//

#ifndef ANNOTATEDTREE_TREETOSTRINGCONVERTER_H
#define ANNOTATEDTREE_TREETOSTRINGCONVERTER_H

#include "../ParseNodeDrawable.h"
#include "../ParseTreeDrawable.h"

char* convert_to_string(Parse_node_drawable_ptr parse_node, View_layer_type layer_type);

char* convert(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type);

#endif //ANNOTATEDTREE_TREETOSTRINGCONVERTER_H
