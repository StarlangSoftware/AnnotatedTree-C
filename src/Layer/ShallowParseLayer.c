//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <stddef.h>
#include <Memory/Memory.h>
#include <StringUtils.h>
#include "ShallowParseLayer.h"

/**
 * Constructor for the shallow parse layer. Sets shallow parse information for each word in
 * the node. Value may consist of multiple shallow parse information
 * separated via space character. Each shallow parse value is a string.
 * @param layer_value Layer value for the shallow parse information. Consists of shallow parse information
 *                   for every word.
 */
Word_layer_ptr create_shallow_parse_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_shallow_parse_layer");
    result->layer_name = str_copy(result->layer_name, "shallowParse");
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = str_split(layer_value, ' ');
    } else {
        result->items = NULL;
    }
    return result;
}
