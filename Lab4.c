#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
	//printf("%s, ", nodePointer->lastName);
	//printf("%s, ", nodePointer->major);
	//printf("%.2f\n", nodePointer->GPA);
}

void PrintList(){

	if(_head == NULL){
		printf("Empty list.\n");
		return;
	}

	struct Node* current = _head;
	while (current != NULL) {
		//printf("%s\n", current->firstName);

		//printf("%s, ", current->firstName);
		//printf("%s, ", current->lastName);
		//printf("%s, ", current->major);
		//printf("%.2f\n", current->GPA);
		PrintNode(current);
		current = current->next;
	}
}

//InsertFront
//ref ll.c example, TA in person assistance
void InsertFront(char firstName[64], char lastName[64], char major[64], float GPA){
	struct Node* nodeToInsert = CreateNode(firstName, lastName, major, GPA);

	nodeToInsert->next = _head; //points next var to front of list, global variable
	_head = nodeToInsert; //inserts node and sets pointer of new front, global varaible
}

//InsertEnd
void InsertEnd(char _firstName[64], char _lastName[64], char _major[64], float _GPA){

	struct Node* nodeToInsert = CreateNode(_firstName, _lastName, _major, _GPA);

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

struct Node* LookUpByIndex(int index){
	struct Node* current = _head;
	int count = 0;
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



//• InsertMiddle - insert a node in the middle of the list. (Hint: use the data
//to know where to insert the node)
//• DeleteFront - delete the first node in the list.
//• DeleteMiddle - delete a node in the middle of the list. (Hint: use the data
//to know where to delete the node)
//• DeleteEnd - delete a node at the end of the list.
//• Traverse - traverse the list based on some key value in the data portion of
//the node.
//DONE • LookUpByIndex - find a particular node by an index number. Return -1 
//if that index does not exist.
//DONE• PrintNode – print information in the current node: first name, last name,
//major, and GPA


int main() {
		
	char student1FirstName[64] = "Cole";
	char student1LastName[64] = "Stack";
	char student1Major[64] = "NET";
	float student1GPA = 3.0;

	char student2FirstName[64] = "Haye";
	char student2LastName[64] = "Bail";
	char student2Major[64] = "CSEC";
	float student2GPA = 6.0;

	char student3FirstName[64] = "Redd";
	char student3LastName[64] = "Stone";
	char student3Major[64] = "SAAD";
	float student3GPA = 2.0;



	// CreatListNode
	InsertEnd(student1FirstName, student1LastName, student1Major, student1GPA);
	InsertEnd(student2FirstName, student2LastName, student2Major, student2GPA);
	InsertEnd(student3FirstName, student3LastName, student3Major, student3GPA);
	PrintList();


	char inputChar;
	printf("Press any key to exit: ");
	scanf("%c", &inputChar);

	FreeList();
	return 0;
}