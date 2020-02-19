#include "TSPSolver.h"
#include "utility.h"
double getCandidateTourLength(vector<int> tour, double **originalGraph, int numCities);
void rvereseArray(vector<int> &arr, int start, int end);
void printTour(vector<int> tour);
//double distanceTableTSP[10][10];
TSPSolver::TSPSolver(vector<vector<double>> n,vector<double> d)
{
    cout<<"\n In TSP Constructor:";
    nodes = n;
    depot=d;
    locationToIndexMap[{d[0],d[1]}]=0;
    for(int i=0;i<n.size();i++)
    {
        double from=n[i][0];
        double to=n[i][1];
        locationToIndexMap[{from,to}]=i+1;
    }
    vector<vector<double>> data;
    data.push_back(d);
    for(int i=0;i<n.size();i++)
    {
       data.push_back(n[i]);
    }

    getLiveDistanceTableTSP(data, distanceTableTSP);
    cout<<"\n Procesing done successfully";
    cout<<"\n Location to index map processed succeffuly";
}

double TSPSolver::getDistance(int x,int y)
{
    //cout<<"\n input index for request is :"<<x<<" , "<<y;
    //cout<<"\nvalue at that location is :"<<distanceTableTSP[x][y];
    //cin>>x;
    //cout<<endl;
    //cout<<" \ndone\n";
    return distanceTableTSP[x][y];
          
            /*double px = x[0];
            double py = x[1];
            double dx = y[0];
            double dy = y[1];
            double a = px - dx;
            double b = py - dy;
            double distance = sqrt(pow(a, 2) + pow(b, 2));
            return distance;*/
}

vector<vector<double>> TSPSolver::solveTSP()
{
    cout<<"\n yes solving";
    int numCities = nodes.size();

    int i;
    double **originalGraph = (double **)malloc(sizeof(double *) * (numCities));
    for (int i = 0; i < numCities; i++)
        originalGraph[i] = (double *)malloc((numCities) * sizeof(double));
    i = 0;
    int j;
    for (i = 0; i < numCities; i++)
    {
        for (j = 0; j < numCities; j++)
        {
            vector<double> x = nodes[i];
            vector<double> y = nodes[j];
            int from=locationToIndexMap[{x[0],x[1]}];
            int to=locationToIndexMap[{y[0],y[1]}];
          
            double distance = getDistance(from,to);
            originalGraph[i][j] = distance;
        }
    }
    vector<int> initialTour;
    for (int i = 0; i < numCities; i++)
        initialTour.push_back(i);

    int initalCost = getCandidateTourLength(initialTour, originalGraph, numCities);
    int from=locationToIndexMap[{depot[0],depot[1]}];
    int to=locationToIndexMap[{nodes[*initialTour.begin()][0],nodes[*initialTour.begin()][1]}];
    initalCost+=getDistance(from,to );
    to=locationToIndexMap[{nodes[*(initialTour.end()-1)] [0],nodes[*(initialTour.end()-1)] [1]}];
    initalCost+=getDistance(from,to);

    double currentCost = INT_MAX;
    vector < int > tour;
	
    /* Iterative hill climbing to always start with random tour and find best until local minima arrives*/
    cout<<"\n stated hill climbing now";
	for (int k = 1; k <= 5; k++)
	
	{

        tour.clear();
        cout<<"\n running iteration number "<<k<<endl;
	srand(time(NULL));
    //cout<<"1";
	int kkk;
    //cin>>kkk;
	//Generate random tour
	int first = (int)(rand() % numCities);
   // cout<<"2";
	tour.push_back(first);
	int cityAdded = 1;
    //cout<<"3";
    //cout<<"\n Waiting for new input";
	while (cityAdded != numCities) {
	int r = (int)(rand() % numCities);
	vector < int > ::iterator it;
	it = find(tour.begin(), tour.end(), r);
	if (it == tour.end()) {
	tour.push_back(r);
	cityAdded++;
	}
	
	}
    cout<<"4";
    cout<<" \n new inut done \n";
	
	/* if(k==1)
	printTour(tour);*/
    cout<<"\n current tour is ";printTour(tour);
	int improvement = 0;
    cout<<"\n cities rae :"<<numCities;
    int yy;
//    cin>>yy;
    
	for (i = 0; i < numCities; i++) {
	
	for (int k = (i + 1) % numCities; k != i; k = (k + 1) % numCities) {
	if (k - i == 1 || i - k == 1 || k == i) {
	continue;
	}
	cout<<"\n done here also";
    cout<<"\n now it will try to reaplace "<<i<<" ->"<<(i + 1) % numCities<<" and : "<<k<<"->"<<(k + 1) % numCities;
    cout<<"\n with "<<i<<" ->"<<k<<" and : "<<(i + 1) % numCities<<"->"<<(k + 1) % numCities;
	int oldEdgesCost = originalGraph[tour[i]][tour[(i + 1) % numCities]] + originalGraph[tour[k]][tour[(k + 1) % numCities]];
	int newEdgesCost = originalGraph[tour[i]][tour[k]] + originalGraph[tour[(i + 1) % numCities]][tour[(k + 1) % numCities]];

cout<<"\n old : "<<oldEdgesCost<<" new :"<<newEdgesCost;
//cin>>yy;
if(oldEdgesCost<0 || newEdgesCost<0 ||originalGraph[tour[i]][tour[(i + 1) % numCities]]<0 || originalGraph[tour[k]][tour[(k + 1) % numCities]]<0 || originalGraph[tour[i]][tour[k]]<0 ||originalGraph[tour[(i + 1) % numCities]][tour[(k + 1) % numCities]]<0)
continue;
	if (newEdgesCost < oldEdgesCost) {
        cout<<"\n yes improvement";
        cout<<" cost are i,i+1\n"<<originalGraph[tour[i]][tour[(i + 1) % numCities]];
        cout<<" cost are k,k+1\n"<<originalGraph[tour[k]][tour[(k + 1) % numCities]];
        cout<<" cost are i,k\n"<<originalGraph[tour[i]][tour[k]];
        cout<<" cost are i+1,k+1\n"<<originalGraph[tour[(i + 1) % numCities]][tour[(k + 1) % numCities]];
	improvement = 1;
    vector<int> tempTour=tour;
	k > i ? rvereseArray(tour, i + 1, k) : rvereseArray(tour, k + 1, i);
    if(getCandidateTourLength(tour,originalGraph, numCities)<getCandidateTourLength(tempTour,originalGraph, numCities))
    {

    }
    else
    {
        tour=tempTour;
        improvement=0;
    }
    
	cout<<"\n current tour is ";printTour(tour);
	}
	
	}
	if (improvement)
	i = -1;
	improvement = 0;
	}
	//cout<<"5";
	double newCost = getCandidateTourLength(tour, originalGraph, numCities);
//cout<<"\n length os tour s :";
    //cout<<"6";
     to=locationToIndexMap[{nodes[*tour.begin()][0],nodes[*tour.begin()][1]}];
    //cout<<"7";
  //  cout<<"\n now getting distance of locations"<<from<<" "<<to;

    newCost+=getDistance(from,to);
    //cout<<"\n here next is "<<*(tour.end()-1);
    //cout<<"\n here next is "<<*tour.end()-1;
    //cout<<"8";
    //cout<<"\n now getting distance of locations"<<from<<" "<<to;

     to=locationToIndexMap[{nodes[*(tour.end()-1)][0],nodes[*(tour.end()-1)][1]}];
     //cout<<"9";
    //cout<<"\n length os tour t: ";
    newCost+=getDistance(from,to);
  //  cout<<"10";
  //  cout<<"11";

	if (newCost < currentCost) {
	currentCost = newCost;
	//printTour(tour);
	}
    //cout<<"\n ending iteration "<<k<<endl;
	}

    vector<vector<double>> result;
    if(currentCost>initalCost)
    tour=initialTour;

    for(int i=0;i<numCities;i++)
    result.push_back(nodes[tour[i]]);

    cout<<"\n TSP completed for given data.Returning optimal tour found..";
    return result;


	}
	
void printTour(vector<int> tour)
{
    for (int i = 0; i < tour.size(); i++)
        cout << tour[i] << " ";
    cout << endl;
}

void rvereseArray(vector<int> &arr, int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
double getCandidateTourLength(vector<int> tour, double **originalGraph, int numCities)
{
    double tourLength = 0;

    vector<int>::iterator it = tour.begin();
    it = tour.begin();
    int pcity = *it, ncity;
    int first = *it;

    for (it = tour.begin() + 1; it != tour.end(); it++)
    {
        ncity = *it;
        tourLength += originalGraph[pcity][ncity];

        pcity = ncity;
    }

    return tourLength;
}
