#include "ContinuedFraction.h"

ContinuedFraction::ContinuedFraction(double a)
{
    if (a < 1e-12)
    {
        nums.push_back(0);
        return;
    }
    //��l�B�I�����~�t�A�g����1e-12�ĪG�̦n
    double esp = 1e-12;
    for (int i = 0; indexZheng == -1 || i <= 2 * (indexZheng + 5); i++)
    {
        unsigned tr = (unsigned)a;
        nums.push_back(tr);
        a -= tr;
        if (a < 1e-12) //�p�Ƴ����O0, �����h�X
        {
            if (indexZheng == -1)
            {
                indexZheng = i;
            }
            return;
        }
        //�]a���Ƴ����Ӥް_���B�I���~�t�W�j
        //�Ҧp123.123�A��?0.123�A��פ]��6����?3��
        while (tr > 0)
        {
            tr /= 10;
            esp *= 10;
        }
        ////�]a���p�Ƥް_���B�I���~�t�W�j
        ////�Ҧp123.00123�A��?0.00123�A��פ]��8����?3��
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