/******************************************************************************
  
  shape.cpp
  
  Entry point for application. Accepts command line arguments from the terminal
  and spawns a window to display the output.
  
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
#include <iterator>
#include <algorithm>
#include <exception>


// Custom include files
#include "window.h"


using namespace std;


class Node
{
	protected:
		virtual void run() = 0;
};


class Command : public Node
{
	protected:
		float value;
		
	public:
		Command();
		Command(float);
		
		~Command();
		
		virtual void run() = 0;
};


class Prog
{
	private:
		vector<Command*> instructions;
		streampos sspos;
			
		inline string StringToUpper (string);
		
		void createInstructionList (ifstream&);
		float getCommandValue (string);
		
	public:		
		Prog();
		Prog (ifstream&, streampos);
		
		~Prog();
		
		friend istream& operator>> (ifstream&, Prog&);
		
		void run();
};


class Forward : public Command
{
	public:
		Forward();
		Forward(float);
	
		~Forward();
		
		void run();
};


class Jump : public Command
{
	public:
		Jump();
		Jump(float);
	
		~Jump();
	
		void run();
};


class Rotate : public Command
{
	public:
		Rotate();
		Rotate(float);
	
		~Rotate();
	
		void run();
};


class Repeat : public Command
{
	private:
		Prog *subset;
		int value;
		
	public:
		Repeat();
		Repeat(ifstream&, streampos, int);
	
		~Repeat();
	
		void run();
};


Prog::Prog() { }


/* Polymorphic constructor for Prog with default function parameters */
Prog::Prog (ifstream &infile, streampos spos = ios::beg)
{
	sspos = spos;
	createInstructionList(infile);
}


Prog::~Prog()
{
	for(vector<Command*>::const_iterator it = instructions.begin(); it != instructions.end(); it++)
        	delete (*it);
}


/* Operator overloading of '>>' operator,
handles passing input file to constructor. */
istream& operator>> (ifstream &in, Prog &p)
{
       p.createInstructionList(in);
       return in;
}


/* Iterates through Command vector and calls run()
for each command encountered in list. */
void Prog::run()
{
    for (vector<Command*>::const_iterator it = instructions.begin(); it != instructions.end(); it++)
	(*it)->run();
}


/* Convert every input string to uppercase */
inline string Prog::StringToUpper(string strToConvert)
{
    // Use STL algorithms to transform string to uppercase
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
    return strToConvert;
}


/* Convert string value of a command to float and return that value */
float Prog::getCommandValue(string word2)
{
	float v = 0;
	
	// Checks whether there's a closing bracket ']'
	// without a whitespace after a command value
	if (word2.find("]") == string::npos)
		v = atof(word2.c_str()); // Convert string to C-type character string, then convert to float
	else
	{
		// If a closing bracket is found, the command
		// value should chop off that bracket before trying
		// to convert to float
		word2 = word2.substr(0,word2.size()-1);
		v = atof(word2.c_str());
	}
	return v;
}


/* Create queue of instruction by reading in instructions file. */
void Prog::createInstructionList (ifstream &infile)
{
	string input;
	
	if(infile.is_open())
	{
		infile.seekg(0, ios::end);
		// Resize input string to only the amount of memory needed
    		input.resize(infile.tellg()); 
    		infile.seekg(0, ios::beg);
    		// Read input file into a string as a block operation
    		// instead of going line-by-line
    		infile.read(&input[0], input.size());
	}
	
	istringstream ss(input);
	ss.seekg(sspos); // Go to position in input file from which instructions need to be processed
			
	string word, word2;
	float v = 0;
	Command* tempCommand;

	while (ss >> word) // Read word-by-word into stringsteam object
	{
		try
		{
			// Command name can be in any case, converting to upper
			word = StringToUpper(word); 
			if (word == "[")
			{
				// Do nothing, discard and iterate to next word
			}
			else if (word.find("FORWARD") != string::npos)
			{
				ss >> word;
				v = getCommandValue(word);
				tempCommand = new Forward(v);
				instructions.push_back(tempCommand);
			}
			else if (word.find("LEFT") != string::npos)
			{
				ss >> word;
				v = getCommandValue(word);
				tempCommand = new Rotate(v);
				instructions.push_back(tempCommand);
			}
			else if (word.find("RIGHT") != string::npos)
			{
				ss >> word;
				v = -1 * getCommandValue(word);
				tempCommand = new Rotate(v);
				instructions.push_back(tempCommand);
			}
			else if (word.find("JUMP") != string::npos)
			{
				ss >> word;
				v = getCommandValue(word);
				tempCommand = new Jump(v);
				instructions.push_back(tempCommand);
			}
			else if (word.find("REPEAT") != string::npos)
			{
				ss >> word; 
				v = getCommandValue(word);
				tempCommand = new Repeat(infile, ss.tellg(), (int)v);
				instructions.push_back(tempCommand);
			}
			else if (word == "]")
			{
				// Do nothing, discard and iterate to next word
			}
			else
			{
				string errMsg = "Unknown command encountered in instruction file.";
				throw errMsg;
			}
		}
		catch (bad_alloc&)
		{
			cout << "Error allocating memory while trying to create instruction queue." << endl;
		}
		catch (string errMsg)
		{
			cout << errMsg << endl;
		}
		catch (...)
		{
			cout << "Unexpected error occured." << endl;
		}
	}
}


// Default constructor for Command class
Command::Command()
{
	value = 0.0;
}


// Constructor for Command class; this is the parent constructor
// called by child classes of Command.
Command::Command(float v)
{
	value = v;
}


Command::~Command() { }


Forward::Forward():Command() { }


Forward::Forward(float v):Command(v) { }


Forward::~Forward() { }


void Forward::run()
{
	// Draw required line starting at origin
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(value, 0.0f);
	glEnd();
	
	// Shift required line to desired location
	glTranslatef(value, 0.0f, 0.0f);
}


Jump::Jump():Command() { }


Jump::Jump(float v):Command(v) { }


Jump::~Jump() { }


void Jump::run()
{
	// Jump to desired location
	glTranslatef(value, 0.0f, 0.0f);
}

Rotate::Rotate():Command() { }


Rotate::Rotate(float v):Command(v) { }


Rotate::~Rotate() { }


void Rotate::run()
{
	// Rotate around Z-axis by desired value.
	// Left / right rotation is handled by
	// adding positive / negative sign while
	// parsing input file in Prog::createInstructionList()
	glRotatef(value, 0, 0, 1);
}


Repeat::Repeat():Command() { }


Repeat::Repeat(ifstream &infile, streampos spos, int v)
{
	value = v;
	subset = new Prog(infile, spos);
}


Repeat::~Repeat()
{
	delete [] (subset);
}


void Repeat::run()
{
	for (int i = 0; i < value; i++)
		subset->run();
}


Prog p; // Global variable of type Prog


// Hook that window.h calls to start excution of the program
void draw()
{
	p.run();
}


int main (int argc, char** argv)   // Main function for program
{
	// Check whether filename has been passed as a command-line argument
	if (argc != 2) 
	{
    		cout << "Usage: " << argv[0] << " filename" << endl ;
    		exit(0) ; 
 	}
 	
 	ifstream in;
 	in.exceptions(ifstream::failbit | ifstream::badbit);
 	
 	try
 	{
 		in.open(argv[1], ios::binary);
 	}
 	catch (ifstream::failure e)
 	{
 		cout << "Exception opening / reading file." << endl;
 	}
 	in >> p; // Call overloaded operator to read input file
 	in.close();
 	
	window w(argc,argv);
	
	return 0;
}


