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
void course_insert();
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
            course_insert();
            break;

	case 'd':
            course_drop();
            break;

	case 's':
            schedule_print();
            break;

	case 'q':
            // main loop will take care of this.
            break;

	default:
            printf("\nError: Invalid Input.  Please try again...");
            break;
	}
}

// Will prompt the user for the course properties then add the course to the 
// schedule.
void course_insert()
{
    // Creating a new course message
    printf(" -- Creating a new course! -- \n");
    // Local variables
    struct CourseNode* new_node, current_list = course_collection;
    int subject_num, course_num, credits;
    char instruct[1026];
    // Prompt the user for the course subject
    printf("What is the course subject? (0 = SER, 1 = EGR, 2 = CSE, 3 = EEE)\n");
    scanf("%d", &subject_num);
    printf("\n");
    // Prompt the user for the course number
    printf("What is the course number? \n");
    scanf("%d", &course_num);
    printf("\n");
    // Prompt the user for the course credit hour
    printf("How many credits is this course worth? \n");
    scanf("%d", &credits);
    printf("\n");
    // Prompt the user for the teacher name
    printf("Who is the instructor of the course? \n");
    scanf("%c", &instruct);
    printf("\n");
    // Populate the struct node
    new_node->subject = subject_num;
    new_node->number = course_num;
    new_node->creditHours = credits;
    new_node->teacher = instruct;
    // Check to see if the schedule is empty
    if(current_list == NULL)
    {
        // Set the course collection to this new node
        course_collection = &new_node;
    }
    else
    {
        // Place the node at the end of the list
        while(*current_list->next != NULL)
        {
            // Go to the next node
            current_list = current_list->next;
        }
        // The last node has been reached, add the new node
        current_list.next = &new_node;
    }
    // Inform the user that the new class has been added to the schedule
    printf("The course has been added to the schedule. \n");
}

// Will print the current course schedule to the console
void schedule_print()
{
    // Check to see if there is a course schedule
    if(course_collection == NULL)
    {
        // Inform the user and return
        printf("-- There are not any courses in your schedule --");
        return;
    }
    // Local variables
    struct CourseNode* current_course = course_collection;
    // Loop through the course nodes
    while(*current_course)
    {
        // Loop variables
        char subject_str[];
        // Convert the enumeration to a string
        switch(current_course)
        {
            case 0: subject_str = "SER";
            case 1: subject_str = "EGR";
            case 2: subject_str = "CSE";
            case 3: subject_str = "EEE";
        }
        // Create the output
        printf("%c%d %d %c", subject_str, current_course->number, 
                             current_course->creditHours, 
                             current_course->teacher);
        // Move onto the next node
        current_course = current_course->next;
    }
}

// Will ask the user about which course to drop, check to see if that course is
// in the schedule and if it is then remove it, if not the user will be informed
// that the course doesn't exist.
void course_drop()
{
   // Local variables
   
}