#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct Student
// {
//     char first_name[32];
//     char last_name[32];
//     char major[32];
//     float GPA;

//     struct Student* next;
// } Student;

struct Student
{
    char first_name[32];
    char last_name[32];
    char major[32];
    float GPA;

    struct Student* next;
};

void print_list(struct Student* first_node)
{
    if(!first_node) 
    {
        printf("attempting to print an empty list...\n");
        return;
    }
    struct Student* curr = first_node;
    while(curr)
    {
        printf("%s\n", curr->first_name);
        curr = curr->next;
    }
    free(curr);
}

// this function allows us to erase the entire list recursively...
// this is an extremely simple implementation, and should show how powerful recursion can be
// the alternative is keeping track of order some how, or by adding pointer directions
// I am returning a Student poinbter so that I can use the same liss address for later, but it is not necessary... it really depends on your design
struct Student* erase_list_recursive(struct Student* curr) {
    // if node is NULL, return it... we want the list to be NULL, which tells us its empty
    if (curr == NULL) return curr;

    // iterate through the list with recursive call
    //  notice nothing is happening yet... we usually have code above to process stuff...
    struct Student* next_student = erase_list_recursive(curr->next);

    // but since we do not want to delete front to back, we can put our code AFTER the recursive call, so that things are done in reverse
    // try putting this above the recursive call, you are likely to get an error if you try to use the list later
    free(curr);
    return next_student;
}

int main()
{
    // create empty linked list of Student nodes
    // since it points to NULL, then it is empty
    // actual start node lets use know which node is at the front; the names of nodes can be confusing here, but just pay attention to actual_start_node
    struct Student* actual_start_node;
    struct Student* first_student = NULL;

    // Create Linked List
    // ------------------
    // creating a linked list is just initializing the first node, or Student in our case; we only need the address of the first node to do what we need to with linked lists
    // allocate memory for storing data
    // make first_student.next = NULL, so we have one piece of data, with potential for more, but still a NULL value so we know the list is ended
    first_student = (struct Student*)malloc(sizeof(struct Student));
    strncpy(first_student->first_name, "a\0", 2);
    first_student->next = NULL;
    // assign start node as the first student
    actual_start_node = first_student;

    // Add Node to End
    // ---------------
    // add a second Student node to the end...
    struct Student* second_student = NULL; 
    second_student = (struct Student*)malloc(sizeof(struct Student));
    strncpy(second_student->first_name, "b\0", 2);
    first_student->next = second_student;
    second_student->next = NULL;

    // Add Node to End
    // ---------------
    // add a third Student node to the end...
    struct Student* third_student = NULL; 
    third_student = (struct Student*)malloc(sizeof(struct Student));
    strncpy(third_student->first_name, "c\0", 2);
    second_student->next = third_student;
    third_student->next = NULL;

    // Add Node to Front
    // -----------------
    // add a fourth student to the beginning
    struct Student* fourth_student = NULL; 
    fourth_student = (struct Student*)malloc(sizeof(struct Student));
    strncpy(fourth_student->first_name, "a\0", 2);
    fourth_student->next = first_student;
    // reassign start node to the fourth node, since it is now the first of the list
    actual_start_node = fourth_student;
    print_list(actual_start_node);

    // Remove Last Node
    // ----------------
    // create curr counter for looping, point to first node
    struct Student* curr = actual_start_node;
    // loop until we get a second-to-last node. This is important if you are not keepijng count, because we can use it to access the last node without reversing or something
    while(curr->next->next)
        curr = curr->next;
    // free the node that did not enter the loop; we broke the loop, but we ended with current node we need
    free(curr->next);
    // assign NULL to current node so that we know it's ended
    curr->next = NULL;

    // Remove First Node
    // -----------------
    // we simply want to assign actual start node to tmp1 and its next address to tmp2, so we can free space from tmp1, then make actual start node tmp2
    // "grabbing" immedate node after desired node is important so we can point to them, delete the desired node, then assign actual start node to the one we grabbed
    // if we do not follow this order, then we may delete the first node, while the subsequent nodes are left in memory, without a way to access them (first node is gone and it has the address)
    struct Student* tmp1 = actual_start_node;
    struct Student* tmp2 = tmp1->next;
    free(tmp1);
    actual_start_node = tmp2;

    printf("\n");
    print_list(actual_start_node);

    // Freeing Pointer Memory
    // ----------------------
    // for every memory allocation you make, you must make a paired free() ijn order to prevent memory leaks
    // there is an order to this operation! you must delete from reverse, or else you will delete a node that points to used memory space, that is not longer easy to free... recursive functions are great for this, because it is simply not easy to this otherwise... you have to keep track of reverse to last on your own
    // the erase function returns the first node, so that you still have the first node to work with for later
    // currently this list is empty; the first node points to NULL
    printf("\n");
    actual_start_node = erase_list_recursive(actual_start_node);
    print_list(actual_start_node);

    free(tmp2);
    free(curr);

    return 0;
}
