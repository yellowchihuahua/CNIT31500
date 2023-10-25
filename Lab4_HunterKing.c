// This code was written with the help of ChatGPT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    char firstName[50];
    char lastName[50];
    char major[50];
    float GPA;
    struct Student* next;
};


struct Student* start = NULL;
struct Student* current = NULL;


struct Student* CreateListNode(char first[], char last[], char major[], float gpa) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newStudent->firstName, first);
    strcpy(newStudent->lastName, last);
    strcpy(newStudent->major, major);
    newStudent->GPA = gpa;
    newStudent->next = NULL;
    return newStudent;
}


void InsertFront(struct Student* newStudent) {
    newStudent->next = start;
    start = newStudent;
}

void InsertMiddle(struct Student* newStudent) {
    if (start == NULL || newStudent->GPA >= start->GPA) {
        InsertFront(newStudent);
        return;
    }

    struct Student* temp = start;
    while (temp->next != NULL && temp->next->GPA > newStudent->GPA) {
        temp = temp->next;
    }
    newStudent->next = temp->next;
    temp->next = newStudent;
}

void InsertEnd(struct Student* newStudent) {
    if (start == NULL) {
        start = newStudent;
    } else {
        struct Student* temp = start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

void DeleteFront() {
    if (start == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }
    struct Student* temp = start;
    start = start->next;
    free(temp);
    printf("Student deleted from the front successfully.\n");
}

void DeleteMiddle(float targetGPA) {
    if (start == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    if (start->GPA == targetGPA) {
        DeleteFront();
        return;
    }

    struct Student* temp = start;
    while (temp->next != NULL && temp->next->GPA != targetGPA) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        printf("Student with GPA %.2f not found.\n", targetGPA);
        return;
    }

    struct Student* toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);
    printf("Student deleted successfully.\n");
}

void DeleteEnd() {
    if (start == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    if (start->next == NULL) {
        free(start);
        start = NULL;
        printf("Student deleted from the end successfully.\n");
        return;
    }

    struct Student* temp = start;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
    printf("Student deleted from the end successfully.\n");
}

void DeleteStudent(char first[], char last[]) {
    if (start == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }

    if (strcmp(start->firstName, first) == 0 && strcmp(start->lastName, last) == 0) {
        struct Student* temp = start;
        start = start->next;
        free(temp);
        printf("Student deleted successfully.\n");
        return;
    }

    struct Student* temp = start;
    while (temp->next != NULL && (strcmp(temp->next->firstName, first) != 0 || strcmp(temp->next->lastName, last) != 0)) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        printf("Student not found.\n");
        return;
    }

    struct Student* toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);
    printf("Student deleted successfully.\n");
}

void Traverse() {
    struct Student* temp = start;
    if (temp == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("Students sorted by GPA (descending order):\n");
    printf("-------------------------------------------------\n");
    printf("First Name   Last Name    Major       GPA\n");
    printf("-------------------------------------------------\n");

    while (temp != NULL) {
        printf("%-13s%-13s%-12s%.2f\n", temp->firstName, temp->lastName, temp->major, temp->GPA);
        temp = temp->next;
    }
}

int LookUpByIndex(int index) {
    struct Student* temp = start;
    int count = 0;
    while (temp != NULL && count < index) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) {
        return -1; // Index not found
    }
    return count;
}

void DisplayMenu() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Print all students\n");
        printf("2. Insert a student\n");
        printf("3. Delete a student by name\n");
        printf("4. Delete the first student\n");
        printf("5. Delete the last student\n");
        printf("6. Delete a student by GPA\n");
        printf("7. Find a student by index\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Traverse();
                break;
            case 2: {
                char first[50], last[50], major[50];
                float gpa;
                printf("Enter student information:\n");
                printf("First Name: ");
                scanf("%s", first);
                printf("Last Name: ");
                scanf("%s", last);
                printf("Major: ");
                scanf("%s", major);
                printf("GPA: ");
                scanf("%f", &gpa);
                struct Student* newStudent = CreateListNode(first, last, major, gpa);
                InsertMiddle(newStudent);
                printf("Student added successfully.\n");
                break;
            }
            case 3: {
                char first[50], last[50];
                printf("Enter the first name of the student you want to delete: ");
                scanf("%s", first);
                printf("Enter the last name of the student you want to delete: ");
                scanf("%s", last);
                DeleteStudent(first, last);
                break;
            }
            case 4:
                DeleteFront();
                break;
            case 5:
                DeleteEnd();
                break;
            case 6:{
                float gpa;
                printf("Enter the GPA of the student you want to delete: ");
                scanf("%f", &gpa);
                DeleteMiddle(gpa);
                printf("Student deleted successfully.\n");
                break;
            }
            case 7: {
                int index;
                printf("Enter the index of the student you want to find: ");
                scanf("%d", &index);
                int result = LookUpByIndex(index);
                if (result == -1) {
                    printf("Student not found at index %d.\n", index);
                } else {
                    printf("Student found at index %d:\n", index);
                    struct Student* foundStudent = start;
                    for (int i = 0; i < index; i++) {
                        foundStudent = foundStudent->next;
                    }
                    printf("First Name: %s\n", foundStudent->firstName);
                    printf("Last Name: %s\n", foundStudent->lastName);
                    printf("Major: %s\n", foundStudent->major);
                    printf("GPA: %.2f\n", foundStudent->GPA);
                }
                break;
            }
            case 8:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");

        }
    }
}

int main() {
    DisplayMenu();
    return 0;
}
