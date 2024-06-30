//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <stddef.h>
#include <StringUtils.h>
#include <Memory/Memory.h>
#include "TurkishSemanticLayer.h"

/**
 * Constructor for the Turkish semantic layer. Sets semantic information for each word in
 * the node. Value may consist of multiple sense information
 * separated via '$' character. Each sense value is a string representing the synset id of the sense.
 * @param layer_value Layer value for the Turkish semantic information. Consists of semantic (Turkish synset id)
 *                   information for every word.
 */
Word_layer_ptr create_turkish_semantic_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_shallow_parse_layer");
    result->layer_name = str_copy(result->layer_name, "shallowParse");
    result->layer_value = str_copy(result->layer_value, layer_value);
    if (layer_value != NULL){
        result->items = str_split(layer_value, '$');
    } else {
        result->items = NULL;
    }
    return result;
}
