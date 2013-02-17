CXXFLAGS := -g -Wall -std=c++98
CXX := c++

all: cachesim

cachesim.o : cachesim.cpp cachesim.hpp Cache_State.h
cachesim_driver.o : cachesim_driver.cpp cachesim.hpp
Cache_State.o : Cache_State.cpp Cache_State.h LRU.h NMRU_FIFO.h Tag_Store.h cachesim.hpp
LRU.o : LRU.cpp LRU.h Tag_Store.h
NMRU_FIFO.o : NMRU_FIFO.cpp NMRU_FIFO.h Tag_Store.h
Tag_Store.o : Tag_Store.cpp Tag_Store.h

cachesim: cachesim.o cachesim_driver.o Cache_State.o LRU.o NMRU_FIFO.o Tag_Store.o
	$(CXX) -o cachesim -lm cachesim.o cachesim_driver.o Cache_State.o LRU.o NMRU_FIFO.o Tag_Store.o

test: test_astar test_bzip2 test_mcf test_perlbench

test_astar: cachesim
	@rm -rf myoutput/atar.out
	@mkdir -p myoutput
	./cachesim -c 15 -b 5 -s 3 -f E -r L < traces/astar.trace > myoutput/astar.out
	@diff output/astar.out myoutput/astar.out || echo "astar failed"


test_bzip2: cachesim
	@rm -rf myoutput/bzip2.out
	@mkdir -p myoutput
	./cachesim -c 15 -b 6 -s 5 -f B -r N < traces/bzip2.trace > myoutput/bzip2.out
	@diff output/bzip2.out myoutput/bzip2.out || echo "bzip2 failed"

test_mcf: cachesim
	@rm -rf myoutput/mcf.out
	@mkdir -p myoutput
	./cachesim -c 15 -b 4 -s 5 -f E -r N < traces/mcf.trace > myoutput/mcf.out
	@diff output/mcf.out myoutput/mcf.out || echo "mcf failed"


test_perlbench: cachesim
	@rm -rf myoutput/perlbench.out
	@mkdir -p myoutput
	./cachesim -c 10 -b 4 -s 5 -f B -r L < traces/perlbench.trace > myoutput/perlbench.out
	@diff output/perlbench.out myoutput/perlbench.out || echo "perlbench failed"


clean:
	rm -rf cachesim *.o myoutput
