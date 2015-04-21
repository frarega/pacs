#ifndef POLINOMYAL_H
#define POLINOMYAL_H

#include <stdio.h>
#include <array>
#include <initializer_list>
#include <complex>

constexpr unsigned mymax(unsigned const & n, unsigned const & m) { return n>m?n:m; }

template<unsigned D, typename scalar>
class polynomial
{
public:
	polynomial();

	//Initializator: coefficent are given from the constant term to the leading term
	polynomial(std::array<scalar,D + 1> const);

	polynomial(polynomial const &)=default;
	polynomial& operator=(polynomial const &)=default;
	
	template<unsigned N>
	polynomial &operator +=(polynomial<N,scalar> const &);
	template<unsigned N>
	polynomial &operator -=(polynomial<N,scalar> const &);
	polynomial operator-() const;
	polynomial operator+() const;
	//! adds 1 to the constant term
	polynomial & operator++();
	//! adds 1 to the constant term
	polynomial operator++(int);
	//! removes 1 from the constant term
	polynomial & operator--();
	//! removes 1 from the constant term
	polynomial operator--(int);
	template<unsigned N, unsigned M, typename scal>
	friend polynomial<mymax(N,M),scal> operator+(polynomial<N,scal> const &,polynomial<M,scal> const &);
	template<unsigned N, unsigned M, typename scal>
	friend polynomial<mymax(N,M),scal> operator-(polynomial<N,scal> const &,polynomial<M,scal> const &);
	
	template<unsigned N, unsigned M, typename scal>
	friend polynomial<N+M,scal> operator*(polynomial<N,scal> const &,polynomial<M,scal> const &);

	//! returns the quotient and the remainder in a pair a polynomials
	template<unsigned N, unsigned M,typename scal>
	friend std::pair<polynomial<N,scal>, polynomial<N,scal>>  operator/(polynomial<N,scal> const &,polynomial<M,scal> const &);
	
	//! Evaluation
	scalar operator()(scalar const &) const;

	//! Get the value of the desired coefficient
	scalar GetCoefficient(unsigned) const;

	//! Get the degree of the template class (the actual degree of the polynomial may be fewer than this!)
	constexpr unsigned GetDegree() const;

	//! Output streaming operator	
	template<unsigned N,typename scal>
	friend std::ostream & operator << (std::ostream &, polynomial<N,scal> const &);
	//! Output streaming operator: specialization
	template<unsigned N,typename scal>
	friend std::ostream & operator << (std::ostream &, polynomial<N,std::complex<scal>> const &);
	

	//! Input streaming operator
	/*! Coefficent are given from the constant term to the leading term and must be separated with spaces. 
	    Just type "Enter" terminate the sequence
	*/	
	template<unsigned N,typename scal>
	friend std::istream & operator >> (std::istream &, polynomial<N,scal> &);
	
	

private:
	//! stores the coefficients (from the constant term to the leading term)
	std::array<scalar, D+1> c;
	
	//! generically implements += and -= operators
	template<unsigned N, unsigned M, int S,typename scal>
	friend polynomial<N,scal> & algebraicplusequal (polynomial<N,scal> &, polynomial<M,scal> const &);

	//! generically implements + and - operators
	template<unsigned N, unsigned M, int S,typename scal>
	friend polynomial<mymax(N,M),scal> algebraicplus (polynomial<N,scal> const &, polynomial<M,scal> const &);

};

#include "polynomial_imp.hpp"

#endif
