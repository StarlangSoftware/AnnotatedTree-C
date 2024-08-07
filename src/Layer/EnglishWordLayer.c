//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <Memory/Memory.h>
#include <StringUtils.h>
#include "EnglishWordLayer.h"

/**
 * Constructor for the word layer for English language. Sets the surface form.
 * @param layer_value Value for the word layer.
 */
Word_layer_ptr create_english_word_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_english_word_layer");
    result->layer_name = str_copy(result->layer_name, "english");
    result->layer_value = str_copy(result->layer_value, layer_value);
    result->items = NULL;
    return result;
}
