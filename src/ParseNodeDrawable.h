//
// Created by Olcay Taner YILDIZ on 13.12.2023.
//

#ifndef ANNOTATEDTREE_PARSENODEDRAWABLE_H
#define ANNOTATEDTREE_PARSENODEDRAWABLE_H

#include <ArrayList.h>
#include <ParseNode.h>
#include "LayerInfo.h"

struct parse_node_drawable{
    Array_list_ptr children;
    struct parse_node_drawable* parent;
    char* data;
    Layer_info_ptr layers;
    int depth;
};

typedef struct parse_node_drawable Parse_node_drawable;

typedef Parse_node_drawable * Parse_node_drawable_ptr;

Parse_node_drawable_ptr create_parse_node_drawable(Parse_node_drawable_ptr parent,
                                                   char* line,
                                                   bool isLeaf,
                                                   int depth);

Parse_node_drawable_ptr create_parse_node_drawable2(char* line);

void free_parse_node_drawable(Parse_node_drawable_ptr parse_node);

char* get_data2(Parse_node_drawable_ptr parse_node);

void clear_layers(Parse_node_drawable_ptr parse_node);

void clear_layer(Parse_node_drawable_ptr parse_node, View_layer_type layer_type);

void clear_data(Parse_node_drawable_ptr parse_node);

void set_data_and_clear_layers(Parse_node_drawable_ptr parse_node, char* data);

void set_data(Parse_node_drawable_ptr parse_node, char* data);

char* get_parse_node_layer_data(Parse_node_drawable_ptr parse_node, View_layer_type layer_type);

void update_depths(Parse_node_drawable_ptr parse_node, int depth);

int max_depth(Parse_node_drawable_ptr parse_node);

bool parse_node_layer_exists(Parse_node_drawable_ptr parse_node, View_layer_type layer_type);

bool layer_all(Parse_node_drawable_ptr parse_node, View_layer_type layer_type);

bool is_dummy_node2(Parse_node_drawable_ptr parse_node);

char* to_turkish_sentence(Parse_node_drawable_ptr parse_node);

void generate_parse_node(Parse_node_drawable_ptr parse_node_drawable, Parse_node_ptr parse_node, bool surface_form);

#endif //ANNOTATEDTREE_PARSENODEDRAWABLE_H
