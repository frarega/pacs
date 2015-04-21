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
	//Initializator: coefficent are given from the constant term to the leading term
	polynomial(std::vector<scalar> const);
	//Initializator: coefficent are given from the constant term to the leading term
	polynomial(std::initializer_list<scalar> const);
	polynomial(polynomial const &)=default;
	polynomial& operator=(polynomial const &)=default;
	
	polynomial &operator +=(polynomial const &);
	polynomial &operator -=(polynomial const &);
	polynomial &operator *=(polynomial const &);
	polynomial operator-() const;
	polynomial operator+() const;
	//adds 1 to the constant term
	polynomial & operator++();
	//adds 1 to the constant term
	polynomial operator++(int);
	//removes 1 from the constant term
	polynomial & operator--();
	//removes 1 from the constant term
	polynomial operator--(int);
	friend polynomial operator+(polynomial const &,polynomial const &);
	friend polynomial operator-(polynomial const &,polynomial const &);
	friend polynomial operator*(polynomial const &,polynomial const &);
	//returns the quotient and the remainder in a pair a polynomials
	friend std::pair<polynomial, polynomial>  operator/(polynomial const &,polynomial const &);
	
	//! Evaluation
	scalar operator()(scalar const &) const;

	//! Get the value of the desired coefficient
	scalar GetCoefficient(unsigned) const;

	//! Get the degree of the polynomial
	unsigned GetDegree() const;

	//! Output streaming operator
	friend std::ostream & operator << (std::ostream &, polynomial const &);

	//! Input streaming operator
	/*! Coefficent are given from the constant term to the leading term and must be separated with spaces. 
	    Just type "Enter" terminate the sequence
	*/	
	friend std::istream & operator >> (std::istream &, polynomial &);
	

private:
	//! stores the coefficients (from the constant term to the leading term)
	std::vector<scalar> c;
	static std::vector<scalar> & trimZeros(std::vector<scalar> &);
	polynomial & trimZeros();
	//! generically implements += and -= operators
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
