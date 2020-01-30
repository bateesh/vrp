all: 
	g++ -c -g src/CVRPTWNode.cpp -o CVRPTWNode.o -I include
	g++ -c -g src/CVRPTW.cpp -o CVRPTW.o -I include
	g++ -c -g src/utility.cpp -lcurl -ljsoncpp -o utility.o -I include 
	g++ -c -g src/CVRPVehicleOutput.cpp -o CVRPVehicleOutput.o -I include
	g++ -c -g src/CVRPInput.cpp -o CVRPInput.o -I include
	g++ -c -g src/TSPSolver.cpp -o TSPSolver.o -I include
	g++ -c -g src/CVRPClarkeAndWrightSavingsSolver.cpp -o CVRPClarkeAndWrightSavingsSolver.o -I include
	g++ -g CVRPClarkeAndWrightSavingsSolver.o utility.o CVRPTW.o CVRPTWNode.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolver -lcurl -ljsoncpp
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
