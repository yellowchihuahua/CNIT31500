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
	InsertFront(&(stack->head), nodeToInsert);
    return 0;
}

struct Node* PopLL(struct Stack* stack){
	if (GetListLength(&(stack->head)) == 0) {
		printf("PopLL(struct Stack* start); -- Empty stack, nothing to pop.\n");
		return NULL;
	}

		struct Node* current = stack->head;
	if (current->next == NULL) { //free head if head is only item
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
	return GetListLength(&(stack->head));
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

	struct Node* _head = CreateStack()->head;
	int studentKeyCounter = 1;
	
	int cont = 1;
	int userInputCounter = 0;
	
	do {
		int functionNumber = 0;
		char input[4];
        printf("\n===============================================================================\n");
        printf("Hi User! You have used %i functions within this program so far!\n", userInputCounter);
        printf("Here are your options: \n");
        printf("(1) Print all students in linked list\n");
        printf("(2) Insert a student to linked list by GPA order\n");
        printf("(3) Delete a student from linked list using their key ID\n");
        printf("(4) Delete a student from linked list using their list index\n");
        printf("(5) Find a student from linked list\n");
        printf("(6) Exit the program\n");

		printf("Enter the number you would like to use (1-6): ");
		scanf("%s", input); //receiving as string then converting to int validates value
		functionNumber = atoi(input);
		userInputCounter++;


		switch(functionNumber){
			case 1:
				printf("\nHere is the list of all your students: ----------------------------------------\n");
				PrintList(&_head);
				printf("\nEND OF LIST--------------------------------------------------------------------\n");
				break;

			case 2:
				//insert a student to linked list
				printf("\nEnter the information of the student you would like to add.\n");

				char newStudentFirstName[64], newStudentLastName[64], newStudentMajor[64];
				char newStudentGPA;
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

				struct Node* currentStudent = CreateNode(studentKeyCounter, newStudentFirstName, newStudentLastName, newStudentMajor, newStudentGPA);
				printf("Node to add: ");
				PrintNode(currentStudent);

				char confirmation[1] = "n";
				printf("Enter y to confirm this is correct, any other key to deny: ");
				scanf("%s", confirmation);
				
				if(strcmp(confirmation, "y") == 0){
					int isSuccessful = true;
					if(isSuccessful){
						printf("New node added!\n");
                        studentKeyCounter++;
						break;
					}
				}
				printf("Add node action cancelled.\n");
				break;

			case 3:
				//delete a student from linked list by key
				printf("\nEnter the key of the student you would like to delete.\n");

				int delStudentKey;
				char delStudentKeyStr[64];
				printf("Student key: ");
                scanf("%s", delStudentKeyStr);
				delStudentKey = atoi(delStudentKeyStr);

				//validate if node exists with this key
				currentStudent = LookUpByKey(&_head, delStudentKey);
				if (currentStudent == NULL) {
					printf("int main(); -- Student does not exist with key %d.\n", delStudentKey);
					printf("No action has been performed.\n");
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
					//do action, check for success
					int isSuccessful = DeleteMiddle(&_head, GetIndexByKey(&_head, delStudentKey));
					if (isSuccessful) {
						printf("Node deleted!\n");
						break;
					}
				} 
				printf("Delete node by key action cancelled.\n");
				break;

			case 4:
				//delete student from ll by index
				printf("\nEnter the index of the student you would like to delete.\n");
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
					printf("No action has been performed.\n");
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
					//do action, check for successs
					int isSuccessful = DeleteMiddle(&_head, delStudentIndex);
					if (isSuccessful){
						printf("Node deleted!\n");
						break;
					}
				} 
				printf("Delete node by index action cancelled.\n");
				break;

			case 5:
				//search engine for all fields basically, need ToString up and running first
				printf("\nEnter the string you would like to search.\n");

				char searchString[256];
				printf("Your search request: ");
				scanf("%s", searchString);


				printf("Key: | Data: FirstName, LastName, Major, GPA\n");
				printf("\nYour search results: ----------------------------------------------------------\n");
				PrintSearch(&_head, searchString);
				printf("\nEND OF LIST--------------------------------------------------------------------\n");
				break;
			case 6:
				cont = 0;
				FreeList(&_head);
				break;
			default:
				printf("\nSorry, that is an invalid operation.\n");
				userInputCounter--;
		}
		
	} while (cont == 1);
}

int main() {
	DisplayMenu();
	return 1;
}