#ifndef MYPOW_H
#define MYPOW_H

template<unsigned D, typename scalar>
struct mypow
{
	static constexpr scalar compute(scalar const & x) { return x*mypow<D-1,scalar>::compute(x); }
};

template<typename scalar>
struct mypow<1,scalar>
{
	static constexpr scalar compute(scalar const & x) { return x; }
};

template<typename scalar>
struct mypow<0,scalar>
{
	static constexpr scalar compute(scalar const & x) { return 1; }
};

#endif
