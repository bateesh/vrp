#include "utility.h"
int main(int argc, char *argv[])
{
	
	vector< vector<int> > data=readFile("../data.txt"); 
	int size= data.size();
	cout<<" Total number of data is :"<<size;
	
}
