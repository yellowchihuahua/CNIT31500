#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void printline(char *toPrint){
    printf("%s\n", toPrint);
}
// referenced https://www.techcrashcourse.com/2016/02/c-program-to-check-number-is-in-range-min-max.html
int checkBetween(float num, int min, int max) {
    if((num-min)*(num-max) <= 0){
        return 0;
    } 

    return 1;
}

float receiveDimensionsFloatInput (char *prompt, int min, int max){
    float value = -1.0f;
    // referenced https://stackoverflow.com/questions/34941692/ask-user-to-repeat-the-program-or-exit-in-c
    do {
        char input[5];
        printf("Enter the %s (%i-%i ft): ", prompt, min, max);
        scanf("%s", &input);
        
        // ref https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
        value = (float) (atof(input));
        
        if(checkBetween(value, min, max)) {
            //referenced https://www.tutorialspoint.com/c_standard_library/c_function_printf.htm
            printf("That is an invalid entry, please enter a value between %i-%i feet.\n", min, max);
            value = -1.0f;
        }
    } while (value == -1.0f);

    return value;
}

int receiveIntInput(char *prompt, int minInclusive){
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

// https://www.geeksforgeeks.org/bubble-sort/
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printline("");
}

//ref https://stackoverflow.com/questions/25925603/swap-function-of-elements-in-array
void swap(int *a, int *b) 
{ 
  int temp = *a;
  *a = *b;
  *b = temp;
}

// ref https://www.geeksforgeeks.org/bubble-sort/
int bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    int swapCount = 0;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
                swapCount++;
            }
        }
 
        // If no two elements were swapped by inner loop, break
        if (swapped == false){
            return swapCount;
            break;
        }
    }
    return swapCount;
}

// ref https://www.geeksforgeeks.org/selection-sort/
int selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    int swapCount = 0;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
           if(min_idx != i){
              swap(&arr[min_idx], &arr[i]);
              swapCount++;
           }
    }

    return swapCount;
}

//ref https://www.geeksforgeeks.org/quick-sort/
// Partition the array using the last element as the pivot
int partition(int arr[], int low, int high, int *swapCountAdd)
{
    // Choosing the pivot
    int pivot = arr[high];

    printf("address: %d", swapCountAdd);
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
            printline("swapping");
            *swapCountAdd == *swapCountAdd + 1;
            printf("count: %d", swapCountAdd);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//ref https://www.geeksforgeeks.org/quick-sort/
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
int quickSort(int arr[], int low, int high)
{
    int swapCount = 0;

    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = partition(arr, low, high, &swapCount);

        printf("\n%d\n", swapCount);
 
        // Separately sort elements before
        // partition and after partition
        swapCount = swapCount + quickSort(arr, low, pi - 1);
        swapCount = swapCount + quickSort(arr, pi + 1, high);
    }

    return swapCount;
}

int main() {
    int cont = 1;
    int userInputInteger = 0;

    char separator[] = ",";
    char *ptr;
    int inputArray[1024];
    char inputString[1024];
    int swapCount;
    int arraySizeCount = 0;

    do {
        char functionNumber = 0; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
        printline("===============================================================================");
        printf("Hi User! You have used %i functions within this program so far!", userInputInteger);
        printline("");
        printline("Here are your options: ");
        printline("");
        printline("(1) Use Bubble Sort to sort an array of integers");
        printline("(2) Use Selection Sort to sort an array of integers");
        printline("(3) Use Quicksort to sort an array of integers");
        printline("(4) Reverse a string through pass by value");
        printline("(5) Reverse a string through pass by reference");
        printline("(6) Exit the program");
        printline("");
        functionNumber = receiveIntInput("Enter the number of the function you would like to use (1-6): ", 1);
        
        userInputInteger++;

        switch(functionNumber) {
            case 1://array, bubble sort, decreasing

                //INPUT START, gave up refactoring
                // clear array ref https://www.geeksforgeeks.org/how-to-empty-a-char-array-in-c/
                inputArray[0] = '\0';

                printline("Enter your integer array, comma separated, no spaces: ");

                inputString[0] = '\0';

                scanf("%s", &inputString);

                ptr = strtok(inputString, separator);
                arraySizeCount = 0;
                while(ptr != NULL){
                    inputArray[arraySizeCount] = atoi(ptr);
                    arraySizeCount++;
                ptr = strtok(NULL, separator);
                }

                printline("");
                printline("Here is the array you input: ");
                printArray(inputArray, arraySizeCount);

                //INPUT END

                swapCount = bubbleSort(inputArray, arraySizeCount);
                printline("Your bubble sorted array: ");
                printArray(inputArray, arraySizeCount);

                printf("Swaps taken: %d\n", swapCount);

                break;
                
            case 2://array, selection sort, decreasing
                //INPUT START, gave up refactoring
                inputArray[0] = '\0';

                printline("Enter your integer array, comma separated, no spaces: ");

                inputString[0] = '\0';

                scanf("%s", &inputString);

                ptr = strtok(inputString, separator);
                arraySizeCount = 0;
                while(ptr != NULL){
                    inputArray[arraySizeCount] = atoi(ptr);
                    arraySizeCount++;
                ptr = strtok(NULL, separator);
                }

                printline("");
                printline("Here is the array you input: ");
                printArray(inputArray, arraySizeCount);

                //INPUT END

                swapCount = selectionSort(inputArray, arraySizeCount);
                printline("Your selection sorted array: ");
                printArray(inputArray, arraySizeCount);

                printf("Swaps taken: %d\n", swapCount);    

                break;

            case 3://array, quick sort, decreasing
                //INPUT START, gave up refactoring
                inputArray[0] = '\0';

                printline("Enter your integer array, comma separated, no spaces: ");

                inputString[0] = '\0';

                scanf("%s", &inputString);

                ptr = strtok(inputString, separator);
                arraySizeCount = 0;
                while(ptr != NULL){
                    inputArray[arraySizeCount] = atoi(ptr);
                    arraySizeCount++;
                ptr = strtok(NULL, separator);
                }

                printline("");
                printline("Here is the array you input: ");
                printArray(inputArray, arraySizeCount);

                //INPUT END

                swapCount = swapCount + quickSort(inputArray, 0, arraySizeCount);
                printline("Your quick sorted array: ");
                printArray(inputArray, arraySizeCount);

                printf("Swaps taken: %d\n", swapCount);

                break;

            case 4://string reversal, pass by value
                
                break;

            case 5://string reversal, pass by reference

                break;

            case 6://program exit
                //exit
                cont = 0;
                break;

            default:
                printline("\nSorry, that is an invalid input.");
                userInputInteger--;

        }

    } while (cont == 1);

    return 0;
}