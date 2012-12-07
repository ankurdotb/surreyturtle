/******************************************************************************
  
  Prog.h
  
  Class definition for 'Node' and 'Prog'. These classes define how the input
  files is read and then broken down into a list of instructions for the 
  program to execute.
  
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
		string readFile(ifstream &infile);
		void createInstructionList(string &input);
	public:
		
		
		Prog();
		Prog(ifstream &infile);
		
		~Prog();
		
		friend istream& operator>> (ifstream &in, Prog &p);
		
		void run();
};
