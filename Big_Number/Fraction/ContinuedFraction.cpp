#include "ContinuedFraction.h"

ContinuedFraction::ContinuedFraction(double a)
{
    if (a < 1e-12)
    {
        nums.push_back(0);
        return;
    }
    //初始浮點型的誤差，經測試1e-12效果最好
    double esp = 1e-12;
    for (int i = 0; indexZheng == -1 || i <= 2 * (indexZheng + 5); i++)
    {
        unsigned tr = (unsigned)a;
        nums.push_back(tr);
        a -= tr;
        if (a < 1e-12) //小數部分是0, 直接退出
        {
            if (indexZheng == -1)
            {
                indexZheng = i;
            }
            return;
        }
        //因a減整數部分而引起的浮點型誤差增大
        //例如123.123，變?0.123，精度也由6位變?3位
        while (tr > 0)
        {
            tr /= 10;
            esp *= 10;
        }
        ////因a取小數引起的浮點型誤差增大
        ////例如123.00123，變?0.00123，精度也由8位變?3位
        //double t = a;
        //while (t < 0.1)
        //{
        //  t *= 10;
        //  esp *= 10;
        //}
        if (indexZheng == -1 && a < esp)
        {
            indexZheng = i;
        }
        a = 1 / a;
    }
}

double ContinuedFraction::ToDouble()
{
    double a = nums.back();
    for (auto it = nums.rbegin() + 1; it != nums.rend(); it++)
    {
        a = 1 / a;
        a += *it;
    }
    return a;
}