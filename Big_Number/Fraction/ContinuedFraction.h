#pragma once
#include <vector>

class ContinuedFraction
{
private:
    //�Ω�O�s�s���ƦC��
    std::vector<unsigned> nums;
    int indexZheng = -1;
public:
    //�p����?�s���ƪ��c�y���
    ContinuedFraction(double a);
    //�s������?�p��
    double ToDouble();
    friend class Fraction;
};