#ifndef POLINOMYAL_IMP_H
#define POLINOMYAL_IMP_H

#include <stdio.h>
#include <array>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include "polyEvaluator.hpp"

template <unsigned D,typename scalar>
polynomial<D,scalar>::polynomial() : c() {}

template <unsigned D,typename scalar>
polynomial<D,scalar>::polynomial(std::array<scalar,D + 1> const l): c(l) {}

template<typename scalar, int S>
constexpr scalar signedValue(scalar const & x) 
{ 
	return (S>0?x:-x);
}

template<unsigned N, unsigned M, int S,typename scalar>
polynomial<N,scalar> & algebraicplusequal (polynomial<N,scalar> & a, polynomial<M,scalar> const & b)
{
	if (M>N) throw std::runtime_error("Attempt to add a higher-grade polynomial to a lower-grade one");
	auto i1=a.c.begin();
	auto i2=b.c.begin(), e2=b.c.end();
	while (i2<e2) *(i1++)+=signedValue<scalar,S>(*(i2++));
	return a;
}

template <unsigned D,typename scalar>
template <unsigned N>
polynomial<D,scalar> & polynomial<D,scalar>::operator +=(polynomial<N,scalar> const & p) { return algebraicplusequal<D,N,1,scalar>(*this,p); }

template <unsigned D,typename scalar>
template <unsigned N>
polynomial<D,scalar> & polynomial<D,scalar>::operator -=(polynomial<N,scalar> const & p){ return algebraicplusequal<D,N,-1,scalar>(*this,p); }

template <unsigned D,typename scalar>
polynomial<D,scalar> polynomial<D,scalar>::operator-() const
{
	polynomial ret(*this);
	for (auto it=ret.c.begin(); it<ret.c.end(); it++) *it=-*it;
	return ret;
}

template <unsigned D,typename scalar>
polynomial<D,scalar> polynomial<D,scalar>::operator+() const
{
	return *this;
}

template<typename scalar>
constexpr void addOne(scalar & x) { x++; }

template<typename scalar>
constexpr void addOne(std::complex<scalar> & x) { x+=std::complex<scalar>(1,0); }

template <unsigned D,typename scalar>
polynomial<D,scalar> & polynomial<D,scalar>::operator++()
{
	addOne(c[0]);
	return *this;
}

template <unsigned D,typename scalar>
polynomial<D,scalar> polynomial<D,scalar>::operator++(int)
{
	polynomial temp(*this);
	this->operator++();
	return temp;
}

template<typename scalar>
constexpr void removeOne(scalar & x) { x--; }

template<typename scalar>
constexpr void removeOne(std::complex<scalar> & x) { x-=std::complex<scalar>(1,0); }

template <unsigned D,typename scalar>
polynomial<D,scalar> & polynomial<D,scalar>::operator--()
{
	removeOne(c[0]);
	return *this;
}

template <unsigned D,typename scalar>
polynomial<D,scalar> polynomial<D,scalar>::operator--(int)
{
	polynomial temp(*this);
	this->operator--();
	return temp;
}

template<unsigned N, unsigned M, int S,typename scalar>
polynomial<mymax(N,M),scalar> algebraicplus (polynomial<N,scalar> const & a, polynomial<M,scalar> const & b)
{
	polynomial<mymax(N,M),scalar> temp;
	auto ita=a.c.begin(), ea=a.c.end();
	auto itb=b.c.begin(), eb=b.c.end();
	for (auto itt=temp.c.begin(); itt<temp.c.end(); itt++)
	{
		if ((ita++)<ea) *itt+=*(ita-1);
		if ((itb++)<eb) *itt+=signedValue<scalar,S>(*(itb-1));
	}
	return temp;
}

template<unsigned N, unsigned M,typename scalar>
polynomial<mymax(N,M),scalar> operator+(polynomial<N,scalar> const & a, polynomial<M,scalar> const & b){ return algebraicplus<N,M,1,scalar>(a,b); }

template<unsigned N, unsigned M,typename scalar>
polynomial<mymax(N,M),scalar> operator-(polynomial<N,scalar> const & a, polynomial<M,scalar> const & b){ return algebraicplus<N,M,-1,scalar>(a,b); }

template<unsigned N, unsigned M,typename scalar>
polynomial<N+M,scalar> operator*(polynomial<N,scalar> const & a ,polynomial<M,scalar> const & b)
{
	polynomial<N+M,scalar> temp;
	for (int i1=0;i1<a.c.size();i1++)		
		for (auto i2=0;i2<b.c.size();i2++)
			temp.c[i1+i2]+=a.c[i1]*b.c[i2];
	return temp;

}

template<typename S>
constexpr bool equalsZero(S x) { return x==0; }


template<typename S>
constexpr bool equalsZero(std::complex<S> x) { return x==std::complex<S>(0,0); }

template<unsigned N, unsigned M,typename scalar>
std::pair<polynomial<N,scalar>, polynomial<N,scalar>>  operator/(polynomial<N,scalar> const & a,polynomial<M,scalar> const & b)
{
	std::pair<polynomial<N,scalar>, polynomial<N,scalar>> ret (polynomial<N,scalar>(), a);
	
	auto itq=ret.first.c.rbegin()+M, eq=ret.first.c.rend();//itq point to the term of the quotien i'm going to write in
	auto itmaxr=ret.second.c.rbegin(), itr=ret.second.c.rbegin(), er=ret.second.c.rend();//itmaxr point to the leading coefficient of the remainder
	auto itmaxb=b.c.rbegin(), itb=b.c.rbegin(), eb=b.c.rend();//itmaxb point to the leading coefficient of the divisor
	while (equalsZero(*itmaxb))
	{
		itmaxb++;
		itq--;
		if (itmaxb==eb) throw std::runtime_error("Division by zero");
	}
	if (itq>=eq) return ret;
	while(true)
	{
		while (equalsZero(*itmaxr))  if ((++itmaxr)==er || (++itq)==eq) return ret;
		*itq=(*itmaxr)/(*itmaxb);
		*itmaxr=0; //just to be sure that rounding errors don't lead to unconsistent results
		itb=itmaxb+1;
		itr=itmaxr+1;
		while (itb!=eb && itr!=er) *(itr++)-=(*itb++)*(*itq);
	}
}

template <unsigned D,typename scalar>
scalar polynomial<D,scalar>::operator()(scalar const & x) const
{
	return polyEvaluator<D,D,scalar>::compute(x,*this);
}

template <unsigned D,typename scalar>
scalar polynomial<D,scalar>::GetCoefficient(unsigned idx) const
{
	if(idx>D) return 0;
	return c[idx];
}

template <unsigned D,typename scalar>
constexpr unsigned polynomial<D, scalar>::GetDegree() const
{
	return D;
}

template <unsigned D,typename scalar>
std::ostream & operator << (std::ostream & str, polynomial<D, scalar> const & r)
{
	int n=D;
	bool firsttime=true;
	for (auto it=r.c.rbegin(); it != r.c.rend(); it++)
	{
		if (*it != 0) 
		{
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

template <unsigned D,typename scalar>
std::ostream & operator << (std::ostream & str, polynomial<D, std::complex<scalar>> const & r)
{
	int n=D;
	bool firsttime=true;
	for (auto it=r.c.rbegin(); it != r.c.rend(); it++)
	{
		if (!equalsZero(*it)) 
		{
			if (!firsttime) str << " + ";
			//coefficient
			str << *it;
			//x^n
			if (n>1) str << "*x^" << n;
			else if (n==1) str << "*x";
			firsttime=false;	
		}
		n--;
	}
	if (firsttime) str << std::complex<scalar>(0,0);
	return str;
}

template<unsigned N,typename scalar>
std::istream & operator >> (std::istream & str, polynomial<N, scalar> & r)
{
	r=polynomial<N, scalar>();
	std::string scoeff;
	scalar coeff;
	std::getline(str,scoeff);
	std::istringstream strcoeff(scoeff);
	auto it = r.c.begin();
	while (true)
	{
  		strcoeff>>coeff;
  		if(it==r.c.end() || strcoeff.fail()) return str;
		else (*it++)=coeff;
	}
}

#endif
