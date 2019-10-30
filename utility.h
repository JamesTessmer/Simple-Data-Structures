//
//  utility.h
//  410_lab002_jtessmer
//
//  Created by James T. Tessmer on 10/17/19.
//  Copyright © 2019 James T. Tessmer. All rights reserved.
//

#ifndef utility_h
#define utility_h

#include <stdio.h>

//parts for double linked list

//node
typedef struct double_linked_list_node{
    int value;
    struct double_linked_list_node* nextNode_ptr;
    struct double_linked_list_node* prevNode_ptr;
}double_linked_list_node;

//main struct for dbl ll
typedef struct double_linked_list{
    struct double_linked_list_node* head_ptr;
    int size;
}double_linked_list;

//methods for manipulating ll
void insertElement(int value, struct double_linked_list* list);
int removeElement(int value,struct double_linked_list* list);
double_linked_list_node* search(int value,struct double_linked_list* list);
int getSize(struct double_linked_list* list);
double_linked_list* makeList(void);



//Making parts for circular buffer
typedef struct circular_buffer{
    int max_size;
    int occ_slots;
    double_linked_list_node* head_ptr;
    double_linked_list_node* tail_ptr;
}circular_buffer;

//functions for manipulating buffer
circular_buffer* makeBuffer(int size);
int getHead(circular_buffer* buffer);
int popHead(circular_buffer* buffer);
int pushTail(int value, circular_buffer* buffer);
int numFreeSlots(circular_buffer* buffer);
int numOccSlots(circular_buffer* buffer);


/*
 Binary tree
 */

typedef struct binary_tree_node{
    int value;
    struct binary_tree_node* parent_ptr;
    struct binary_tree_node* left_child_ptr;
    struct binary_tree_node* right_child_ptr;
    
}binary_tree_node;


typedef struct binary_tree{
    binary_tree_node* root_ptr;
    int size;
    
}binary_tree;

// functions to manipulate the tree
binary_tree* makeTree(void);
int insertToTree(int value, binary_tree* tree);
int removeFromTree(int value, binary_tree* tree);
binary_tree_node* searchTree(int value, binary_tree* tree);
int getTreeSize(binary_tree* tree);
int leafCaseRemoval(int value, binary_tree_node* rem_node);
int oneChildCaseRemoval(binary_tree_node* rem_node);
int recursiveInsert( int value, binary_tree_node* node);
binary_tree_node* recursiveSearch(int value, binary_tree_node* node);

#endif /* utility_h */
