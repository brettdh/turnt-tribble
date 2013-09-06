CXXFLAGS = -Wall -g -pthread --std=c++11

all: pimpl_demo

pimpl_demo: foo.o fooImpl.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o pimpl_demo
