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
#define _GNU_SOURCE
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
    struct value_node* current_burst; // The burst value to use next;
    struct process_node* next;      // The address of the next process in the list
};

// Define the structure types
typedef struct value_node value_node;       // Defining a type value to the struct defined above
typedef struct process_node process_node;   // Defining a type value to the struct defined above

// Global variables
int tick_count = -1;                // How many ticks the simulation should run for
int process_count = -1;             // How many processes to be used in this simulation
process_node* process_list = NULL;  // A list of the process defined by the input file
value_node* turnaround_list = NULL; // A list of current turnaround times
value_node* wait_list = NULL;       // A list of current wait times
value_node* est_time_list = NULL;// A list to store the actual times to determine the error

////////////////////////////////////////////////////////////////////////////////
//SUPPORTING FUNCTIONS

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

void process_list_cleanup(process_node* list)
{
    // Loop through the list and cleanup all of the nodes
    while(list)
    {
        // Store the current node for deletion
        process_node* current_node = list;
        // Move on to the next node
        list = list->next;
        // Delete the internal value lists
        value_list_cleanup(current_node->burst_list);
        free(current_node->burst_list);
        free(current_node->current_burst);        
        // Delete the current node
        free(current_node);
    }
}

void add_process_node(process_node* new_node, process_node* list)
{
    // Check for an empty list
    if(list == NULL)
    {
        // Set the new node as the head of the process list
        list = new_node;
        return;
    }    
    // Create an iterator node
    process_node* temp = list;    
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
        // Set the burst list head as the current burst
        new_process->current_burst = new_process->burst_list;
        // Add the process to the list of processes
        add_process_node(new_process, process_list);
    }    
}

void read_file(const char* file_path)
{
    // Open the file
    FILE* file = fopen(file_path, "r");
    
    // Check to see if the file open properly
    if(file != NULL)
    {
        printf("Could not open the file specified! Check the file path and "
                "try again \n");
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
        printf("Tick count read error\n");
        exit(0);
    }
    if(process_count == -1)
    {
        printf("process count read error\n");
        exit(0);
    }
    
    // Read in the process data
    populate_processes(file);
    
    // Close the file
    fclose(file);
    
    // Clean up of data
    if(line)
        free(line);
}

void compute_tau(process_node* process, int previous_burst)
{
    // Compute a new tau value and replace the current
    process->tau = process->alpha * previous_burst + (1 - process->alpha) * process->tau;
}

float compute_time_total(value_node* list)
{
    // Local variables
    float total = 0;
    // Temp node to facilitate the walk through
    value_node* temp = list;
    // Walk through the list and add all of the node values together
    while(temp != NULL)
    {
        // Add the value to the running total
        total += temp->value;
        // Move to the next node
        temp = temp->next;
    }
    // Return the computed value
    return total;
}

void sort_process_burst(process_node* output_list)
{
    for(int i = 0; i < process_count; i++)
    {
        // Temp variable to allow traversal of the list
        process_node* temp = process_list;
        // Variable to hold lowest value
        process_node* low = temp;
        // Move to the next node
        temp = temp->next;
        // Walk through the list of current processes
        while(temp != NULL)
        {
            // Check to see if the next node is lower than the current low
            if(low->current_burst->value > temp->current_burst->value)
            {
                // Set this process as the new low
                low = temp;
            }
        }
        // Add the low to the output_list in the next position
        add_process_node(low, output_list);
    }
}

void sort_process_tau(process_node* output_list)
{
    for(int i = 0; i < process_count; i++)
    {
        // Temp variable to allow traversal of the list
        process_node* temp = process_list;
        // Variable to hold lowest value
        process_node* low = temp;
        // Move to the next node
        temp = temp->next;
        // Walk through the list of current processes
        while(temp != NULL)
        {
            // Check to see if the next node is lower than the current low
            if(low->tau > temp->tau)
            {
                // Set this process as the new low
                low = temp;
            }
        }
        // Add the low to the output_list in the next position
        add_process_node(low, output_list);
    }
}

void run_process(process_node* list)
{
    // Temp node to walk through list
    process_node* temp = list;
    // Time trackers
    value_node* turnaround_node = malloc(sizeof(value_node));
    turnaround_node->value = 0;
    value_node* wait_node = malloc(sizeof(value_node));
    wait_node->value = 0;
    // Walk through entire list
    while(temp != NULL)
    {
        // Display the value on the UI
        printf("\tProcess %d took %d.\n", temp->pid, temp->current_burst->value);
        // Add wait time
        wait_node->value += turnaround_node->value;
        // Add turnaround time to the list
        turnaround_node->value += temp->current_burst->value;
        // Go to the next burst value
        temp->current_burst = temp->current_burst->next;
    }
    // Add the turnaround and wait values to their respective lists
    add_value_node(turnaround_node, turnaround_list);
    add_value_node(wait_node, wait_list);
}

void run_process_live(process_node* list)
{
    // Temp node to walk through list
    process_node* temp = list;
    // Time trackers
    value_node* turnaround_node = malloc(sizeof(value_node));
    turnaround_node->value = 0;
    value_node* est_node = malloc(sizeof(value_node));
    est_node->value = 0;
    value_node* wait_node = malloc(sizeof(value_node));
    wait_node->value = 0;
    // Walk through entire list
    while(temp != NULL)
    {
        // Display the value on the UI
        printf("\tProcess %d was estimated for %g and took %d.\n", temp->pid, 
                temp->tau, temp->current_burst->value);
        // Add wait time
        wait_node->value += turnaround_node->value;
        // Add estimation time
        est_node->value += temp->tau;
        // Add the actual turnaround time to the list
        turnaround_node->value += temp->current_burst->value;
        // Calculate the next tau value
        compute_tau(temp, temp->current_burst->value);
        // Go to the next burst value
        temp->current_burst = temp->current_burst->next;
    }
}

void SJF()
{
    // Local variables
    process_node* sorted_list;
    int current_time = 0;
    // Display the SJF header on the console
    printf("========== Shortest - Job - First ==========\n");
    // Walk through the simulation one tick at a time
    for(int tick = 0; tick < tick_count; tick++)
    {
        // Display tick value on the console
        printf("Simulating %d th tick of processes @ time %d:\n",
                tick, current_time);
        // Sort the processes by CPU burst value
        sort_process_burst(sorted_list);
        // Run each process in the sorted list
        run_process(sorted_list);
    }
    // Compute and display the turnaround time
    float time = compute_time_total(turnaround_list);
    printf("Turnaround time :\t%d\n", (int)time);
    // Compute and display the wait time
    time = compute_time_total(wait_list);
    printf("Waiting time :\t%d\n", (int)time);
}

void SJFL()
{
    // Local variables
    process_node* sorted_list;
    int current_time = 0;
    // Display the SJF header on the console
    printf("========== Shortest - Job - First - Live ==========\n");
    // Walk through the simulation one tick at a time
    for(int tick = 0; tick < tick_count; tick++)
    {
        // Display tick value on the console
        printf("Simulating %d th tick of processes @ time %d:\n",
                tick, current_time);
        // Sort the processes by CPU burst value
        sort_process_tau(sorted_list);
        // Run each process in the sorted list
        run_process(sorted_list);
    }
    // Compute and display the turnaround time
    float turn_time = compute_time_total(turnaround_list);
    printf("Turnaround time :\t%d\n", (int)turn_time);
    // Compute and display the wait time
    float wait_time = compute_time_total(wait_list);
    printf("Waiting time :\t%d\n", (int)wait_time);
    // Compute the estimation error
    float est_time = compute_time_total(est_time_list);
    printf("Estimation Error :\t%d\n", abs(turn_time - est_time));
}

////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE
int main(int argc, const char* argv[])
{
    // Get the file path from the passed arguments
    if(argc == 0)
    {
        printf("File path to process definition not passed as an argument, "
                "exiting!");
        exit(0);
    }
    // Read in the file data
    read_file(argv[0]);
    // Run the Shortest Job First Scheduling Algorithm
    SJF();
    // Walk through the processes and set the current burst back to the head of 
    // the burst list
    process_node* temp = process_list;
    while(temp != NULL)
    {
        // Set the current burst as the head of the burst list
        temp->current_burst = temp->burst_list;
        // Go to the next process
        temp = temp->next;
    }
    // Clear the time lists
    value_list_cleanup(turnaround_list);
    value_list_cleanup(wait_list);
    // Run the Shortest Job First Live Algorithm
    SJFL();
    // Clear the lists
    process_list_cleanup(process_list);
    free(process_list);
    value_list_cleanup(turnaround_list);
    value_list_cleanup(wait_list);
    value_list_cleanup(est_time_list);
    free(turnaround_list);
    free(wait_list);
    free(est_time_list);
    
    
}

