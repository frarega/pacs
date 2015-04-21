#ifndef POLINOMYAL_IMP_H
#define POLINOMYAL_IMP_H

#include <stdio.h>
#include <array>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include "scalar.hpp"
#include "polyEvaluator.hpp"

template <unsigned D>
polynomial<D>::polynomial() : c() {}

template <unsigned D>
polynomial<D>::polynomial(std::array<scalar,D + 1> const l): c(l) {}

template<unsigned N, unsigned M, int S>
polynomial<N> & algebraicplusequal (polynomial<N> & a, polynomial<M> const & b)
{
	if (M>N) throw std::runtime_error("Attempt to add a higher-grade polynomial to a lower-grade one");
	auto i1=a.c.begin();
	auto i2=b.c.begin(), e2=b.c.end();
	while (i2<e2) *(i1++)+=*(i2++)*S;
	return a;
}

template <unsigned D>
template <unsigned N>
polynomial<D> & polynomial<D>::operator +=(polynomial<N> const & p) { return algebraicplusequal<D,N,1>(*this,p); }

template <unsigned D>
template <unsigned N>
polynomial<D> & polynomial<D>::operator -=(polynomial<N> const & p){ return algebraicplusequal<D,N,-1>(*this,p); }

template <unsigned D>
polynomial<D> polynomial<D>::operator-() const
{
	polynomial ret(*this);
	for (auto it=ret.c.begin(); it<ret.c.end(); it++) *it*=-1;
	return ret;
}

template <unsigned D>
polynomial<D> polynomial<D>::operator+() const
{
	return *this;
}

template <unsigned D>
polynomial<D> & polynomial<D>::operator++()
{
	c[0]++;
	return *this;
}

template <unsigned D>
polynomial<D> polynomial<D>::operator++(int)
{
	polynomial temp(*this);
	this->operator++();
	return temp;
}

template <unsigned D>
polynomial<D> & polynomial<D>::operator--()
{
	c[0]--;
	return *this;
}

template <unsigned D>
polynomial<D> polynomial<D>::operator--(int)
{
	polynomial temp(*this);
	this->operator--();
	return temp;
}

template<unsigned N, unsigned M, int S>
polynomial<mymax(N,M)> algebraicplus (polynomial<N> const & a, polynomial<M> const & b)
{
	polynomial<mymax(N,M)> temp;
	auto ita=a.c.begin(), ea=a.c.end();
	auto itb=b.c.begin(), eb=b.c.end();
	for (auto itt=temp.c.begin(); itt<temp.c.end(); itt++)
	{
		if ((ita++)<ea) *itt+=*(ita-1);
		if ((itb++)<eb) *itt+=*(itb-1)*S;
	}
	return temp;
}

template<unsigned N, unsigned M>
polynomial<mymax(N,M)> operator+(polynomial<N> const & a, polynomial<M> const & b){ return algebraicplus<N,M,1>(a,b); }

template<unsigned N, unsigned M>
polynomial<mymax(N,M)> operator-(polynomial<N> const & a, polynomial<M> const & b){ return algebraicplus<N,M,-1>(a,b); }

template<unsigned N, unsigned M>
polynomial<N+M> operator*(polynomial<N> const & a ,polynomial<M> const & b)
{
	polynomial<N+M> temp;
	for (int i1=0;i1<a.c.size();i1++)		
		for (auto i2=0;i2<b.c.size();i2++)
			temp.c[i1+i2]+=a.c[i1]*b.c[i2];
	return temp;

}


template<unsigned N, unsigned M>
std::pair<polynomial<N>, polynomial<N>>  operator/(polynomial<N> const & a,polynomial<M> const & b)
{
	std::pair<polynomial<N>, polynomial<N>> ret (polynomial<N>(), a);
	
	auto itq=ret.first.c.rbegin()+M, eq=ret.first.c.rend();//itq point to the term of the quotien i'm going to write in
	auto itmaxr=ret.second.c.rbegin(), itr=ret.second.c.rbegin(), er=ret.second.c.rend();//itmaxr point to the leading coefficient of the remainder
	auto itmaxb=b.c.rbegin(), itb=b.c.rbegin(), eb=b.c.rend();//itmaxb point to the leading coefficient of the divisor
	while (*itmaxb==0)
	{
		itmaxb++;
		itq--;
		//degb--;
		if (itmaxb==eb) throw std::runtime_error("Division by zero");
	}
	if (itq>=eq) return ret;
	while(true)
	{
		while (*itmaxr==0)  if ((++itmaxr)==er || (++itq)==eq) return ret;
		*itq=(*itmaxr)/(*itmaxb);
		*itmaxr=0; //just to be sure that rounding errors don't lead to unconsistent results
		itb=itmaxb+1;
		itr=itmaxr+1;
		while (itb!=eb && itr!=er) *(itr++)-=(*itb++)*(*itq);
	}
}

template <unsigned D>
scalar polynomial<D>::operator()(scalar const & x) const
{
	return polyEvaluator<D,D>::compute(x,*this);
}

template <unsigned D>
scalar polynomial<D>::GetCoefficient(unsigned idx) const
{
	if(idx>D) return 0;
	return c[idx];
}

template <unsigned D>
constexpr unsigned polynomial<D>::GetDegree() const
{
	return D;
}

template <unsigned D>
std::ostream & operator << (std::ostream & str, polynomial<D> const & r)
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

template<unsigned N>
std::istream & operator >> (std::istream & str, polynomial<N> & r)
{
	r=polynomial<N>();
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
