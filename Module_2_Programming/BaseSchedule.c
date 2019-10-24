/**
* (basic description of the program or class)
*
* Completion time: 
*
* @author Swanson, Acuna
* @version 1.0 
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS



////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
// Subjects enumeration
enum { SER=0, EGR, CSE, EEE } Subjects;

// Course Node Struct, for linking of lists lol
struct CourseNode 
{
    typedef enum Subjects subject;
    int number;
    int creditHours;
    char teacher[1024];
    struct CourseNode* next;
};


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

//place to store course information
struct CourseNode* course_collection = NULL;
// Current number of classes
int courseCount = 0;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);
void course_Insert();
void schedule_print();
void course_drop();

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {
	char input_buffer;

	printf("\n\nWelcome to ASU Class Schedule\n");

	//menu and input loop
	do {
		printf("\nMenu Options\n");
		printf("------------------------------------------------------\n");
		printf("a: Add a class\n");
		printf("d: Drop a class\n");
		printf("s: Show your classes\n");
		printf("q: Quit\n");
		printf("\nTotal Credits: %d\n\n", courseCount);
		printf("Please enter a choice ---> ");

		scanf(" %c", &input_buffer);

		branching(input_buffer);
	} while (input_buffer != 'q');
        
        // Clean up memory to prevent leaking

	return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
	switch (option) {
	case 'a':
		//TODO
		break;

	case 'd':
		//TODO
		break;

	case 's':
		//TODO
		break;

	case 'q':
		// main loop will take care of this.
		break;

	default:
		printf("\nError: Invalid Input.  Please try again...");
		break;
	}
}