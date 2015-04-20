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
	//Constructor	
	polynomial(std::initializer_list<scalar>);
	
	//Operations (postif and prefix operators ++ and -- add/remove 1 to the constan term)
	polynomial &operator +=(polynomial const &);
	polynomial &operator -=(polynomial const &);
	polynomial &operator /=(polynomial const &);
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
	friend polynomial operator/(polynomial const &,polynomial const &);

	//Evaluation
	scalar operator()(scalar const &) const;

	//Get the value of the desired coefficient
	scalar GetCoefficient(unsigned) const;

	//Get the degree of the polynomial
	unsigned GetDegree() const;

	//output streaming operator
	friend std::ostream & operator << (std::ostream &, polynomial const &);
	

private:
	//stores the coefficients (from 0 degree to n degree)
	std::vector<scalar> c;
	polynomial & trimZeros();
	//generically implements += and -= operators
	template<int S>
	polynomial & algebraicplusequal (polynomial const & p)
	{
		if (p.c.size()>this->c.size()) this->c.resize(p.c.size());
		auto i1=this->c.begin(), e1=this->c.end();
		auto i2=p.c.begin();
		while (i1<e1) *(i1++)+=*(i2++)*S;
		return trimZeros();
	};
};

#endif
