/**
* Implements the collatz algorithm
*
* Completion time: 0.2 hours
*
* @author Swanson
* @version 1.0
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES

#include <stdio.h>
#include <stdlib.h>

/*
 * Main method to test the collatz algorithm method
 */
int main(int argc, char** argv) 
{
    // Local variables
    int collatzNum, collatzIterations;

    // Call termination passing a number input from the user
    printf("What number would you like to test the collatz conjecture against? Number = ");
    scanf("%d", &collatzNum);
    
    // Perform the algorithm on the number passed
    collatzIterations = termination(collatzNum);
    
    // Display the value to the user
    printf("The integer %d took %d iterations to solve", collatzNum, collatzIterations);
    
    // Return success
    return (EXIT_SUCCESS);
}

// Write a C program to implement the algorithm as a function termination
// that is called from main [ 4 points]
int termination(int n)
{
    // Local variables
    int count = 0;
    // perform the collatz conjecture
    while(n != 1)
    {
        if(n%2 == 0)
        {
            n = n/2;
        }
        else
        {
            n = 3*n+1;
        }
        count = count + 1;
    }
    // return the number of iterations
    return count;
}