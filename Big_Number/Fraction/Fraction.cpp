#include "Fraction.h"
#include <cmath>
#include <vector>
#include <iostream>
Fraction::Fraction(ContinuedFraction confrac) : b(1), sign(false)
{
    a = confrac.nums.back();
    for (auto it = confrac.nums.rbegin() + 1; it != confrac.nums.rend(); it++)
    {
        Invert();
        a += b * *it;
    }
}

Fraction::Fraction(double a)
{
    sign = a < 0;
    if (sign) a = -a;

    if (a < 1e-12)
    {
        this->a = 0;
        this->b = 1;
        this->sign = false;
        return;
    }
    ContinuedFraction confrac(a);
    std::vector<unsigned> nums = confrac.nums;

    int firstIndex = confrac.indexZheng - 4;
    firstIndex = firstIndex >= 0 ? firstIndex : 0;
    confrac.nums.resize(firstIndex);

    std::vector<Fraction> vfr;
    std::vector<double> vesp;
    //一次一次增加連分數精度，並計算誤差
    for (size_t i = firstIndex; i < nums.size(); i++)
    {
        confrac.nums.push_back(nums[i]);
        Fraction fr(confrac);
        double d = fr.ToDouble();
        vfr.push_back(fr);
        vesp.push_back(abs(d - a));
    }
    //查找誤差最小的index
    int mindex = 0;
    double m = 1e100;
    for (size_t i = 0; i < vesp.size(); i++)
    {
        if (vesp[i] < m)
        {
            mindex = i;
            m = vesp[i];
        }
    }
    this->a = vfr[mindex].a;
    this->b = vfr[mindex].b;
    return;
}

void Fraction::Invert()
{
    unsigned t = a;
    a = b;
    b = t;
}

void Fraction::Print()
{
    std::cout << (sign ? "-" : "") << a << "/" << b << std::endl;
}

double Fraction::ToDouble()
{
    double n = (double)a / b;
    return sign ? -n : n;
}