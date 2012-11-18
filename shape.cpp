// shape.cpp : Defines the entry point for the console application.


#include "window.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstdlib>


using namespace std;


class instructions
{
	private:
		
	protected:
		static vector<string> instructionTokens;
	public:
		instructions();
		~instructions();
		void readFile(char *);
};


class commands : public instructions
{
	private:
		double x, y, z;
		void line(int);
		void rotate(int);
		void translate(int);
	protected:
		
	public:
		commands();
		~commands();
		void run();
		
};


void instructions::instructions() { } // Constructor for instructions class


void instructions::~instructions() { } // Destructor for instructions class


void instructions::readFile(char *fileName)
{
	string line, string buf; // Temporary variables for processing instructions file
	ifstream instructionsFile;
	instructionsFile.open(fileName);
	if (instructionsFile.is_open())
	{
		while(instructionsFile.good())
		{
			getline(instructionsFile,line);
			stringstream ss(line);
			while(ss>>buf)
			this.instructionTokens.push_back(buf);
		}
		instructionsFile.close();
	}
}


void commands::commands() { } // Constructor for commands class


void commands::~commands() { } // Destructor for commands class


void commands::line(int value) { } // Draw straight lines
{
	
}


void commands::rotate(int value) { } // Rotate pointer


void commands::translate(int value) { } // Translate pointer without drawing anything


void commands::run()
{
	string temp;
	for ( int index = 0; index < instructionSet.token.size(); index += 2)
	{
		if(instructionSet.token[index] == "FORWARD")
		{
			temp = instructionSet.token[index+1];
			commands::line( (int) temp);		
		}

		if(instructionSet.token[index] == "LEFT"){
			temp = instructionSet.token[index+1];
			commands::line( (int) temp);	
		}	
	}
}

void draw(void)   
{
	commands.run(instructionSet);
}


int main (int argc, char** argv)   // Main function for program
{
	if (!(argc > 1)) // Check whether correct number of parameters have been passed from the terminal
	{
    		cout << "Usage: " << argv[0] << " filename" << endl ;
    		exit(0) ; 
 	}
 	
 	instructions instructionSet;
 	instructionSet.readFile(argv[1]);
 	
	window w(argc,argv);
	
	return 0;
}

