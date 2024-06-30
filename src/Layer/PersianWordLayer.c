//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include <Memory/Memory.h>
#include "PersianWordLayer.h"

/**
 * Constructor for the word layer for Persian language. Sets the surface form.
 * @param layer_value Value for the word layer.
 */
Word_layer_ptr create_persian_word_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_persian_word_layer");
    result->layer_name = str_copy(result->layer_name, "persian");
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = str_split(layer_value, ' ');
    } else {
        result->items = NULL;
    }
    return result;
}
