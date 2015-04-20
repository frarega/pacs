#include <iostream>
#include "polynomial.hpp"

int main()
{
	using namespace std;
	polynomial a({-1 , 0 ,0 ,1, 0 ,0}), b({0,0,0}),c({}),d({2,3,0,7,9});
	std::cout << "a = "<< a << endl;
	std::cout << "b = "<< b << endl;
	std::cout << "c = "<< c << endl;
	std::cout << "d = "<< d << endl;
	//std::cout << "Insert new polynomial:"<<endl;
	//polynomial e;
	//std::cin>>e;
	//std::cout << "e = "<< e << endl;	
	std::cout << "degree of a = "<< a.GetDegree()<< endl;
	std::cout << "degree of b = "<< b.GetDegree()<< endl;
	std::cout << "degree of c = "<< b.GetDegree()<< endl;
	std::cout << "third coefficient of a = "<< a.GetCoefficient(3)<< endl;
	std::cout << "third coefficient of b = "<< b.GetCoefficient(3)<< endl;
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
	std::cout << "a*d: "<< a*d << endl;
	std::cout << "a*=d = "<< (a*=d) << endl;
	std::cout << "a = "<< a << endl;
	std::cout << "d*b = "<< d*b << endl;

	polynomial q({0 , 0 ,0 ,-1, 3}), w({-2 , 0 ,1});

	auto div= q/w;
	cout << q << " / " << w << " = " << endl<< "quotient = " << div.first << endl << "remainder = "<< div.second << endl<< endl;

	auto div2=w/q;
	cout << w << " / " << q << " = " << endl<< "quotient = " << div2.first << endl << "remainder = "<< div2.second << endl<< endl;

	auto div4 = q/polynomial({2});
	cout << q << " / 2 = " << endl<< "quotient = " << div4.first << endl << "remainder = "<< div4.second << endl<< endl;
	
	auto div3 = q/polynomial({0});
	cout << q << " / 0 = " << endl<< "quotient = " << div3.first << endl << "remainder = "<< div3.second << endl<< endl;

	return 0;
}
