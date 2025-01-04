#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

float poolMaxVolume(float depthPoolShallow, float depthPoolDeep, float widthPool, float lengthPool, float lengthWalkinPool, float lengthShallowPool, float lengthDeepPool){
    float deepChunkVolume = depthPoolDeep*lengthDeepPool*widthPool;
    float lengthWalkinDeepPool = lengthPool - (lengthWalkinPool + lengthShallowPool + lengthDeepPool);
    float deepSlopeVolume = lengthWalkinDeepPool*widthPool*((depthPoolDeep+depthPoolShallow)/2);

    float shallowChunkVolume = depthPoolShallow*lengthShallowPool*widthPool;
    float shallowSlopeVolume = lengthWalkinPool*widthPool*((depthPoolShallow)/2);
    
    return (deepChunkVolume + deepSlopeVolume + shallowChunkVolume + shallowSlopeVolume);
}

float poolWaterVolume(float depthPoolShallow, float depthPoolDeep, float widthPool, float lengthPool, float lengthWalkinPool, float lengthShallowPool, float lengthDeepPool){

    float deepChunkVolume = (depthPoolDeep-0.5f)*lengthDeepPool*widthPool;
    float lengthWalkinDeepPool = lengthPool - (lengthWalkinPool + lengthShallowPool + lengthDeepPool);
    float deepSlopeVolume = lengthWalkinDeepPool*widthPool*(((depthPoolDeep+depthPoolShallow)/2)-0.5f);

    float shallowChunkVolume = (depthPoolShallow-0.5f)*lengthShallowPool*widthPool;
    float shallowSlopeVolume = lengthWalkinPool*widthPool*(((depthPoolShallow)/2)-0.5f);
    
    return (deepChunkVolume + deepSlopeVolume + shallowChunkVolume + shallowSlopeVolume);
}

//referenced Lab1Bootstrap.c example 
float hotTubMaxVolume(float widthHotTub, float depthHotTub){
    float radiusHotTub = widthHotTub / 2;
    float area = M_PI*pow(radiusHotTub, 2);
    
    return area * depthHotTub;
}

float hotTubWaterVolume(float widthHotTub, float depthHotTub){
    float radiusHotTub = widthHotTub / 2;
    float depthWaterHotTub = depthHotTub - 0.5f; //for 6 inches
    float area = M_PI*pow(radiusHotTub, 2);
    
    return area * depthWaterHotTub;
}

float waterCostFtCubed(float waterVolume){
    float gallons = waterVolume*7.481;
    float quarts = gallons*4;
    float cost = quarts*0.07;

    return cost;
}

int factorial(int n) {
    if (n==0) {
        return 1;
    } else {
        return n*factorial(n-1);
    }
}

//ref https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi-2/
void towerOfHanoi(int disks, char from_rod, char to_rod, char other_rod){
    if (disks == 1){
        printf("\nMove disk %i from rod %c to rod %c", disks, from_rod, to_rod);
        return ;
    }
    towerOfHanoi(disks-1, from_rod, other_rod, to_rod);
    printf("\nMove disk %i from rod %c to rod %c", disks, from_rod, to_rod);
    towerOfHanoi(disks-1, other_rod, to_rod, from_rod);
}

//ref https://medium.com/launch-school/recursive-fibonnaci-method-explained-d82215c5498e
int fibonacci(int n) {
    if (n < 2){
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

//ref https://stackoverflow.com/questions/69982525/how-to-print-sum-of-numbers-to-n-recursively
int sumToN(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + sumToN(n-1);
    }
}

int main() {
    int cont = 1;
    int userInputInteger = 0;
    float widthHotTub, depthHotTub;
    float depthPoolShallow, depthPoolDeep, widthPool, lengthPool, lengthWalkinPool, lengthShallowPool, lengthDeepPool;

    do {
        char functionNumber = 0; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
        printf("\n\n===============================================================================");
        printf("\nHi User! You have used %i functions within this program so far!", userInputInteger);
        printf("\nHere are your options: ");
        printf("\n(1) Calculate the max volume and water needed to fill a circular hot tub");
        printf("\n(2) Calculate the max volume and water needed to fill a pool");
        printf("\n(3) Calculate the factorial of a number");
        printf("\n(4) List moves for Tower of Hanoi");
        printf("\n(5) Calculate Fibonacci sequence for a number");
        printf("\n(6) Calculate sum of all positive integers from 1 to a number, inclusive");
        printf("\n(7) Exit the program");
        functionNumber = receiveIntInput("\nEnter the number of the function you would like to use (1-7): ", 1);
        
        userInputInteger++;

        switch(functionNumber) {
            case 1:
                //hot tub
                widthHotTub = receiveDimensionsFloatInput("width of the hot tub", 6, 12);
                depthHotTub = receiveDimensionsFloatInput("depth of the hot tub", 3, 5);
                                
                printf("Maximum Volume of Hot Tub: %f ft3\n", hotTubMaxVolume(widthHotTub, depthHotTub));
                float hotTubWater = hotTubWaterVolume(widthHotTub, depthHotTub);
                printf("Water Volume of Hot Tub: %f ft3\n", hotTubWater);
                printf("Cost of water for Hot Tub at recommended water level (6in below max): %f USD\n", waterCostFtCubed(hotTubWater));
                break;
                
            case 2:
                //pool
                depthPoolShallow = receiveDimensionsFloatInput("depth of the shallow end of the pool", 0, 4);
                depthPoolDeep = receiveDimensionsFloatInput("depth of the deep end of the pool", 8, 17);
                widthPool = receiveDimensionsFloatInput("width of the pool", 15, 30);
                lengthPool = receiveDimensionsFloatInput("length of the pool", 40, 70);
                lengthWalkinPool = receiveDimensionsFloatInput("length of the walk in", 5, lengthPool/3);
                lengthShallowPool = receiveDimensionsFloatInput("length of the shallow end of the pool", 10, lengthPool/2);
                lengthDeepPool = receiveDimensionsFloatInput("length of the deep end", 12, lengthPool/2);

                printf("\nMaximum Volume of Pool: %f ft3", poolMaxVolume(depthPoolShallow, depthPoolDeep, widthPool, lengthPool, lengthWalkinPool, lengthShallowPool, lengthDeepPool));
                float poolWater = poolWaterVolume(depthPoolShallow, depthPoolDeep, widthPool, lengthPool, lengthWalkinPool, lengthShallowPool, lengthDeepPool);
                printf("\nWater Volume of Pool: %f ft3", poolWater);
                printf("\nCost of water for Pool at recommended water level (6in below max): %f USD\n", waterCostFtCubed(poolWater));
                break;

            case 3:
                //factorial
                int value = receiveIntInput("Enter a non-negative integer: ", 0);
                
                printf("\nThe number you input: %i", value);
                printf("\nThe factorial of %i, or %i!, is %i", value, value, factorial(value));

                break;

            case 4:
                //tower of hanoi
                value = receiveIntInput("Enter a positive integer: ", 1);
                

                printf("\nThe number you input: %i", value);
                printf("\nThe steps to solve this are: ");
                towerOfHanoi(value, 'A', 'C', 'B');
                
                break;

            case 5:
                //fibonacci
                value = receiveIntInput("Enter a positive integer: ", 1);
                
                printf("\nThe number you input: %i", value);
                printf("\nThe %ith fibonacci number is %i", value, fibonacci(value));
                printf("\nHere is the list of all fibonacci numbers up to the %ith fibonacci number: \n", value);

                //ref https://www.programiz.com/c-programming/c-for-loop
                for (int i = 1; i < (value+1); i++){
                    printf("%i ", fibonacci(i));
                }
                break;

            case 6:
                //sum of integers to N inclusive
                value = receiveIntInput("Enter a non-negative integer: ", 0);
                
                printf("\nThe number you input: %i", value);
                printf("\nThe sum of integers up to %i is %i", value, sumToN(value));

                break;

            case 7:
                //exit
                cont = 0;
                break;
            
            default:
                printf("\nSorry, that is an invalid input.\n");
                userInputInteger--;

        }

    } while (cont == 1);

    return 0;
}