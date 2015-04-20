#include <iostream>
#include <string> 
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <vector>
#include "polynomial.hpp"

polynomial::polynomial(): c() {};

polynomial::polynomial(std::vector<scalar> const v): c(v) {};
	
polynomial::polynomial(std::initializer_list<scalar> const l): c(l) { trimZeros(); };

polynomial & polynomial::operator +=(polynomial const & p) { return algebraicplusequal<1>(p); }

polynomial & polynomial::operator -=(polynomial const & p) { return algebraicplusequal<-1>(p); }

polynomial & polynomial::operator *=(polynomial const & p)
{
	/*std::vector<scalar> newc(c.size()+p.c.size()-1,0);
	for (int i1=0;i1<c.size();i1++)		
		for (auto i2=0;i2<p.c.size();i2++)
			newc[i1+i2]+=c[i1]*p.c[i2];	
	c=newc;
	return trimZeros();*/
	*this=*this*p;
	return *this;
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
	std::vector<scalar> newc(a.c.size()+b.c.size()-1,0);
	for (int i1=0;i1<a.c.size();i1++)		
		for (auto i2=0;i2<b.c.size();i2++)
			newc[i1+i2]+=a.c[i1]*b.c[i2];
	return polynomial(newc);
}

std::pair<polynomial, polynomial> operator /(polynomial const &a, polynomial const & b)
{
	int nb=b.c.size();
	int nr=a.c.size();
	std::vector<scalar>::const_iterator itb;
	std::vector<scalar>::iterator itr;
	if (nb==1 && b.c[0]==0) throw std::runtime_error("Division by zero");
	if (nb>a.c.size()) return std::pair<polynomial, polynomial>(polynomial({0}),a);
	std::vector<scalar> q(a.c.size()-nb+1,0.0),r(a.c);
	while(true)
	{
		scalar d=r[nr-1]/b.c[nb-1];
		q[nr-nb]=d;
		itb = b.c.begin();
		itr = r.begin() + nr-nb;
		for (int i=0;i<nb-1;i++) *(itr++)-=(*itb++)*d;
		*itr=0;
		polynomial::trimZeros(r);
		nr=r.size();
		if (nr<nb || (nr==1 && r[0]==0)) return std::pair<polynomial, polynomial>(polynomial(q),polynomial(r));
	}
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

std::istream & operator >> (std::istream & str, polynomial & r)
{
	std::vector<scalar> newc;
	std::string scoeff;
	scalar coeff;
	bool end=false;
	while (!end)
	{
		std::getline(str,scoeff,' ');
		std::istringstream strcoeff(scoeff);
  		strcoeff>>coeff;
  		if(strcoeff.fail()) end=true;
		else newc.push_back(coeff);
	}
	r.c=newc;
	r.trimZeros();
	return str;
}


std::vector<scalar> & polynomial::trimZeros(std::vector<scalar> & v)
{
	auto it=v.rbegin();
	while(it!=v.rend() && *it==0) it++;
	v.erase(it.base(), v.end());
	if (v.size()==0) v.push_back(0.0);
	return v;

}

polynomial & polynomial::trimZeros()
{
	/*auto it=c.rbegin();
	while(it!=c.rend() && *it==0) it++;
	c.erase(it.base(), c.end());
	if (c.size()==0) c.push_back(0.0);
	return *this;*/
	trimZeros(c);
	return *this;
}


