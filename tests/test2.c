#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
   	pid_t pid1, pid2;
    
    	pid1 = fork();
    	if (pid1 < 0) {
    		perror("Failed to fork process 1");
        	exit(EXIT_FAILURE);
    	}
                
    	if (pid1 == 0) {
        	printf("Process 1 (PID: %d) started.\n", getpid());
        	set_scheduling_params(1, 800, 2000);
         	while (1);
   	 }	       
                        
    	pid2 = fork();
    	if (pid2 < 0) {
    		perror("Failed to fork process 2");
        	exit(EXIT_FAILURE);
   	 }
                        
    	if (pid2 == 0) {
        	printf("Process 2 (PID: %d) started.\n", getpid());
        	set_scheduling_params(1, 600, 2000);
        	while (1);
    	}
                        
    	int status; int status2;
    
   	waitpid(pid1, &status, 0);
    	printf("Child 1 terminated\n");
    	waitpid(pid2, &status2 , 0);
    	printf("Child 2 terminated\n");
      
    	printf("Parent process terminating because child processes died.\n");
    	kill(getpid(), SIGTERM);


    	return 0;
}
                                                         
