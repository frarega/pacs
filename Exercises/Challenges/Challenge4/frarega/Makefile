DEPS = polynomial.hpp
OBJ = polynomial.o
CXXFLAGS = -std=c++11
SOURCE = main.cpp

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 
main: $(OBJ) $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	$(RM) $(OBJ) main
