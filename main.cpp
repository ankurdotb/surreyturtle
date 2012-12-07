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


class node
{
	virtual node() {};
	virtual ~node() {};
	virtual void run()=0;
};


class Prog
{
	vector<node*> listing;
	Prog();
	~Prog();
	void run();
	friend std::istream& operator>> (std::istream& in, command& a);
};


class command : public node
{
	float v;
	command();
	~command();
	friend std::istream& operator>> (std::istream& in, command& a);
};


class forward : public command
{
	void run();
};


class jump : public command
{

	void run();
};


class rotate : public command
{
	void run();
};


class repeat : public command
{
	Prog pg;
};


Prog p;
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
 	
 	ifstream in(argv[1]);
 	in>>p;
 	in.close();
	window w(argc,argv);
	
	return 0;
}

