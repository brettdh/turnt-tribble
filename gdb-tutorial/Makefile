CXXFLAGS = -Wall -g -pthread -ldl --std=c++11
LDFLAGS = libcpu.a -ldl -pthread 

all: gdb_demo handout

handout: handout.o thread.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

gdb_demo: parent.o child.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f parent.o child.o handout.o gdb_demo handout
