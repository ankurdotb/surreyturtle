/******************************************************************************
  
  Prog.cpp
  
  Function definitions for declarations in Prog.h
  
******************************************************************************/


#include "Prog.h"


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


void progC::run()
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
			v = -1 * getCommandValue(word);
			tempCommand = new Rotate(v);
			instructions.push_back(tempCommand);
		}
		else if (word.find("RIGHT") != string::npos)
		{
			ss >> word;
			v = getCommandValue(word);
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
			tempCommand = new Repeat((int)v);
			instructions.push_back(tempCommand);
		}
		
		if (word.find("]") != string::npos)
		{
			tempCommand = new Repeat((int)-1);
			instructions.push_back(tempCommand);
		}
	}
}
