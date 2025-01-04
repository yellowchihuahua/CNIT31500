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

int movesStackLL, movesQueueLL, movesStackA, movesQueueA = 0;

struct Node _stackA[100]; //stack of 100 nodes, global scope
int _stackATop = -1;

struct Node _queueA[100]; //queue of 100 nodes max, global scope
//last is where to pull from
int _queueALast = -1;

struct Stack
{
	Node* head;
} Stack;

//ref https://www.geeksforgeeks.org/introduction-to-stack-data-structure-and-algorithm-tutorials/#
//struct StackA {
//	int top;
//	unsigned capacity;
//	Node** array;
//} StackA;

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
	movesStackLL++;
	return stack;
}

//put at front
void PushLL(struct Stack* stack, struct Node* nodeToInsert)
{ 
	struct Node** top = &(stack->head);
	InsertFront(top, nodeToInsert);
	movesStackLL++;
}

//pop from front
struct Node* PopLL(struct Stack* stack)
{
	movesStackLL++; //get list length traversal
	if (GetListLength(&(stack->head)) == 0)
	{
		printf("PopLL(struct Stack* start); -- Empty stack, nothing to pop.\n");
		return NULL;
	}

	//return head, make new head
	struct Node* temp = stack->head;
	stack->head = stack->head->next;
	movesStackLL++;
	return temp;
}

// struct StackA* CreateStackA(unsigned capacity) 
// { 
//     struct StackA* stack = (struct StackA*)malloc(sizeof(struct StackA)); 
//     stack->capacity = capacity; 
//     stack->top = -1; 
//     stack->array = (Node**)malloc(stack->capacity * sizeof(struct Node)); 
//     return stack; 
// } 

int StackAIsFull(){
	int arrSize = sizeof(_stackA) / sizeof(_stackA[0]);
	return _stackATop == arrSize - 1; 
}

int StackAIsEmpty() 
{ 
    return _stackATop == -1; 
} 

void PushA(struct Node nodeToInsert)
{
	if (StackAIsFull()) {
		printf("PushA(struct Node nodeToInsert); - Stack (array) is full, unable to push");
    	return; 
	}
	_stackATop = _stackATop + 1;
    (_stackA[_stackATop]) = nodeToInsert; 
	PrintNode(&nodeToInsert);
    printf(" pushed to stack\n");
}

struct Node PopA() 
{
	if (StackAIsEmpty()) {
        return _stackA[0]; 
	}
	Node temp = _stackA[_stackATop];

	movesStackA++;
	//reset values
	strcpy(_stackA[_stackATop].firstName, ""); 
	strcpy(_stackA[_stackATop].lastName, ""); 
	strcpy(_stackA[_stackATop].puid, ""); 
	_stackA[_stackATop].age = 0;

	//minus index of top
	_stackATop = _stackATop - 1;

    return temp;
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
	movesQueueLL++;
	return queue;
}

//put at end 
void EnqueueLL(struct Queue* queue, struct Node* nodeToInsert){
	struct Node** top = &(queue->head);
	movesQueueLL++;//traversal
	InsertEnd(top, nodeToInsert);
	movesQueueLL++;//insertion
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
	movesQueueLL++;
	return temp;
}

int QueueAIsFull(){
	int arrSize = sizeof(_queueA) / sizeof(_queueA[0]);
	return _queueALast == arrSize - 1; 
}

int QueueAIsEmpty() 
{
    return _queueALast == -1; 
} 

void EnqueueA(struct Node nodeToInsert){
	if (QueueAIsFull()) {
		printf("EnqueueA(struct Node nodeToInsert); - Queue (array) is full, unable to push");
    	return; 
	}
	movesQueueA++;
	_queueALast = _queueALast+1;
	_queueA[_queueALast] = nodeToInsert;
	PrintNode(&nodeToInsert);
	printf(" pushed to stack\n");
}


struct Node DequeueA(){
	if (QueueAIsEmpty()) {
        return _queueA[0]; //not nullable so returning this
	}
	//pull from beginning
	Node temp = _queueA[0];

	//clear first element first to ensure edge case of dequeueing the last remaining element
	movesQueueA++;
	strcpy(_queueA[0].firstName, ""); 
	strcpy(_queueA[0].lastName, ""); 
	strcpy(_queueA[0].puid, ""); 
	_queueA[0].age = 0;

	//shift all nodes to beginning to have next in queue at beginning
    int size = sizeof(_queueA) / sizeof(_queueA[0]);
    for (int i = 0; i < size; i++) {
		_queueA[i] = _queueA[i+1];
		movesQueueA++;
    }

	//minus index of last
	_queueALast = _queueALast - 1;

    return temp;
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

void EmptyStackA(){
	int size = sizeof(_stackA) / sizeof(_stackA[0]);
	for (int i = 0; i < size; i++) {
		strcpy(_stackA[i].firstName, ""); 
		strcpy(_stackA[i].lastName, ""); 
		strcpy(_stackA[i].puid, ""); 
		_stackA[i].age = 0;
	}
}

void EmptyQueueA(){
	int size = sizeof(_queueA) / sizeof(_queueA[0]);

	for (int i = 0; i < size; i++){
		strcpy(_queueA[i].firstName, ""); 
		strcpy(_queueA[i].lastName, ""); 
		strcpy(_queueA[i].puid, ""); 
		_queueA[i].age = 0;
	}
}

int SizeStackA()
{
	return sizeof(_stackA) / sizeof(_stackA[0]);
}

int SizeQueueA(){
	return sizeof(_queueA) / sizeof(_queueA[0]);
}

void PrintStackArray() {
    // Calculate the size of the array
    int size =  _stackATop +2;//sizeof(_stackA) / sizeof(_stackA[0]);

    // Print the elements of the array
    for (int i = 0; i < size; i++) {
		printf("Printing\n");
        PrintNode(&(_stackA[i]));
    }
    printf("\n");
}

void PrintQueueArray() {
    // Calculate the size of the array
    int size = _queueALast +2;//sizeof(_queueA) / sizeof(_queueA[0]);

    // Print the elements of the array
    for (int i = 0; i < size; i++) {
		printf("Printing\n");
        PrintNode(&(_queueA[i]));
    }
    printf("\n");
}



struct Node *CreateNodeFromUserInput() // will use the count
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

	currentNode = CreateNode(newStudentFirstName, newStudentLastName, newStudentPuid, newStudentAge);
	return currentNode;
}

// array: https://www.digitalocean.com/community/tutorials/stack-in-c
void DisplayMenu()
{
	struct Stack *_stack = CreateStack();
	struct Queue *_queue = CreateQueue();

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

		printf("Enter the number you would like to use (1-13): ");
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

			_currentNode = CreateNodeFromUserInput();
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
				PushA(*_currentNode);
				_currentNode = NULL;
				break;
			}
			// if no exist: create a node and add to top of stack
			printf("A current node does not exist. Please enter your inputs to create and push a new node to stack.\n");
			_currentNode = CreateNodeFromUserInput();
			printf("Node added to stack: ");
			PrintNode(_currentNode);
			PushLL(_stack, _currentNode);
			PushA(*_currentNode);
			_currentNode = NULL;
			break;

		case 3: // pop from stack
			// if current node exists, warn about overwriting
			printf("\n");
			if (_currentNode != NULL)
			{
				printf("A current node already exists. It WILL be overwritten with your popped item.\n");
				_currentNode = PopLL(_stack);
			}
			printf("Node popped and assigned to current node");

			printf("From LL: ");
			_currentNode = PopLL(_stack);
			PrintNode(_currentNode);

			printf("From array: ");
			*_currentNode = PopA();
			PrintNode(_currentNode);
			break;

		case 4: // enqueue to queue
			printf("\n");
			// check if the current node exists
			if (_currentNode != NULL)
			{ // if exists: add to top of stack
				printf("Pushing current node to back of queue.\n");
				EnqueueLL(_queue, _currentNode);
				EnqueueA(*_currentNode);
				_currentNode = NULL;
				break;
			}
			// if no currentNode exist: create a node and add to top of stack
			printf("A current node does not exist. Please enter your inputs to create and push a new node to stack.\n");
			_currentNode = CreateNodeFromUserInput();
			printf("Node added to queue: ");
			PrintNode(_currentNode);
			EnqueueLL(_queue, _currentNode);
			EnqueueA(*_currentNode);
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
			printf("From LL: ");
			PrintNode(_currentNode);

			*_currentNode = DequeueA();
			printf("From Array: ");
			PrintNode(_currentNode);
			break;

		case 6: // add node to both stack and queue
			printf("\n");
			// check if the current node exists
			if (_currentNode != NULL)
			{ // if exists: add to top of stack
				printf("Pushing current node to top of stack.\n");
				printf("Pushing current node to back of queue.\n");
				PushLL(_stack, _currentNode);
				PushA(*_currentNode);
				EnqueueLL(_queue, _currentNode);
				EnqueueA(*_currentNode);

				_currentNode = NULL;
				break;
			}
			// if no currentNode exist: create a node and add to top of stack
			printf("A current node does not exist. Please enter your inputs to create and push a new node to stack.\n");
			_currentNode = CreateNodeFromUserInput();
			printf("Node added to stack: \n");
			printf("Node added to queue: \n");
			PrintNode(_currentNode);
			PushLL(_stack, _currentNode);
			PushA(*_currentNode);
			EnqueueLL(_queue, _currentNode);
			EnqueueA(*_currentNode);
			_currentNode = NULL;

			break;

		case 7: // remove node from both stack and queue
			printf("\n");
			if (_currentNode != NULL)
			{
				printf("A current node already exists. It WILL be overwritten with your dequeued item.\n");
			}
			printf("Node removed from stack");
			printf("Node dequeued and assigned to current node");

			*_currentNode = PopA();
			*_currentNode = DequeueA();
			_currentNode = PopLL(_stack);
			_currentNode = DequeueLL(_queue);

			PrintNode(_currentNode);
			break;

		case 8: // empty stack
			printf("\n");
			EmptyLL(&(_stack->head));
			EmptyStackA();
			printf("Stacks emptied!\n");
			break;

		case 9: // empty queue
			printf("\n");
			EmptyLL(&(_queue->head));
			EmptyQueueA();
			printf("Queues emptied!\n");
			break;

		case 10: // print stack
			printf("\n");
			printf("Your current stack: ----------------------------------------------------\n");
			PrintList(&(_stack->head));
			printf("------------------------------------------------------------------------\n");

			printf("Your current stack (array): --------------------------------------------\n");
			PrintStackArray();
			printf("------------------------------------------------------------------------\n");
			break;

		case 11: // print queue
			printf("\n");
			printf("Your current queue: ----------------------------------------------------\n");
			PrintList(&(_queue->head));
			printf("------------------------------------------------------------------------\n");

			printf("Your current queue (array): --------------------------------------------\n");
			PrintQueueArray();
			printf("------------------------------------------------------------------------\n");

			break;

		case 12: // print number of moves so far
			// number of traversals and actions used, needs global tracker
			break;

		case 13: // exit the program
			cont = 0;
			FreeList(&_stack->head);
			FreeList(&_queue->head);
			// free all the shit
			break;
		default:
			printf("\nSorry, that is an invalid operation.\n");
			userInputCounter--;
		}

	} while (cont == 1);
}

int main()
{
	DisplayMenu();
	return 1;
}