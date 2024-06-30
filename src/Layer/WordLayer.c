//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//
#include <Memory/Memory.h>
#include <StringUtils.h>
#include <MetamorphicParse.h>
#include <string.h>
#include <MorphologicalParse.h>
#include <stdio.h>
#include "WordLayer.h"

/**
 * Frees memory allocated for a word layer. If the layer contains multiple items, items array list will be deallocated.
 * @param word_layer Word layer to be deallocated.
 */
void free_word_layer(Word_layer_ptr word_layer) {
    free_(word_layer->layer_value);
    if (word_layer->items != NULL){
        if (string_in_list(word_layer->layer_name, (char*[]){"metaMorphemes", "metaMorphemesMoved"}, 2)){
            free_array_list(word_layer->items, (void (*)(void *)) free_metamorphic_parse);
        } else {
            if (strcmp(word_layer->layer_name, "morphologicalAnalysis") == 0){
                free_array_list(word_layer->items, (void (*)(void *)) free_morphological_parse);
            } else {
                if (strcmp(word_layer->layer_name, "englishPropbank") == 0){
                    free_array_list(word_layer->items, (void (*)(void *)) free_argument);
                } else {
                    free_array_list(word_layer->items, free_);
                }
            }
        }
    }
    free_(word_layer->layer_name);
    free_(word_layer);
}

/**
 * Creates a metamorpheme or metamorphemesmoved layer from the given layer value.
 * @param layer_value Value for the word layer.
 * @param layer_name Name of the layer
 * @return New metamorpheme or metamorphemesmoved layer
 */
Word_layer_ptr create_morpheme_layer(const char *layer_value, const char *layer_name) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_morpheme_layer");
    result->layer_name = str_copy(result->layer_name, layer_name);
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = create_array_list();
        Array_list_ptr split_words = str_split(layer_value, ' ');
        for (int i = 0; i < split_words->size; i++){
            array_list_add(result->items, create_metamorphic_parse(array_list_get(split_words, i)));
        }
        free_array_list(split_words, free_);
    } else {
        result->items = NULL;
    }
    return result;
}

/**
 * For morphological analysis layer, returns the total number of morphological tags (for PART_OF_SPEECH) or inflectional
 * groups (for INFLECTIONAL_GROUP) in the words in the node. For metamorphic parse layer, Returns the total number of
 * metamorphemes in the words in the node.
 * @param viewLayer Layer type.
 * @return For morphological analysis layer, total number of morphological tags (for PART_OF_SPEECH) or inflectional
 * groups (for INFLECTIONAL_GROUP) in the words in the node. For metamorphic parse layer, Returns the total number of
 * metamorphemes in the words in the node.
 */
int get_word_layer_size(Word_layer_ptr word_layer, View_layer_type view_layer) {
    int size = 0;
    if (string_in_list(word_layer->layer_name, (char*[]){"metaMorphemes", "metaMorphemesMoved"}, 2)){
        for (int i = 0; i < word_layer->items->size; i++){
            Metamorphic_parse_ptr parse = array_list_get(word_layer->items, i);
            size += parse->meta_morpheme_list->size;
        }
    } else {
        if (strcmp(word_layer->layer_name, "morphologicalAnalysis") == 0){
            switch (view_layer) {
                case PART_OF_SPEECH:
                    for (int i = 0; i < word_layer->items->size; i++){
                        Morphological_parse_ptr parse = array_list_get(word_layer->items, i);
                        size += tag_size(parse);
                    }
                    break;
                case INFLECTIONAL_GROUP:
                    for (int i = 0; i < word_layer->items->size; i++){
                        Morphological_parse_ptr parse = array_list_get(word_layer->items, i);
                        size += parse->inflectional_groups->size;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return size;
}

/**
 * Get the named entity value.
 * @param word_layer Word layer
 * @return Named entity value.
 */
Named_entity_type get_named_entity(Word_layer_ptr word_layer) {
    return get_named_entity_type(word_layer->layer_value);
}

/**
 * Get the argument value.
 * @param word_layer Word layer
 * @return Argument value.
 */
Argument_ptr get_argument(Word_layer_ptr word_layer) {
    return create_argument2(word_layer->layer_value);
}

char *get_word_layer_description(Word_layer_ptr word_layer) {
    char tmp[MAX_WORD_LENGTH];
    sprintf(tmp, "{%s=%s}", word_layer->layer_name, word_layer->layer_value);
    return clone_string(tmp);
}

