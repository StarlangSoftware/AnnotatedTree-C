//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include "MetaMorphemesMovedLayer.h"

/**
 * Constructor for the metaMorphemesMoved layer. Sets the metamorpheme information for multiple words in the node.
 * @param layer_value Layer value for the metaMorphemesMoved information. Consists of metamorpheme information of
 *                   multiple words separated via space character.
 */
Word_layer_ptr create_meta_morphemes_moved_layer(const char *layer_value) {
    return create_morpheme_layer(layer_value, "metaMorphemesMoved");
}
