//
// Created by Olcay Taner YILDIZ on 19.12.2023.
//

#ifndef ANNOTATEDTREE_PARSETREEDRAWABLE_H
#define ANNOTATEDTREE_PARSETREEDRAWABLE_H

#include <FileDescription.h>
#include <ParseTree.h>
#include <Sentence.h>
#include "ParseNodeDrawable.h"

struct parse_tree_drawable {
    Parse_node_drawable_ptr root;
    File_description_ptr file_description;
};

typedef struct parse_tree_drawable Parse_tree_drawable;

typedef Parse_tree_drawable *Parse_tree_drawable_ptr;

Parse_tree_drawable_ptr create_parse_tree_drawable(File_description_ptr file_description);

Parse_tree_drawable_ptr create_parse_tree_drawable2(const char* path, const char* raw_file_name);

Parse_tree_drawable_ptr create_parse_tree_drawable3(const char* path, const char* extension, int index);

Parse_tree_drawable_ptr create_parse_tree_drawable4(const char* path, File_description_ptr file_description);

void free_parse_tree_drawable(Parse_tree_drawable_ptr parse_tree);

void read_from_file(Parse_tree_drawable_ptr parse_tree, const char* file_name);

int tree_max_depth(Parse_tree_drawable_ptr parse_tree);

bool tree_layer_exists(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type);

bool tree_layer_all(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type);

void tree_clear_layer(Parse_tree_drawable_ptr parse_tree, View_layer_type layer_type);

int compare_parse_tree_drawable(const Parse_tree_drawable *parse_tree1, const Parse_tree_drawable *parse_tree2);

Parse_tree_ptr generate_parse_tree(const Parse_tree_drawable *parse_tree, bool surface_form);

Sentence_ptr generate_annotated_sentence(const Parse_tree_drawable *parse_tree);

#endif //ANNOTATEDTREE_PARSETREEDRAWABLE_H
