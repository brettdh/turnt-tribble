CXXFLAGS = -Wall -g -pthread --std=c++11

all: leaky

leaky: leaky.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o leaky
