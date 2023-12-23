//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <Memory/Memory.h>
#include <StringUtils.h>
#include <MorphologicalParse.h>
#include "MorphologicalAnalysisLayer.h"

Word_layer_ptr create_morphological_analysis_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_morphological_analysis_layer");
    result->layer_name = str_copy(result->layer_name, "morphologicalAnalysis");
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = create_array_list();
        Array_list_ptr split_words = str_split(layer_value, ' ');
        for (int i = 0; i < split_words->size; i++){
            array_list_add(result->items, create_morphological_parse(array_list_get(split_words, i)));
        }
        free_array_list(split_words, free_);
    } else {
        result->items = NULL;
    }
    return result;
}
