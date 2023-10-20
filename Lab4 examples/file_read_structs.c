#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXCHAR 1024

// typedef struct lets us basically create out own variable datatype. So, besides int, float, string, etc... we now have Student and can operate on intsances directly. 
typedef struct Student
{
    int id;
    char name[MAXCHAR];
    float GPA;
} Student;

int main()
{
    /// file stuff
    FILE* fp;
    fp = fopen("test.csv", "r");
    char row[MAXCHAR];
    char* token;


    ////// struct stuff... typedef allows us to use Student as a variable type, basically
    Student students[3];

    // we can use this to capture every row, but you will need to figure out how to fit it in your array without knowing. We created an array of size 3*Student, but we may not know how many rows we have at the time. This is where dyanmic memory allocation is useful...
    // while(fgets(row, MAXCHAR, fp))
    // {
    //     Student tmp;
    //     token = strtok(row, ",");
    //     if(token) tmp.id = atoi(token);

    //     token = strtok(NULL, ",");
    //     if(token) strncpy(tmp.name, token, sizeof(tmp.name));

    //     token = strtok(NULL, ",");
    //     if(token) tmp.GPA = atof(token);

    //     printf("%d, %s, %f\n", tmp.id, tmp.name, tmp.GPA);
    // }

    // but since we DO know the number of elements in the csv...
    for(int i = 0; i < 3; i++)
    {
        Student tmp;
        fgets(row, MAXCHAR, fp);
        token = strtok(row, ",");
        if(token) tmp.id = atoi(token);

        token = strtok(NULL, ",");
        if(token) strncpy(tmp.name, token, sizeof(tmp.name));

        token = strtok(NULL, ",");
        if(token) tmp.GPA = atof(token);

        students[i] = tmp;
    }

    // you can get the amount of used blocks in an array by using the below, but this is only guaranteed to work locally, to where the array was declared, so instead of using this inside other functions besides main(), it may be a good idea to have a member variable store length instead of calculating it.
    int array_length = sizeof(students) / sizeof(Student);
    for(int i = 0; i < array_length; i++)
        printf("%d, %s, %f\n", students[i].id, students[i].name, students[i].GPA);

    // we created pointers, so we have to clear them
    free(fp);
    free(token);
    return 0;
}