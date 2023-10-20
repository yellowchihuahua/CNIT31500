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

	return newNode;
}


//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
void FreeList(struct Node* _startPointer){
//traverse through and free allocated memory
	struct Node* head = _startPointer;
	struct Node* tmp;
    while (head != NULL) {
        tmp = head;
		head = head->next;
		free(tmp);
    }
}

void PrintNode(struct Node* _nodePointer){
	printf("%s, ", _nodePointer->firstName);
	printf("%s, ", _nodePointer->lastName);
	printf("%s, ", _nodePointer->major);
	printf("%.2f\n", _nodePointer->GPA);
}

void PrintList(struct Node* _startPointer){

	if(_startPointer == NULL){
		printf("Empty list.\n");
		return;
	}

	struct Node* current = _startPointer;
	while (current != NULL) {
		//printf("%s\n", current->firstName);

		printf("%s, ", current->firstName);
		printf("%s, ", current->lastName);
		printf("%s, ", current->major);
		printf("%.2f\n", current->GPA);
		//PrintNode(current);
		current = current->next;
	}
}

//InsertFront
//ref ll.c example, TA in person assistance
void InsertFront(struct Node **_startPointer, char _firstName[64], char _lastName[64], char _major[64], float _GPA){
	struct Node* nodeToInsert = CreateNode(_firstName, _lastName, _major, _GPA);

	//check if already has items
	if (*_startPointer == NULL){
		*_startPointer = nodeToInsert;
		return;
	}

	nodeToInsert->next = *_startPointer; //points next var to front of list
	*_startPointer = nodeToInsert; //inserts node and sets pointer of new front
}

//InsertEnd
void InsertEnd(struct Node **_startPointer, char _firstName[64], char _lastName[64], char _major[64], float _GPA){

	struct Node* nodeToInsert = CreateNode(_firstName, _lastName, _major, _GPA);

	printf("node created");
	//check if already has items
	if (*_startPointer == NULL){
		*_startPointer = nodeToInsert;
		printf("no items, using this");
		return;
	}

	//get to the last node in linked list
	struct Node* current = *_startPointer;
	while(current != NULL){
		current = current->next;
		printf("traversing to end");
	}
	current->next = nodeToInsert;
	printf("adding to end");
	nodeToInsert->next = NULL;
}

struct Node* FindNodeByName(struct Node *_startPointer, char *_firstName){
	struct Node* current = _startPointer;
	while (current != NULL) {
		if (current->firstName == _firstName) {
			return current;
		}
		current = current->next;
	}
	return NULL; //no node with matching data
}



//• InsertMiddle - insert a node in the middle of the list. (Hint: use the data
//to know where to insert the node)
//• DeleteFront - delete the first node in the list.
//• DeleteMiddle - delete a node in the middle of the list. (Hint: use the data
//to know where to delete the node)
//• DeleteEnd - delete a node at the end of the list.
//• Traverse - traverse the list based on some key value in the data portion of
//the node.
//• LookUpByIndex - find a particular node by an index number. Return -1
//if that index does not exist.
//• PrintNode – print information in the current node: first name, last name,
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



	//CreateListNode
	struct Node* llHead;

	// CreatListNode
	printf("1");
	InsertEnd(&llHead, student1FirstName, student1LastName, student1Major, student1GPA);
	printf("1");
	InsertEnd(&llHead, student2FirstName, student2LastName, student2Major, student2GPA);
	printf("1");
	InsertEnd(&llHead, student3FirstName, student3LastName, student3Major, student3GPA);
	printf("1");
	PrintList(llHead);


	char inputChar;
	printf("Press any key to exit: ");
	scanf(" %c", &inputChar);

	FreeList(llHead);
	return 0;
}