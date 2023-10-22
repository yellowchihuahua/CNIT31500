#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct Node {
	char firstName[64];
	char lastName[64];
	char major[64];
	float GPA;

	struct Node* next;
};
struct Node* _head = NULL;

struct Node* CreateNode(char *firstName, char *lastName, char *major, float GPA){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Failed memory allocation.\n");
		exit(1);
	}

	strcpy(newNode->firstName, firstName);
	strcpy(newNode->lastName, lastName);
	strcpy(newNode->major, major);
	newNode->GPA = GPA;
	newNode->next = NULL;

	return newNode;
}


//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
void FreeList(){
//traverse through and free allocated memory
	struct Node* head = _head;
	struct Node* temp;
    while (head != NULL) {
        temp = head;
		head = head->next;
		free(temp);
    }
}

void PrintNode(struct Node* nodePointer){
	printf("%s, %s, %s, %.2f\n", nodePointer->firstName, nodePointer->lastName, nodePointer->major, nodePointer->GPA);
}

void PrintList(){
	if(_head == NULL){
		printf("Empty list.\n");
		return;
	}
	struct Node* current = _head;
	while (current != NULL) {
		PrintNode(current);
		current = current->next;
	}
}

//InsertFront
//ref ll.c example, TA in person assistance
void InsertFront(struct Node* nodeToInsert){
	if (_head == NULL){
		_head = nodeToInsert;
		return;
	}
	nodeToInsert->next = _head; //points next var to front of list, global variable
	_head = nodeToInsert; //inserts node and sets pointer of new front, global varaible
}

//InsertEnd generalized
void InsertEnd(struct Node* nodeToInsert){
	//check if already has items
	if (_head == NULL){
		_head = nodeToInsert;
		return;
	}

	//get to the last node in linked list
	struct Node* current = _head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = nodeToInsert;
}

//general usage, param index is the index to look up
struct Node* LookUpByIndex(int index){
	struct Node* current = _head;
	int count = 0;

	if(index < 0){
		return NULL;
	}

	while (current != NULL && count < index) {
		current = current->next;
		count++;
	}
	
	if (current != NULL){
		return current; //no node with matching data
	}
	printf("No node with matching index.\n");
	return NULL; //reached end of LL, no node with matching data
}

//general usage insert middle function, param index is the index before node to insert
void InsertMiddle(int index, struct Node* nodeToInsert){
	struct Node* previousNode = LookUpByIndex(index);
	struct Node* nextNode = LookUpByIndex(index+1);

	if(nextNode != NULL) {
		previousNode->next = nodeToInsert;
		nodeToInsert->next = nextNode; //linking 
	} else {
		InsertEnd(nodeToInsert);
	}
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

//not transferable to general linked list functionality?
void InsertByGPA(struct Node* nodeToInsert) {	
	if (_head == NULL) {
		InsertFront(nodeToInsert);
		printf("head is null, putting it in front\n");
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

	printf("NODE TO INSERT COMPARING STRING: %s \n", nodeToInsertStr);

	struct Node* current = _head;
	char currentStr[256]; 
	char currentGpaStr[10];
	ftoa((5.0f-current->GPA), currentGpaStr, 2); //'inverse' of gpa goes first so i can sort completely alphabetically and still get largest gpa first
	strcpy(currentStr, currentGpaStr); 
	strcat(currentStr, current->lastName); //insert the rest of them to compare alphabetically in order
	strcat(currentStr, current->firstName);
	strcat(currentStr, current->major);

	int comp = strcmp(nodeToInsertStr, currentStr);
	if(comp < 0) {//smaller alphabetically
		InsertFront(nodeToInsert);
		printf("smaller alphabetically than head, putting in front\n");
		return;
	}

	printf("comparing from second item\n");
	current = _head->next; //start iterating from second item to utilize InsertMiddle()
	int count = 0; //counter, index to use InsertMiddle() on
	while (current != NULL) {
		currentStr[0] = '\0'; //clear strings
		currentGpaStr[0] = '\0';
		ftoa((5.0f-current->GPA), currentGpaStr, 2); //'inverse' of gpa goes first so i can sort completely alphabetically and still get largest gpa first
		strcpy(currentStr, currentGpaStr); 
		strcat(currentStr, current->lastName); //insert the rest of them to compare alphabetically in order
		strcat(currentStr, current->firstName);
		strcat(currentStr, current->major);
		printf("CURRENT NODE COMPARING STRING: %s\n", currentStr);
		comp = strcmp(nodeToInsertStr, currentStr);
		
		if(comp < 0) { //alphabetically smaller, inserting before current node
			printf("smaller alphabetically than current, inserting before %s\n", ToString(current));
			InsertMiddle(count, nodeToInsert);
			return;
		}
		current = current->next;
		count++;
	}
	//reached the end of list and it's not bigger than anything, so inserting at end
	printf("reached end of list, inserting at end\n");
	InsertEnd(nodeToInsert);
}

// DONE InsertMiddle - insert a node in the middle of the list. (Hint: use the data
//to know where to insert the node)
// DeleteFront - delete the first node in the list.
// DeleteMiddle - delete a node in the middle of the list. (Hint: use the data
//to know where to delete the node)
// DeleteEnd - delete a node at the end of the list.
// Traverse - traverse the list based on some key value in the data portion of
//the node.
//DONE  LookUpByIndex - find a particular node by an index number. Return -1 
//if that index does not exist.
//DONE PrintNode  print information in the current node: first name, last name,
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

	printf("nodes created\n");


	printf("inserting student 1: %s\n", ToString(student1));
	InsertByGPA(student1);
	printf("inserting student 2: %s\n", ToString(student2));
	InsertByGPA(student2);
	printf("inserting student 3: %s\n", ToString(student3));
	InsertByGPA(student3);
	printf("inserting student 4: %s\n", ToString(student4));
	InsertByGPA(student4);
	printf("inserting student 5: %s\n", ToString(student5));
	InsertByGPA(student5);
	printf("inserting student 6: %s\n", ToString(student6));
	InsertByGPA(student6);
	
	PrintList();


	char inputChar;
	printf("Press any key to exit: ");
	scanf("%c", &inputChar);

	FreeList();
	return 0;
}