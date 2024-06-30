//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include "DependencyLayer.h"
#include "Memory/Memory.h"

/**
 * Constructor for the dependency layer. Dependency layer stores the dependency information of a node.
 * @param layer_value Value of the dependency layer.
 */
Word_layer_ptr create_dependency_layer(const char* layer_value){
    Word_layer_ptr result = malloc_(sizeof(Word_layer), "create_dependency_layer");
    result->layer_name = str_copy(result->layer_name, "dependency");
    result->layer_value = str_copy(result->layer_value, layer_value);
    result->items = NULL;
    return result;
}