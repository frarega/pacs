#ifndef POLINOMYAL_H
#define POLINOMYAL_H

#include <stdio.h>
#include <vector>
#include <initializer_list>
#include "scalar.hpp"

class polynomial
{
public:
	polynomial();
	polynomial(std::vector<scalar> const);
	polynomial(std::initializer_list<scalar> const);
	polynomial(polynomial const &)=default;
	polynomial& operator=(polynomial const &)=default;
	
	
	//Operations (postif and prefix operators ++ and -- add/remove 1 to the constan term)
	polynomial &operator +=(polynomial const &);
	polynomial &operator -=(polynomial const &);
	polynomial &operator *=(polynomial const &);
	polynomial operator-() const;
	polynomial operator+() const;
	polynomial & operator++();
	polynomial operator++(int);
	polynomial & operator--();
	polynomial operator--(int);
	friend polynomial operator+(polynomial const &,polynomial const &);
	friend polynomial operator-(polynomial const &,polynomial const &);
	friend polynomial operator*(polynomial const &,polynomial const &);
	friend std::pair<polynomial, polynomial>  operator/(polynomial const &,polynomial const &);

	//Evaluation
	scalar operator()(scalar const &) const;

	//Get the value of the desired coefficient
	scalar GetCoefficient(unsigned) const;

	//Get the degree of the polynomial
	unsigned GetDegree() const;

	//output streaming operator
	friend std::ostream & operator << (std::ostream &, polynomial const &);

	//input streaming operator

	friend std::istream & operator >> (std::istream &, polynomial &);
	

private:
	//stores the coefficients (from 0 degree to n degree)
	std::vector<scalar> c;
	static std::vector<scalar> & trimZeros(std::vector<scalar> &);
	polynomial & trimZeros();
	//generically implements += and -= operators
	template<int S>
	polynomial & algebraicplusequal (polynomial const & p)
	{
		if (p.c.size()>c.size()) c.resize(p.c.size());
		auto i1=c.begin(), e1=c.end();
		auto i2=p.c.begin();
		while (i1<e1) *(i1++)+=*(i2++)*S;
		return trimZeros();
	};
};

#endif
