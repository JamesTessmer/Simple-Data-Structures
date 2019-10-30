//
//  utility.c
//  410_lab002_jtessmer
//
//  Created by James T. Tessmer on 10/17/19.
//  Copyright © 2019 James T. Tessmer. All rights reserved.
//

#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

//defining ll functions
/*
 Use passed ll to get a ptr to the head, then set the new node as the new head
 and point the new node to the previous head as next
 
 If there are no nodes (size = 0) then the struct points to the new node as head without shuffling anything around
 */
void insertElement(int value, struct double_linked_list* list){
    //initializing new node
    double_linked_list_node* new_node_ptr = (double_linked_list_node*) malloc(sizeof(double_linked_list_node));
    new_node_ptr->value = value;
    new_node_ptr->prevNode_ptr = NULL;
    new_node_ptr->nextNode_ptr = NULL;
    //if there are no nodes in the list then set new node to the head
    
    if(list->size == 0){
        list->head_ptr = new_node_ptr;
        list -> size = list ->size + 1;
        return;
    }
    
    //if there are other nodes present, set new head to new node and current head to next node of the new head
    double_linked_list_node* previous_head_ptr = list->head_ptr;
    list -> head_ptr = new_node_ptr;
    new_node_ptr -> nextNode_ptr = previous_head_ptr;
    previous_head_ptr -> prevNode_ptr = new_node_ptr;
    list -> size = list ->size + 1;
    
}

/*
 Uses the search function to find the matching node, then removes it from the linked list and returns the value. If the node isn't present -1 is returned. Nodes are freed when removed
 
 When a node is removed it sets the previous nodes next node to the removed nodes next node, and does the same with the previous node. If the removed node is the head then the required adjustments are made in the list struct.
 
 */
int removeElement(int value,struct double_linked_list* list){
    //searching for the node
    double_linked_list_node* rem_node = search(value, list);
    
    //If the result of the search is null then return null
    if(rem_node == NULL){
        return -1;
    }
    
    //decrementing list size
    list -> size -= 1;
    
    //if the node is the head then previous node should be NULL
    if(rem_node -> prevNode_ptr == NULL){
        
        //If the last node in the list is the head (0 because decrementing already occured)
        if(list->size == 0){
            free(rem_node);
            return value;
        }
        list -> head_ptr = rem_node -> nextNode_ptr; // set the head to the removed nodes next node
        rem_node -> nextNode_ptr -> prevNode_ptr = NULL; //adjusting so the previous node is null so that this function works more than once
        free(rem_node);
        return value;
    } else if (rem_node->nextNode_ptr == NULL){ //if the node to be removed is the tail
        rem_node -> prevNode_ptr -> nextNode_ptr = NULL; //setting the previous nodes next node value to Null to signify it as the new tail
        free(rem_node);
        return value;
    } else {
        //this case would be a node in the middle of the list
        //getting a pointer to the prev and next node
        double_linked_list_node* prev_node = rem_node -> prevNode_ptr;
        double_linked_list_node* next_node = rem_node -> nextNode_ptr;
        //assigning the previous nodes next node to the removed nodes next node, and vice versa
        prev_node -> nextNode_ptr = next_node;
        next_node -> prevNode_ptr = prev_node;
        free(rem_node);
        return value;
        
    }
    
    
}

/*
 Starts at the head and searches until the requested node value is found.
 If that node is found the pointer to that node is returned. If it is not found then null is returned
 */
double_linked_list_node* search(int value,struct double_linked_list* list){
    //making sure there are nodes to iterate through
    if(list -> size == 0){
        return NULL;
    }
    //using a for loop go through each node
    double_linked_list_node* current_node_ptr = list -> head_ptr;
    for(int i =0; i < list-> size;i++){
        if(current_node_ptr-> value == value){
            return current_node_ptr;
        }
        //if the value isn't found move to the next node
        current_node_ptr = current_node_ptr -> nextNode_ptr;
    }
    
    //if code reaches this far then the matching value wasn't found
    return NULL;
    
}

/*
 Returns the size of the linked list by returning size value of passed in struct
 */
int getSize(struct double_linked_list* list){
    return list -> size;
}

/*
 Initializes the double linked list for the user. The head pointer can be unassigned as this is managed when adding nodes, but size needs to be initialized as 0
 */
double_linked_list* makeList(){
    double_linked_list* list_ptr = (double_linked_list*) malloc(sizeof(double_linked_list));
    list_ptr -> size = 0;
    return list_ptr;
}


/*
 Functions for circle buffer
 */

/*
 Creating the circular buffer and initializing the head and tail pointers as well as creating empty nodes.
 */
circular_buffer* makeBuffer(int size){
    //creating the buffer and the head node
    circular_buffer* buff = (circular_buffer*) malloc(sizeof(circular_buffer));
    buff -> max_size = size;
    buff -> occ_slots = 0;
    
    double_linked_list* list = makeList();
    
    //creating the rest of the nodes, just going to make a ll then bind the ends
    for(int i = 0; i <= size; i++){
        //printf("%d",i);
        insertElement(i, list);
    }
    
    //closing the loop
    buff -> head_ptr = list -> head_ptr;
    buff -> tail_ptr = search(0, list);
    
    buff -> head_ptr -> prevNode_ptr = buff -> tail_ptr;
    buff -> tail_ptr -> nextNode_ptr = buff -> head_ptr;
    
    buff ->head_ptr = buff ->tail_ptr; //making sure the head and tail point to the same place
    //buff -> tail_ptr = buff -> tail_ptr -> nextNode_ptr;
    free(list);
    return buff;
}

/*
 returns the value at the head
 */
int getHead(circular_buffer* buffer){
    return buffer -> head_ptr -> value;
}
/*
 Gets and returns the head value and moves the head of the buffer to the next node, making necessary adjustments. If there is no currently stored value in the buffer 0 is returned
 */
int popHead(circular_buffer* buffer){
    if(buffer -> occ_slots == 0){
        return 0;
    }
    buffer -> occ_slots --;
    int value = getHead(buffer);
    buffer -> head_ptr = buffer -> head_ptr -> nextNode_ptr;
    return value;
}

/*
 Pushes a value into an empty node at the tail of the buffer making necessary adjustments. If the buffer is full then 0 is returned, otherwise 1 is returned to indicate success
 */
int pushTail(int value, circular_buffer* buffer){
    if( buffer -> occ_slots == buffer -> max_size){
        return 0;
    }
    //updating counter
    
    if(buffer -> occ_slots == 0){
        buffer -> tail_ptr -> value = value;
        buffer -> occ_slots ++;
        return 1;

    }
    
    buffer -> occ_slots ++;
    
    //updating buffer tail ptr, and updating value of the new tail
    buffer -> tail_ptr = buffer -> tail_ptr -> nextNode_ptr;
    buffer -> tail_ptr -> value = value;
    return 1;
}

/*
 Returns the number of free slots available in the buffer
 */
int numFreeSlots(circular_buffer* buffer){
    int free_slots = buffer -> max_size - buffer -> occ_slots;
    return free_slots;
}

/*
 Returns the number of occupied slots in the buffer
 */
int numOccSlots(circular_buffer* buffer){
    return buffer -> occ_slots;
}

/*
 Search tree functions
 */

/*
 Makes a tree and initializes values
 */
binary_tree* makeTree(void){
    binary_tree* tree = (binary_tree*) malloc(sizeof(binary_tree));
    tree -> size = 0;
    tree -> root_ptr = NULL;
    return tree;
}

/*
 Inserts a node into the tree by recursively searching. returns 1 on success and 0 on failure, kicks off the recursive method
 */
int insertToTree(int value, binary_tree* tree){
    if(tree -> size == 0){ //if the node is going to be the root
        binary_tree_node* new_node = (binary_tree_node*) malloc(sizeof(binary_tree_node));
        tree -> root_ptr = new_node;
        new_node -> value = value;
        new_node -> left_child_ptr = NULL;
        new_node -> right_child_ptr = NULL;
        tree -> size ++;
        return 1;
    }
    
    //if you get to this point then the recursive function kicks off
    tree -> size ++;
    return recursiveInsert(value, tree -> root_ptr);
}

/*
 Recursive function that finds the next available slot to insert a node. Returns 1 on success, 0 on failure (only occurs when a value already exists)
 */
int recursiveInsert( int value, binary_tree_node* node)
{
    if(node -> value > value){ //if value is less than node's then go left
        // checking to see if the left node is occupied
        if(node -> left_child_ptr == NULL){ // if it's available
            binary_tree_node* new_node = (binary_tree_node*) malloc(sizeof(binary_tree_node));
            new_node -> value = value;
            new_node -> left_child_ptr = NULL;
            new_node -> right_child_ptr = NULL;
            node -> left_child_ptr = new_node;
            new_node -> parent_ptr = node;
            return 1;
        } else { //if that node is occupied, keep going
            return recursiveInsert(value, node -> left_child_ptr);
        }
        
        
    }else if(node -> value < value){ //if value is greater than node's then go right
        if(node -> right_child_ptr == NULL){ // if it's available
            binary_tree_node* new_node = (binary_tree_node*) malloc(sizeof(binary_tree_node));
            new_node -> value = value;
            new_node -> left_child_ptr = NULL;
            new_node -> right_child_ptr = NULL;
            new_node -> parent_ptr = node;
            node -> right_child_ptr = new_node;
            return 1;
        } else { //if that node is occupied, keep going
            return recursiveInsert(value, node -> right_child_ptr);
        }
    }
    
    //if it gets here then the value matches, return 0
    return 0;
    
}

/*
 Calls the search function to find the node to remove. Then makes the necessary changes to the tree and frees the node. Returns 1 on success, 0 on failure.
 */
int removeFromTree(int value, binary_tree* tree){
    //search for the node in question
    binary_tree_node* rem_node = searchTree(value, tree); //handle on the node to remove
    if(rem_node == NULL){ //if there's no matching node
        return 0;
    }
    
    tree -> size --;
    
    binary_tree_node* parent = rem_node -> parent_ptr; //ptr to the parent for changing ptr to child node
    
    int is_leaf = leafCaseRemoval(value, rem_node);
    if(is_leaf == 1){
        return 1;
    }
    
    //Dealing with the case where the node only has 1 child
    int is_one_child = oneChildCaseRemoval(rem_node);
    if(is_one_child == 1){
        return 1;
    }
    
    //if the node is not a leaf then we must find the left most right child to swap in, and then remove the rem_node
    //finding the left most right node
    
    binary_tree_node* left_most = rem_node -> right_child_ptr;
    while(left_most -> left_child_ptr != NULL){ //once it's NULL then that's the left most right
        left_most = left_most -> left_child_ptr;
        
    }
    
    //setting rem_nodes value to be the same as left_most,then freeing left_most
    rem_node -> value = left_most -> value;
    
    //if the left-most right has a right child then shift that to the left node of the parent of the left-most right
    if(left_most -> right_child_ptr != NULL){
        left_most -> parent_ptr -> left_child_ptr = left_most -> right_child_ptr;
        left_most -> right_child_ptr -> parent_ptr = left_most -> parent_ptr;
    }
    //we have the left-most right node
    
    printf("%d", left_most -> value);
    
    free(left_most);
    return 1;
}

/*
 Helper functions for removal
 */

int leafCaseRemoval(int value, binary_tree_node* rem_node){
    binary_tree_node* parent = rem_node -> parent_ptr; //ptr to the parent for changing ptr to child node
    
    if(rem_node ->left_child_ptr == NULL && rem_node -> right_child_ptr == NULL){ //if no children then it's a leaf
        //checking to see if rem node is right or left
        
        if(parent -> left_child_ptr != NULL){
            if(parent -> left_child_ptr -> value == value){// if the parent has a left child then compare values, if same then remove left child reference
                parent -> left_child_ptr = NULL;
            }
        }
        
        //checking the right side
        
        if(parent -> right_child_ptr != NULL){
            if(parent -> right_child_ptr -> value == value){// if the parent has a left child then compare values, if same then remove left child reference
                parent -> right_child_ptr = NULL;
            }
        }
        
        //the proper child pointer should be set to NULL now
        free(rem_node);
        return 1;
    }
    
    return 0;
}

int oneChildCaseRemoval(binary_tree_node* rem_node){
    //when this function is called the leaf case should've been checked, so we know this node has 1 child or 2 children
    if(rem_node -> left_child_ptr != NULL && rem_node -> right_child_ptr != NULL){ //if both children are presnt then this case doesn't matter
        return 0;
    }
    
    binary_tree_node* parent = rem_node -> parent_ptr;
    if(rem_node -> left_child_ptr != NULL){ //if the left child is present
        parent -> left_child_ptr = rem_node -> left_child_ptr;
        rem_node -> left_child_ptr -> parent_ptr = parent;
        free(rem_node);
        return 1;
    } else{ //if the right child is present
        parent -> right_child_ptr = rem_node -> right_child_ptr;
        rem_node -> right_child_ptr -> parent_ptr = parent;
        free(rem_node);
        return 1;
        
    }
}


/*
 Recursively searches the tree to find the right node. If it is found the node is returned, else NULL is returned.
 */
binary_tree_node* searchTree(int value, binary_tree* tree){
    //checking root
    binary_tree_node* root = tree -> root_ptr;
    if(root == NULL){
        return NULL;
    }
    
    if(root -> value == value){
        return root;
    }
    
    
    
    //if it's not root then compare
    if (root -> value > value){ //if value is less than tree's go left
        //if left node is empty then return null
        if(root -> left_child_ptr == NULL){
            return NULL;
        }
        return recursiveSearch(value, root -> left_child_ptr);
    } else { //else go right
        //if right node is empty then return null
        if(root -> right_child_ptr == NULL){
            return NULL;
        }
        return recursiveSearch(value, root -> right_child_ptr);
    }
}

/*
 The recursive search kicked off by the previous function
 */
binary_tree_node* recursiveSearch(int value, binary_tree_node* node){
    //checking if current node is the right one
    if(value == node -> value){
        return node;
    }
    
    
    if (node -> value > value){ //if value is less than node's go left
        //if left node is empty then return null
        if(node -> left_child_ptr == NULL){
            return NULL;
        }
        return recursiveSearch(value, node -> left_child_ptr);
    } else { //else go right
        //if right node is empty then return null
        if(node -> right_child_ptr == NULL){
            return NULL;
        }
        return recursiveSearch(value, node -> right_child_ptr);
    }
    
    
}

int getTreeSize(binary_tree* tree){
    return tree -> size;
}
