//
// Created by Olcay Taner YILDIZ on 20.12.2023.
//

#include <Memory/Memory.h>
#include <dirent.h>
#include "TreeBankDrawable.h"
#include "ParseTreeDrawable.h"

/**
 * A constructor of {@link TreeBankDrawable} class which reads all {@link ParseTreeDrawable} files inside the given
 * folder. For each file inside that folder, the constructor creates a ParseTreeDrawable and puts in inside the list
 * parseTrees.
 * @param folder Folder where all parseTrees reside.
 */
Tree_bank_ptr create_tree_bank_drawable(const char *folder) {
    Tree_bank_ptr result = malloc_(sizeof(Tree_bank), "create_tree_bank_drawable");
    result->parse_trees = create_array_list();
    DIR *d;
    struct dirent *dir;
    d = opendir(folder);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG){
                Parse_tree_drawable_ptr parse_tree = create_parse_tree_drawable2(folder, dir->d_name);
                array_list_add(result->parse_trees, parse_tree);
            }
        }
        closedir(d);
    }
    array_list_sort(result->parse_trees, (int (*)(const void *, const void *)) compare_parse_tree_drawable);
    return result;
}

/**
 * Clears the given layer for all nodes in all trees
 * @param tree_bank Current treeBank object.
 * @param layer_type Layer name
 */
void tree_bank_clear_layer(Tree_bank_ptr tree_bank, View_layer_type layer_type) {
    for (int i = 0; i < tree_bank->parse_trees->size; i++){
        Parse_tree_drawable_ptr parse_tree = array_list_get(tree_bank->parse_trees, i);
        tree_clear_layer(parse_tree, layer_type);
    }
}

/**
 * Frees memory allocated for the tree bank. Frees array list of parse trees.
 * @param tree_bank Tree bank to be deallocated.
 */
void free_tree_bank_drawable(Tree_bank_ptr tree_bank) {
    free_array_list(tree_bank->parse_trees, (void (*)(void *)) free_parse_tree_drawable);
    free_(tree_bank);
}

