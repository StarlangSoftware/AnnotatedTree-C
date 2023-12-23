//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#ifndef ANNOTATEDTREE_LAYERINFO_H
#define ANNOTATEDTREE_LAYERINFO_H

#include <HashMap/HashMap.h>
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <AnnotatedWord.h>
#include "Layer/WordLayer.h"

struct layer_info{
    Hash_map_ptr layers;
};

typedef struct layer_info Layer_info;

typedef Layer_info *Layer_info_ptr;

Layer_info_ptr create_layer_info(const char* info);

Layer_info_ptr create_layer_info2();

void set_layer_data(Layer_info_ptr layer_info,
                    View_layer_type view_layer,
                    const char* layer_value);

void set_morphological_analysis(Layer_info_ptr layer_info, const Morphological_parse* parse);

void set_meta_morphemes(Layer_info_ptr layer_info, const Metamorphic_parse* parse);

bool layer_exists(Layer_info_ptr layer_info, View_layer_type layer_type);

View_layer_type check_layer(Layer_info_ptr layer_info, View_layer_type layer_type);

int get_number_of_words(Layer_info_ptr layer_info);

void free_layer_info(Layer_info_ptr layer_info);

void* get_multi_word_at(Layer_info_ptr layer_info,
                        View_layer_type layer_type,
                        int index);

char* get_turkish_word_at(Layer_info_ptr layer_info, int index);

int get_number_of_meanings(Layer_info_ptr layer_info);

Word_layer_ptr get_layer(Layer_info_ptr layer_info, View_layer_type layer_type);

char* get_semantic_at(Layer_info_ptr layer_info, int index);

char* get_shallow_parse_at(Layer_info_ptr layer_info, int index);

Argument_ptr get_layer_argument(Layer_info_ptr layer_info);

Argument_ptr get_argument_at(Layer_info_ptr layer_info, int index);

Morphological_parse_ptr get_morphological_parse_at(Layer_info_ptr layer_info, int index);

Metamorphic_parse_ptr get_metamorphic_parse_at(Layer_info_ptr layer_info, int index);

int get_layer_size(Layer_info_ptr layer_info, View_layer_type layer_type);

char* get_layer_description(Layer_info_ptr layer_info);

char* get_layer_data(Layer_info_ptr layer_info, View_layer_type layer_type);

char* get_robust_layer_data(Layer_info_ptr layer_info, View_layer_type layer_type);

void remove_layer(Layer_info_ptr layer_info, View_layer_type layer_type);

void meta_morpheme_clear(Layer_info_ptr layer_info);

void english_clear(Layer_info_ptr layer_info);

void dependency_clear(Layer_info_ptr layer_info);

void meta_morphemes_moved_clear(Layer_info_ptr layer_info);

void semantic_clear(Layer_info_ptr layer_info);

void english_semantic_clear(Layer_info_ptr layer_info);

void morphological_analysis_clear(Layer_info_ptr layer_info);

#endif //ANNOTATEDTREE_LAYERINFO_H
