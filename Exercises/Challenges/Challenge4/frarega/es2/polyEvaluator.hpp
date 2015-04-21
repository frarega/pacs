#ifndef POLYEVALUATOR_H
#define POLYEVALUATOR_H

#include "scalar.hpp"
#include "pow.hpp"
#include "polynomial.hpp"


template<unsigned D, unsigned N>
class polyEvaluator
{
public:
	static constexpr scalar compute(scalar const & x, polynomial<D> const &p) { return p.GetCoefficient(N)*pow<N>::compute(x) + polyEvaluator<D,N-1>::compute(x,p); }
};

template<unsigned D>
class polyEvaluator<D,0>
{
public:
	static constexpr scalar compute(scalar const & x, polynomial<D> const &p) { return p.GetCoefficient(0); }
};

#endif
