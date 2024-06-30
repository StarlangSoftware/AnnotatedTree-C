//
// Created by Olcay Taner YILDIZ on 22.12.2023.
//

#include <stddef.h>
#include "NodeDrawableCollector.h"

/**
 * Recursive method to check all descendants of the parseNode, if they ever satisfy the given node condition
 * @param parse_node Root node of the subtree
 * @param collected The {@link ArrayList} where the collected ParseNode's will be stored.
 * @param node_condition Condition to check
 */
void collect_nodes(Parse_node_drawable_ptr parse_node,
                   Array_list_ptr collected,
                   bool (*node_condition)(const Parse_node_drawable *)) {
    if (node_condition == NULL || node_condition(parse_node)){
        array_list_add(collected, parse_node);
    }
    for (int i = 0; i < parse_node->children->size; i++){
        collect_nodes(array_list_get(parse_node->children, i), collected, node_condition);
    }
}

/**
 * Recursive method to check all descendants of the parseNode, if they ever satisfy the given node condition
 * @param parse_node Root node of the subtree
 * @param collected The {@link ArrayList} where the collected ParseNode's will be stored.
 * @param node_condition Condition to check
 * @param data Data used in the condition
 */
void collect_nodes2(Parse_node_drawable_ptr parse_node,
                    Array_list_ptr collected,
                    bool (*node_condition)(const Parse_node_drawable *, const void *),
                    void* data) {
    if (node_condition == NULL || node_condition(parse_node, data)){
        array_list_add(collected, parse_node);
    }
    for (int i = 0; i < parse_node->children->size; i++){
        collect_nodes2(array_list_get(parse_node->children, i), collected, node_condition, data);
    }
}

/**
 * Collects and returns all ParseNodes satisfying the node condition.
 * @param node_condition Condition to check
 * @return All ParseNodes satisfying the node condition.
 */
Array_list_ptr collect(Parse_node_drawable_ptr root_node, bool (*node_condition)(const Parse_node_drawable *)) {
    Array_list_ptr result = create_array_list();
    collect_nodes(root_node, result, node_condition);
    return result;
}

/**
 * Collects and returns all ParseNodes satisfying the node condition.
 * @param node_condition Condition to check
 * @param data Data used in the condition
 * @return All ParseNodes satisfying the node condition.
 */
Array_list_ptr collect2(Parse_node_drawable_ptr root_node,
                        bool (*node_condition)(const Parse_node_drawable *, const void *),
                        void *data) {
    Array_list_ptr result = create_array_list();
    collect_nodes2(root_node, result, node_condition, data);
    return result;
}
