// VERY IMPORTANT !!!!!!!!!!!!! 
// PLEASE READ
// I HAVE CREATED A HEADER FILE LINKEDLIST.H FOR LINKEDLIST.C THAT NEED TO BE INCLUDED
// compilation command:
// gcc Lab5.c -o lab.exe -include linkedlist.h -include linkedlist.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"

struct Stack
{
	Node* head;
} Stack;

struct Queue {
	Node* head;
} Queue;

//stack methods
struct Stack* CreateStack()
{
	struct Stack *stack = malloc(sizeof(struct Stack));
	if (stack == NULL)
	{
		printf("CreateStack(); -- Failed memory allocation.\n");
		return NULL;
	}
	stack->head = NULL;
	return stack;
}

//put at front
void PushLL(struct Stack* stack, struct Node* nodeToInsert)
{ 
	struct Node** top = &(stack->head);
	InsertFront(top, nodeToInsert);
}

//pop from front
struct Node* PopLL(struct Stack* stack)
{
	if (GetListLength(&(stack->head)) == 0)
	{
		printf("PopLL(struct Stack* start); -- Empty stack, nothing to pop.\n");
		return NULL;
	}

	//return head, make new head
	struct Node* temp = stack->head;
	stack->head = stack->head->next;
	return temp;
}

int SizeLL(struct Stack* stack)
{
	struct Node *current = stack->head;
	return GetListLength(&current);
}

void EmptyLL(struct Stack* stack)
{
	FreeList(&(stack->head));
}

int PushA()
{
	return 0;
}

int PopA()
{
	return 0;
}

//queue methods
struct Queue* CreateQueue()
{
	struct Queue *queue = malloc(sizeof(struct Queue));
	if (queue == NULL)
	{
		printf("CreateQueue(); -- Failed memory allocation.\n");
		return NULL;
	}
	queue->head = NULL;
	return queue;
}

//put at end 
void EnqueueLL(struct Queue* queue, struct Node* nodeToInsert){
	struct Node** top = &(queue->head);
	InsertEnd(top, nodeToInsert);
}

//take from head
struct Node* DequeueLL(struct Queue* queue){
	if (GetListLength(&(queue->head)) == 0)
	{
		printf("DequeueLL(struct Queue* queue); -- Empty queue, nothing to dequeue.\n");
		return NULL;
	}

	//return head, make new head
	struct Node* temp = queue->head;
	queue->head = queue->head->next;
	return temp;
}

void EnqueueA(){

}

void DequeueA(){

}

//generic size and free methods for both stack and queue
int SizeLL(struct Node** start)
{
	//struct Node *current = stack->head;
	return GetListLength(start);
}

void EmptyLL(struct Node** start)
{
	FreeList(start);
}

int SizeA()
{
	return 0;
}

int EmptyA()
{
	return 0;
}



// param int *studentKeyCounter: need to assign a key after output from this node
struct Node *CreateNodeFromUserInput(int *studentKeyCounter) // will use the count
{
	struct Node *currentNode = NULL;

	printf("Enter the information of the student you would like to create, and presse enter:\n");
	char newStudentFirstName[64], newStudentLastName[64], newStudentPuid[64];
	int newStudentAge;
	char newStudentAgeStr[8];
	printf("New student's First Name: ");
	scanf("%s", newStudentFirstName);
	printf("New student's Last Name: ");
	scanf("%s", newStudentLastName);
	printf("New student's PUID: ");
	scanf("%s", newStudentPuid);
	printf("New student's Age: ");
	scanf("%s", &newStudentAgeStr);
	newStudentAge = atof(newStudentAgeStr);

	currentNode = CreateNode(*studentKeyCounter, newStudentFirstName, newStudentLastName, newStudentPuid, newStudentAge);
	(*studentKeyCounter)++;
	return currentNode;
}

// array: https://www.digitalocean.com/community/tutorials/stack-in-c
void DisplayMenu()
{
	struct Stack *_stack = CreateStack();
	struct Queue *_queue = CreateQueue();
	int studentKeyCounter = 1; // this key is used to identify every created node as unique. auto increments

	struct Node *_currentNode = NULL;
	int cont = 1;
	int userInputCounter = 0;
	char confirmation[1] = "n";

	do
	{
		int functionNumber = 0;
		char input[4];
		printf("\n==================================================================================\n");
		printf("Hi User! You have used %i functions within this program so far!\n", userInputCounter);
		printf("Here are your options: \n");
		printf("(1) Create node and set as current\n");
		printf("(2) Push node to stack\n");
		printf("(3) Pop node from stack and set as current\n");
		printf("(4) Enqueue node to queue\n");
		printf("(5) Dequeue node from queue and set as current\n");
		printf("(6) Add node to both stack and queue\n");
		printf("(7) Remove node from both stack and queue and set as current\n");
		printf("(8) Empty stack\n");
		printf("(9) Empty queue\n");
		printf("(10) Print stack\n");
		printf("(11) Print queue\n");
		printf("(12) Print number of moves so far for array and LL\n");
		printf("(13) Exit the program\n");

		printf("Your current node: -----------------------------------------------------\n");
		PrintNode(_currentNode);
		printf("------------------------------------------------------------------------\n");

		printf("Enter the number you would like to use (0-12): ");
		scanf("%s", input); // receiving as string then converting to int validates value
		functionNumber = atoi(input);
		userInputCounter++;

		//]have a current node
		// every move, print the current node
		// choose action

		switch (functionNumber)
		{
		case 1: // create a node and set as current
			printf("\n");
			// if current node exists, free it
			if (_currentNode != NULL)
			{
				printf("A current node already exists. It WILL be overwritten with your new input.\n");
				free(_currentNode);
			}

			_currentNode = CreateNodeFromUserInput(&studentKeyCounter);
			printf("Current node set to: ");
			PrintNode(_currentNode);
			break;

		case 2: // push to stack
			printf("\n");
			// check if the current node exists
			if (_currentNode != NULL)
			{ // if exists: add to top of stack
				printf("Pushing current node to top of stack.\n");
				PushLL(_stack, _currentNode);
				_currentNode = NULL;
				break;
			}
			// if no exist: create a node and add to top of stack
			printf("A current node does not exist. Please enter your inputs to create and push a new node to stack.\n");
			_currentNode = CreateNodeFromUserInput(&studentKeyCounter);
			printf("Node added to stack: ");
			PrintNode(_currentNode);
			PushLL(_stack, _currentNode);
			_currentNode = NULL;
			break;

		case 3: // pop from stack
			// if current node exists, warn about overwriting
			printf("\n");
			if (_currentNode != NULL)
			{
				printf("A current node already exists. It WILL be overwritten with your popped item.\n");
				//_currentNode = PopLL(_stack);
			}
			printf("Node popped and assigned to current node");
			_currentNode = PopLL(_stack);
			break;

		case 4: // enqueue to queue
			printf("\n");
			// check if the current node exists
			if (_currentNode != NULL)
			{ // if exists: add to top of stack
				printf("Pushing current node to back of queue.\n");
				EnqueueLL(_queue, _currentNode);
				_currentNode = NULL;
				break;
			}
			// if no currentNode exist: create a node and add to top of stack
			printf("A current node does not exist. Please enter your inputs to create and push a new node to stack.\n");
			_currentNode = CreateNodeFromUserInput(&studentKeyCounter);
			printf("Node added to queue: ");
			PrintNode(_currentNode);
			EnqueueLL(_queue, _currentNode);
			_currentNode = NULL;
			break;

		case 5: // dequeue from queue, make dequeued node the 'current' node

			// if current node exists, warn about overwriting
			printf("\n");
			if (_currentNode != NULL)
			{
				printf("A current node already exists. It WILL be overwritten with your dequeued item.\n");
			}
			printf("Node dequeued and assigned to current node");
			_currentNode = DequeueLL(_queue);
			break;

		case 6: // add node to both stack and queue

			break;

		case 7: // remove node from both stack and queue
			// if node exists in each
			// remove node from each
			// remove node from just one if it only exists in one
			// set node as current
			break;

		case 8: // empty stack
			printf("\n");
			EmptyLL(&(_stack->head));
			printf("Stack emptied!\n");
			break;

		case 9: // empty queue
			printf("\n");
			EmptyLL(&(_queue->head));
			printf("Queue emptied!\n");
			break;

		case 10: // print stack
			printf("\n");
			printf("Your current stack: ----------------------------------------------------\n");
			PrintList(&(_stack->head));
			printf("------------------------------------------------------------------------\n");
			break;

		case 11: // print queue
			printf("\n");
			printf("Your current queue: ----------------------------------------------------\n");
			PrintList(&(_queue->head));
			printf("------------------------------------------------------------------------\n");
			break;

		case 12: // print number of moves so far
			// number of traversals and actions used, needs global tracker
			break;

		case 13: // exit the program
			cont = 0;
			// FreeList(&_head);
			// free all the shit
			break;
		default:
			printf("\nSorry, that is an invalid operation.\n");
			userInputCounter--;
		}

		// switch(functionNumber){
		// 	case 1:
		// 		printf("\nHere is the list of all your students: ----------------------------------------\n");
		// 		PrintList(&_head);
		// 		printf("\nEND OF LIST--------------------------------------------------------------------\n");
		// 		break;

		// 	case 2:
		// 		//insert a student to linked list
		// 		printf("\nEnter the information of the student you would like to add.\n");

		// 		char newStudentFirstName[64], newStudentLastName[64], newStudentMajor[64];
		// 		char newStudentGPA;
		// 		char newStudentGPAStr[8];
		// 		printf("Type your inputs and press enter:\n");
		// 		printf("New student's First Name: ");
		//         scanf("%s", newStudentFirstName);
		//         printf("New student's Last Name: ");
		//         scanf("%s", newStudentLastName);
		//         printf("New student's Major: ");
		//         scanf("%s", newStudentMajor);
		//         printf("New student's GPA: ");
		//         scanf("%s", &newStudentGPAStr);
		// 		newStudentGPA = atof(newStudentGPAStr);

		// 		struct Node* currentStudent = CreateNode(studentKeyCounter, newStudentFirstName, newStudentLastName, newStudentMajor, newStudentGPA);
		// 		printf("Node to add: ");
		// 		PrintNode(currentStudent);

		// 		char confirmation[1] = "n";
		// 		printf("Enter y to confirm this is correct, any other key to deny: ");
		// 		scanf("%s", confirmation);

		// 		if(strcmp(confirmation, "y") == 0){
		// 			int isSuccessful = true;
		// 			if(isSuccessful){
		// 				printf("New node added!\n");
		//                 studentKeyCounter++;
		// 				break;
		// 			}
		// 		}
		// 		printf("Add node action cancelled.\n");
		// 		break;

		// 	case 3:
		// 		//delete a student from linked list by key
		// 		printf("\nEnter the key of the student you would like to delete.\n");

		// 		int delStudentKey;
		// 		char delStudentKeyStr[64];
		// 		printf("Student key: ");
		//         scanf("%s", delStudentKeyStr);
		// 		delStudentKey = atoi(delStudentKeyStr);

		// 		//validate if node exists with this key
		// 		currentStudent = LookUpByKey(&_head, delStudentKey);
		// 		if (currentStudent == NULL) {
		// 			printf("int main(); -- Student does not exist with key %d.\n", delStudentKey);
		// 			printf("No action has been performed.\n");
		// 			break;
		// 		}

		// 		//print node before confirming
		// 		printf("Student to delete: \n");
		// 		PrintNode(currentStudent);

		// 		//confirm action
		// 		confirmation[0]='n';
		// 		printf("Enter y to confirm this is correct, any other key to deny: ");
		// 		scanf("%s", confirmation);
		// 		if(strcmp(confirmation, "y") == 0){
		// 			//do action, check for success
		// 			int isSuccessful = DeleteMiddle(&_head, GetIndexByKey(&_head, delStudentKey));
		// 			if (isSuccessful) {
		// 				printf("Node deleted!\n");
		// 				break;
		// 			}
		// 		}
		// 		printf("Delete node by key action cancelled.\n");
		// 		break;

		// 	case 4:
		// 		//delete student from ll by index
		// 		printf("\nEnter the index of the student you would like to delete.\n");
		// 		printf("Reminder: indices start from 0.\n");

		// 		int delStudentIndex;
		// 		char delStudentIndexStr[64];
		// 		printf("Student index: ");
		//         scanf("%s", delStudentIndexStr);
		// 		delStudentIndex = atoi(delStudentIndexStr);

		// 		//validate if node exists with this key
		// 		currentStudent = LookUpByIndex(&_head, delStudentIndex);
		// 		if (currentStudent == NULL) {
		// 			printf("int main(); -- Student does not exist with index %d.\n", delStudentIndex);
		// 			printf("No action has been performed.\n");
		// 			break;
		// 		}

		// 		//print node before confirming
		// 		printf("Student to delete: \n");
		// 		PrintNode(currentStudent);

		// 		//confirm action
		// 		confirmation[0]='n';
		// 		printf("Enter y to confirm this is correct, any other key to deny: ");
		// 		scanf("%s", confirmation);
		// 		if(strcmp(confirmation, "y") == 0){
		// 			//do action, check for successs
		// 			int isSuccessful = DeleteMiddle(&_head, delStudentIndex);
		// 			if (isSuccessful){
		// 				printf("Node deleted!\n");
		// 				break;
		// 			}
		// 		}
		// 		printf("Delete node by index action cancelled.\n");
		// 		break;

		// 	case 5:
		// 		//search engine for all fields basically, need ToString up and running first
		// 		printf("\nEnter the string you would like to search.\n");

		// 		char searchString[256];
		// 		printf("Your search request: ");
		// 		scanf("%s", searchString);

		// 		printf("Key: | Data: FirstName, LastName, Major, GPA\n");
		// 		printf("\nYour search results: ----------------------------------------------------------\n");
		// 		PrintSearch(&_head, searchString);
		// 		printf("\nEND OF LIST--------------------------------------------------------------------\n");
		// 		break;
		// 	case 6:
		// 		cont = 0;
		// 		FreeList(&_head);
		// 		break;
		// 	default:
		// 		printf("\nSorry, that is an invalid operation.\n");
		// 		userInputCounter--;
		// }

	} while (cont == 1);
}

int main()
{
	DisplayMenu();
	return 1;
}