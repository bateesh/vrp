all: 
	g++ -c -g src/utility.cpp -o utility.o -I include
	g++ -c -g src/CVRPBruteForceSolver.cpp -o CVRPBruteForceSolver.o -I include
	g++ -c -g src/CVRPVehicleOutput.cpp -o CVRPVehicleOutput.o -I include
	g++ -c -g src/CVRPInput.cpp -o CVRPInput.o -I include
	g++ -c -g src/TSPSolver.cpp -o TSPSolver.o -I include
	g++ -c -g src/TSPEuc2Approximation.cpp -o TSPApprox.o -I include
	g++ -c -g src/CVRPSweepAlgorithm.cpp -o CVRPSweepAlgorithm.o -I include
	g++ -c -g src/CVRPClarkeAndWrightSavingsSolver.cpp -o CVRPClarkeAndWrightSavingsSolver.o -I include
	g++ -c -g src/CVRPClarkeAndWrightHeuristicSolver.cpp -o CVRPClarkeAndWrightHeuristicSolver.o -I include
	g++ -c -g src/CentroidBased3Phase.cpp -o CentroidBased3Phase.o -I include
	g++ -c -g src/temp.cpp -o temp.o -I include
	g++ -c -g src/CVRPClusterringImplementation.cpp -o CVRPClusterringImplementation.o -I include
	g++ -c -g src/CentroidBasedCompleteHeuristic.cpp -o CentroidBasedCompleteHeuristic.o -I include
	g++ -c -g src/CVRPTweaked.cpp -o CVRPTweaked.o -I include
	g++ -c -g src/CVRP1.5Approx.cpp -o CVRP1.5Approx.o -I include
	g++ -g CVRPBruteForceSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o -o CVRPBruteForceSolver
	g++ -g CVRPTweaked.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPTweaked 
	g++ -g CVRPClarkeAndWrightSavingsSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolver 
	g++ -g CVRP1.5Approx.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRP1.5Approx 
	g++ -g CVRPClarkeAndWrightHeuristicSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightHeuristicSolver 
	g++ -g TSPApprox.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolverTSPApprox
	g++ -g CentroidBasedCompleteHeuristic.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CentroidBasedCompleteHeuristic 
	g++ -g CVRPSweepAlgorithm.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPSweepAlgorithm 
	g++ -g temp.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o temp 
	g++ -g CVRPClusterringImplementation.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClusterringImplementation 
	g++ -g CentroidBased3Phase.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CentroidBased3Phase 

clean:
	rm -f utility.o
	rm -f test.o
	rm -f CVRPBruteForceSolver
	rm -f CVRPVehicleOutput.o
	rm -f CVRPInput.o
	rm -f CVRPClarkeAndWrightSavingsSolver.o
	rm -f CVRPClarkeAndWrightSavingsSolver
	rm -f TSPSolver
	rm -f CVRPSweepAlgorithm
	rm -f CVRPSweepAlgorithm.o
