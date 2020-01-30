#include "TSPSolver.h"
double getCandidateTourLength(vector<int> tour, double **originalGraph, int numCities);
void rvereseArray(vector<int> &arr, int start, int end);
void printTour(vector<int> tour);

TSPSolver::TSPSolver(vector<vector<double>> n,vector<double> d)
{
    nodes = n;
    depot=d;
}

double getDistance(vector<double> x,vector<double> y)
{
          
            double px = x[0];
            double py = x[1];
            double dx = y[0];
            double dy = y[1];
            double a = px - dx;
            double b = py - dy;
            double distance = sqrt(pow(a, 2) + pow(b, 2));
            return distance;
}

vector<vector<double>> TSPSolver::solveTSP()
{
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
          
            double distance = getDistance(x,y);
            originalGraph[i][j] = distance;
        }
    }
    vector<int> initialTour;
    for (int i = 0; i < numCities; i++)
        initialTour.push_back(i);

    int initalCost = getCandidateTourLength(initialTour, originalGraph, numCities);
    initalCost+=getDistance(depot,nodes[*initialTour.begin()] );
    initalCost+=getDistance(depot,nodes[*(initialTour.end()-1)] );

    double currentCost = INT_MAX;
    vector < int > tour;
	
    /* Iterative hill climbing to always start with random tour and find best until local minima arrives*/
	for (int k = 1; k <= 85; k++)
	
	{
        tour.clear();
      //  cout<<"\n running iteration number "<<k<<endl;
	srand(time(NULL));
	
	//Generate random tour
	int first = (int)(rand() % numCities);
	tour.push_back(first);
	int cityAdded = 1;
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
    //cout<<" \n new inut done \n";
	
	/* if(k==1)
	printTour(tour);*/
	int improvement = 0;
	for (i = 0; i < numCities; i++) {
	
	for (int k = (i + 1) % numCities; k != i; k = (k + 1) % numCities) {
	if (k - i == 1 || i - k == 1 || k == i) {
	continue;
	}
	
	int oldEdgesCost = originalGraph[tour[i]][tour[(i + 1) % numCities]] + originalGraph[tour[k]][tour[(k + 1) % numCities]];
	int newEdgesCost = originalGraph[tour[i]][tour[k]] + originalGraph[tour[(i + 1) % numCities]][tour[(k + 1) % numCities]];
	
	if (newEdgesCost < oldEdgesCost) {
	improvement = 1;
	k > i ? rvereseArray(tour, i + 1, k) : rvereseArray(tour, k + 1, i);
	
	}
	
	}
	if (improvement)
	i = -1;
	improvement = 0;
	}
	
	double newCost = getCandidateTourLength(tour, originalGraph, numCities);
    newCost+=getDistance(depot,nodes[*tour.begin()] );
    newCost+=getDistance(depot,nodes[*(tour.end()-1)] );

	if (newCost < currentCost) {
	currentCost = newCost;
	//printTour(tour);
	}
	}

    vector<vector<double>> result;
    if(currentCost>initalCost)
    tour=initialTour;

    for(int i=0;i<numCities;i++)
    result.push_back(nodes[tour[i]]);

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
