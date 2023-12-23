//
// Created by Olcay Taner YILDIZ on 23.12.2023.
//

#ifndef ANNOTATEDTREE_TREEMODIFIER_H
#define ANNOTATEDTREE_TREEMODIFIER_H

#include "../ParseNodeDrawable.h"
#include "../ParseTreeDrawable.h"

void node_modify(Parse_node_drawable_ptr parse_node, void (*modifier_function)(Parse_node_drawable_ptr parse_node));

void modify(Parse_tree_drawable_ptr parse_tree, void (*modifier_function)(Parse_node_drawable_ptr parse_node));

#endif //ANNOTATEDTREE_TREEMODIFIER_H
