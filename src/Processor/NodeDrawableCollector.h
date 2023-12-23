//
// Created by Olcay Taner YILDIZ on 22.12.2023.
//

#ifndef ANNOTATEDTREE_NODEDRAWABLECOLLECTOR_H
#define ANNOTATEDTREE_NODEDRAWABLECOLLECTOR_H

#include "../ParseNodeDrawable.h"

void collect_nodes(Parse_node_drawable_ptr parse_node,
                   Array_list_ptr collected,
                   bool (*node_condition)(const Parse_node_drawable* parse_node));

void collect_nodes2(Parse_node_drawable_ptr parse_node,
                    Array_list_ptr collected,
                    bool (*node_condition)(const Parse_node_drawable* parse_node, const void* data),
                    void* data);

Array_list_ptr collect(Parse_node_drawable_ptr root_node, bool (*node_condition)(const Parse_node_drawable* parse_node));

Array_list_ptr collect2(Parse_node_drawable_ptr root_node, bool (*node_condition)(const Parse_node_drawable* parse_node, const void* data), void* data);

#endif //ANNOTATEDTREE_NODEDRAWABLECOLLECTOR_H
