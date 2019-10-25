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
typedef enum { SER=0, EGR, CSE, EEE } subjects;

// Course Node Struct, for linking of lists lol
struct CourseNode 
{
    subjects Subject;
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
        
        // Clean up memory to prevent leaking, loop through schedule
        while(course_collection)
        {
            // Store the current node for memory cleanup
            struct CourseNode* deleteMe = course_collection;
            // Move on to the next node
            course_collection = course_collection->next;
            // Remove the current node
            free(deleteMe);
        }
        

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
    struct CourseNode* new_node;
    struct CourseNode* current_list = course_collection;
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
    new_node->Subject = subject_num;
    new_node->number = course_num;
    new_node->creditHours = credits;
    strcpy(instruct, new_node->teacher);
    // Check to see if the schedule is empty
    if(current_list == NULL)
    {
        // Set the course collection to this new node
        course_collection = &new_node;
    }
    else
    {
        // Place the node at the end of the list
        while(current_list->next != NULL)
        {
            // Go to the next node
            current_list = current_list->next;
        }
        // The last node has been reached, add the new node
        current_list->next = &new_node;
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
    while(current_course)
    {
        // Loop variables
        char* subject_str[4];
        // Convert the enumeration to a string
        switch(current_course->Subject)
        {
            case 0: strcpy(subject_str, "SER");
            case 1: strcpy(subject_str, "EGR");
            case 2: strcpy(subject_str, "CSE");
            case 3: strcpy(subject_str, "EEE");
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
    // Check to see if the schedule has any courses in it
    if(course_collection == NULL)
    {
        // Inform the user then return
        printf("There are not any courses in the schedule to remove!");
        return;
    }
    // Local variables
   struct CourseNode* current_course = course_collection;
   int course_num;
   struct CourseNode* deleteMe;
    // Ask the user for the course number
   printf("What is the number of the course to remove? \n");
   scanf("%d", &course_num);
   printf("\n");
   // Check the first course
   if(current_course->number == course_num)
   {
       // Store this for memory cleanup
       deleteMe = current_course;
       // check if there is another course
       if(current_course->next == NULL)
       {
           // Clear the schedule
           course_collection == NULL;
       }
       // Set the next course at the front
       course_collection = current_course->next;
       // Clean up memory
       free(deleteMe);
       // Inform the user
       printf("The course has been removed");
       // return
       return;
   }
   // Loop through the schedule
   while(current_course -> next != NULL)
   {
       // Check the course number on the current node
       if(current_course->next->number == course_num)
       {
           // Store the next node for memory cleanup
           deleteMe = current_course->next;
           // Check to see if the next course has a next course
           if(current_course->next->next == NULL)
           {
               // Set the current node's next to null
               current_course->next = NULL;
           }
           else
           {
               // set the next next course as the next
               current_course->next = current_course->next->next;
           }
           // Remove the next course from memory
           free(deleteMe);
           // Inform the user the course has been removed
           printf("Course has been removed");
           // Return
           return;
       }
   }
   // Inform the user that the course could not be found
   printf("The course cannot be deleted, it is not in the schedule!");   
}