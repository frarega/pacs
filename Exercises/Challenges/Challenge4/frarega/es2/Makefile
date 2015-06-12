CXXFLAGS = -std=c++11

main: main.cpp  polyEvaluator.hpp  polynomial.hpp  polynomial_imp.hpp  pow.hpp  scalar.hpp
	$(CXX) $(CXXFLAGS) -O3 -o $@ main.cpp

.PHONY: clean

clean:
	$(RM) main
