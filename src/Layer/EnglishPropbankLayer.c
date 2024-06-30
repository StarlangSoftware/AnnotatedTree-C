//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <Memory/Memory.h>
#include <StringUtils.h>
#include <Argument.h>
#include "EnglishPropbankLayer.h"

/**
 * Constructor for the propbank layer for English language. Value may consist of multiple propbank information separated
 * via '#' character. Each propbank value consists of argumentType and id info separated via '$' character.
 * @param layer_value Value for the English propbank layer.
 */
Word_layer_ptr create_english_propbank_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_english_propbank_layer");
    result->layer_name = str_copy(result->layer_name, "englishPropbank");
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = create_array_list();
        Array_list_ptr split_words = str_split(layer_value, '#');
        for (int i = 0; i < split_words->size; i++){
            array_list_add(result->items, create_argument2(array_list_get(split_words, i)));
        }
        free_array_list(split_words, free_);
    } else {
        result->items = NULL;
    }
    return result;
}
