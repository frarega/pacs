#include <iostream>	
#include "polynomial.hpp"

int main()
{
	using namespace std;
	
	polynomial<2> a({-1 , 1 ,0}), b({0}),c({3,4,5});
	polynomial<1> d({2,3});

	//polynomial<3> e(a);
	/*std::cout << "Insert new polynomial:"<<endl;
	polynomial<4> e;
	std::cin>>e;
	std::cout << "e = "<< e << endl;*/

	std::cout << "a = "<< a << " degree: " << a.GetDegree()<< endl;
	std::cout << "b = "<< b << " degree: " << b.GetDegree()<< endl;
	std::cout << "c = "<< c << " degree: " << c.GetDegree()<< endl;
	std::cout << "d = "<< d << " degree: " << d.GetDegree()<< endl;
	std::cout <<(a-d)<<endl;
	std::cout <<(d-a)<<endl;
	std::cout <<(d-d)<<endl;
	std::cout <<(d+d)<<endl;
	std::cout <<-c<<endl;
	a-=c;	
	std::cout << "a = "<< a << " degree: " << a.GetDegree()<< endl;
	std::cout <<(c-=d)<<endl;
	auto prod1=a*b;
	auto prod2=b*c;
	auto prod3=d*b;
	auto prod4=a*d;
	std::cout <<prod1<<endl;
	std::cout <<prod2<<endl;
	std::cout <<prod3<<endl;
	std::cout <<prod4<<endl;

	
	std::cout << "a = "<< a << " degree: " << a.GetDegree()<< endl;
	std::cout <<a(1)<<endl;
	std::cout <<d(0)<<endl;
	std::cout <<d(-1)<<endl;
	std::cout <<d(0.5)<<endl;
	std::cout <<b(1)<<endl;

	auto div1=a/b;
	//std::cout << "e = "<< e << " degree: " << e.GetDegree()<< endl;
/*
	std::cout << "Insert new polynomial:"<<endl;
	polynomial e;
	std::cin>>e;
	std::cout << "e = "<< e << endl;	
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
	cout << q << " / " << w << " :" << endl<< "quotient = " << div.first << endl << "remainder = "<< div.second << endl<< endl;

	auto div2=w/q;
	cout << w << " / " << q << " : " << endl<< "quotient = " << div2.first << endl << "remainder = "<< div2.second << endl<< endl;

	auto div4 = q/polynomial({2});
	cout << q << " / 2 : " << endl<< "quotient = " << div4.first << endl << "remainder = "<< div4.second << endl<< endl;
	*/

	return 0;
}
