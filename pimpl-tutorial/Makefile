CXXFLAGS = -Wall -g -pthread --std=c++11

all: pimpl_demo

pimpl_demo: foo.o fooImpl.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<

-include *.d

clean:
	rm -f *.o *.d pimpl_demo
