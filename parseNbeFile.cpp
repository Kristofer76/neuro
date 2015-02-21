#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <complex>
#include <ctime>

using std::vector;
using namespace std;

struct HeadCoord
{
	double coords[3];
	double norm[3];
	double dir[3];
	double loc[3];
};

vector<HeadCoord> parseNbe(char* path)
{
	char a[100000];
	double b;
	vector<HeadCoord> data;
	HeadCoord HeadData;
	
	ifstream F;
	F.open(path, ios::in);

	//read not useful strings
	for (int i=0; i<6; i++)
		F.getline(a,10000);

	//read not useful words in the first informative string
	for (int i=0;i<10;i++)
		F>>a;
	
	//read our values and write them in structure
	F>>b;
	HeadData.coords[0]=b;
	F>>b;
	HeadData.coords[1]=b;
	F>>b;
	HeadData.coords[2]=b;
	F>>b;
	HeadData.norm[0]=b;
	F>>b;
	HeadData.norm[1]=b;
	F>>b;
	HeadData.norm[2]=b;
	F>>b;
	HeadData.dir[0]=b;
	F>>b;
	HeadData.dir[1]=b;
	F>>b;
	HeadData.dir[2]=b;
	F>>b;
	HeadData.loc[0]=b;
	F>>b;
	HeadData.loc[1]=b;
	F>>b;
	HeadData.loc[2]=b;

	data.push_back(HeadData);

	//again useless symbols
	for (int i=0;i<14;i++)
		F>>a;

	while (!F.eof())
	{
		//read not useful words in the informative string
		for (int i=0;i<10;i++)
			F>>a;

		//now we gonna read and write
		F>>b; 
		HeadData.coords[0]=b;
		F>>b;
		HeadData.coords[1]=b;
		F>>b; 
		HeadData.coords[2]=b;
		F>>b;
		HeadData.norm[0]=b;
		F>>b; 
		HeadData.norm[1]=b;
		F>>b;
		HeadData.norm[2]=b;
		F>>b;
		HeadData.dir[0]=b;
		F>>b;
		HeadData.dir[1]=b;
		F>>b;
		HeadData.dir[2]=b;
		F>>b;
		HeadData.loc[0]=b;
		F>>b;
		HeadData.loc[1]=b;
		F>>b;
		HeadData.loc[2]=b;
		//end of exercise

		//again useless symbols
		for (int i=0;i<14;i++)
			F>>a; 
		
		data.push_back(HeadData);
	}

	//delete last wrong extra data
	data.erase(data.begin()+data.size()-1);

	F.close();

	return data;
}
	
int main()
{
	char path[10000];
	int n;
	vector<HeadCoord> data;

	cout<<"How many files do you want to check at once?"<<endl;
	cin>>n;

	//if we need to analyse few files at once
	for (int i=0; i<n; i++)
	{
		cout<<"Enter the path to the file"<<endl;	
		cin>>path;

	// check ----------------------------------------------------------
		ifstream F;
		F.open(path, ios::in);
		if (F==NULL)
		{
			perror("can't open");
			return -1;
		}
		F.close();
	//-----------------------------------------------------------------	

		vector<HeadCoord> input=parseNbe(path);

		for (int j=0; j<input.size(); j++)
			data.push_back(input[j]);
	}

	//let's watch what we have
	for (int i=0; i<data.size(); i++)
		cout<<"coord (x): "<<data[i].coords[0]<<endl; 
}
