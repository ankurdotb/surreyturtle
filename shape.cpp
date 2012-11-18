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


class commands
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
};


class instructions : public commands
{
	private:
		static vector<string> instructionTokens;
	protected:
	public:
		instructions();
		~instructions();
		void readFile(char *);
		void run();
};



commands::commands() { } // Constructor for commands class

commands::~commands() { } // Destructor for commands class

void commands::line(int value) { } // Draw straight lines

void commands::rotate(int value) { } // Rotate pointer

void commands::translate(int value) { } // Translate pointer without drawing anything

instructions::instructions() { } // Constructor for instructions class

instructions::~instructions() { } // Destructor for instructions class


void instructions::readFile(char *fileName)
{
	string line, buf; // Temporary variables for processing instructions file
	ifstream instructionsFile;
	instructionsFile.open(fileName);
	if (instructionsFile.is_open())
	{
		while(instructionsFile.good())
		{
			getline(instructionsFile,line);
			stringstream ss(line);
			while(ss>>buf)
			this->instructionTokens.push_back(buf);
		}
		instructionsFile.close();
	}
}


void instructions::run()
{
	commands commandSet;
	string temp;
	for ( int index = 0; index < this->instructionTokens.size(); index += 2)
	{
		if(this->instructionTokens[index] == "FORWARD")
		{
			temp = this->instructionTokens[index+1];
			//commandSet.line(temp);		
		}

		if(this->instructionTokens[index] == "LEFT"){
			temp = this->instructionTokens[index+1];
			//commandSet.rotate(temp);	
		}	
	}
}


instructions instructionSet;


void draw(void)   
{
	instructionSet.run();
}



int main (int argc, char** argv)   // Main function for program
{
	if (!(argc > 1)) // Check whether correct number of parameters have been passed from the terminal
	{
    		cout << "Usage: " << argv[0] << " filename" << endl ;
    		exit(0) ; 
 	}
 	
 	instructionSet.readFile(argv[1]);
 	
	window w(argc,argv);
	
	return 0;
}

