#ifndef POLYEVALUATOR_H
#define POLYEVALUATOR_H

#include "mypow.hpp"
#include "polynomial.hpp"


template<unsigned D, unsigned N, typename scalar>
class polyEvaluator
{
public:
	static constexpr scalar compute(scalar const & x, polynomial<D,scalar> const &p) 
	{ 
		return p.GetCoefficient(N)*mypow<N,scalar>::compute(x) + polyEvaluator<D,N-1,scalar>::compute(x,p); 
	}
};

template<unsigned D, typename scalar>
class polyEvaluator<D,0,scalar>
{
public:
	static constexpr scalar compute(scalar const & x, polynomial<D,scalar> const &p) { return p.GetCoefficient(0); }
};

#endif
