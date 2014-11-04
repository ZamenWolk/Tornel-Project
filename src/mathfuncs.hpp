#ifndef MATHFUNCS_HPP_INCLUDED
#define MATHFUNCS_HPP_INCLUDED

#include <cmath>

/**
*   \file mathfuncs.hpp
*   \brief Contains class declaration for maths functions
*/

/**
* \addtogroup both
* @{
*/

/**
*   \brief Parent class of all the math functions classes
*/

class MathFunction
{
public:

	MathFunction(int minimalXValue = -1, int maximalXValue = -1);

	/**
	*   \brief Applies the function for the given number
	*   \param[in] x Number to give to the math function
	*	\return \f$ f(x) \f$
	*/

	virtual double result(double x) = 0;

	/**
    *   \brief Applies the function for the given number
    *   \param[in] x Number to give to the math function
    *	\return \f$ f(x) \f$
    */

	virtual double result(int x) = 0;

	int iresult(double x);

	int iresult(int x);

protected:

	int minimalXValue, ///< Minimal value of x as handled in the game. -1 is none
		maximalXValue; ///< Maximal value of x as handled in the game. -1 is none
};

/**
*   \brief Third Power function
*	\details Function \f$ f(x) = ax^3 + bx^2 + cx + d  \f$
*/

class ThirdPowerFunction : public MathFunction
{
public:

	ThirdPowerFunction(double yIntercept = 0,
						   double firstPowerFactor = 0,
						   double secondPowerFactor = 0,
						   double thirdPowerFactor = 0,
						   int minimalXValue = -1,
						   int maximalXValue = -1);

	virtual double result(double x);

	virtual double result(int x);

protected:

	double thirdPowerFactor, ///< Factor of \f$ x^3 \f$ when calculating \f$ f(x) \f$
		   secondPowerFactor, ///< Factor of \f$ x^2 \f$ when calculating \f$ f(x) \f$
		   firstPowerFactor, ///< Factor of \f$ x \f$ when calculating \f$ f(x) \f$
		   yIntercept; ///< Value of \f$ f(x) \f$ when \f$ x=0 \f$

};

/**
*   \brief Invert function
*	\details Function \f$ f(x) = a\sqrt[3]{x} + b\sqrt{x} + cx + d  \f$
*/

class InvertFunction : public MathFunction
{
public:

	InvertFunction(double yIntercept = 0,
					   double firstPowerFactor = 0,
					   double secondPowerFactor = 0,
					   double thirdPowerFactor = 0,
					   int minimalXValue = -1,
					   int maximalXValue = -1);

	virtual double result(double x);

	virtual double result(int x);

protected:

	double thirdPowerFactor, ///< Factor of \f$ cbrt(x) \f$ when calculating \f$ f(x) \f$
		   secondPowerFactor, ///< Factor of \f$ sqrt(x) \f$ when calculating \f$ f(x) \f$
		   firstPowerFactor, ///< Factor of \f$ x \f$ when calculating \f$ f(x) \f$
		   yIntercept; ///< Value of \f$ f(x) \f$ when \f$ x=0 \f$

};

/**
*   \brief Sequence defined by a recurring
*	\details Sequence \f$ u(n) = u(n-1) * q + r  \f$
*/

class RecurrentSequence : public MathFunction
{
public:

	RecurrentSequence(double valueAtMinimumX = 0,
						  double commonDifference = 0,
						  double commonRatio = 1,
						  int minimalXValue = 0,
						  int maximalXValue = -1);

	virtual double result(double x);

	virtual double result(int x);

protected:

	double valueAtMinimumX, ///< Value of \f$ u(x) \f$ at the minimum value of x
		   commonDifference, ///< Value to add to the sequence at each occuring
		   commonRatio; ///< Value to multiply the sequence with at each occuring
};

/**
*   \brief Recurring sequence following another sequence
*	\details Sequence \f$ u(n) = u(n-1) * q + r + u'(n)  \f$
*/

class SequenceUsing_Sequence : public RecurrentSequence
{
public:

	SequenceUsing_Sequence(double valueAtMinimumX = 0,
							   double commonDifference = 0,
							   double commonRatio = 1,
							   RecurrentSequence usedSequence = RecurrentSequence(),
							   int minimalXValue = 0,
							   int maximalXValue = -1);

	virtual double result(double x);

	virtual double result(int x);

protected:

	RecurrentSequence usedSequence; ///< Sequence added to \f$ u(n) \f$ at each occuring
};

/**
*   \brief Exponential function
*	\details Function \f$ f(x) = a^{x-b} + c  \f$
*/

class ExponentialFunction : public MathFunction
{
public:

	ExponentialFunction(bool negativeOfExponential = false,
							double exponentialFactor = 1,
							double horizontalTranslater = 0,
							double verticalTranslater = 0,
							int minimalXValue = -1,
							int maximalXValue = -1);

	virtual double result(double x);

	virtual double result(int x);

protected:

	bool   negativeOfExponential; ///< Whether the exponential factor is inverted or not
	double exponentialFactor, ///< Factor of the exponential
		   horizontalTranslater, ///< Horizontal translater of the function
		   verticalTranslater; ///< Vertical translater of the function
};

/// @}

#endif // MATHFUNCS_HPP_INCLUDED
