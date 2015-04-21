#include <iostream>	
#include "polynomial.hpp"

using namespace std;

template<unsigned N, unsigned M>
void test(polynomial<N> a, polynomial<M> b)
{
	cout << "a = "<< a << endl;
	cout << "\tdegree: " << a.GetDegree()<< endl;
	cout << "\tconstant term: " << a.GetCoefficient(0)<< endl;
	cout << "a(0) = " << a(0) << endl;
	cout << "a(1) = " << a(1) << endl;
	cout << "a(-1) = " << a(-1) << endl;
	cout << "a(0.5) = " << a(0.5) << endl<<endl;
	cout << "b = "<< b << endl;
	cout << "\tdegree: " << b.GetDegree()<< endl;
	cout << "\tconstant term: " << b.GetCoefficient(0)<< endl;
	cout << "b(0) = " << b(0) << endl;
	cout << "b(1) = " << b(1) << endl;
	cout << "b(-1) = " << b(-1) << endl;
	cout << "b(0.5) = " << b(0.5) << endl<<endl;
	cout << "a+b = "<< a+b << endl;
	cout << "a-d = "<< a-b << endl;
	try
	{
		cout << "a+=b: "<< (a+=b) << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	cout << "a = "<< a << endl;
	try
	{
		cout << "a-=b: "<< (a-=b) << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	cout << "a = "<< a << endl;
	cout << "a++ = "<< a++ << endl;
	cout << "a = "<< a << endl;
	cout << "++a = "<< ++a << endl;
	cout << "a = "<< a << endl;
	cout << "a-- = "<< a-- << endl;
	cout << "a = "<< a << endl;
	cout << "--a = "<< --a << endl;
	cout << "a = "<< a << endl;
	cout << "a*b: "<< a*b << endl;
	cout << "a/b:" << endl;
	try
	{
		auto div1= a/b;
		cout << "\tquotient = " << div1.first << endl << "\tremainder = "<< div1.second << endl;
		cout << "\ttest: quotient*dividend+remainder= " << div1.first* b + div1.second << endl;
 	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	cout << "b/a:" << endl;
	try
	{
		auto div2= b/a;
		cout << "\tquotient = " << div2.first << endl << "\tremainder = "<< div2.second << endl;
		cout << "\ttest: quotient*dividend+remainder= " << div2.first* a + div2.second << endl;
 	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	cout<<endl;	
}

int main()
{
	test(polynomial<2>({-1,1,0}),polynomial<2>({0}));
	test(polynomial<2>({3,4,5}),polynomial<1>({2,3}));

	cout << "Insert a 4th degree polynomial:"<<endl;
	polynomial<4> a;
	cin>>a;
	cout << "Now insert a 3th degree polynomial:"<<endl;
	polynomial<3> b;
	cin>>b;
	test(a,b);

	return 0;
}

