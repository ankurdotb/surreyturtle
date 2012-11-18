// assign1011.cpp : Defines the entry point for the console application.
//

#include "window.h"
//#include "trial.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

void translate(float,float,float);
void drawing();
void rotating();

class trial;
static vector<string> tokens;
//static trial t(tokens);


class trial {

private:
 float x2;float y2;float z2;
 vector<string> trialVector;
public:
	trial(float,float,float);
	trial(vector<string>);	
	trial();	
	~trial(){};

	void readFile();
	void trialTranslating(float);
	void trialRotatingLeft(string);
	void trialDrawing(string);
	void logic();

};

trial::trial(){
}

trial::trial(vector<string> v){
	trialVector=v;
}

//trial::trial(float x3,float y3,float z3){
//x2=x3;y2=y3;z2=z3;
//}

void trial::trialTranslating(float tr){

glTranslatef(tr,0.0f,0.0f);

}

void trial::trialRotatingLeft(string rotate){

	float rt;
	istringstream(rotate) >> rt;
	glRotatef(rt,0,0,1);

}

void trial::trialDrawing(string assign){
	
	//char *sz = new char[assign.size()+1];
	//sz[assign.size()]=0;
	//memcpy(sz,assign.c_str(),assign.size());

	//char strarray[10];
	//for(int l=0;l<assign.length();l++){
	//char strarray=assign[l];
	//double d1 = strtod(strarray,NULL);		
	//double tem = atof(strarray[l].c_str());	
	//}


	float d1;
	istringstream(assign) >> d1;

	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(d1,0.0f);
	glEnd();
	
	trial::trialTranslating(d1);
	

}

void trial::logic(){
	
	string temp;

	for(int index=0;index<trialVector.size();index+=2){
		if(trialVector[index] == "FORWARD"){
			temp = trialVector[index+1];
			trial::trialDrawing(temp);		

		}

		if(trialVector[index] == "LEFT"){
			temp = trialVector[index+1];
			trial::trialRotatingLeft(temp);		

		}	

	}

}

void draw(void)   
{
	trial t2(tokens);
	t2.logic();
	/*	
	for(int j=0;j<7;j++){
	drawing();
	//trial t(0.4,0.0,0.0);	
	//t.trialTranslating();
	translate(0.4f,0.0f,0.0f);
	rotating();
	}
	*/


	//Uncomment this to get curve
	
	/*
	//glTranslatef(0.6f,0.0f,0.0f);

	translate(0.4f,0.0f,0.0f);
	//trial.translate(0.4,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(f,0.0f);
	glEnd();
	glTranslatef(0.4f,0.0f,0.0f);
	glRotatef(10,0,0,1);
	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(f,0.0f);
	glEnd();

	glTranslatef(0.4f,0.0f,0.0f);
	glRotatef(10,0,0,1);
	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(f,0.0f);
	glEnd();*/

}

void translate(float x,float y, float z){
 glTranslatef(x,y,z);
}

void drawing(){

glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(0.4,0.0f);
	glEnd();
}

void rotating(){
glRotatef(10,0,0,1);
}

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
		
	string line;
	string buf;
	//static vector<string> tokens;
	//ifstream myfile("file1.txt");
	ifstream myfile(argv[1]);	
	//cout << argv[1] << endl;
	
	if (myfile.is_open())
	{
		while(myfile.good())
		{
			getline(myfile,line);
			stringstream ss(line);

			

			while(ss>>buf)
			tokens.push_back(buf);
		}

	//trial t(tokens);
	//trial t(tokens);
	myfile.close();
	}
	//trial t(0.4,0.0,0.0);
		

	window w(argc,argv);
	  
}





