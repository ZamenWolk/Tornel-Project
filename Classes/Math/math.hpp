#ifndef CLASSES_MATH_MATH
#define CLASSES_MATH_MATH

class MathFunction
{
public:

    MathFunction(int minimalXValue = -1, int maximalXValue = -1);

    virtual double result(double x) = 0;

    int iresult(double x);

protected:

    int minimalXValue,
        maximalXValue;
};

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

protected:

    double thirdPowerFactor,
           secondPowerFactor,
           firstPowerFactor,
           yIntercept;

};

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

protected:

    double thirdPowerFactor,
           secondPowerFactor,
           firstPowerFactor,
           yIntercept;

};

class RecurrentSequence : public MathFunction
{
public:

    RecurrentSequence(double valueAtMinimumX = 0,
                      double commonDifference = 0,
                      double commonRatio = 1,
                      int minimalXValue = 0,
                      int maximalXValue = -1);

    virtual double result(double x);

protected:

    double valueAtMinimumX,
           commonDifference,
           commonRatio;
};

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

protected:

    RecurrentSequence usedSequence;
};

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

protected:

    bool   negativeOfExponential;
    double exponentialFactor,
           horizontalTranslater,
           verticalTranslater;
};

#endif