CXXFLAGS = -std=c++11

main: polynomial.o main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ 

polynomial.o: polynomial.cpp polynomial.hpp scalar.hpp
	$(CXX) $(CXXFLAGS) -c -o polynomial.o polynomial.cpp

.PHONY: clean

clean:
	$(RM) polynomial.o main
