//
// Created by Olcay Taner YILDIZ on 6.12.2023.
//

#include <StringUtils.h>
#include <Memory/Memory.h>
#include <ViewLayerType.h>
#include <string.h>
#include <stdio.h>
#include "LayerInfo.h"
#include "Layer/TurkishWordLayer.h"
#include "Layer/PersianWordLayer.h"
#include "Layer/EnglishWordLayer.h"
#include "Layer/MorphologicalAnalysisLayer.h"
#include "Layer/MetaMorphemeLayer.h"
#include "Layer/MetaMorphemesMovedLayer.h"
#include "Layer/DependencyLayer.h"
#include "Layer/TurkishSemanticLayer.h"
#include "Layer/NERLayer.h"
#include "Layer/TurkishPropbankLayer.h"
#include "Layer/EnglishPropbankLayer.h"
#include "Layer/EnglishSemanticLayer.h"
#include "Layer/ShallowParseLayer.h"

/**
 * Constructs the layer information from the given string. Layers are represented as
 * {layername1=layervalue1}{layername2=layervalue2}...{layernamek=layervaluek} where layer name is one of the
 * following: turkish, persian, english, morphologicalAnalysis, metaMorphemes, metaMorphemesMoved, dependency,
 * semantics, namedEntity, propBank, englishPropbank, englishSemantics, shallowParse. Splits the string w.r.t.
 * parentheses and constructs layer objects and put them layers map accordingly.
 * @param info Line consisting of layer info.
 */
Layer_info_ptr create_layer_info(const char *info) {
    Layer_info_ptr result = malloc_(sizeof(Layer_info), "create_layer_info");
    result->layers = create_hash_map((unsigned int (*)(const void *, int)) hash_function_view_layer_type,
                                     (int (*)(const void *, const void *)) compare_view_layer_type);
    Array_list_ptr splitLayers = str_split3(info, "[{}]");
    for (int i = 0; i < splitLayers->size; i++){
        char* layer = array_list_get(splitLayers, i);
        Array_list_ptr items = str_split(layer, '=');
        char* layerType = array_list_get(items, 0);
        char* layerValue = array_list_get(items, 1);
        if (strcmp(layerType, "turkish") == 0){
            hash_map_insert(result->layers, create_view_layer_type(TURKISH_WORD), create_turkish_word_layer(layerValue));
        } else {
            if (strcmp(layerType, "persian") == 0){
                hash_map_insert(result->layers, create_view_layer_type(PERSIAN_WORD), create_persian_word_layer(layerValue));
            } else {
                if (strcmp(layerType, "english") == 0){
                    hash_map_insert(result->layers, create_view_layer_type(ENGLISH_WORD), create_english_word_layer(layerValue));
                } else {
                    if (strcmp(layerType, "morphologicalAnalysis") == 0){
                        hash_map_insert(result->layers, create_view_layer_type(INFLECTIONAL_GROUP), create_morphological_analysis_layer(layerValue));
                        hash_map_insert(result->layers, create_view_layer_type(PART_OF_SPEECH), create_morphological_analysis_layer(layerValue));
                    } else {
                        if (strcmp(layerType, "metaMorphemes") == 0){
                            hash_map_insert(result->layers, create_view_layer_type(META_MORPHEME), create_meta_morpheme_layer(layerValue));
                        } else {
                            if (strcmp(layerType, "metaMorphemesMoved") == 0){
                                hash_map_insert(result->layers, create_view_layer_type(META_MORPHEME_MOVED), create_meta_morphemes_moved_layer(layerValue));
                            } else {
                                if (strcmp(layerType, "dependency") == 0){
                                    hash_map_insert(result->layers, create_view_layer_type(DEPENDENCY), create_dependency_layer(layerValue));
                                } else {
                                    if (strcmp(layerType, "semantics") == 0){
                                        hash_map_insert(result->layers, create_view_layer_type(SEMANTICS), create_turkish_semantic_layer(layerValue));
                                    } else {
                                        if (strcmp(layerType, "namedEntity") == 0){
                                            hash_map_insert(result->layers, create_view_layer_type(NER), create_ner_layer(layerValue));
                                        } else {
                                            if (strcmp(layerType, "propBank") == 0){
                                                hash_map_insert(result->layers, create_view_layer_type(PROPBANK), create_turkish_propbank_layer(layerValue));
                                            } else {
                                                if (strcmp(layerType, "englishPropbank") == 0){
                                                    hash_map_insert(result->layers, create_view_layer_type(ENGLISH_PROPBANK), create_english_propbank_layer(layerValue));
                                                } else {
                                                    if (strcmp(layerType, "englishSemantics") == 0){
                                                        hash_map_insert(result->layers, create_view_layer_type(ENGLISH_SEMANTICS), create_english_semantic_layer(layerValue));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        free_array_list(items, free_);
    }
    free_array_list(splitLayers, free_);
    return result;
}


Layer_info_ptr create_layer_info2() {
    Layer_info_ptr result = malloc_(sizeof(Layer_info), "create_layer_info");
    result->layers = create_hash_map((unsigned int (*)(const void *, int)) hash_function_view_layer_type,
                                     (int (*)(const void *, const void *)) compare_view_layer_type);
    return result;
}

/**
 * Changes the given layer info with the given string layer value. For all layers new layer object is created and
 * replaces the original object. For turkish layer, it also destroys inflectional_group, part_of_speech,
 * meta_morpheme, meta_morpheme_moved and semantics layers. For persian layer, it also destroys the semantics layer.
 * @param layer_info Current layer info object
 * @param view_layer Layer name.
 * @param layer_value New layer value.
 */
void set_layer_data(Layer_info_ptr layer_info, View_layer_type view_layer, const char *layer_value) {
    switch (view_layer){
        case PERSIAN_WORD:
            hash_map_insert(layer_info->layers, create_view_layer_type(PERSIAN_WORD), create_persian_word_layer(layer_value));
            break;
        case TURKISH_WORD:
            hash_map_insert(layer_info->layers, create_view_layer_type(TURKISH_WORD), create_turkish_word_layer(layer_value));
            break;
        case ENGLISH_WORD:
            hash_map_insert(layer_info->layers, create_view_layer_type(ENGLISH_WORD), create_english_word_layer(layer_value));
            break;
        case PART_OF_SPEECH:
        case INFLECTIONAL_GROUP:
            hash_map_insert(layer_info->layers, create_view_layer_type(INFLECTIONAL_GROUP), create_morphological_analysis_layer(layer_value));
            hash_map_insert(layer_info->layers, create_view_layer_type(PART_OF_SPEECH), create_morphological_analysis_layer(layer_value));
            break;
        case META_MORPHEME:
            hash_map_insert(layer_info->layers, create_view_layer_type(META_MORPHEME), create_meta_morpheme_layer(layer_value));
            break;
        case META_MORPHEME_MOVED:
            hash_map_insert(layer_info->layers, create_view_layer_type(META_MORPHEME_MOVED), create_meta_morphemes_moved_layer(layer_value));
            break;
        case DEPENDENCY:
            hash_map_insert(layer_info->layers, create_view_layer_type(DEPENDENCY), create_dependency_layer(layer_value));
            break;
        case SEMANTICS:
            hash_map_insert(layer_info->layers, create_view_layer_type(SEMANTICS), create_turkish_semantic_layer(layer_value));
            break;
        case ENGLISH_SEMANTICS:
            hash_map_insert(layer_info->layers, create_view_layer_type(ENGLISH_SEMANTICS), create_english_semantic_layer(layer_value));
            break;
        case NER:
            hash_map_insert(layer_info->layers, create_view_layer_type(NER), create_ner_layer(layer_value));
            break;
        case PROPBANK:
            hash_map_insert(layer_info->layers, create_view_layer_type(PROPBANK), create_turkish_propbank_layer(layer_value));
            break;
        case ENGLISH_PROPBANK:
            hash_map_insert(layer_info->layers, create_view_layer_type(ENGLISH_PROPBANK), create_english_propbank_layer(layer_value));
            break;
        case SHALLOW_PARSE:
            hash_map_insert(layer_info->layers, create_view_layer_type(SHALLOW_PARSE), create_shallow_parse_layer(layer_value));
            break;
        default:
            break;
    }
}

/**
 * Updates the inflectional_group and part_of_speech layers according to the given parse.
 * @param layer_info Current layer info object
 * @param parse New parse to update layers.
 */
void set_morphological_analysis(Layer_info_ptr layer_info, const Morphological_parse *parse) {
    char* parse_string = morphological_parse_to_string(parse);
    hash_map_insert(layer_info->layers, create_view_layer_type(INFLECTIONAL_GROUP), create_morphological_analysis_layer(parse_string));
    hash_map_insert(layer_info->layers, create_view_layer_type(PART_OF_SPEECH), create_morphological_analysis_layer(parse_string));
    free_(parse_string);
}

/**
 * Updates the metamorpheme layer according to the given parse.
 * @param layer_info Current layer info object
 * @param parse NEw parse to update layer.
 */
void set_meta_morphemes(Layer_info_ptr layer_info, const Metamorphic_parse *parse) {
    char* parse_string = metamorphic_parse_to_string(parse);
    hash_map_insert(layer_info->layers, create_view_layer_type(META_MORPHEME), create_meta_morpheme_layer(parse_string));
    free_(parse_string);
}

/**
 * Checks if the given layer exists.
 * @param layer_info Current layer info object
 * @param layer_type Layer name
 * @return True if the layer exists, false otherwise.
 */
bool layer_exists(Layer_info_ptr layer_info, View_layer_type layer_type) {
    View_layer_type_ptr layer_ptr = create_view_layer_type(layer_type);
    bool result = hash_map_contains(layer_info->layers, layer_ptr);
    free_(layer_ptr);
    return result;
}

/**
 * Returns the word layer for the given layer type.
 * @param layer_info Current layer info object
 * @param layer_type Layer name
 * @return Word layer for the given layer type
 */
Word_layer_ptr get_layer(Layer_info_ptr layer_info, View_layer_type layer_type) {
    View_layer_type_ptr layer_ptr = create_view_layer_type(layer_type);
    Word_layer_ptr result = hash_map_get(layer_info->layers, layer_ptr);
    free_(layer_ptr);
    return result;
}

/**
 * Two level layer check method. For turkish, persian and english_semantics layers, if the layer does not exist,
 * returns english layer. For part_of_speech, inflectional_group, meta_morpheme, semantics, propbank, shallow_parse,
 * english_propbank layers, if the layer does not exist, it checks turkish layer. For meta_morpheme_moved, if the
 * layer does not exist, it checks meta_morpheme layer.
 * @param layer_info Current layer info object
 * @param view_layer Layer to be checked.
 * @return Returns the original layer if the layer exists. For turkish, persian and english_semantics layers, if the
 * layer  does not exist, returns english layer. For part_of_speech, inflectional_group, meta_morpheme, semantics,
 * propbank,  shallow_parse, english_propbank layers, if the layer does not exist, it checks turkish layer
 * recursively. For meta_morpheme_moved, if the layer does not exist, it checks meta_morpheme layer recursively.
 */
View_layer_type check_layer(Layer_info_ptr layer_info, View_layer_type view_layer) {
    View_layer_type result = view_layer;
    switch (view_layer){
        case TURKISH_WORD:
        case PERSIAN_WORD:
        case ENGLISH_SEMANTICS:
            if (!layer_exists(layer_info, view_layer)){
                return ENGLISH_WORD;
            }
        case PART_OF_SPEECH:
        case INFLECTIONAL_GROUP:
        case META_MORPHEME:
        case SEMANTICS:
        case NER:
        case PROPBANK:
        case SHALLOW_PARSE:
        case ENGLISH_PROPBANK:
            if (!layer_exists(layer_info, view_layer)) {
                return check_layer(layer_info, TURKISH_WORD);
            }
            break;
        case META_MORPHEME_MOVED:
            if (!layer_exists(layer_info, view_layer)) {
                return check_layer(layer_info, META_MORPHEME);
            }
            break;
        default:
            break;
    }
    return result;
}

/**
 * Returns number of words in the Turkish or Persian layer, whichever exists.
 * @param layer_info Current layer info object
 * @return Number of words in the Turkish or Persian layer, whichever exists.
 */
int get_number_of_words(Layer_info_ptr layer_info) {
    Word_layer_ptr layer = NULL;
    if (layer_exists(layer_info, TURKISH_WORD)){
        layer = get_layer(layer_info, TURKISH_WORD);
    } else {
        if (layer_exists(layer_info, PERSIAN_WORD)){
            layer = get_layer(layer_info, PERSIAN_WORD);
        }
    }
    if (layer != NULL){
        return layer->items->size;
    } else {
        return 0;
    }
}

void free_layer_info(Layer_info_ptr layer_info) {
    free_hash_map2(layer_info->layers, free_, (void (*)(void *)) free_word_layer);
    free_(layer_info);
}

/**
 * Returns the layer value at the given index.
 * @param layer_info Current layer info object
 * @param layer_type Layer for which the value at the given word index will be returned.
 * @param index Word Position of the layer value.
 * @return Layer info at word position index for a multiword layer.
 */
void* get_multi_word_at(Layer_info_ptr layer_info,
                        View_layer_type layer_type,
                        int index) {
    View_layer_type_ptr layer_ptr = create_view_layer_type(layer_type);
    if (hash_map_contains(layer_info->layers, layer_ptr)){
        Word_layer_ptr word_layer = hash_map_get(layer_info->layers, layer_ptr);
        if (word_layer->items != NULL && index < word_layer->items->size && index >= 0){
            return array_list_get(word_layer->items, index);
        } else {
            if (layer_type == SEMANTICS){
                return array_list_get(word_layer->items, word_layer->items->size - 1);
            }
        }
    }
    free_(layer_ptr);
    return NULL;
}

/**
 * Layers may contain multiple Turkish words. This method returns the Turkish word at position index.
 * @param layer_info Current layer info object
 * @param index Position of the Turkish word.
 * @return The Turkish word at position index.
 */
char *get_turkish_word_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, TURKISH_WORD, index);
}

/**
 * Returns number of meanings in the Turkish layer.
 * @param layer_info Current layer info object
 * @return Number of meanings in the Turkish layer.
 */
int get_number_of_meanings(Layer_info_ptr layer_info) {
    if (layer_exists(layer_info, SEMANTICS)){
        return get_layer(layer_info, SEMANTICS)->items->size;
    } else {
        return 0;
    }
}

/**
 * Layers may contain multiple semantic information corresponding to multiple Turkish words. This method returns
 * the sense id at position index.
 * @param layer_info Current layer info object
 * @param index Position of the Turkish word.
 * @return The Turkish sense id at position index.
 */
char *get_semantic_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, SEMANTICS, index);
}

/**
 * Layers may contain multiple shallow parse information corresponding to multiple Turkish words. This method
 * returns the shallow parse tag at position index.
 * @param layer_info Current layer info object
 * @param index Position of the Turkish word.
 * @return The shallow parse tag at position index.
 */
char *get_shallow_parse_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, SHALLOW_PARSE, index);
}

/**
 * Returns the Turkish PropBank argument info.
 * @param layer_info Current layer info object
 * @return Turkish PropBank argument info.
 */
Argument_ptr get_layer_argument(Layer_info_ptr layer_info) {
    if (layer_exists(layer_info, PROPBANK)){
        Word_layer_ptr argument_layer = get_layer(layer_info, PROPBANK);
        return get_argument(argument_layer);
    } else {
        return NULL;
    }
}

/**
 * A word may have multiple English propbank info. This method returns the English PropBank argument info at
 * position index.
 * @param layer_info Current layer info object
 * @return English PropBank argument info at position index.
 */
Argument_ptr get_argument_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, ENGLISH_PROPBANK, index);
}

/**
 * Layers may contain multiple morphological parse information corresponding to multiple Turkish words. This method
 * returns the morphological parse at position index.
 * @param layer_info Current layer info object
 * @param index Position of the Turkish word.
 * @return The morphological parse at position index.
 */
Morphological_parse_ptr get_morphological_parse_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, INFLECTIONAL_GROUP, index);
}

/**
 * Layers may contain multiple metamorphic parse information corresponding to multiple Turkish words. This method
 * returns the metamorphic parse at position index.
 * @param layer_info Current layer info object
 * @param index Position of the Turkish word.
 * @return The metamorphic parse at position index.
 */
Metamorphic_parse_ptr get_metamorphic_parse_at(Layer_info_ptr layer_info, int index) {
    return get_multi_word_at(layer_info, META_MORPHEME, index);
}

/**
 * For layers with multiple item information, this method returns total items in that layer.
 * @param layer_info Current layer info object
 * @param layer_type Layer name
 * @return Total items in the given layer.
 */
int get_layer_size(Layer_info_ptr layer_info, View_layer_type layer_type) {
    switch (layer_type) {
        case META_MORPHEME:
        case META_MORPHEME_MOVED:
        case PART_OF_SPEECH:
        case INFLECTIONAL_GROUP:
        case ENGLISH_PROPBANK:
            return get_word_layer_size(get_layer(layer_info, layer_type), layer_type);
        default:
            return 0;
    }
}

/**
 * Returns the string form of all layer information except part_of_speech layer.
 * @param layer_info Current layer info object
 * @return The string form of all layer information except part_of_speech layer.
 */
char *get_layer_description(Layer_info_ptr layer_info) {
    char tmp[MAX_WORD_LENGTH] = "";
    Array_list_ptr list = value_list(layer_info->layers);
    for (int i = 0; i < list->size; i++){
        char* description = get_word_layer_description(array_list_get(list, i));
        sprintf(tmp, "%s%s", tmp, description);
        free_(description);
    }
    free_array_list(list, NULL);
    return clone_string(tmp);
}

/**
 * Returns the layer info for the given layer.
 * @param layer_info Current layer info object
 * @param layer_type Layer name.
 * @return Layer info for the given layer.
 */
char *get_layer_data(Layer_info_ptr layer_info, View_layer_type layer_type) {
    if (layer_exists(layer_info, layer_type)){
        return get_layer(layer_info, layer_type)->layer_value;
    } else {
        return NULL;
    }
}

/**
 * Returns the layer info for the given layer, if that layer exists. Otherwise, it returns the fallback layer info
 * determined by the checkLayer.
 * @param layer_info Current layer info object
 * @param layer_type Layer name
 * @return Layer info for the given layer if it exists. Otherwise, it returns the fallback layer info determined by
 * the checkLayer.
 */
char *get_robust_layer_data(Layer_info_ptr layer_info, View_layer_type layer_type) {
    layer_type = check_layer(layer_info, layer_type);
    return get_layer_data(layer_info, layer_type);
}

/**
 * Removes the given layer from hash map.
 * @param layer_info Current layer info object
 * @param layer_type Layer to be removed.
 */
void remove_layer(Layer_info_ptr layer_info, View_layer_type layer_type) {
    View_layer_type_ptr layer_ptr = create_view_layer_type(layer_type);
    hash_map_remove(layer_info->layers, layer_ptr, (void (*)(void *)) free_word_layer);
    free_(layer_ptr);
}

/**
 * Removes metamorpheme and metamorphemesmoved layers.
 * @param layer_info Current layer info object
 */
void meta_morpheme_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, META_MORPHEME);
    remove_layer(layer_info, META_MORPHEME_MOVED);
}

/**
 * Removes English layer.
 * @param layer_info Current layer info object
 */
void english_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, ENGLISH_WORD);
}

/**
 * Removes the dependency layer.
 * @param layer_info Current layer info object
 */
void dependency_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, DEPENDENCY);
}

/**
 * Removed metamorphemesmoved layer.
 * @param layer_info Current layer info object
 */
void meta_morphemes_moved_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, META_MORPHEME_MOVED);
}

/**
 * Removes the Turkish semantic layer.
 * @param layer_info Current layer info object
 */
void semantic_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, SEMANTICS);
}

/**
 * Removes the English semantic layer.
 * @param layer_info Current layer info object
 */
void english_semantic_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, ENGLISH_SEMANTICS);
}

/**
 * Removes the morphological analysis, part of speech, metamorpheme, and metamorphemesmoved layers.
 * @param layer_info Current layer info object
 */
void morphological_analysis_clear(Layer_info_ptr layer_info) {
    remove_layer(layer_info, INFLECTIONAL_GROUP);
    remove_layer(layer_info, PART_OF_SPEECH);
    remove_layer(layer_info, META_MORPHEME);
    remove_layer(layer_info, META_MORPHEME_MOVED);
}

/**
 * Converts layer info of the word at position word_index to an AnnotatedWord. Layers are converted to their
 * counterparts in the AnnotatedWord.
 * @param layer_info Current layer info object
 * @param word_index Index of the word to be converted.
 * @return Converted annotatedWord
 */
Annotated_word_ptr to_annotated_word(Layer_info_ptr layer_info, int word_index) {
    char* st;
    Annotated_word_ptr word = create_annotated_word(get_turkish_word_at(layer_info, word_index));
    if (layer_exists(layer_info, INFLECTIONAL_GROUP)){
        st = morphological_parse_to_string(get_morphological_parse_at(layer_info, word_index));
        word->parse = create_morphological_parse(st);
        free_(st);
    }
    if (layer_exists(layer_info, META_MORPHEME)){
        st = metamorphic_parse_to_string(get_metamorphic_parse_at(layer_info, word_index));
        word->metamorphic_parse = create_metamorphic_parse(st);
        free_(st);
    }
    if (layer_exists(layer_info, SEMANTICS)){
        word->semantic = str_copy(word->semantic, get_semantic_at(layer_info, word_index));
    }
    if (layer_exists(layer_info, NER)){
        word->named_entity_type = get_named_entity_type(get_layer_data(layer_info, NER));
    }
    if (layer_exists(layer_info, PROPBANK)){
        st = argument_to_string(get_layer_argument(layer_info));
        word->argument_list = create_argument_list(st);
        free_(st);
    }
    if (layer_exists(layer_info, SHALLOW_PARSE)){
        word->shallow_parse = str_copy(word->shallow_parse, get_shallow_parse_at(layer_info, word_index));
    }
    return word;
}

