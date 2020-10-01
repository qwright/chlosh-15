// closh.c - COSC 315, Winter 2020
// Group 15

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
		
		pid_t pid; //parent id
		int status; //status of process
		time_t start, final;
		int final_time;
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code
        
        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////
        
        // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
        //execvp(cmdTokens[0], cmdTokens);replaces the current process with the given program

				//loop for child processes as specified by count
				while(count > 1){
					pid = fork();//literally think of this as a fork in the road, two processes will execute, child gets 0, parent gets child id
					time(&start);//start a timer for each proccess
					if(pid==0){
						printf("CHILD PID: %d, Creating Process...\n", pid);
						sleep(5);
						execvp(cmdTokens[0], cmdTokens);//this ends the current scope
					}else{
						printf("Parent PID: %d, Keeping track of Child process...\n", pid); //dont execvp, as it would end program
						if(parallel==0){
						printf("Waiting for Child to wrap up...\n");
						do{
							pid = waitpid(pid, &status, WCONTINUED); //
							time(&final);
							final_time = final - start;
							printf("TIME: %d\n", final_time);
							if(timeout !=0 && final_time > timeout){
								printf("Killing child process: %d\n", pid);
								kill(pid, SIGKILL);
							}
						}while(!WIFEXITED(status));
					count--;
					}
					//if process is sequential, wait for child to wrap up.
					
					}
				}
				//parent executes here i.e. final count
				printf("Not a forked process, Creating Final Process...\n");
				execvp(cmdTokens[0], cmdTokens);
				
        // doesn't return unless the calling failed
        printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);        
    }
}

