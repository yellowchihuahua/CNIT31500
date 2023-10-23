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
	printf("LookUpByIndex(struct Node** start, int index); -- No node with matching index exists in list.\n");
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

struct Node* LookUpByKey(struct Node** start, int key) {
	if(key < 1){
		printf("GetIndexByKey(struct Node** start, int key); -- Given key is invalid (less than 1).\n");
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

int ReceiveIntInput(char *prompt, int minInclusive){
    int value = -1;
    do {
        char input[5];
        printf("%s", prompt);
        scanf("%s", &input);
        value = atoi(input);

        if (value < minInclusive) {
            printf("That is an invalid entry, please enter a valid integer over %i.\n", minInclusive);
            value = -1;
        }
    } while (value == -1);

    return value;
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

//NOT FUNCTIONAL, todo: look at snprintf to generalize
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
		printf("Index: %d | ", GetIndexByKey(&_head, current->key));
		PrintNode(current);
		current = current->next;
	}
}

//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
void FreeList(struct Node** start){
//traverse through and free allocated memory
	struct Node* temp = *start;
    while ((*start) != NULL) {
        temp = (*start);
		(*start) = _head->next;
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

// EXAMPLE: void DeleteFront() { WHERE _is global
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
		FreeList(start);
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
		printf("DeleteMiddle(struct Node** start, int index); -- Requested node to delete is start of list, deleting head node.\n");

		return;
	}
	struct Node* nodeAfter = LookUpByIndex(start, index+1);
	if (nodeAfter == NULL) { //means that index given was last in list, so delete end
		DeleteEnd(start);
		printf("DeleteMiddle(struct Node** start, int index); -- Requested node to delete is end of list, deleting end node.\n");
		return;
	}

	nodeBefore->next = nodeAfter;
	free(nodeToDelete);
}

int main() {

	int cont = 1;
	int userInputCounter = 0;
	
	do {
		int functionNumber = 0;
        printf("\n===============================================================================\n");
        printf("Hi User! You have used %i functions within this program so far!\n", userInputCounter);
        printf("Here are your options: \n");
        printf("(1) Print all students in linked list\n");
        printf("(2) Insert a student to linked list by GPA order\n");
        printf("(3) Delete a student from linked list using their key ID\n");
        printf("(4) Delete a student from linked list using their list index\n");
        printf("(5) Find a student from linked list\n");
        printf("(6) Exit the program\n");
        //functionNumber =ReceiveIntInput("Enter the number of the function you would like to use (1-5): ", 1);

		printf("Enter the number you would like to use (1-6): ");
		scanf("%d", &functionNumber);
		userInputCounter++;


		switch(functionNumber){
			case 1:
				printf("Here is the list of all your students: ----------------------------------------\n");
				PrintList(&_head);
				printf("-------------------------------------------------------------------------------\n");
				break;

			case 2:
				//insert a student to linked list
				printf("Enter the information of the student you would like to add.\n");

				char newStudentFirstName[64], newStudentLastName[64], newStudentMajor[64];
				float newStudentGPA;
				char newStudentGPAStr[8];
				printf("Type your inputs and press enter:\n");
				printf("New student's First Name: ");
                scanf("%s", newStudentFirstName);
                printf("New student's Last Name: ");
                scanf("%s", newStudentLastName);
                printf("New student's Major: ");
                scanf("%s", newStudentMajor);
                printf("New student's GPA: ");
                scanf("%s", &newStudentGPAStr);
				newStudentGPA = atof(newStudentGPAStr);

				struct Node* currentStudent = CreateNode(newStudentFirstName, newStudentLastName, newStudentMajor, newStudentGPA);
				printf("Node to add: ");
				PrintNode(currentStudent);

				char confirmation[1] = "n";
				printf("Enter y to confirm this is correct, any other key to deny: ");
				scanf("%s", confirmation);
				
				if(strcmp(confirmation, "y") == 0){
					InsertByGPA(&_head, currentStudent);
					printf("New node added!\n");
				} else {
					printf("Add node action cancelled.\n");
					studentKeyCounter--;//free usage of ID
				}
				break;

			case 3:
				//delete a student from linked list by key
				printf("Enter the key of the student you would like to delete.\n");

				int delStudentKey;
				char delStudentKeyStr[64];
				printf("Student key: ");
                scanf("%s", delStudentKeyStr);
				delStudentKey = atoi(delStudentKeyStr);

				//validate if node exists with this key
				currentStudent = LookUpByKey(&_head, delStudentKey);
				if (currentStudent == NULL) {
					printf("int main(); -- Student does not exist with key %d.\n", delStudentKey);
					printf("No action has been performed.");
					break;
				}

				//print node before confirming
				printf("Student to delete: \n");
				PrintNode(currentStudent);

				//confirm action
				confirmation[0]='n';
				printf("Enter y to confirm this is correct, any other key to deny: ");
				scanf("%s", confirmation);
				if(strcmp(confirmation, "y") == 0){
					//do action
					DeleteMiddle(&_head, GetIndexByKey(&_head, delStudentKey));
					printf("Node deleted!\n");
					break;
				} 
				printf("Delete node by key action cancelled.\n");
				break;

			case 4:
				//delete student from ll by index
				printf("Enter the index of the student you would like to delete.\n");
				printf("Reminder: indices start from 0.\n");

				int delStudentIndex;
				char delStudentIndexStr[64];
				printf("Student index: ");
                scanf("%s", delStudentIndexStr);
				delStudentIndex = atoi(delStudentIndexStr);

				//validate if node exists with this key
				currentStudent = LookUpByIndex(&_head, delStudentIndex);
				if (currentStudent == NULL) {
					printf("int main(); -- Student does not exist with index %d.\n", delStudentIndex);
					printf("No action has been performed.");
					break;
				}

				//print node before confirming
				printf("Student to delete: \n");
				PrintNode(currentStudent);

				//confirm action
				confirmation[0]='n';
				printf("Enter y to confirm this is correct, any other key to deny: ");
				scanf("%s", confirmation);
				if(strcmp(confirmation, "y") == 0){
					//do action
					DeleteMiddle(&_head, delStudentIndex);
					printf("Node deleted!\n");
					break;
				} 
				printf("Delete node by index action cancelled.\n");
				break;

			case 5:
				//search engine for all fields basically, need ToString up and running first
				break;
			case 6:
				cont = 0;
				FreeList(&_head);
				break;
			default:
				printf("\nSorry, that is an invalid input.\n");
				userInputCounter--;
		}
		
	} while (cont == 1);

	return 0;

}