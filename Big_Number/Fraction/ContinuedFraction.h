#pragma once
#include <vector>

class ContinuedFraction
{
private:
    //ノ玂硈だ计
    std::vector<unsigned> nums;
    int indexZheng = -1;
public:
    //计锣?硈だ计篶硑ㄧ计
    ContinuedFraction(double a);
    //硈だ计锣?计
    double ToDouble();
    friend class Fraction;
};