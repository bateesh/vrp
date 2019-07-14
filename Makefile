all: 
	g++ -c src/utility.cpp -o utility.o -I include
	g++ -c src/CVRPBruteForceSolver.cpp -o CVRPBruteForceSolver.o -I include
	g++ -c src/CVRPVehicleOutput.cpp -o CVRPVehicleOutput.o -I include
	g++ -c src/CVRPInput.cpp -o CVRPInput.o -I include
	g++ CVRPBruteForceSolver.o utility.o CVRPVehicleOutput.o CVRPInput.o -o CVRPBruteForceSolver 

clean:
	rm -f utility.o
	rm -f test.o
	rm -f CVRPBruteForceSolver
	rm -f CVRPVehicleOutput.o
	rm -f CVRPInput.o
