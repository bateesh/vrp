#include "utility.h"


using namespace std;

// extract the first number in a string
int extract_int(const string &term) {
    size_t start_p = term.find_first_of("-0123456789"); 
    int i;
    istringstream(term.substr(start_p, term.size() - start_p)) >> i;
    return i;
}

// extract all numbers in a string
vector<int> extract_ints(const string &term) {
	// split string term into string vector by spaces
    istringstream ss(term);
    string token;
    vector<int> data;
    while(getline(ss, token, ' ')) 
        data.push_back(extract_int(token));
    return data;
}

// read CVRP data file and parse to a vector
// first vector contains dimension and capacity
// next 'dimension' vectors contain locations (x, y)
// then the customer demands (demand)
vector< vector<int> > readFile(const char *path) {
    ifstream file(path);
    string line;
    vector< vector<int> > data;

    vector<int> constraint;
    // read the first line and second line to get the dimension and capacity
    getline(file, line);
    // extract demand
    constraint.push_back(extract_int(line));
    getline(file, line);
    // extract capacity
    constraint.push_back(extract_int(line));
    data.push_back(constraint);
    
    // ignore the node section start line
    file.ignore(256, '\n');
   
    // extract locations
    for (int i = 0; i < constraint[0]; ++i) {
        getline(file, line);
        vector<int> p = extract_ints(line);
        // p[1]: x-coordinate, p[2]: y-coordinate
        // -> p[0]: x, p[1]: y
        p.erase(p.begin());
        data.push_back(p);
    }
    	cout<<" in Total number of data is :"<<data.size();
    	cout<<" capacity is  :"<<constraint[0];

    
    //ignore the demand section start line	
    file.ignore(256, '\n');

    vector<int> demand;
    // read the customer demand to the 1D array
    for (int j = 0; j < constraint[0]; ++j) {
        getline(file, line);
	demand.push_back(extract_ints(line)[1]);
    }
    data.push_back(demand);
   
    return data;
}
