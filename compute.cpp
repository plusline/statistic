#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>


#define N 1000
#define filename "data1.txt"
using namespace std;

int main(int argc, char *argv[]){
	cout<<argv[1]<<endl;
	fstream myfile,file;
	myfile.open(argv[1]);
	if(!myfile)cout<<"can't open."<<endl;
	int num;
	double data,sum=0;
	string s;
	int count=0;
	while(myfile>>num){
		myfile>>data;
		myfile>>s;
		sum+=data/N;
	}
	myfile.close();
	
	double deviation=0;
	file.open(argv[1]);
	if(!file)cout<<"file can't open."<<endl;
	while(file>>num){
		file>>data;
		file>>s;
		deviation+=((data-sum)*(data-sum))/N;
	}
	deviation=sqrt(deviation);

	double limit=1.96*deviation*sqrt((pow(2,32)-N)/(pow(2,32)-1)/N);

	cout<<"sum: "<<sum<<endl;
	cout<<"standard deviation: "<<deviation<<endl;
	cout<<"limit: "<<limit<<endl;
	return 0;

}
