//
// Created by Olcay Taner YILDIZ on 23.12.2023.
//

#include <TreeBank.h>
#include <stdio.h>
#include <string.h>
#include "../src/TreeBankDrawable.h"
#include "../src/ParseTreeDrawable.h"

void check_depth(Tree_bank_ptr tree_bank, int index, int depth){
    Parse_tree_drawable_ptr parse_tree = array_list_get(tree_bank->parse_trees, index);
    if (tree_max_depth(parse_tree) != depth){
        printf("Error in depth of tree with index %d with depth %d\n", index, tree_max_depth(parse_tree));
    }
}

int main(){
    Tree_bank_ptr tree_bank = create_tree_bank_drawable("../../trees");
    check_depth(tree_bank, 0, 5);
    check_depth(tree_bank, 1, 5);
    check_depth(tree_bank, 2, 5);
    check_depth(tree_bank, 3, 5);
    check_depth(tree_bank, 4, 6);
    check_depth(tree_bank, 5, 3);
    check_depth(tree_bank, 6, 4);
    check_depth(tree_bank, 7, 6);
    check_depth(tree_bank, 8, 5);
    check_depth(tree_bank, 9, 6);
    Parse_tree_drawable_ptr parse_tree = create_parse_tree_drawable2("../../trees", "0000.dev");
    Parse_tree_ptr parse_tree2 = generate_parse_tree(parse_tree, true);
    String_ptr st = parse_tree_to_string(parse_tree2);
    if (strcmp(st->s, "(S (NP (NP (ADJP (ADJP yeni) (ADJP Büyük))  (NP yasada))  (NP (ADJP karmaşık) (NP dil)) )  (VP (NP savaşı) (VP bulandırmıştır))  (. .)) ") != 0){
        printf("Error\n");
    }
    free_string_ptr(st);
    free_parse_tree(parse_tree2);
    parse_tree2 = generate_parse_tree(parse_tree, false);
    st = parse_tree_to_string(parse_tree2);
    if (strcmp(st->s, "(S (NP (NP (ADJP (ADJP yeni) (ADJP büyük))  (NP yasa))  (NP (ADJP karmaşık) (NP dil)) )  (VP (NP savaş) (VP bulan))  (. .)) ") != 0){
        printf("Error\n");
    }
    free_string_ptr(st);
    free_parse_tree(parse_tree2);
    free_parse_tree_drawable(parse_tree);
    free_tree_bank_drawable(tree_bank);
}