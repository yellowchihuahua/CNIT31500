#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct Node {
	int key;
	char firstName[64];
	char lastName[64];
	char major[64];
	float GPA;

	struct Node* next;
};
struct Node* _head = NULL;
int studentKeyCounter = 1;

struct Node* CreateNode(char *firstName, char *lastName, char *major, float GPA){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("CreateNode(char *firstName, char *lastName, char *major, float GPA); -- Failed memory allocation.\n");
		exit(1);
	}

	newNode->key = studentKeyCounter;
	studentKeyCounter++;

	strcpy(newNode->firstName, firstName);
	strcpy(newNode->lastName, lastName);
	strcpy(newNode->major, major);
	newNode->GPA = GPA;
	newNode->next = NULL;

	return newNode;
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

int GetIndexByKey(struct Node** start, int key) {
	struct Node* current = *start;
	int count = 0;

	if(key < 1){
		printf("GetIndexByKey(struct Node** start, int key); -- Given key is invalid (less than 1).\n");
		return -1;
	}

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

//generalized function
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
 
    while (i < d) 
        str[i++] = '0'; 
 
    ReverseString(str, i); 
    str[i] = '\0'; 
    return i; 
} 

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
void ftoa(float n, char* res, int afterpoint) 
{ 
    int ipart = (int)n; 
    float fpart = n - (float)ipart; 
 
    int i = IntToStr(ipart, res, 0); 

    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
 
        fpart = fpart * pow(10, afterpoint); 
 
        IntToStr((int)fpart, res + i + 1, afterpoint); 
    } 
} 


//not transferable, todo look at snprintf to generalize
char* ToString(struct Node* node) {
	//todo: look into snprintf
	if(node == NULL){
		printf("ToString(struct Node* node); -- Node is null, nothing to convert.\n");
		return '\0';
	}

	char nodeStr[256];
	strcpy(nodeStr, node->firstName);
	strcat(nodeStr, ", ");
	strcat(nodeStr, node->lastName);
	strcat(nodeStr, ", ");
	strcat(nodeStr, node->major);
	strcat(nodeStr, ", ");
	char gpaStr[10];
	ftoa(node->GPA, gpaStr, 2);
	strcat(nodeStr, gpaStr);
}

void PrintNode(struct Node* node){
	if (node == NULL) {
		printf("PrintNode(struct Node* node); -- Given node is NULL, nothing to print.\n");
		return;
	}
	printf("Key: %d | Data: %s, %s, %s, %.2f\n", node->key, node->firstName, node->lastName, node->major, node->GPA);
}

void PrintList(struct Node** start){
	if(GetListLength(start) == 0){
		printf("PrintList(struct Node** start); -- Empty list, nothing to print.\n");
		return;
	}
	struct Node* current = *start;
	while (current != NULL) {
		PrintNode(current);
		current = current->next;
	}
}

//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
void FreeList(){
//traverse through and free allocated memory
	struct Node* temp;
    while (_head != NULL) {
        temp = _head;
		_head = _head->next;
		free(temp);
    }
}

//InsertFront
//ref ll.c example, TA in person assistance
void InsertFront(struct Node** start, struct Node* nodeToInsert){
	if (GetListLength(start) == 0){
		*start = nodeToInsert;
		return;
	}
	
	nodeToInsert->next = *start; //points next var to front of list, global variable
	*start = nodeToInsert; //inserts node and sets pointer of new front, global varaible
}

//InsertEnd generalized
void InsertEnd(struct Node** start, struct Node* nodeToInsert){
	//check if already has items
	if (GetListLength(start) == 0){
		*start = nodeToInsert;
		return;
	}

	//get to the last node in linked list
	struct Node* current = *start;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = nodeToInsert;
}

//param index is the index before node to insert
void InsertMiddle(struct Node** start, int index, struct Node* nodeToInsert){
	struct Node* previousNode = LookUpByIndex(start, index);
	struct Node* nextNode = LookUpByIndex(start, index+1);

	if(previousNode == NULL){ //if index is at beginning
		InsertFront(start, nodeToInsert);
		return;
	}
	if (nextNode == NULL) { //if index is at end
		InsertEnd(start, nodeToInsert);
		return;
	}
	previousNode->next = nodeToInsert;
	nodeToInsert->next = nextNode; //linking 
}


//not transferable to general linked list functionality?
void InsertByGPA(struct Node** start, struct Node* nodeToInsert) {	
	if (GetListLength(start) == 0) {
		InsertFront(start, nodeToInsert);
		return;
	} 
	//compare with head first

	char nodeToInsertStr[256]; //convert it to a string to compare entir ething alphabetically
	char toInsertGpaStr[10];
	ftoa((5.0f-nodeToInsert->GPA), toInsertGpaStr, 2); //'inverse' of gpa goes first so i can sort completely alphabetically and still get largest gpa first
	strcpy(nodeToInsertStr, toInsertGpaStr); 
	strcat(nodeToInsertStr, nodeToInsert->lastName);
	strcat(nodeToInsertStr, nodeToInsert->firstName);
	strcat(nodeToInsertStr, nodeToInsert->major);

	struct Node* current = *start;
	char currentStr[256]; 
	char currentGpaStr[10];
	ftoa((5.0f-current->GPA), currentGpaStr, 2); //'inverse' of gpa goes first so i can sort completely alphabetically and still get largest gpa first
	strcpy(currentStr, currentGpaStr); 
	strcat(currentStr, current->lastName); //insert the rest of them to compare alphabetically in order
	strcat(currentStr, current->firstName);
	strcat(currentStr, current->major);

	int comp = strcmp(nodeToInsertStr, currentStr);
	if(comp < 0) {//smaller alphabetically
		InsertFront(start, nodeToInsert);
		return;
	}

	current = (*start)->next; //start iterating from second item to utilize InsertMiddle()
	int count = 0; //counter, index to use InsertMiddle() on
	while (current != NULL) {
		currentStr[0] = '\0'; //clear strings
		currentGpaStr[0] = '\0';
		ftoa((5.0f-current->GPA), currentGpaStr, 2); //'inverse' of gpa goes first so i can sort completely alphabetically and still get largest gpa first
		strcpy(currentStr, currentGpaStr); 
		strcat(currentStr, current->lastName); //insert the rest of them to compare alphabetically in order
		strcat(currentStr, current->firstName);
		strcat(currentStr, current->major);
		comp = strcmp(nodeToInsertStr, currentStr);
		
		if(comp < 0) { //alphabetically smaller, inserting before current node
			InsertMiddle(start, count, nodeToInsert);
			return;
		}
		current = current->next;
		count++;
	}
	//reached the end of list and it's not bigger than anything, so inserting at end
	InsertEnd(start, nodeToInsert);
}

//void DeleteFront() {
//	if (_head == NULL) {
//		printf("DeleteFront(); -- Empty list, nothing to delete\n");
//		return;
//	}
//	struct Node* temp = _head; //temp pointer to hold current head
//	_head = _head->next; //make head point to 2nd item in list
//	free(temp); //free temp pointer

void DeleteFront(struct Node** start) {
	if (GetListLength(start) == 0) {
		printf("DeleteFront(struct Node** start); -- Empty list, nothing to delete\n");
		return;
	}
	struct Node* temp = *start; //temp pointer to hold current head
	*start = (*start)->next; //make head point to 2nd item in list
	free(temp); //free temp pointer
}

void DeleteEnd(struct Node** start){
	if (GetListLength(start) == 0) {
		printf("DeleteEnd(struct Node** start); -- Empty list, nothing to delete\n");
		return;
	}
	if ((*start)->next == NULL) {
		FreeList(*start);
	}
	struct Node* current = *start;
	while (current->next->next != NULL) {
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
}

void DeleteMiddle(struct Node** start, int index){
	if (GetListLength(start) == 0) {
		printf("DeleteMiddle(struct Node** start, int index); -- Empty list, nothing to delete.\n");
		return;
	}
	struct Node* nodeToDelete = LookUpByIndex(start, index);
	if(nodeToDelete == NULL) {
		printf("DeleteMiddle(struct Node** start, int index); -- No node exists at given index to delete.\n");
		return;
	}
	struct Node* nodeBefore = LookUpByIndex(start, index-1);
	if(nodeBefore == NULL) { //means the index given was 0, so delete front node
		DeleteFront(start);
		return;
	}
	struct Node* nodeAfter = LookUpByIndex(start, index+1);
	if (nodeAfter == NULL) { //means that index given was last in list, so delete end
		DeleteEnd(start);
		return;
	}

	nodeBefore->next = nodeAfter;
	free(nodeToDelete);
}

//� DONE InsertMiddle - insert a node in the middle of the list. (Hint: use the data
//to know where to insert the node)
//� DONE DeleteFront - delete the first node in the list.
//� DeleteMiddle - delete a node in the middle of the list. (Hint: use the data
//to know where to delete the node)
//� DONE DeleteEnd - delete a node at the end of the list.
//� Traverse - traverse the list based on some key value in the data portion of
//the node.
//DONE � LookUpByIndex - find a particular node by an index number. Return -1 
//if that index does not exist.
//DONE� PrintNode � print information in the current node: first name, last name,
//major, and GPA


int main() {
		
	char student1FirstName[64] = "Cole";
	char student1LastName[64] = "Stack";
	char student1Major[64] = "NET";
	float student1GPA = 3.0;
	struct Node* student1 = CreateNode(student1FirstName, student1LastName, student1Major, student1GPA);

	char student2FirstName[64] = "Haye";
	char student2LastName[64] = "Zail";
	char student2Major[64] = "CSEC";
	float student2GPA = 4.0;
	struct Node* student2 = CreateNode(student2FirstName, student2LastName, student2Major, student2GPA);

	char student3FirstName[64] = "Redd";
	char student3LastName[64] = "Stone";
	char student3Major[64] = "SAAD";
	float student3GPA = 2.0;
	struct Node* student3 = CreateNode(student3FirstName, student3LastName, student3Major, student3GPA);

	char student4FirstName[64] = "Blow";
	char student4LastName[64] = "Torch";
	char student4Major[64] = "Business";
	float student4GPA = 2.5;
	struct Node* student4 = CreateNode(student4FirstName, student4LastName, student4Major, student4GPA);

	char student5FirstName[64] = "Levi";
	char student5LastName[64] = "Er";
	char student5Major[64] = "CGT";
	float student5GPA = 3.9;
	struct Node* student5 = CreateNode(student5FirstName, student5LastName, student5Major, student5GPA);

	char student6FirstName[64] = "Glow";
	char student6LastName[64] = "Stone";
	char student6Major[64] = "SAAD";
	float student6GPA = 2.0;
	struct Node* student6 = CreateNode(student6FirstName, student6LastName, student6Major, student6GPA);

	int listLength = GetListLength(&_head);
	printf("Count: %d\n", listLength);

	InsertByGPA(&_head, student1);
	InsertByGPA(&_head, student2);
	InsertByGPA(&_head, student3);
	InsertByGPA(&_head, student4);
	InsertByGPA(&_head, student5);
	InsertByGPA(&_head, student6);
	
	PrintList(&_head);

	PrintNode(LookUpByIndex(&_head, GetIndexByKey(&_head, 2)));

	DeleteMiddle(&_head, 2);
	PrintNode(LookUpByIndex(&_head, GetIndexByKey(&_head, 1)));
	PrintList(&_head);



	
	listLength = GetListLength(&_head);
	printf("Count: %d\n", listLength);


	char inputChar;
	printf("Press any key to exit: ");
	scanf("%c", &inputChar);

	FreeList();
	return 0;
}