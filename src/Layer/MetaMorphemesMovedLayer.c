//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include "MetaMorphemesMovedLayer.h"

Word_layer_ptr create_meta_morphemes_moved_layer(const char *layer_value) {
    return create_morpheme_layer(layer_value, "metaMorphemesMoved");
}
