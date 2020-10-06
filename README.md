# chlosh-15
COSC 315-15 Closh Shell Project

## Project Description:

Closh is a basic shell implementation, which will execute a given program a given number of times.

In addition to this, the shell can either run processes in parallel or sequentially, with an optional timeout.


To build:

	git clone https://github.com/qwright/closh-15.git

Build closh with:

	make

Run with:

	./closh

***
Group Member Contributions:

	Quinn Wright - Closh Design and Implementation
	
	Christian Pasteris - Debugging
	
	Jesse Plamondon - Documentation

	Chinmay Gopal - Sample Outputs

***
## Design Choices:

	The program was designed purposefully to minimize friction within child and parent processes by keeping

	variables and intentionally seperate. This reduced some early friction, which had been causing issues between

	the processes, inevitably leading to a smoother and more efficient experience for the user.


### Parent Process
The parent process is responsible for keeping track of the children and overall program operatation, it implements a timer that if a process is running sequentially.

### Child Process
The child process forks from the parent and executes the program inputted by the user, it changes image to do so and becomes a zombie.

### Worker Process
The worker process was initially implemented to keep track of the child process, for the parent, as it was thought that execvp() did not exit the program correctly. Thus the idea was for this process to wait on the child to end while the parent process kept a timer, waiting for the worker. This was later deemed potentially unecessary, and future work could remove this altogether. However, it does provide some robustness and modality to a larger program using this logic. 

## Example
[Sample Output](SampleOutput.pdf)
