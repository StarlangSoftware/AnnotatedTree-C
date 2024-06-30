//
// Created by Olcay Taner YILDIZ on 19.12.2023.
//

#include <Memory/Memory.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include "ParseTreeDrawable.h"
#include "Processor/NodeDrawableCollector.h"
#include "Processor/Condition/IsTurkishLeafNode.h"

/**
 * Another constructor for the ParseTreeDrawable. Sets the file description and reads the tree from the file
 * description.
 * @param file_description File description that contains the path, index and extension information.
 */
Parse_tree_drawable_ptr create_parse_tree_drawable(File_description_ptr file_description) {
    Parse_tree_drawable_ptr result = malloc_(sizeof(Parse_tree_drawable), "create_parse_tree_drawable");
    result->file_description = file_description;
    char* file_name = get_file_name(file_description);
    read_from_file(result, file_name);
    free_(file_name);
    return result;
}

/**
 * Frees memory allocated for the parse tree.
 * @param parse_tree Parse tree to be deallocated.
 */
void free_parse_tree_drawable(Parse_tree_drawable_ptr parse_tree) {
    free_file_description(parse_tree->file_description);
    free_parse_node_drawable(parse_tree->root);
    free_(parse_tree);
}

/**
 * Constructor for the ParseTreeDrawable. Sets the file description and reads the tree from the file description.
 * @param path Path of the tree
 * @param raw_file_name File name of the tree such as 0123.train.
 */
Parse_tree_drawable_ptr create_parse_tree_drawable2(const char *path, const char *raw_file_name) {
    File_description_ptr file_description = create_file_description(path, raw_file_name);
    return create_parse_tree_drawable(file_description);
}

/**
 * Another constructor for the ParseTreeDrawable. Sets the file description and reads the tree from the file
 * description.
 * @param path Path of the tree
 * @param extension Extension of the file such as train, test or dev.
 * @param index Index of the file such as 1235.
 */
Parse_tree_drawable_ptr create_parse_tree_drawable3(const char *path, const char *extension, int index) {
    File_description_ptr file_description = create_file_description2(path, extension, index);
    return create_parse_tree_drawable(file_description);
}

/**
 * Another constructor for the ParseTreeDrawable. Sets the file description and reads the tree from the file
 * description.
 * @param path Path of the tree
 * @param file_description File description that contains the path, index and extension information.
 */
Parse_tree_drawable_ptr create_parse_tree_drawable4(const char *path, File_description_ptr file_description) {
    return create_parse_tree_drawable3(path, file_description->extension, file_description->index);
}

/**
 * Reads the parse tree from the given line. It sets the root node which calls ParseNodeDrawable constructor
 * recursively.
 * @param file_name Line containing the definition of the tree.
 */
void read_from_file(Parse_tree_drawable_ptr parse_tree, const char *file_name) {
    char line[MAX_LINE_LENGTH];
    FILE* input_file = fopen(file_name, "r");
    fgets(line, MAX_LINE_LENGTH, input_file);
    line[strcspn(line, "\n")] = 0;
    if (str_contains(line, "(") && str_contains(line, ")")){
        String_ptr st = substring(line, str_find_c(line, "(") + 1, str_find_last_c(line, ")") - str_find_c(line, "("));
        String_ptr st2 = trim(st->s);
        free_string_ptr(st);
        parse_tree->root = create_parse_node_drawable(NULL, st2->s, false, 0);
        free_string_ptr(st2);
    }
    fclose(input_file);
}

/**
 * Calculates the maximum depth of the tree.
 * @param parse_tree Currect parse tree object
 * @return The maximum depth of the tree.
 */
int tree_max_depth(Parse_tree_drawable_ptr parse_tree) {
    return max_depth(parse_tree->root);
}

/**
 * The method checks if all nodes in the tree has the annotation in the given layer.
 * @param parse_tree Currect parse tree object
 * @param layer_type Layer name
 * @return True if all nodes in the tree has the annotation in the given layer, false otherwise.
 */
bool tree_layer_exists(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type) {
    return parse_node_layer_exists(parse_tree->root, layer_type);
}

/**
 * Clears the given layer for all nodes in the tree
 * @param parse_tree Currect parse tree object
 * @param layer_type Layer name
 */
void tree_clear_layer(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type) {
    clear_layer(parse_tree->root, layer_type);
}

/**
 * Compares two parse trees according to their file indexes.
 * @param parse_tree1 First parse tree to compare
 * @param parse_tree2 Second parse tree to compare
 * @return -1 if the index of the first tree is smaller that the index of the second tree, 1 for otherwise, and 0
 * if their indexes are the same.
 */
int compare_parse_tree_drawable(const Parse_tree_drawable *parse_tree1, const Parse_tree_drawable *parse_tree2) {
    return compare_int(&(parse_tree1->file_description->index), &(parse_tree2->file_description->index));
}

Parse_tree_ptr generate_parse_tree(const Parse_tree_drawable *parse_tree, bool surface_form) {
    Parse_tree_ptr result = create_parse_tree2(create_parse_node(clone_string(parse_tree->root->data)));
    generate_parse_node(parse_tree->root, result->root, surface_form);
    return result;
}

/**
 * Constructs an AnnotatedSentence object from the Turkish tree. Collects all leaf nodes, then for each leaf node
 * converts layer info of all words at that node to AnnotatedWords. Layers are converted to the counterparts in the
 * AnnotatedWord.
 * @param parse_tree Currect parse tree object
 * @return AnnotatedSentence counterpart of the Turkish tree
 */
Sentence_ptr generate_annotated_sentence(const Parse_tree_drawable *parse_tree) {
    Sentence_ptr sentence = create_sentence();
    Array_list_ptr leaf_list = collect(parse_tree->root, is_turkish_leaf_node);
    for (int i = 0; i < leaf_list->size; i++){
        Parse_node_drawable_ptr parse_node = array_list_get(leaf_list, i);
        for (int j = 0; j < get_number_of_words(parse_node->layers); j++){
            array_list_add(sentence->words, to_annotated_word(parse_node->layers, j));
        }
    }
    free_array_list(leaf_list, NULL);
    return sentence;
}
