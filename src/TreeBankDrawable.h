//
// Created by Olcay Taner YILDIZ on 20.12.2023.
//

#ifndef ANNOTATEDTREE_TREEBANKDRAWABLE_H
#define ANNOTATEDTREE_TREEBANKDRAWABLE_H

#include <TreeBank.h>
#include <ViewLayerType.h>

Tree_bank_ptr create_tree_bank_drawable(const char *folder);

void tree_bank_clear_layer(Tree_bank_ptr tree_bank, View_layer_type layer_type);

void free_tree_bank_drawable(Tree_bank_ptr tree_bank);

#endif //ANNOTATEDTREE_TREEBANKDRAWABLE_H
