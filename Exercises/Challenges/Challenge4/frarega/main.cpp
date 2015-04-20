#include <iostream>
#include <stdio.h>
#include "polynomial.hpp"

int main()
{
	using namespace std;
	polynomial a({-1 , 0 ,0 ,1, 0 ,0}), b({0,0,0}),c({}),d({2,3,0,7,9});
	std::cout << "a = "<< a << endl;
	std::cout << "b = "<< b << endl;
	std::cout << "c = "<< c << endl;
	std::cout << "d = "<< d << endl;
	std::cout << "degree of a = "<< a.GetDegree()<< endl;
	std::cout << "degree of b = "<< b.GetDegree()<< endl;
	std::cout << "degree of c = "<< b.GetDegree()<< endl;
	std::cout << "coefficient n 3 = "<< a.GetCoefficient(3)<< endl;
	std::cout << "coefficient n 3 = "<< b.GetCoefficient(3)<< endl;
	std::cout << "a(0) = "<< a(0)<< endl;
	std::cout << "a(1) = "<< a(1)<< endl;
	std::cout << "a(-0.5) = "<< a(-0.5)<< endl;
	std::cout << "b(100) = "<< b(100)<< endl;
	std::cout << "b(0) = "<< b(0)<< endl;
	std::cout << "a+d: "<< a+d << endl;
	std::cout << "a+=d = "<< (a+=d) << endl;
	std::cout << "a-d = "<< a-d << endl;
	std::cout << "a-=d = "<< (a-=d) << endl;
	std::cout << "a++ = "<< a++ << endl;
	std::cout << "a = "<< a << endl;
	std::cout << "++a = "<< ++a << endl;
	std::cout << "a = "<< a << endl;
	std::cout << "a-- = "<< a-- << endl;
	std::cout << "a = "<< a << endl;
	std::cout << "--a = "<< --a << endl;
	std::cout << "a = "<< a << endl;
	
	return 0;
}
