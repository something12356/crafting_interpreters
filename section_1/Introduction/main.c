#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct PSP{ // Each node in list will be a PSP struct. Has a back pointer, value, forward pointer.
    struct PSP* bptr;
    char string[256];
    struct PSP* fptr;
};

struct PSP* find(int index, struct PSP start_node){
    int count = 0;
    struct PSP* current_ptr = start_node.fptr;
    while (count < index){
        current_ptr = (*current_ptr).fptr; // Update pointer to be the pointer to the next node in list
        count++;
    }
    if (current_ptr == NULL){exit(EXIT_FAILURE);} // If you've got a null pointer you've fucked up
    return current_ptr;
}

void update(int index, char value[256], struct PSP start_node){ // Changes value of existing item in list
    struct PSP* node_to_update = find(index, start_node);
    memcpy((*node_to_update).string, value, 256);
    // Assigning arrays in C is weird. If you have two arrays A, B that are same size, can't just do B=A.
    // Need to use memcpy to copy bytes of A to B.
    return;
} 

void insert(int index, char value[256], struct PSP* start_node, struct PSP* new_node){
    struct PSP* prev_node; // Node behind node we're inserting
    struct PSP prev_node_actually_a_node_not_a_pointer;
    if (index == 0){
        prev_node = start_node;
    }
    else{
        prev_node = find(index-1, (*start_node));
    }

    struct PSP* post_node = (*prev_node).fptr; // Node in front of node we're inserting
     // Insert node
    (*new_node).fptr = post_node;
    (*new_node).bptr = prev_node;
    // I can't just initialise new_node with value apparently :/ need to copy it over ffs
    for (int i=0; i<256; i++){
        (*new_node).string[i]=value[i];
    }

    (*prev_node).fptr = new_node; // Update previous node front pointer
    (*post_node).bptr = new_node; // Update next node front_pointer
    return; // Length has increased!
}

void delete(int index, struct PSP start_node){
    struct PSP* node_to_delete = find(index, start_node);
    struct PSP* prev_node = (*node_to_delete).bptr;
    struct PSP* post_node = (*node_to_delete).fptr;
    (*prev_node).fptr = post_node;
    (*post_node).bptr = prev_node;
    return; // Length has decreased!
}

int main(){
    struct PSP start_node = {0, 0, 0}; // points to first item in list
    struct PSP end_node = {0, 0, 0}; // points to last item in list
    start_node.fptr = &end_node;
    end_node.bptr = &start_node; // Initialise pointers for the end nodes

    // length = 0;
    // struct PSP node_0 = {0, "Hiii", 0};
    // start_node.fptr = &node_0;
    // printf(find(0, length, start_node).string);
    struct PSP node1;
    struct PSP node2;
    struct PSP node3;
    
    insert(0, "Hey", &start_node, &node1);
    printf((*find(0, start_node)).string);
    printf("\n");

    insert(1, "Helloooo", &start_node, &node2);
    printf((*find(1, start_node)).string);
    printf("\n");

    insert(2, "does this work???", &start_node, &node3);
    printf((*find(1, start_node)).string);
    printf("\n");
    printf((*find(2, start_node)).string);
    printf("\n");

    delete(1, start_node);
    printf((*find(1, start_node)).string);
    printf("\n");

    update(1, "Testing update function", start_node);
    printf((*find(1, start_node)).string);

    return 0;
}