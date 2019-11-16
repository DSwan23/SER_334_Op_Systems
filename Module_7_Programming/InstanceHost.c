/**
 * Source file definition of functions to simulate a cloud-like server instance
 * host.
 * 
 * @author Swanson
 * @version 1.0
 */

#include "InstanceHost.h"
#include <math.h>

// Host structure definition
struct host{
    
};

/**
* Initializes the host environment.
*/
host* host_create()
{
    // Create a host structure object
    host *new_host = malloc(sizeof(struct host));
    // Populate the host values
    
    // Return the pointer to the host structure address
    return new_host;
}

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_destroy(host**){
    // free the host from memory
    
}

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host* h, struct job_node* batch)
{
    // Create a new server thread
    
    // Walk through the list passed and compute the square root of the data in each node
    
    // Return the thread to the thread pool
    
}



