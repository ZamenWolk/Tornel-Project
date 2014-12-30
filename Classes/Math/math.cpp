#include <iostream>
#include <cmath>

#include "math.hpp"

using namespace std;

MathFunction::MathFunction(int minimalXValue, int maximalXValue) :
        minimalXValue(minimalXValue),
        maximalXValue(maximalXValue)
{

}

int MathFunction::iresult(double x)
{
    return (int)result(x);
}

ThirdPowerFunction::ThirdPowerFunction(double yIntercept,
                                       double firstPowerFactor,
                                       double secondPowerFactor,
                                       double thirdPowerFactor,
                                       int minimalXValue,
                                       int maximalXValue) :
                            MathFunction(minimalXValue, maximalXValue),
                            thirdPowerFactor(thirdPowerFactor),
                            secondPowerFactor(secondPowerFactor),
                            firstPowerFactor(firstPowerFactor),
                            yIntercept(yIntercept)
{

}

double ThirdPowerFunction::result(double x)
{
    if (minimalXValue != -1 && x < minimalXValue)
    {
        return result(minimalXValue);
    }
    else if (maximalXValue != -1 && x > maximalXValue)
    {
        return result(maximalXValue);
    }
    else
    {
        return thirdPowerFactor*pow(x, 3) + secondPowerFactor*pow(x, 2) + firstPowerFactor*x + yIntercept;
    }
}

InvertFunction::InvertFunction(double yIntercept,
                               double firstPowerFactor,
                               double secondPowerFactor,
                               double thirdPowerFactor,
                               int minimalXValue,
                               int maximalXValue) :
                    MathFunction(minimalXValue, maximalXValue),
                    thirdPowerFactor(thirdPowerFactor),
                    secondPowerFactor(secondPowerFactor),
                    firstPowerFactor(firstPowerFactor),
                    yIntercept(yIntercept)
{

}

double InvertFunction::result(double x)
{
    if (minimalXValue != -1 && x < minimalXValue)
    {
        return result(minimalXValue);
    }
    else if (maximalXValue != -1 && x > maximalXValue)
    {
        return result(maximalXValue);
    }
    else
    {
        return thirdPowerFactor*cbrt(x) + secondPowerFactor*sqrt(x) + firstPowerFactor*x + yIntercept;
    }
}

RecurrentSequence::RecurrentSequence(double valueAtMinimumX,
                                     double commonDifference,
                                     double commonRatio,
                                     int minimalXValue,
                                     int maximalXValue) :
                        MathFunction(minimalXValue, maximalXValue),
                        valueAtMinimumX(valueAtMinimumX),
                        commonDifference(commonDifference),
                        commonRatio(commonRatio)
{

}

double RecurrentSequence::result(double x)
{
    int xPrime = (int)x;

    if (xPrime <= minimalXValue)
    {
        return valueAtMinimumX;
    }
    else if (maximalXValue != 1 && xPrime > maximalXValue)
    {
        return result(maximalXValue);
    }
    else
    {
        return result(xPrime - 1)*commonRatio + commonDifference;
    }
}

SequenceUsing_Sequence::SequenceUsing_Sequence(double valueAtMinimumX,
                                               double commonDifference,
                                               double commonRatio,
                                               RecurrentSequence usedSequence,
                                               int minimalXValue,
                                               int maximalXValue) :
                                    RecurrentSequence(valueAtMinimumX,
                                                      commonDifference,
                                                      commonRatio,
                                                      minimalXValue,
                                                      maximalXValue),
                                    usedSequence(usedSequence)
{

}

double SequenceUsing_Sequence::result(double x)
{
    int xPrime = (int)x;

    if (xPrime <= minimalXValue)
    {
        return valueAtMinimumX;
    }
    else if (maximalXValue != 1 && xPrime > maximalXValue)
    {
        return result(maximalXValue);
    }
    else
    {
        return result(xPrime - 1)*commonRatio + commonDifference + usedSequence.result(xPrime);
    }
}

ExponentialFunction::ExponentialFunction(bool negativeOfExponential,
                                         double exponentialFactor,
                                         double horizontalTranslater,
                                         double verticalTranslater,
                                         int minimalXValue,
                                         int maximalXValue) :
                                MathFunction(minimalXValue, maximalXValue),
                                negativeOfExponential(negativeOfExponential),
                                exponentialFactor(exponentialFactor),
                                horizontalTranslater(horizontalTranslater),
                                verticalTranslater(verticalTranslater)
{

}

double ExponentialFunction::result(double x)
{
    if (minimalXValue != -1 && x < minimalXValue)
    {
        return result(minimalXValue);
    }
    else if (maximalXValue != -1 && x > maximalXValue)
    {
        return result(maximalXValue);
    }
    else if (negativeOfExponential)
    {
        return -pow(exponentialFactor, x - horizontalTranslater) + verticalTranslater;
    }
    else
    {
        return pow(exponentialFactor, x - horizontalTranslater) + verticalTranslater;
    }
}