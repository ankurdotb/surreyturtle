/******************************************************************************
  
  main.cpp
  
  Entry point for application. Accepts command line arguments from the terminal
  and spawns a window to display the output.
  
******************************************************************************/


// Standard C++ libaries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstdlib>

// Custom include files
#include "window.h"
#include "Prog.h"
#include "Command.h"


using namespace std;
Prog p;


// Hook that window.h calls to start excution of the program
void draw()
{
	p.run();
}


int main (int argc, char** argv)   // Main function for program
{
	if (!(argc > 1)) // Check whether correct number of parameters have been passed from the terminal
	{
    		cout << "Usage: " << argv[0] << " filename" << endl ;
    		exit(0) ; 
 	}
 	
 	ifstream in(argv[1]);
 	in>>p;
 	in.close();
	window w(argc,argv);
	
	return 0;
}

