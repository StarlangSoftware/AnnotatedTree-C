//
// Created by Olcay Taner YILDIZ on 22.12.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>
#include "TreeToStringConverter.h"
#include "LeafConverter/LeafToLanguageConverter.h"
#include "LeafConverter/LeafToRootFormConverter.h"

/**
 * Converts recursively a parse node to a string. If it is a leaf node, calls the converter's leafConverter method,
 * otherwise concatenates the converted strings of its children.
 * @param parse_node Parse node to convert to string.
 * @param layer_type Layer for which conversion done.
 * @return String form of the parse node and all of its descendants.
 */
char *convert_to_string(Parse_node_drawable_ptr parse_node, View_layer_type layer_type) {
    if (parse_node->children->size == 0){
        switch (layer_type) {
            case PERSIAN_WORD:
            case ENGLISH_WORD:
            case TURKISH_WORD:
                return leaf_converter(parse_node, layer_type);
            case WORD:
            default:
                return leaf_to_root_form_converter(parse_node);
        }
    } else {
        char st[MAX_WORD_LENGTH] = "";
        for (int i = 0; i < parse_node->children->size; i++){
            char* child_string = convert_to_string(array_list_get(parse_node->children, i), layer_type);
            sprintf(st, "%s%s", st, child_string);
            free_(child_string);
        }
        return clone_string(st);
    }
}

/**
 * Calls the convertToString method with root of the tree to convert the parse tree to string.
 * @param parse_tree Parse tree to convert.
 * @param layer_type Layer for which conversion done.
 * @return String form of the parse tree.
 */
char *convert(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type) {
    return convert_to_string(parse_tree->root, layer_type);
}
