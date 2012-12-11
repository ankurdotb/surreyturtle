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
#include <algorithm>


// Custom include files
#include "window.h"


using namespace std;


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
		vector<Command*> instructions;
		string input;
		
		inline string StringToUpper(string);
		
		void readFile (ifstream&);
		void createInstructionList (string&);
		float getCommandValue(string);
		
	public:		
		Prog();
		Prog (ifstream&);
		
		~Prog();
		
		friend istream& operator>> (ifstream&, Prog&);
		
		void run();
};


class Command : public Node
{
	protected:
		float value;
	public:
		Command();
		Command(float);
		
		~Command();
		
		//friend istream& operator>> (istream& in, Command &c);
		
		virtual void run() = 0;
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


/*class Repeat : public Command
{
	private:
		Prog *subset;
	public:
		Repeat();
		Repeat(ifstream &infile, float value);
	
		~Repeat();
	
		void run();
};*/


Prog::Prog() { }


Prog::Prog (ifstream &infile)
{
	readFile(infile);
}


Prog::~Prog()
{
	for(vector<Command*>::const_iterator it = instructions.begin(); it != instructions.end(); it++)
        	delete (*it);
}


istream& operator>> (ifstream &in, Prog &p)
{
       p.readFile(in);
       return in;
}


void Prog::run()
{
    for (std::vector<Command*>::const_iterator it(instructions.begin()); it != instructions.end(); it++)
    {
        (*it)->run();
    }
}


void Prog::readFile (ifstream &infile)
{
	if(infile.is_open())
	{
		infile.seekg(0, ios::end);
    		input.resize(infile.tellg());
    		infile.seekg(0, ios::beg);
    		infile.read(&input[0], input.size());
	}
}


inline string Prog::StringToUpper(string strToConvert)
{
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
    return strToConvert;
}


float Prog::getCommandValue(string word2)
{
	float v = 0;
	
	if (word2.find("]") == string::npos)
		v = atof(word.c_str());
	else
	{
		word2 = word2.substr(0,word2.size()-1);
		v = atof(word2.c_str());
	}
	return v;
}

void Prog::createInstructionList(string &input)
{
	istringstream ss(input);
	string word, word2;
	float v = 0;
	Command* tempCommand;
	
	while (ss >> word)
	{
		word = StringToUpper(word); // Command name can be in any case, converting to upper
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
		/*else if (word.find("REPEAT") != string::npos)
		{
			ss >> word;
			v = getCommandValue(word);
			tempCommand = new Repeat((int)v);
			instructions.push_back(tempCommand);
		}
		
		if (word.find("]") != string::npos)
		{
			tempCommand = new Repeat((int)-1);
			instructions.push_back(tempCommand);
		}*/
	}
}


// Default constructor for Command class
Command::Command()
{
	value = 0.0;
}


// Constructor for Command class; this is the parent constructor called by
// child classes of Command.
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
	// Rotate around Z-axis by desired value. Left / right rotation is
	// handled by adding positive / negative sign while parsing input file
	// in Prog::createInstructionList()
	glRotatef(value, 0, 0, 1);
}


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
 	
 	ifstream in(argv[1], ios::binary);
 	in >> p;
 	in.close();
	window w(argc,argv);
	
	return 0;
}

