//
//  main.c
//  410_lab002_jtessmer
//
//  Created by James T. Tessmer on 10/17/19.
//  Copyright © 2019 James T. Tessmer. All rights reserved.
//

#include <stdio.h>
#include "utility.h"
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //Testing double linked list functions
    double_linked_list* my_list = makeList();
    printf("The current size of the list is %d \n", getSize(my_list));
    insertElement(10, my_list); //tail
    insertElement(22, my_list); //middle
    insertElement(-14, my_list); //head
    printf("The current size of the list is %d after adding 3 nodes \n", getSize(my_list));


    double_linked_list_node* search_result = search(22, my_list);
    //the result of this search should have the node with value of 22
    printf("The value of the searched node is %d , this should be equal to 22\n", search_result-> value);
    //the previous node should have the value of 10 and the next node should have the value of -14
    printf("The value of the previous node should be -14 and is %d \n", search_result->prevNode_ptr->value);
    printf("The value of the next node should be 10 and is %d \n", search_result->nextNode_ptr->value);


    //removing the middle node
    int removed_num = removeElement(22,my_list);
    printf("The new size should be 2 and is %d \n", getSize(my_list));
    double_linked_list_node* bad_result = search(22, my_list);
    printf("22 was removed, after searching for 22 the result is %d \n", bad_result);


    //searching for 10 and making sure the previous node is now -14
    double_linked_list_node* tail_node = search(10, my_list);
    printf("the node that comes before 10 has the value of %d, and should be -14 \n", tail_node->prevNode_ptr->value);
    removed_num = removeElement(-14, my_list);


    //with -14 removed the node with 10 should be the head
    printf("The value at the head node is %d and should be 10 \n", my_list ->head_ptr->value);
    removeElement(10,my_list); //clearing the list out
    printf("All elements removed from list, the size is now %d \n", my_list ->size);
    free(my_list);


    /*
     Testing circular buffer methods
     */

    circular_buffer* buffy = makeBuffer(4); //Should have 4 slots, 0 occupied
    printf("Buffy has %d of %d slots occupied \n",buffy->occ_slots, buffy ->max_size);
    pushTail(5,buffy); //head
    pushTail(3, buffy); //middle
    pushTail(13, buffy); //middle
    pushTail(7, buffy); //tail

    printf("Buffy has %d of %d slots occupied \n",buffy->occ_slots, buffy -> max_size);
    printf("The value of the head of the buffer is %d \n", buffy -> head_ptr -> value);
    printf("The value of the tail of the buffer is %d \n", buffy -> tail_ptr -> value);
    printf("Adding a new element to the full list. The following num should be 0 and is %d \n", pushTail(22, buffy));
    printf("Buffy has %d of %d slots occupied \n",buffy->occ_slots, buffy -> max_size);


    printf("Moving through the buffer. The returned value is %d \n", popHead(buffy));
    printf("Moving through the buffer. The returned value is %d \n", popHead(buffy));
    printf("Moving through the buffer. The returned value is %d \n", popHead(buffy));
    printf("The number of free slots is %d \n", numFreeSlots(buffy));
    printf("The number of occ slots is %d \n", numOccSlots(buffy));

    printf("Moving through the buffer. The returned value is %d \n", popHead(buffy));
    printf("Buffy has %d of %d slots occupied \n",buffy->occ_slots, buffy ->max_size);
    printf("This should return 0, the value is %d \n", popHead(buffy));

    /*
     Testing binary search tree
     */
    
    binary_tree* cherry = makeTree();
    printf("A new tree has been planted. It's size is %d \n", getTreeSize(cherry));
    insertToTree(10, cherry);
    insertToTree(8, cherry);
    insertToTree(17, cherry);
    insertToTree(13, cherry);
    insertToTree(12, cherry);
    insertToTree(11, cherry);
    insertToTree(15, cherry);
    insertToTree(14, cherry);
    insertToTree(20, cherry);
    
    //size should now be 9
    printf("The tree has grown! It's size is %d \n", getTreeSize(cherry));
    binary_tree_node* search_result_tree = searchTree(17, cherry);
    printf("Searched the tree for 17. What was the value of the searched node? %d \n", search_result_tree -> value);
    int removal_result = removeFromTree(13, cherry);
    printf("Removed 13 from the tree. Was this sucessful %d (1 yes, 2 no) \n", removal_result);
    search_result_tree = searchTree(13, cherry);
    printf("tried to search for 13. Was it found? %d (should print 0 as the address should be NULL) \n", search_result_tree);
    printf("the new size of the tree is %d \n", getTreeSize(cherry));
    search_result_tree = searchTree(17, cherry);
    printf("With 13 gone the left child of 17 should be 14. The value of that child is actually %d \n", search_result_tree -> left_child_ptr -> value);
    removeFromTree(10, cherry);
    printf("Removed the head of the tree. The value of the new head is %d \n", cherry -> root_ptr -> value);



    
    
    return 0;
}
