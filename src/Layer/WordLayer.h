//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#ifndef ANNOTATEDTREE_WORDLAYER_H
#define ANNOTATEDTREE_WORDLAYER_H

#include <NamedEntityType.h>
#include <Argument.h>
#include "ViewLayerType.h"

struct word_layer{
    char* layer_name;
    char* layer_value;
    Array_list_ptr items;
};

typedef struct word_layer Word_layer;

typedef Word_layer *Word_layer_ptr;

void free_word_layer(Word_layer_ptr word_layer);

Word_layer_ptr create_morpheme_layer(const char* layer_value, const char* layer_name);

int get_word_layer_size(Word_layer_ptr word_layer, View_layer_type view_layer);

Named_entity_type get_named_entity(Word_layer_ptr word_layer);

Argument_ptr get_argument(Word_layer_ptr word_layer);

char* get_word_layer_description(Word_layer_ptr word_layer);

#endif //ANNOTATEDTREE_WORDLAYER_H
