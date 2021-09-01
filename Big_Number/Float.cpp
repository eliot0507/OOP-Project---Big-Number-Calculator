#include <sstream>
#include "Integer.h"
#include "Float.h"
#include "Fraction/Fraction.h"

void to100places(Int a,Int b,int acc, ostream& strm);
Float squareRoot(Float a);
Int gcd(Int n1, Int n2)
{
	if (n2 == 0)
	{
		return n1;
	}
	else
	{
		return gcd(n2, n1 % n2);
	}
	
}
Float::Float()
{
	//name = "";
	sign = true;
	top = 0;
	bottom = 1;
}
Float::Float(double x)
{
	//name = "";
	if (x >= 0)
	{
		sign = true;
	}
	else
	{
		sign = false;
	}
	//top
	Fraction ff(x);
	top = ff.a;
	//bottom
	bottom = ff.b;
}
Float::Float(Int x)
{
	sign = x.sign;
	bottom = 1;
	if (sign == false)
	{
		top = -x;//if(x<0) sign=0 top=abs(x)
	}
	else
		top = x;
}
Float::Float(const Float& rhs)
{
	//name = "";
	sign = rhs.sign;
	top = rhs.top;
	bottom = rhs.bottom;
}
Float::Float(string value)
{
	//name = "";
	if (value[0] == '-')
	{
		sign = false;
		value.erase(0, 1);
	}
	else
		sign = true;

	int point_id = value.length();
	for (int i = 0; i < value.length(); ++i)
	{
		if (value[i] == '.')
		{
			point_id = i;
			break;
		}
	}
	int fraction_length = value.length() - 1 - point_id; //小數點後有幾位數
	if(point_id != value.length())
		value.erase(point_id, 1); //移除.
	string multiplier = "1";
	for (int i = 1; i <= fraction_length; i++)
	{
		multiplier.push_back('0');
	}
	//top --> sum = value * multiplier
	//bottom --> multiplier
	Int v(value);
	Int m(multiplier);
	top = v;
	bottom = m;
	if (v == 0)
		bottom = 1;
	else
	{
		Int g = gcd(top, bottom);
		top = top / g;
		bottom = bottom / g;
	}
}
//operator
Float& Float::operator =(Float rhs)
{
	sign = rhs.sign;
	top = rhs.top;
	bottom = rhs.bottom;
	return rhs;
}
Float operator +(const Float& value1, const Float& value2)
{
	Int temp_top, temp_bottom;
	Int a = value1.top, b = value1.bottom, c = value2.top, d = value2.bottom;//a/b + c/d
	if (!value1.sign)
		a = -a;
	if (!value2.sign)
		c = -c;
	temp_bottom = b * d;
	temp_top = a * d + b * c;
	Float sum;
	if (temp_top >= 0)
		sum.sign = true;
	else
	{
		sum.sign = false;
		temp_top = -temp_top;
	}
	Int g = gcd(temp_top, temp_bottom);
	sum.top = temp_top / g;
	sum.bottom = temp_bottom / g;
	return sum;
}
Float operator -(const Float& value1, const Float& value2)
{
	Int temp_top, temp_bottom;
	Int a = value1.top, b = value1.bottom, c = value2.top, d = value2.bottom;
	if (!value1.sign)
		a = -a;
	if (!value2.sign)
		c = -c;
	temp_bottom = b * d;
	temp_top = a * d - c * b;
	Float sum;
	if (temp_top >= 0)
		sum.sign = true;
	else
	{
		sum.sign = false;
		temp_top = -temp_top;
	}
	Int g = gcd(temp_top, temp_bottom);
	sum.top = temp_top / g;
	sum.bottom = temp_bottom / g;
	return sum;
}
Float operator *(const Float& value1, const Float& value2)
{
	Int temp_top, temp_bottom;
	temp_bottom = value1.bottom * value2.bottom;
	temp_top = value1.top * value2.top;
	Float sum;
	if (value1.sign == value2.sign)
		sum.sign = true;
	else
		sum.sign = false;
	Int g = gcd(temp_top, temp_bottom);
	sum.top = temp_top / g;
	sum.bottom = temp_bottom / g;
	return sum;
}
Float operator /(const Float& value1, const Float& value2)
{
	Int temp_top, temp_bottom;
	temp_bottom = value1.bottom * value2.top;
	temp_top = value1.top * value2.bottom;
	Float sum;
	if (value1.sign == value2.sign)
		sum.sign = true;
	else
		sum.sign = false;
	Int g = gcd(temp_top, temp_bottom);
	sum.top = temp_top / g;
	sum.bottom = temp_bottom / g;
	return sum;
}
Float Float::operator -() const
{
	if (*this == 0)//-0=0
		return *this;
	Float result;
	result.sign = !(*this).sign;
	result.top = top;
	result.bottom = bottom;
	return result;
}
Float operator ^(const Float& value1, const Float& n)
{
	if (value1 == 1)//1^x = 1
		return value1;
	if (value1 == 0 && n >= 0.5)//0^x = 0 for x>0 
		return value1;
	//value != 0 or 1
	if (n == 0)
		return 1;
	if (n == 1)
		return value1;
	if (n == 0.5)
	{
		return squareRoot(value1) ;
	}	
	if (!(n >= 0))//n is negative
		return 1 / (value1 ^ (-n));
	if (n.bottom == 1)//n is integer greater than 1
	{
		if (n.top % 2 == 0)
			return (value1 ^ (n / 2)) * (value1 ^ (n / 2));
		else
			return value1 * (value1 ^ (n - 1));
	}
	else//n is decimal greater than 0.5
	{
		return (value1 ^ 0.5) * (value1 ^ (n - 0.5));
	}
}
ostream& operator<<(ostream& strm,const Float& a)
{
	if (!a.sign)
		strm << '-';
	Int temp1,temp2;
	temp1 = a.top / a.bottom;
	temp2 = a.top % a.bottom;
	strm << temp1 << '.';
	to100places(temp2, a.bottom,100, strm);
	return strm;
}
istream& operator>>(istream& strm, Float& a)
{
	string input;
	strm >> input;
	a = Float(input);
	return strm;
}
bool Float::operator==(const Float rhs) const
{
	if (sign == rhs.sign && top == rhs.top && bottom == rhs.bottom) 
	{
		return true;
	}
	else 
	{
		return false;
	}

}
bool Float::operator>=(const Float rhs) const
{
	if (*this == rhs)
		return true;
	//this != rhs
	if (sign ^ rhs.sign)
	{
		if (sign)//(+), 0 > (-)
			return true;
		else//(-) < (+), 0
			return false;
	}
	//通分
	Int ltop, rtop;
	ltop = top * rhs.bottom;
	rtop = rhs.top * bottom;
	bool compare = (ltop >= rtop);
	if (sign)
	{
		return compare;
	}
	else
		return !compare;
}
Int Float::Fac()
{
	return top.Fac();
}
Float Float::abs()
{
	if (!sign)
		return -(*this);
	else
		return (*this);
}
void to100places(Int a,Int b,int acc, ostream& strm)
{
	int c = 0;
	a = a * 10;
	while (c < acc)
	{
		if (a == 0)
		{
			for (int i = c; i < acc; i++)
				strm << 0;
			break;
		}
		if (a >= b)
		{
			strm << a / b;
			a = a % b * 10;
		}
		else
		{
			strm << 0;
			a = a * 10;
		}
		c++;
	}
}
Float squareRoot(Float a)
{
	/*Float err = 1;
	//Float fine = 1;
	for (int i = 0; i < 100; i++)
	{
		err = err / 10;
		//fine = fine * 10;
	}
	Float x_n, x_n1(2);
	do
	{
		x_n = x_n1;
		x_n1 = (x_n + a / x_n) / 2;
		//x_n1 = x_n - ((2 * x_n * x_n * x_n - 2 * a * x_n) / (2 * x_n * x_n + a));
		//cout <<x_n << endl <<x_n1 << endl << (x_n1 - x_n) <<endl<<"--------"<<endl;
	} while ((x_n1-x_n).abs()>=err);
	return x_n1;*/
	
	 stringstream ss;
	 to100places(a.top, a.bottom, 200, ss);
	 string str=ss.str();
	 for(int i=0;i<str.size();i++)
	 {
		if(str[i]=='.')
			str.erase(i,1);
	 }
	 string result;
	 int i, i_last = 0;
	 if(str.size()%2)
		i=1;
	 else
		i=2;
	 Int x=0;
	 Int part=0;
	 for(;i<=str.size();i_last=i,i+=2)
	 {
		x = x * 10;
		part = part * 100;
		part = part + Int(string(str.begin() + i_last, str.begin() + i));
		int j;
		for (j = 1; j < 10; j++)
		{
			if ((x + j) * j > part)
				break;
		}
		j = j - 1;
		result += to_string(j);
		part = part - (x + j) * j;
		x = x + j + j;
	 }
	 result.insert(result.size()-100,".");
	 return Float(result);
	
	
}
