//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <Memory/Memory.h>
#include <StringUtils.h>
#include "TurkishPropbankLayer.h"

Word_layer_ptr create_turkish_propbank_layer(const char *layer_value) {
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_turkish_propbank_layer");
    result->layer_name = str_copy(result->layer_name, "propbank");
    result->layer_value = str_copy(result->layer_value, layer_value);
    result->items = NULL;
    return result;
}
