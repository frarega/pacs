#ifndef POLINOMYAL_H
#define POLINOMYAL_H

#include <stdio.h>
#include <array>
#include <initializer_list>
#include "scalar.hpp"
//#include "polyEvaluator.hpp"	


constexpr unsigned mymax(unsigned const & n, unsigned const & m) { return n>m?n:m; }

template<unsigned D>
class polynomial
{
public:
	polynomial();

	//Initializator: coefficent are given beginning with the constant term
	polynomial(std::array<scalar,D + 1> const);

	polynomial(polynomial const &)=default;
	polynomial& operator=(polynomial const &)=default;
	
	template<unsigned N>
	polynomial &operator +=(polynomial<N> const &);
	template<unsigned N>
	polynomial &operator -=(polynomial<N> const &);
	//polynomial &operator *=(polynomial const &);
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
	template<unsigned N, unsigned M>
	friend polynomial<mymax(N,M)> operator+(polynomial<N> const &,polynomial<M> const &);
	template<unsigned N, unsigned M>
	friend polynomial<mymax(N,M)> operator-(polynomial<N> const &,polynomial<M> const &);
	
	template<unsigned N, unsigned M>
	friend polynomial<N+M> operator*(polynomial<N> const &,polynomial<M> const &);

	//returns the quotient and the remainder in a pair a polynomials
	template<unsigned N, unsigned M>
	friend std::pair<polynomial<mymax(N-M,0)>, polynomial<M>>  operator/(polynomial<N> const &,polynomial<M> const &);
	
	//! Evaluation
	scalar operator()(scalar const &) const;

	//! Get the value of the desired coefficient
	scalar GetCoefficient(unsigned) const;

	//! Get the degree of the polynomial
	constexpr unsigned GetDegree() const;

	//! Output streaming operator	
	template<unsigned N>
	friend std::ostream & operator << (std::ostream &, polynomial<N> const &);
	

	//! Input streaming operator
	/*! Coefficent are given beginning with the constant term, 
	    and must be separated with spaces. 
	    The return carriage terminates the sequence
	*/	
	template<unsigned N>
	friend std::istream & operator >> (std::istream &, polynomial<N> &);
	
	

private:
	//! stores the coefficients (from 0 degree to n degree)
	std::array<scalar, D+1> c;
	
	//! generically implements += and -= operators
	template<unsigned N, unsigned M, int S>
	friend polynomial<N> & algebraicplusequal (polynomial<N> &, polynomial<M> const &);

	//! generically implements + and - operators
	template<unsigned N, unsigned M, int S>
	friend polynomial<mymax(N,M)> algebraicplus (polynomial<N> const &, polynomial<M> const &);
	
	//template <unsigned N>
	//constexpr scalar eval(scalar const &);


	//template<unsigned N>
//	friend class polyEvaluator<D,N>;
};

#include "polynomial_imp.hpp"

#endif
