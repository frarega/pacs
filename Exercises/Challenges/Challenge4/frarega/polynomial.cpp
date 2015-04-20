#include <iostream>
#include <math.h>
#include "polynomial.hpp"

polynomial::polynomial(): c() {};

//polynomial::polynomial(std::vector<scalar> v): c(v) {};
	
polynomial::polynomial(std::initializer_list<scalar> l): c(l) { trimZeros(); };

polynomial & polynomial::operator +=(polynomial const & p) { return algebraicplusequal<1>(p); }

polynomial & polynomial::operator -=(polynomial const & p) { return algebraicplusequal<-1>(p); }

polynomial & polynomial::operator /=(polynomial const & p)
{

}

polynomial & polynomial::operator *=(polynomial const & p)
{
	
}

polynomial polynomial::operator-() const
{
	polynomial ret(*this);
	for (auto it=ret.c.begin(); it<ret.c.end(); it++) *it*=-1;
	return ret; //no need of normalization	
}

polynomial polynomial::operator+() const
{
	return *this;
}

polynomial & polynomial::operator++()
{
	c[0]++;
	return *this; //no need of normalization (as policy, even if the polinomial equals 0, c contains one element)
}

polynomial polynomial::operator++(int)
{
	polynomial temp(*this);
	this->operator++();
	return temp;
}

polynomial & polynomial::operator--()
{
	c[0]--;
	return *this; //no need of normalization (as policy, even if the polinomial equals 0, c contains one element)
}

polynomial polynomial::operator--(int)
{
	polynomial temp(*this);
	this->operator--();
	return temp;
}


polynomial operator +(polynomial const &a, polynomial const & b)
{
	polynomial ret(a);
	return (ret+=b);
}

polynomial operator -(polynomial const &a, polynomial const & b)
{
	polynomial ret(a);
	return (ret-=b);
}

polynomial operator *(polynomial const &a, polynomial const & b)
{
	polynomial ret(a);
	return (ret*=b);
}

polynomial operator /(polynomial const &a, polynomial const & b)
{
	polynomial ret(a);
	return (ret/=b);
}

scalar polynomial::operator()(scalar const & x) const
{
	scalar ret(0);
	auto N = c.size();
	for (unsigned i = 0; i < N; i++) ret+=c[i]*pow(x,i);
	return ret;
}

scalar polynomial::GetCoefficient(unsigned idx) const
{
	if(idx>GetDegree()) return 0;
	return c[idx];
}

unsigned polynomial::GetDegree() const
{
	return c.size()-1;
}

std::ostream & operator << (std::ostream & str, polynomial const & r)
{
	int n=r.c.size()-1;
	bool firsttime=true;
	for (auto it=r.c.rbegin(); it != r.c.rend(); it++)
	{
		if (*it != 0) 
		{
			//if (!firsttime) str << " ";
			//coefficient
			if (*it==1 && n>0) str << (firsttime? "" : "+");
			else if (*it==-1 && n>0) str << "-";
			else str << (firsttime? std::noshowpos : std::showpos) << *it;
			//x^n
			if (n>1) str << "x^" << std::noshowpos << n;
			else if (n==1) str << "x";
			firsttime=false;	
		}
		n--;
	}
	if (firsttime) str << "0";
	str << std::noshowpos;
	return str;
}

polynomial & polynomial::trimZeros()
{
	auto it=c.rbegin();
	while(it!=c.rend() && *it==0) it++;
	c.erase(it.base(), c.end());
	if (c.size()==0) c.push_back(0.0);
	return *this;
}


