//
// Created by Olcay Taner YILDIZ on 13.12.2023.
//

#include <Memory/Memory.h>
#include <string.h>
#include <stdio.h>
#include <FileUtils.h>
#include "ParseNodeDrawable.h"

/**
 * Constructs a ParseNodeDrawable from a single line. If the node is a leaf node, it only sets the data. Otherwise,
 * splits the line w.r.t. spaces and parenthesis and calls itself recursively to generate its child parseNodes.
 * @param parent The parent node of this node.
 * @param line The input line to create this parseNode.
 * @param is_leaf True, if this node is a leaf node; false otherwise.
 * @param depth Depth of the node.
 */
Parse_node_drawable_ptr create_parse_node_drawable(Parse_node_drawable_ptr parent,
                                                   const char *line,
                                                   bool is_leaf,
                                                   int depth) {
    Parse_node_drawable_ptr result = malloc_(sizeof(Parse_node_drawable), "create_parse_node_drawable");
    int parenthesisCount = 0;
    result->depth = depth;
    result->parent = parent;
    result->children = create_array_list();
    result->layers = NULL;
    result->data = NULL;
    char childLine[MAX_LINE_LENGTH] = "";
    if (is_leaf){
        if (!str_contains(line, "{")){
            result->data = str_copy(result->data, line);
        } else {
            result->layers = create_layer_info(line);
        }
    } else {
        int startPos = str_find_c(line, " ");
        String_ptr st = substring(line, 1, startPos - 1);
        result->data = str_copy(result->data, st->s);
        free_string_ptr(st);
        if (str_find_c(line, ")") == str_find_last_c(line, ")")){
            st = substring(line, startPos + 1, str_find_c(line, ")") - startPos - 1);
            array_list_add(result->children, create_parse_node_drawable(result, st->s, true, depth + 1));
            free_string_ptr(st);
        } else {
            for (int i = startPos + 1; i < strlen(line); i++){
                if (line[i] != ' ' || parenthesisCount > 0){
                    sprintf(childLine, "%s%c", childLine, line[i]);
                }
                if (line[i] == '('){
                    parenthesisCount++;
                } else {
                    if (line[i] == ')'){
                        parenthesisCount--;
                    }
                }
                if (parenthesisCount == 0 && strlen(childLine) != 0){
                    st = trim(childLine);
                    array_list_add(result->children, create_parse_node_drawable(result, st->s, false, depth + 1));
                    free_string_ptr(st);
                    sprintf(childLine, "");
                }
            }
        }
    }
    return result;
}

Parse_node_drawable_ptr create_parse_node_drawable2(const char *line) {
    Parse_node_drawable_ptr result = malloc_(sizeof(Parse_node_drawable), "create_parse_node_drawable2");
    result->depth = 0;
    result->parent = NULL;
    result->data = str_copy(result->data, line);
    result->children = create_array_list();
    result->layers = NULL;
    return result;
}

char *get_data2(Parse_node_drawable_ptr parse_node) {
    if (parse_node->layers == NULL){
        return parse_node->data;
    } else {
        return get_layer_data(parse_node->layers, ENGLISH_WORD);
    }
}

/**
 * Clears the layers hash map.
 * @param parse_node Current parse node object
 */
void clear_layers(Parse_node_drawable_ptr parse_node) {
    parse_node->layers = create_layer_info2();
}

/**
 * Recursive method to clear a given layer.
 * @param parse_node Current parse node object
 * @param layer_type Name of the layer to be cleared
 */
void clear_layer(Parse_node_drawable_ptr parse_node, View_layer_type layer_type) {
    if (parse_node->children->size == 0 && layer_exists(parse_node->layers, layer_type)){
        remove_layer(parse_node->layers, layer_type);
    }
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
        clear_layer(child, layer_type);
    }
}

/**
 * Clears the node tag.
 * @param parse_node Current parse node object
 */
void clear_data(Parse_node_drawable_ptr parse_node) {
    free_(parse_node->data);
    parse_node->data = NULL;
}

/**
 * Setter for the data attribute and also clears all layers.
 * @param parse_node Current parse node object
 * @param data New data field.
 */
void set_data_and_clear_layers(Parse_node_drawable_ptr parse_node, const char *data) {
    free_(parse_node->data);
    parse_node->data = str_copy(parse_node->data, data);
    if (parse_node->layers != NULL){
        free_layer_info(parse_node->layers);
        parse_node->layers = NULL;
    }
}

/**
 * Mutator for the data field. If the layers is null, its sets the data field, otherwise it sets the English layer
 * to the given value.
 * @param parse_node Current parse node object
 * @param data Data to be set.
 */
void set_data(Parse_node_drawable_ptr parse_node, const char *data) {
    if (parse_node->layers == NULL){
        free_(parse_node->data);
        parse_node->data = str_copy(parse_node->data, data);
    } else {
        set_layer_data(parse_node->layers, ENGLISH_WORD, data);
    }
}

/**
 * Returns the layer value of a given layer.
 * @param parse_node Current parse node object
 * @param layer_type Layer name
 * @return Value of the given layer
 */
char* get_parse_node_layer_data(Parse_node_drawable_ptr parse_node, View_layer_type layer_type) {
    if (layer_type == WORD || parse_node->layers == NULL){
        return parse_node->data;
    }
    return get_layer_data(parse_node->layers, layer_type);
}

/**
 * Recursive method which updates the depth attribute
 * @param parse_node Current parse node object
 * @param depth Current depth to set.
 */
void update_depths(Parse_node_drawable_ptr parse_node, int depth) {
    parse_node->depth = depth;
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
        update_depths(child, depth + 1);
    }
}

void free_parse_node_drawable(Parse_node_drawable_ptr parse_node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        free_parse_node_drawable(array_list_get(parse_node->children, i));
    }
    free_array_list(parse_node->children, NULL);
    free_(parse_node->data);
    free_(parse_node);
    if (parse_node->layers != NULL){
        free_layer_info(parse_node->layers);
    }
}

/**
 * Calculates the maximum depth of the subtree rooted from this node.
 * @param parse_node Current parse node object
 * @return The maximum depth of the subtree rooted from this node.
 */
int max_depth(Parse_node_drawable_ptr parse_node) {
    int depth = parse_node->depth;
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
        if (max_depth(child) > depth){
            depth = max_depth(child);
        }
    }
    return depth;
}

/**
 * Recursive method that checks if all nodes in the subtree rooted with this node has the annotation in the given
 * layer.
 * @param parse_node Current parse node object
 * @param layer_type Layer name
 * @return True if all nodes in the subtree rooted with this node has the annotation in the given layer, false
 * otherwise.
 */
bool parse_node_layer_exists(Parse_node_drawable_ptr parse_node, View_layer_type layer_type) {
    if (parse_node->children->size == 0){
        if (get_parse_node_layer_data(parse_node, layer_type) != NULL){
            return true;
        }
    } else {
        for (int i = 0; i < parse_node->children->size; i++){
            Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
            if (parse_node_layer_exists(child, layer_type)){
                return true;
            }
        }
    }
    return false;
}

/**
 * Checks if all nodes in the subtree rooted with this node has annotation with the given layer.
 * @param parse_node Current parse node object
 * @param layer_type Layer name
 * @return True if all nodes in the subtree rooted with this node has annotation with the given layer, false
 * otherwise.
 */
bool layer_all(Parse_node_drawable_ptr parse_node, View_layer_type layer_type) {
    if (parse_node->children->size == 0){
        if (get_parse_node_layer_data(parse_node, layer_type) == NULL && !is_dummy_node2(parse_node)){
            return false;
        }
    } else {
        for (int i = 0; i < parse_node->children->size; i++){
            Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
            if (!layer_all(child, layer_type)){
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if the current node is a dummy node or not. A node is a dummy node if its data contains '*', or its
 * data is '0' and its parent is '-NONE-'.
 * @param parse_node Current parse node object
 * @return True if the current node is a dummy node, false otherwise.
 */
bool is_dummy_node2(Parse_node_drawable_ptr parse_node) {
    char* data = get_layer_data(parse_node->layers, ENGLISH_WORD);
    char* parent_data = get_layer_data(parse_node->parent->layers, ENGLISH_WORD);
    char* target_data = get_layer_data(parse_node->layers, TURKISH_WORD);
    if (data != NULL && parent_data != NULL){
        if (target_data != NULL && str_contains_c(target_data, '*')){
            return true;
        }
        return str_contains_c(data, '*') || (strcmp(data, "0") == 0 && strcmp(parent_data, "-NONE-") == 0);
    } else {
        return false;
    }
}

/**
 * Recursive method to convert the subtree rooted with this node to a string. All parenthesis types are converted to
 * their regular forms.
 * @param parse_node Current parse node object
 * @return String version of the subtree rooted with this node.
 */
char *to_turkish_sentence(Parse_node_drawable_ptr parse_node) {
    char tmp[MAX_WORD_LENGTH];
    if (parse_node->children->size == 0){
        if (get_parse_node_layer_data(parse_node, TURKISH_WORD) != NULL && !is_dummy_node2(parse_node)){
            sprintf(tmp, " %s", get_parse_node_layer_data(parse_node, TURKISH_WORD));
            return clone_string(tmp);
        } else {
            return clone_string(" ");
        }
    } else {
        sprintf(tmp, "");
        for (int i = 0; i < parse_node->children->size; i++){
            Parse_node_drawable_ptr child = array_list_get(parse_node->children, i);
            char* st = to_turkish_sentence(child);
            sprintf(tmp, "%s%s", tmp, st);
            free_(st);
        }
        return clone_string(tmp);
    }
}

/**
 * Recursive method that sets the tag information of the given parse node with all descendants with respect to the
 * morphological annotation of the current node with all descendants.
 * @param parse_node_drawable Current parse node object
 * @param parse_node Parse node whose tag information will be changed.
 * @param surface_form If true, tag will be replaced with the surface form annotation.
 */
void generate_parse_node(Parse_node_drawable_ptr parse_node_drawable,
                         Parse_node_ptr parse_node,
                         bool surface_form) {
    if (parse_node_drawable->children->size == 0){
        if (surface_form){
            parse_node->data = clone_string(get_parse_node_layer_data(parse_node_drawable, TURKISH_WORD));
        } else {
            parse_node->data = clone_string(get_morphological_parse_at(parse_node_drawable->layers, 0)->root);
        }
    } else {
        parse_node->data = clone_string(parse_node_drawable->data);
        for (int i = 0; i < parse_node_drawable->children->size; i++){
            Parse_node_ptr new_child = create_parse_node5();
            add_child(parse_node, new_child);
            Parse_node_drawable_ptr child = array_list_get(parse_node_drawable->children, i);
            generate_parse_node(child, new_child, surface_form);
        }
    }
}
