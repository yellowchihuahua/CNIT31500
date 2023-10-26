#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"
//ref https://github.com/skorks/c-linked-list/blob/master/linkedlist.h 


//typedef'd in linkedlist.h 
//ref //ref https://stackoverflow.com/questions/26439354/error-incomplete-type-is-not-allowed
//struct Node {
//	int key;
//	char firstName[64];
//	char lastName[64];
//	char major[64];
//	float GPA;
//
//	struct Node* next;
//};
//
//struct LinkedList{
//	Node* head;
//};

// *needs to be changed if struct Node changes (data received and processed)
struct Node* CreateNode(int key, char *firstName, char *lastName, char *major, float GPA){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("CreateNode(char *firstName, char *lastName, char *major, float GPA); -- Failed memory allocation.\n");
		exit(1);
	}

	newNode->key = key;

	strcpy(newNode->firstName, firstName);
	strcpy(newNode->lastName, lastName);
	strcpy(newNode->major, major);
	newNode->GPA = GPA;
	newNode->next = NULL;

	return newNode;
}

//ref https://github.com/skorks/c-linked-list/blob/master/linkedlist.c
struct LinkedList* CreateList() {
	LinkedList* llist = malloc(sizeof(struct LinkedList));
	if (llist == NULL) {
		printf("CreateList(); -- Failed memory allocation.\n");
		return NULL;
	}
	llist->head = NULL;
	return llist;
}

struct Node* LookUpByIndex(struct Node** start, int index){
	struct Node* current = *start;
	int count = 0;
	if(index < 0){
		printf("LookUpByIndex(struct Node** start, int index); -- Given index is less than 0.\n");
		return NULL;
	}
	while (current != NULL && count < index) {
		current = current->next;
		count++;
	}
	if (current != NULL){
		return current; 
	}
	printf("LookUpByIndex(struct Node** start, int index); -- No node with matching index exists in list.\n");
	return NULL; //reached end of LL, no node with matching data
}

struct Node* LookUpByKey(struct Node** start, int key) {
	if(key < 1){
		printf("LookUpByKey(struct Node** start, int key); -- Given key is invalid (less than 1).\n");
		return NULL;
	}
	struct Node* current = *start;
	while (current != NULL && current->key != key) {
		current = current->next;
	}
	if (current != NULL){
		return current; 
	}
	printf("LookUpByKey(struct Node** start, int key); -- No node with matching key exists in list.\n");
	return NULL; //reached end of LL, no node with matching data
}

int GetKeyByIndex(struct Node** start, int index){
	if (index < 0){
		printf("GetKeyByIndex(struct Node** start, int index); -- Given index is invalid (less than 0).\n");
		return -1;
	}

	struct Node* current = *start;
	int count = 0;
	while (current != NULL && count < index) {
		current = current->next;
		count++;
	}
	if(current != NULL) {
		return current->key;
	}
	printf("GetKeyByIndex(struct Node** start, int index); -- No node with matching index exists in list.\n");
	return -1;
}

int GetIndexByKey(struct Node** start, int key) {
	if(key < 1){
		printf("GetIndexByKey(struct Node** start, int key); -- Given key is invalid (less than 1).\n");
		return -1;
	}
	
	struct Node* current = *start;
	int count = 0;
	while (current != NULL && current->key != key) {
		current = current->next;
		count++;
	}
	if (current != NULL){
		return count; 
	}
	printf("GetIndexByKey(struct Node** start, int key); -- No node with matching key exists in list.\n");
	return -1; //reached end of LL, no node with matching data
}

int GetListLength(struct Node** start){
	int count = 0;
	struct Node* head = *start;
	if (head == NULL){
		return count;
	}
	count++;
	struct Node* current = head;
	while(current->next != NULL){
		current = current->next;
		count++;
	}

	return count;
}

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
void ReverseString(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
int IntToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
    while (i < d) str[i++] = '0'; 
 
    ReverseString(str, i); 
    str[i] = '\0'; 
    return i; 
} 

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
//returns 0 if unsuccessful, 1 if successful
int ftoa(float n, char* res, int afterpoint) 
{ 
    int ipart = (int)n; 
    float fpart = n - (float)ipart; 
 
    int i = IntToStr(ipart, res, 0); 

    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
 
        fpart = fpart * pow(10, afterpoint); 
 
        IntToStr((int)fpart, res + i + 1, afterpoint); 
    } 
	return 1;
} 

//ref https://stackoverflow.com/questions/25798977/returning-string-from-c-function
// *needs to be changed if struct Node changes (snprintf statement)
//Converts node to CSV format. Usage:
//char newNodeCsvString[256];
//ToCsv(node, newNodeCsvString);
//returns 0 if unsuccessful, 1 if successful
int ToCsv(struct Node* node, char *string) {
	if(node == NULL){
		printf("ToCsv(char *string, struct Node* node); -- Node is null, nothing to convert.\n");
		return 0;
	}
	
	snprintf(string, 256, "%d, %s, %s, %s, %.2f\n", node->key, node->firstName, node->lastName, node->major, node->GPA);
	return 1;
}

//ref https://stackoverflow.com/questions/25798977/returning-string-from-c-function
// *needs to be changed if struct Node changes (snprintf statement)
//Converts node to human readable format. Usage: //usage:
//char newNodeString[256];
//ToCsv(node, newNodeString);
//returns 0 if unsuccessful, 1 if successful
int ToString(struct Node* node, char *string) {
	//todo: look into snprintf
	if(node == NULL){
		printf("ToString(char *string, struct Node* node); -- Node is null, nothing to convert.\n");
		return 0;
	}
	snprintf(string, 256, "Key: %d | Data: %s, %s, %s, %.2f\n", node->key, node->firstName, node->lastName, node->major, node->GPA);
	return 1;
}

void PrintNode(struct Node* node){
	if (node == NULL) {
		printf("PrintNode(struct Node* node); -- Given node is NULL, nothing to print.\n");
		return;
	}
	char nodeStr[256];
	ToString(node, nodeStr);
	printf("%s", nodeStr);
}

void PrintList(struct Node** start){
	if(GetListLength(start) == 0){
		printf("PrintList(struct Node** start); -- Empty list, nothing to print.\n");
		return;
	}
	struct Node* current = *start;
	while (current != NULL) {
		printf("Index: %d | ", GetIndexByKey(start, current->key));
		PrintNode(current);
		current = current->next;
	}
}

//Traverse() functionality?
//ref https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
void PrintSearch(struct Node** start, char* searchRequest) {
	struct Node* current = *start;
	char nodeString[256];

	while(current != NULL) {
		ToCsv(current, nodeString);
		if(strstr(nodeString, searchRequest) != NULL){
			PrintNode(current);
		}
		current = current->next;
	}
}

//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
void FreeList(struct Node** start){
//traverse through and free allocated memory
	struct Node* temp = *start;
    while ((*start) != NULL) {
        temp = (*start);
		(*start) = (*start)->next;
		free(temp);
    }
}

//InsertFront
//ref ll.c example, TA in person assistance
int InsertFront(struct Node** start, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertFront(struct Node** start, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}
	if (GetListLength(start) == 0){
		*start = nodeToInsert;
		return 1;
	}
	nodeToInsert->next = *start; //points next var to front of list, global variable
	*start = nodeToInsert; //inserts node and sets pointer of new front, global varaible
	return 1;
}

//InsertEnd generalized
//returns 0 if unsuccessful, 1 if successful
int InsertEnd(struct Node** start, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertEnd(struct Node** start, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}
	if (GetListLength(start) == 0){
		*start = nodeToInsert;
		return 1;
	}
	struct Node* current = *start;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = nodeToInsert;
	return 1;
}

//param index is the index before node to insert
//returns 0 if unsuccessful, 1 if successful
int InsertMiddle(struct Node** start, int index, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertMiddle(struct Node** start, int index, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}

	//check end cases
	if(index == 0){ //if index is at beginning
		InsertFront(start, nodeToInsert);
		return 1;
	}
	if (index == GetListLength(start)) { //if index is at end
		InsertEnd(start, nodeToInsert);
		return 1;
	}
	
	struct Node* previousNode = LookUpByIndex(start, index);
	struct Node* nextNode = LookUpByIndex(start, index+1);
	previousNode->next = nodeToInsert;
	nodeToInsert->next = nextNode; //linking 
	return 1;
}

// *needs to be changed if struct Node changes (snprintf usage)
//Created to streamline InsertByGPA. Converts entire node to a string in order of comparison priority to use strcmp to sort entire thing alphabetically
//Usage: refer to ToString and ToCsv usage
//returns 0 if unsuccessful, 1 if successful
int ToComparisonString(struct Node* node, char* string){
	if(node == NULL){
		printf("ToComparisonString(char *string, struct Node* node); -- Node is null, nothing to convert.\n");
		return 0;
	}
	
	//to string and inverting gpa to maintain descending order
	char gpaStr[10];
	ftoa((5.0f-node->GPA), gpaStr, 2);

	//ORDER OF COMPARISON:
	//inverted gpa, last name, first name, major
	snprintf(string, 256, "%.2f%s%s%s\n", gpaStr, node->lastName, node->firstName, node->major);
	return 1;
}

// *needs to be changed if struct Node changes
//not transferable to general linked list functionality?
//returns 0 if unsuccessful, 1 if successful
int InsertByGPA(struct Node** start, struct Node* nodeToInsert) {	
	//validate GPA data first
	if(nodeToInsert->GPA < 0 || nodeToInsert->GPA > 4.0f){
		printf("InsertByGPA(struct Node** start, struct Node* nodeToInsert); -- Invalid GPA.\n");
		return 0;
	}


	if (GetListLength(start) == 0) {
		InsertFront(start, nodeToInsert);
		return 1;
	} 
	//compare with head first

	char nodeToInsertStr[256]; //convert it to a string to compare entir ething alphabetically
	ToComparisonString(nodeToInsert, nodeToInsertStr);

	struct Node* current = *start;
	char currentStr[256]; 
	ToComparisonString(current, currentStr);

	int comp = strcmp(nodeToInsertStr, currentStr);
	if(comp < 0) {//smaller alphabetically
		InsertFront(start, nodeToInsert);
		return 1;
	}

	current = (*start)->next; //start iterating from second item to utilize InsertMiddle()
	int count = 0; //counter, index to use InsertMiddle() on
	while (current != NULL) {
		currentStr[0] = '\0'; //clear strings
		ToComparisonString(current, currentStr);

		comp = strcmp(nodeToInsertStr, currentStr);
		if(comp < 0) { //alphabetically smaller, inserting before current node
			InsertMiddle(start, count, nodeToInsert);
			return 1;
		}
		current = current->next;
		count++;
	}
	//reached the end of list and it's not bigger than anything, so inserting at end
	InsertEnd(start, nodeToInsert);
	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteFront(struct Node** start) {
	if (GetListLength(start) == 0) {
		printf("DeleteFront(struct Node** start); -- Empty list, nothing to delete\n");
		return 0;
	}
	struct Node* temp = *start; //temp pointer to hold current head
	*start = (*start)->next; //make head point to 2nd item in list
	free(temp); //free temp pointer

	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteEnd(struct Node** start){
	if (GetListLength(start) == 0) {
		printf("DeleteEnd(struct Node** start); -- Empty list, nothing to delete\n");
		return 0;
	}
	if ((*start)->next == NULL) { //free head if head is only item
		FreeList(start);
	}
	struct Node* current = *start;
	while (current->next->next != NULL) {
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteMiddle(struct Node** start, int index){
	if (GetListLength(start) == 0) {
		printf("DeleteMiddle(struct Node** start, int index); -- Empty list, nothing to delete.\n");
		return 0;
	}
	struct Node* nodeToDelete = LookUpByIndex(start, index);
	if(nodeToDelete == NULL) {
		printf("DeleteMiddle(struct Node** start, int index); -- No node exists at given index to delete.\n");
		return 0;
	}
	
	//check ends
	if(index == 0) { 
		DeleteFront(start);
		return 1;
	}
	if (index == GetListLength(start)) { 
		DeleteEnd(start);
		return 1;
	}
	struct Node* nodeBefore = LookUpByIndex(start, index-1);
	struct Node* nodeAfter = LookUpByIndex(start, index+1);
	nodeBefore->next = nodeAfter;
	free(nodeToDelete);
	return 1;
}
