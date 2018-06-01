CXX=g++

CXXFLAGS= -std=c++1z -Wall -g

all: payoff_sched
	
payoff_sched: payoff_solver.o 
	g++ -o payoff_sched payoff_solver.o 

payoff_solver.o: payoff_solver.cpp

clean:
	rm -rf *.o payoff_solver