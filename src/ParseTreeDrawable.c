//
// Created by Olcay Taner YILDIZ on 19.12.2023.
//

#include <Memory/Memory.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include "ParseTreeDrawable.h"

Parse_tree_drawable_ptr create_parse_tree_drawable(File_description_ptr file_description) {
    Parse_tree_drawable_ptr result = malloc_(sizeof(Parse_tree_drawable), "create_parse_tree_drawable");
    result->file_description = file_description;
    char* file_name = get_file_name(file_description);
    read_from_file(result, file_name);
    free_(file_name);
    return result;
}

void free_parse_tree_drawable(Parse_tree_drawable_ptr parse_tree) {
    free_file_description(parse_tree->file_description);
    free_parse_node_drawable(parse_tree->root);
    free_(parse_tree);
}

Parse_tree_drawable_ptr create_parse_tree_drawable2(const char *path, const char *raw_file_name) {
    File_description_ptr file_description = create_file_description(path, raw_file_name);
    return create_parse_tree_drawable(file_description);
}

Parse_tree_drawable_ptr create_parse_tree_drawable3(const char *path, const char *extension, int index) {
    File_description_ptr file_description = create_file_description2(path, extension, index);
    return create_parse_tree_drawable(file_description);
}

Parse_tree_drawable_ptr create_parse_tree_drawable4(const char *path, File_description_ptr file_description) {
    return create_parse_tree_drawable3(path, file_description->extension, file_description->index);
}

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

int tree_max_depth(Parse_tree_drawable_ptr parse_tree) {
    return max_depth(parse_tree->root);
}

bool tree_layer_exists(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type) {
    return parse_node_layer_exists(parse_tree->root, layer_type);
}

void tree_clear_layer(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type) {
    clear_layer(parse_tree->root, layer_type);
}

int compare_parse_tree_drawable(const Parse_tree_drawable *parse_tree1, const Parse_tree_drawable *parse_tree2) {
    return compare_int(&(parse_tree1->file_description->index), &(parse_tree2->file_description->index));
}

Parse_tree_ptr generate_parse_tree(const Parse_tree_drawable *parse_tree, bool surface_form) {
    Parse_tree_ptr result = create_parse_tree2(create_parse_node(clone_string(parse_tree->root->data)));
    generate_parse_node(parse_tree->root, result->root, surface_form);
    return result;
}