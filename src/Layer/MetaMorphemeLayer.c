//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include "MetaMorphemeLayer.h"

/**
 * Constructor for the metamorpheme layer. Sets the metamorpheme information for multiple words in the node.
 * @param layer_value Layer value for the metamorpheme information. Consists of metamorpheme information of multiple
 *                   words separated via space character.
 */
Word_layer_ptr create_meta_morpheme_layer(const char *layer_value) {
    return create_morpheme_layer(layer_value, "metaMorphemes");
}
