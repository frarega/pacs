Challange 4.3

The executable performs main operations on some given polynomials; then it asks the user to type two complex polynomials, and performs the same operations with them.
Remember to type coefficients form the constant term to the leading term. Just type "Enter" to terminate the sequence.

Remark: a polynomial<D,scalar> is just formally of degree D. Indeed, the actual degree may be fewer than D (if the leading coefficient(s) equals zero)

Remark: in order to allow for std::complex<T> coefficients, some class methods and functions had to be specialized:
	1. output stream operator
	2. increment (++) / decrement (--) operator
	3. each method where a comparison with "0" is needed
	4. each method where the signum of a coefficient has to be inverted (since it was previously implemented with a moltiplication by -1)
Since stream operators are friend external functions, it was possible to perform partial specialization. In the other cases, since the specialization of the full class would be excessive, I overcame the problem resorting to template functions (addOne, removeOne, equalsZero) and then I partially-specialized them. Problem 4 was overcome just resorting to operator()- instead of moltiplication by -1.
