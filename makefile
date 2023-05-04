main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o main

CXX: clang++

unit_test: unit_test_driver.o 
	$(CXX) unit_test_driver.o

memoryleaktest:
	valgrind --tool=memcheck ./main arg1 arg2 arg3
