/******************************************************************************
  
  Prog.cpp
  
  Function definitions for declarations in Prog.h
  
******************************************************************************/


#include "Prog.h"


Prog::Prog() { }


Prog::Prog(ifstream &infile)
{
	input = readFile(infile);
}


Prog::~Prog() {}


istream& operator>> (ifstream &in, Prog &p)
{
       p.readFile(in);
       return in;
}


string Prog::readFile(ifstream &infile)
{
	string line;
	if (infile.is_open())
	{
		while(instructionsFile.good())
		{
			getline(infile, line);
		}
	}
	return line;
}

void Prog::createInstructionList(string &input)
{
	
}
