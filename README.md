# chlosh-15
COSC 315-15 Closh Shell Project

Project Description:

	Closh is a basic shell implementation, which will execute a given execution a given number of times.

	In addition to this, the shell can either run processes in parallel or sequentially, with an optional timeout.


To build:

	`git clone https://github.com/qwright/closh-15.git`

Build closh with:

	`make`

Run with:

	`./closh`


Group Member Contributions:

	Quinn Wright - Closh Design and Implementation
	
	Christian Pasteris - Debugging
	
	Jesse Plamondon - Documentation

	Chinmay Gopal - Sample Outputs


Design Choices:

	The program was designed purposefully to minimize friction within child and parent processes by keeping

	variables and intentionally seperate. This reduced some early friction, which had been causing issues between

	the processes, inevitably leading to a smoother and more efficient experience for the user.

	