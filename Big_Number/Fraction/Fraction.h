#pragma once
#include "ContinuedFraction.h"

class Fraction
{
private:
    //符號位
    bool sign;
    //倒數
    void Invert();
public:
    //分子
    unsigned a;
    //分母
    unsigned b;
    Fraction() {}
    Fraction(double a);
    Fraction(ContinuedFraction confrac);
    void Print();
    double ToDouble();
};