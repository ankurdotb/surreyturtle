/******************************************************************************
  
  Prog.cpp
  
  Function definitions for declarations in Prog.h
  
******************************************************************************/


#include "Prog.h"


Prog::Prog() { }


Prog::Prog(ifstream &infile)
{
	readFile(infile);
}


Prog::~Prog() {}


istream& operator>> (ifstream &in, Prog &p)
{
       p.readFile(in);
       return in;
}


void Prog::readFile(ifstream &infile)
{
	if(infile.is_open())
	{
		infile.seekg(0, ios::end);
    		input.resize(infile.tellg());
    		infile.seekg(0, ios::beg);
    		infile.read(&input[0], input.size());
	}
}

void Prog::createInstructionList(string &input)
{
	
}
