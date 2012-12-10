/******************************************************************************
  
  Command.h
  
  Class definitions for 'Command', 'Forward', 'Rotate', 'Jump', 'Repeat'. These
  classes determine how each command is executed by the program.
  
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
#include "Prog.h"


class Command : public Node
{
	private:
		float value;
	public:
		Command();
		Command(float value);
		
		~Command();
		
		friend istream& operator>> (std::istream& in, Command &c);
		
		virtual void run() = 0;
};


class Forward : public Command
{
	public:
		Forward();
		Forward(float value);
	
		~Forward();
	
		void run();
};


class Jump : public Command
{
	public:
		Jump();
		Jump(float value);
	
		~Jump();
	
		void run();
};


class Rotate : public Command
{
	public:
		Rotate();
		Rotate(float value);
	
		~Rotate();
	
		void run();
};


class Repeat : public Command
{
	private:
		Prog *subset;
	public:
		Repeat();
		Repeat(std::ifstream &infile, float value);
	
		~Repeat();
	
		void run();
};
