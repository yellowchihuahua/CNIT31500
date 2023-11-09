//compilation command:
//gcc Lab5.c -o 1.exe -include linkedlist.h -include linkedlist.c


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linkedlist.h"


struct Stack{
	Node* head;
} Stack;

struct Stack* CreateStack(){
	struct Stack* stack = malloc(sizeof(struct Stack));
	if (stack == NULL) {
		printf("CreateStack(); -- Failed memory allocation.\n");
		return NULL;
	}
	stack->head = NULL;
	return stack;
}


int PushLL(struct Stack* stack, struct Node* nodeToInsert, char* type){ //dunno what to do with type yet
	struct Node* current = stack->head;
	InsertFront(&current, nodeToInsert);
    return 0;
}

struct Node* PopLL(struct Stack* stack){

	struct Node* current = stack->head;
	if (GetListLength(&current) == 0) {
		printf("PopLL(struct Stack* start); -- Empty stack, nothing to pop.\n");
		return NULL;
	}

	if (current->next == NULL) { //free list if head is only item
		FreeList(&current);
	}
	while (current->next->next != NULL) {
		current = current->next;
	}
	struct Node* temp = current->next;
	//free(current->next);
	current->next = NULL; //unlink but don't free
	return temp;
}

int SizeLL(struct Stack* stack){
	struct Node* current = stack->head;
	return GetListLength(&current);
}

void EmptyLL(struct Stack* stack){
    FreeList(&(stack->head));
}

int PushA(){
    return 0;
}

int PopA(){
    return 0;
}

int SizeA(){
    return 0;
}

int EmptyA(){
    return 0;
}


//array: https://www.digitalocean.com/community/tutorials/stack-in-c
void DisplayMenu(){

	struct Node* _stack = CreateStack()->head;
	int studentKeyCounter = 1;

	struct Node* _currentNode = NULL;	
	int cont = 1;
	int userInputCounter = 0;
	
	do {
		int functionNumber = 0;
		char input[4];
        printf("\n===============================================================================\n");
        printf("Hi User! You have used %i functions within this program so far!\n", userInputCounter);
        printf("Here are your options: \n");
		printf("(0) Create node and set as current\n");
        printf("(1) Push node to stack\n");
        printf("(2) Pop node from stack and set as current\n");
        printf("(3) Enqueue node to queue\n");
        printf("(4) Dequeue node from queue and set as current\n");
        printf("(5) Add node to both stack and queue\n");
		printf("(6) Remove node from both stack and queue and set as current\n");
		printf("(7) Empty stack\n");
		printf("(8) Empty queue\n");
		printf("(9) Print stack\n");
		printf("(10) Print queue\n");
		printf("(11) Print number of moves so far for array and LL\n");
        printf("(12) Exit the program\n");

		printf("Your current node: --------------------------------------------------------------\n");
		PrintNode(_currentNode);

		printf("Enter the number you would like to use (0-12): ");
		scanf("%s", input); //receiving as string then converting to int validates value
		functionNumber = atoi(input);
		userInputCounter++;


	//]have a current node
	//every move, print the current node
	//choose action

		switch(functionNumber){
			case 0: //create a node and set as current
				printf("\n");
				//if current node exists, free it
				if (_currentNode != NULL) {
					printf("A current node already exists. It will be overwritten with your new input.\n");
					studentKeyCounter--;//also free the usage of the key, since this node has not been used
					free(_currentNode);
				}

				printf("Enter the information of the student you would like to add, and presse enter:\n");
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

				_currentNode = CreateNode(studentKeyCounter, newStudentFirstName, newStudentLastName, newStudentPuid, newStudentAge);
				printf("Current node set to: ");
				studentKeyCounter++;
				PrintNode(_currentNode);
				break;

			case 1: //push to stack
				//check if the current node exists
				PushLL(_stack, _currentNode, 'idk');
				//if exists: add to top of stack
				//if no exist: create a node and add to top of stack
				break;

			case 2: //pop from stack
				//remove popped node from stack, unlink
				//make popped node the current node
				break;

			case 3: //enqueue to queue
				//check if current node exists
				//if exists: add to back of queue
				// if no exist: create a node and add to back of queue
				break;
			
			case 4: //dequeue from queue
				//remove dequeued node from queue, unlink
				//make dequeued node the current node
				break;
			
			case 5: //add node to both stack and queue
				
				break;

			case 6: //remove node from both stack and queue
				//if node exists in each
				//remove node from each
				//remove node from just one if it only exists in one
				//set node as current
				break;

			case 7: //empty stack
				break;

			case 8: //empty queue
				break;
			
			case 9: //print stack
				break;

			case 10: //print queue
				break;

			case 11: //print number of moves so far
				//number of traversals and actions used, needs global tracker
				break;
			
			case 12: //exit the program
				cont = 0;
				//FreeList(&_head);
				//free all the shit
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

int main() {
	DisplayMenu();
	return 1;
}