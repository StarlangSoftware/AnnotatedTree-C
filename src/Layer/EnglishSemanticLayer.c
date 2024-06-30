//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <stddef.h>
#include <StringUtils.h>
#include <Memory/Memory.h>
#include "EnglishSemanticLayer.h"

/**
 * Constructor for the semantic layer for English language. Sets the layer value to the synset id defined in English
 * WordNet.
 * @param layer_value Value for the English semantic layer.
 */
Word_layer_ptr create_english_semantic_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_english_semantic_layer");
    result->layer_name = str_copy(result->layer_name, "englishSemantics");
    result->layer_value = str_copy(result->layer_value, layer_value);
    result->items = NULL;
    return result;
}
