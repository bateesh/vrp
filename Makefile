all: 
	g++ -c src/utility.cpp -o utility.o -I include
	g++ -c src/CVRPBruteForceSolver.cpp -o CVRPBruteForceSolver.o -I include
	g++ -c src/CVRPVehicleOutput.cpp -o CVRPVehicleOutput.o -I include
	g++ -c src/CVRPInput.cpp -o CVRPInput.o -I include
	g++ -c src/TSPSolver.cpp -o TSPSolver.o -I include
	g++ -c src/TSPEuc2Approximation.cpp -o TSPApprox.o -I include
	g++ -c src/CVRPSweepAlgorithm.cpp -o CVRPSweepAlgorithm.o -I include
	g++ -c src/CVRPClarkeAndWrightSavingsSolver.cpp -o CVRPClarkeAndWrightSavingsSolver.o -I include
	g++ -c src/CVRPClarkeAndWrightHeuristicSolver.cpp -o CVRPClarkeAndWrightHeuristicSolver.o -I include
	g++ -c src/temp.cpp -o temp.o -I include
	g++ -c src/CVRPTweaked.cpp -o CVRPTweaked.o -I include
	g++ -c src/CVRP1.5Approx.cpp -o CVRP1.5Approx.o -I include
	g++ CVRPBruteForceSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o -o CVRPBruteForceSolver 
	g++ CVRPTweaked.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPTweaked 
	g++ CVRPClarkeAndWrightSavingsSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolver 
	g++ CVRP1.5Approx.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRP1.5Approx 
	g++ CVRPClarkeAndWrightHeuristicSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightHeuristicSolver 
	g++ TSPApprox.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolverTSPApprox
	g++ CVRPSweepAlgorithm.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPSweepAlgorithm 
	g++ temp.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o temp 

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
