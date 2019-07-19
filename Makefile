all: 
	g++ -c src/utility.cpp -o utility.o -I include
	g++ -c src/CVRPBruteForceSolver.cpp -o CVRPBruteForceSolver.o -I include
	g++ -c src/CVRPVehicleOutput.cpp -o CVRPVehicleOutput.o -I include
	g++ -c src/CVRPInput.cpp -o CVRPInput.o -I include
	g++ -c src/TSPSolver.cpp -o TSPSolver.o -I include
	g++ -c src/CVRPSweepAlgorithm.cpp -o CVRPSweepAlgorithm.o -I include
	g++ -c src/CVRPClarkeAndWrightSavingsSolver.cpp -o CVRPClarkeAndWrightSavingsSolver.o -I include
	g++ -c src/temp.cpp -o temp.o -I include
	g++ CVRPBruteForceSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o -o CVRPBruteForceSolver 
	g++ CVRPClarkeAndWrightSavingsSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o TSPSolver.o -o CVRPClarkeAndWrightSavingsSolver 
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