DEPS = polynomial.hpp polynomial_imp.hpp scalar.hpp
CXXFLAGS = -std=c++11
SOURCE = main.cpp

main: $(SOURCE) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCE)

.PHONY: clean

clean:
	$(RM) main
