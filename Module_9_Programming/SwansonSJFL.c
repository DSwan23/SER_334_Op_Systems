/*
 * Description: Implementation of a Shortest Job First Scheduler, Implements 
 *              The live and standard versions.
 * Author: Douglas Swanson
 * Due: December 1st 2019
 * Time Spent:
 * Version: 1.0
 */

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
struct value_node
{
    int value;                  // This node's value
    struct value_node* next;    // The address to the node in the list
};

struct process_node
{
    int pid;                        // The process identification number
    float tau;                      // The starting tau number to be used in the live algorithm
    float alpha;                    // The alpha value to be used in the live algorithm
    struct value_node* burst_list;  // The address of the first node in the cpu burst time list
    struct process_node* next;      // The address of the next process in the list
};

// Define the structure types
typedef struct value_node value_node;
typedef struct process_node process_node;

// Global variables
int tick_count = -1;    // How many ticks the simulation should run for
int process_count = -1;  // How many processes to be used in this simulation
struct process_node* process_list = NULL;

////////////////////////////////////////////////////////////////////////////////
//SUPPORTING FUNCTIONS

void process_list_cleanup()
{
    // Loop through the list and cleanup all of the nodes
    while(process_list)
    {
        // Store the current node for deletion
        process_node* current_node = process_list;
        // Move on to the next node
        process_list = process_list->next;
        // Delete the current node
        free(current_node);
    }
}

void value_list_cleanup(value_node* list)
{
        // Loop through the list and cleanup all of the nodes
    while(list)
    {
        // Store the current node for deletion
        value_node* current_node = list;
        // Move on to the next node
        list = list->next;
        // Delete the current node
        free(current_node);
    }
}

void add_process_node(process_node* new_node)
{
    // Check for an empty list
    if(process_list == NULL)
    {
        // Set the new node as the head of the process list
        process_list = new_node;
        return;
    }    
    // Create an iterator node
    process_node* temp = process_list;    
    // Iterate over the list, until the last node is found
    while(temp->next != NULL)
    {
        temp = temp->next;
    }    
    // Add the new node as the las node's next node
    temp->next = new_node;   
}

void add_value_node(value_node* new_node, value_node* list)
{
    // Check for an empty list
    if(list == NULL)
    {
        // Set the new node as the head of the process list
        list = new_node;
        return;
    }    
    // Create an iterator node
    value_node* temp = list;    
    // Iterate over the list, until the last node is found
    while(temp->next != NULL)
    {
        temp = temp->next;
    }    
    // Add the new node as the las node's next node
    temp->next = new_node;   
}

void populate_processes(FILE* file)
{
    // Local variables
    char* line = NULL;
    size_t len = 0;
    __ssize_t line_size;
    process_node* new_process = NULL;
    value_node* new_value = NULL;
    // Loop through the remaining file and create a process node for each 
    // process
    while(line_size = getline(&line, &len, file) != -1)
    {
        // Create a new process node
        new_process = malloc(sizeof(new_process));
        // Set the process id
        new_process->pid = atoi(line);
        // Get the tau value
        line_size = getline(&line, &len, file);
        new_process->tau = atof(line);
        // Get the alpha value
        line_size = getline(&line, &len, file);
        new_process->alpha = atof(line);
        // Loop over the next lines and get the burst values
        for(int i = 0; i < tick_count; i++)
        {
            // Create a new value node
            new_value = malloc(sizeof(value_node));
            // Get the data
            line_size = getline(&line, &len, file);
            new_value->value = atoi(line);
            // Add the value to the process burst value list
            add_value_node(new_value, new_process->burst_list);
        }
        // Add the process to the list of processes
        add_process_node(new_process);
    }
    
}

void read_file(char* file_path)
{
    // Open the file
    FILE* file = fopen(file_path, "r");
    
    // Check to see if the file open properly
    if(file != NULL)
    {
        printf("Could not open the file specified! Check the file path and "
                "try again");
        exit(0);
    }
    
    // Read in the tick and process counts [first 2 lines]
    char* line = NULL;
    size_t len = 0;
    __ssize_t line_size = getline(&line, &len, file);
    tick_count = atoi(line);
    line_size = getline(&line, &len, file);
    process_count = atoi(line);
    
    // Check to see if the values were brought in successfully
    if(tick_count == -1)
    {
        printf("Tick count read error");
        exit(0);
    }
    if(process_count == -1)
    {
        printf("process count read error");
        exit(0);
    }
    
    // Read in the process data
    
    // Close the file
    fclose(file);
    
    // Clean up of data
    if(line)
        free(line);
}



////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE
int main(int argc, const char* argv[])
{
    //
}

