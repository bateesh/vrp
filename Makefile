all: 
	g++ -c src/utility.cpp -o bin/utility.o -I include
	g++ -c src/test.cpp -o bin/test.o -I include
	g++ bin/test.o bin/utility.o  -o bin/test 

clean:
	rm -f bin/utility.o
	rm -f bin/test.o
	rm -f bin/test
