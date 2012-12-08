/******************************************************************************
  
  Prog.h
  
  Class definition for 'Node' and 'Prog'. These classes define how the input
  files is read and then broken down into a list of instructions for the 
  program to execute.
  
******************************************************************************/


// Standard C++ libaries
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <tr1/regex>

// Custom include files
#include "Command.h"


class Node
{
	protected:
		virtual Node() {};
		virtual ~Node() {};
		virtual void run() = 0;
};


class Prog
{
	private:
		static vector<Node*> instructions;
		static string input;
		void readFile(ifstream&);
		void createInstructionList(string&);
	public:
		
		
		Prog();
		Prog(ifstream&);
		
		~Prog();
		
		friend istream& operator>> (ifstream&, Prog&);
		
		void run();
};
