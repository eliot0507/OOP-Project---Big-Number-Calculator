#pragma once
#include "ContinuedFraction.h"

class Fraction
{
private:
    //�Ÿ���
    bool sign;
    //�˼�
    void Invert();
public:
    //���l
    unsigned a;
    //����
    unsigned b;
    Fraction() {}
    Fraction(double a);
    Fraction(ContinuedFraction confrac);
    void Print();
    double ToDouble();
};