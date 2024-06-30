//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <Memory/Memory.h>
#include <StringUtils.h>
#include "NERLayer.h"

/**
 * Constructor for the named entity layer. Sets single named entity information for multiple words in
 * the node.
 * @param layer_value Layer value for the named entity information. Consists of single named entity information
 *                   of multiple words.
 */
Word_layer_ptr create_ner_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_ner_layer");
    result->layer_name = str_copy(result->layer_name, "namedEntity");
    result->layer_value = str_copy(result->layer_value, layer_value);
    result->items = NULL;
    return result;
}
