//
// Created by Olcay Taner YILDIZ on 17.12.2023.
//

#include <stddef.h>
#include "SemiContainsLayerInformation.h"
#include "../../ParseNodeDrawable.h"
#include "../Condition/IsTurkishLeafNode.h"

bool semi_contains_layer_information(Array_list_ptr leaf_list, View_layer_type layer_type) {
    int not_done = 0, done = 0;
    for (int i = 0; i < leaf_list->size; i++){
        Parse_node_drawable_ptr parse_node = array_list_get(leaf_list, i);
        char* data = get_parse_node_layer_data(parse_node, ENGLISH_WORD);
        if (!str_contains_c(data, '*')){
            switch (layer_type) {
                case TURKISH_WORD:
                    if (get_parse_node_layer_data(parse_node, layer_type) != NULL){
                        done++;
                    } else {
                        not_done++;
                    }
                    break;
                case PART_OF_SPEECH:
                case INFLECTIONAL_GROUP:
                case NER:
                case SEMANTICS:
                case PROPBANK:
                    if (is_turkish_leaf_node(parse_node)){
                        if (get_parse_node_layer_data(parse_node, layer_type) != NULL){
                            done++;
                        } else {
                            not_done++;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return done != 0 && not_done != 0;
}
