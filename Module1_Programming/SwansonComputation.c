/**
* (basic description of the program or class)
*
* Completion time: 1.0 hour
*
* @author Douglas Swanson, Ruben Acuna
* @version 1.0
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <math.h>



int main(void)
{
    // Local variables
    int numCylinders, index;
    float height, radius, totalVolume;
    //Add a prompt for the number of cylinders to sum. Make sure to use the control
    //symbol for integers. [2 points]
    printf("How many cylinders need their volumes summed? Count = ");
    scanf("%d", &numCylinders);
    
    //Create a loop based on the number of cylinders the user enters. [2 points]
    totalVolume = 0;
    for(index = 0 ;index < numCylinders; index = index + 1)
    {
        //    Within the loop, prompt for height and radius parameters (allow floating
        //    point numbers), and calculate the volume for that particular cylinder.
        //    [4 points]  
        printf("What is the height of the %d cylinder? Height = ", index+1);
        scanf("%f", &height);
        printf("What is the radius of the %d cylinder? Radius = ", index +1);
        scanf("%f", &radius);
        totalVolume = totalVolume + (M_PI*radius*radius*height); 
    }
    
    //Display the total volume sum back to the user. Make sure to use the right control
    //symbol. [2 points]
    printf("The total volume of the cylinders is %f. \n", totalVolume);
    
    // Return a 0 to indicate the main method is done running
    return 0;
}