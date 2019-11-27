/**
 * source file definition of functions to simulate a load balancer.
 * 
 * @author Swanson
 * @version 1.0
 */
#include <stdlib.h>
#include "LoadBalancer.h"
#include "InstanceHost.h"

// balancer struct definition
struct balancer{
    struct job_node *head;  // The starting node in the list
    int current_count;      // The number of nodes in the list
    int batch_size;         // The number of node in a given batch
};

/**
 * Initializes the load balancer. Takes batch size as parameter.
 */
balancer* balancer_create(int batch_size)
{
    // Create and allocate memory for the balancer object
    balancer *job_list = malloc(sizeof(balancer));
    // Assign initial conditions to the balancer
    job_list->head = NULL;
    job_list->current_count = 0;
    job_list->batch_size = batch_size;
    // Return the address to this new balancer
    return job_list;
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_destroy(balancer** lb)
{
    // Check to see if the list has any nodes assigned
    
}

/**
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 * 
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */
void balancer_add_job(balancer* lb, int user_id, int data, int* data_return)
{
    // Create a new job node
    struct job_node *new_node = malloc(sizeof(struct job_node));
    // Populate the new node
    new_node->data = data;
    new_node->user_id = user_id;
    // check for an empty list
    if(lb->head == NULL)
    {
        // Add the new node as the beginning of the list
        lb->head = new_node;
        // Increase the current count by one
        lb->current_count++;
        // exit this function
        return;
    }
    // Assign a iterator node
    struct job_node *temp_node = lb->head;
    // Loop through the next statements until 
    while(temp_node->next != NULL){
        // get the next job node
        temp_node = temp_node->next;
    }
    // On the last node
    temp_node-> next = new_node;
    // Increase the count by one
    lb->current_count++;    
    // Check to see if enough jobs have been assigned to start an instance host
    if(lb->current_count == lb->batch_size)
    {
        // Create a new instance host
        
        // Lock the host resource
        
        // Request a new job instance and wait until it is finished
        
        // Unlock the host resource
        
        // Store the data result in a desired memory location
        
        // Clear the values from the list, freeing the memory
        temp_node = lb->head;
    }
}
