#ifndef POW_H
#define POW_H

#include "scalar.hpp"

template<unsigned D>
struct pow
{
	static constexpr scalar compute(scalar const & x) { return x*pow<D-1>::compute(x); }
};

template<>
struct pow<1>
{
	static constexpr scalar compute(scalar const & x) { return x; }
};

template<>
struct pow<0>
{
	static constexpr scalar compute(scalar const & x) { return 1; }
};

#endif
