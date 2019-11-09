/**
 * SwansnLKM.c
 *
 * A kernal module that lists all of the details on processes higher than a 
 * given PID. 
 * 
 * To compile, run makefile by entering "make"
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>

// Global Variables
static int startPID = 0;
struct task_struct* task;
struct list_head* iterateList;


void display_processes(void)
{
	// Loop through the processes in the scheduled task
	for_each_process( task )
	{
		if(task->pid >= startPID)
		{
			// Print the current task header
			printk(KERN_INFO "PROCESS\t\tPID\t\tSTATE\t\tPRIO\t\tST_PRIO\t\tNORM_PRIO\n");
			// Print out this process information
			printk(KERN_INFO "%s\t\t%d\t\t%ld\t\t%d\t\t%d\t\t%d", task->comm, task->pid, task->state, task->prio, task->static_prio, task->normal_prio);
			// Check for a Parent task
			if(task->parent != NULL)
			{
				// Local Parent Task
				struct task_struct* parent = task->parent;
				// Print Parent Header
				printk(KERN_INFO "PARENT");
				// Print Parent Information
				printk(KERN_INFO "%s\t\t%d\t\t%ld\t\t%d\t\t%d\t\t%d", parent->comm, parent->pid, parent->state, parent->prio, parent->static_prio, parent->normal_prio);
			}
				// Child Header Flag
				int header = 0;
				
				// Loop thorugh all of the children processes
				list_for_each( iterateList, &task->children)
				{
					// Check to see if the header has been printed
					if(header == 0)
					{
						// print the header
						printk(KERN_INFO "CHILDREN");
						// change the flag
						header = 1;
					}
					// Get the child information using the list entry
					struct task_struct* child = list_entry(iterateList, struct task_struct, sibling);
					// Print child Information
					printk(KERN_INFO "%s\t\t%d\t\t%ld\t\t%d\t\t%d\t\t%d", child->comm, child->pid, child->state, child->prio, child->static_prio, child->normal_prio);
				}
			// Asthetic Spacing
			printk("\n=================================================================================================\n");
		}
	}
}

/* This function is called when the module is loaded. */
int init(void)
{
	// Insert Message
     printk(KERN_INFO "SwansonLKM Loaded\n");
	 // Debugging
	 printk(KERN_INFO "startPID = %d\n", startPID);
	 // Loop through the proesses
	 display_processes();
	 // Return sucess
      return 0;
}

/* This function is called when the module is removed. */
void exit(void) {
	// Exit Message
	printk(KERN_INFO "SwansonLKM UnLoaded\n");
}


/* Macros for registering module entry and exit points. */
module_init( init );
module_exit( exit );

/* Macros for getting information from the user */
module_param(startPID, int, 0);
MODULE_PARM_DESC(startPID, "The process id number in which to begin the list at");


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Swanson Process List Module");
MODULE_AUTHOR("Douglas Swanson");

