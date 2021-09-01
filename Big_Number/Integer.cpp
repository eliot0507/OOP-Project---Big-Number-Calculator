#include<iterator>
#include "Float.h"
#include "Integer.h"
vector<int> add(const vector<int>& a, const vector<int>& b);
void nineCom(vector<int>& v);
void tenCom(vector<int>& v);
bool absLargerEqual(Int a, Int b);
int absCompare(Int a, Int b);
void removeZero(vector<int>& v, bool remainLastZero);

//anonymous object
Int::Int()
{
	//name = "";
	sign = true;
	value.push_back(0);
}
Int::Int(int x)
{
	//name = "";
	if (x >= 0)
		sign = true;
	else
	{
		sign = false;
		x = -x;
	}
	if (x == 0)
		value.push_back(0);
	else
		while (x > 0)
		{
			value.push_back(x % 10);
			x /= 10;
		}
}
Int::Int(const Int& rhs)
{
	//name == "";
	sign = rhs.sign;
	value = rhs.value;
}
Int::Int(string str)
{
	//name = "";
	if (str[0] == '-')
	{
		sign = false;
		str.erase(0, 1);
	}
	else
		sign = true;
	int max = str.length();
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
			max = i;
	}
	for (int i = max - 1; i >= 0; i--)
	{
		value.push_back(str[i] - '0');
	}
	removeZero(value, true);
}
Int::Int(vector<int> v)
{
	sign = true;
	value = v;
}
const Int& Int::operator =(const Int rhs)
{
	sign = rhs.sign;
	value = rhs.value;
	return *this;
}
const Int Int::operator +(const Int a) const
{
	if (*this == Int(0))//0 + a = a
		return a;
	if (a == Int(0))//this + 0 = this
		return *this;
	if (sign ^ a.sign)//different sign
	{
		if (sign)//this + (-|a|) -> this - |a|
		{
			Int b = -a;//b is absolute value of a
			return *this - b;
		}
		else//-|this| + a -> a-|this|
		{
			Int b = -*this;
			return a - b;
		}
	}
	else//same sign owo
	{

		Int s;
		s.sign = sign;
		s.value = add(value, a.value);
		return s;
	}

}
const Int Int::operator -(const Int a)const
{
	if (*this == a)//a - a = 0
		return Int(0);
	if (*this == Int(0))//0 - a = -a
		return -a;
	if (a == Int(0))//this - 0 = this
		return *this;
	//this!=0  a!=0
	if (sign ^ a.sign)//different signs
	{
		//this>0 a<0, this-(-|a|)=this+|a|
		//this<0 a>0, -|this|-a=-|this|+(-|a|)
		return *this + (-a);
	}
	else//same sign
	{
		if (sign == false)//-|this|-(-|a|)=|a|-|this|
			return (-a) - (-*this);
		else//both positive, this - a = |this| - |a|
		{
			Int s;
			vector<int> left = value, right = a.value;
			//add additional digits
			if (left.size() < right.size())
				for (int i = left.size(); i < right.size(); i++)
				{
					left.push_back(0);
				}
			else if (left.size() > right.size())
				for (int i = right.size(); i < left.size(); i++)
				{
					right.push_back(0);
				}
			left.push_back(0);
			right.push_back(0);
			//make right into 10's complement
			vector<int> right_10com = right;
			tenCom(right_10com);//if a==0, it's already returned, so there's no need to consider 00000->99999->100000 situation
			right_10com = add(left, right_10com);
			if (right_10com.size() > right.size())
				right_10com.pop_back();
			if (*(right_10com.end() - 1) < 5)//positive, actually it would be 0
			{
				s.sign = true;
				right_10com.pop_back();
			}
			else//negative
			{
				s.sign = false;
				tenCom(right_10com);
			}
			//removing leading zero
			removeZero(right_10com, true);
			s.value = right_10com;
			return s;
		}
	}
}
const Int Int::operator *(const Int a)const
{
	if ((*this) == 0 || a == 0)
		return Int(0);
	Int p;
	//(+) * (-) = (-) * (+) = (-)
	//(+) * (+) = (-) * (-) = (+)
	p.sign = !(sign ^ a.sign);
	p.value = vector<int>(value.size() + a.value.size(), 0);//this: m digits, a: n digits, p: m + n (-1) digits
	for (int i = 0; i < value.size(); i++)
	{
		for (int j = 0; j < a.value.size(); j++)
		{
			int temp = value[i] * a.value[j];
			p.value[i + j] += temp;
			if (p.value[i + j] >= 10)
			{
				p.value[i + j + 1] += p.value[i + j] / 10;
				p.value[i + j] %= 10;
			}
		}
	}
	//if(largest digit == 0 -> pop back)
	if (*(p.value.end() - 1) == 0)
		p.value.pop_back();
	return p;
}
const Int Int::operator /(const Int a) const
{
	int compare = absCompare(*this, a);
	if (compare == -1)//|this| < |a| : this / a = 0
		return Int(0);
	if (compare == 0)//|this| == |a| : this / a = +-1
	{
		if ((sign ^ a.sign))
			return Int(-1);
		else
			return Int(1);
	}
	Int q(vector<int>(value.size(), 0));//q can have at most the same digits as numerator does
	q.sign = !(sign ^ a.sign);
	Int left = (*this).abs(), right = a.abs();
	int i = left.value.size() - right.value.size();
	while (absLargerEqual(left, right))
	{
		if (left.value.size() > i)
		{
			Int temp = vector<int>(left.value.begin() + i, left.value.end());
			if (absLargerEqual(temp, right))
			{
				do
				{
					temp = temp - right;
					q.value[i]++;
				} while (temp - right >= 0);
				//get remainder
				if (i == 0)
					left.value.clear();
				else
					left = vector<int>(left.value.begin(), left.value.begin() + i);
				for (int i : temp.value)
					left.value.push_back(i);
				//removing leading zero of remainder
				removeZero(left.value, false);
			}
		}
		i--;
	}
	removeZero(q.value, true);
	return q;
	/*
	Int num = (*this).abs();
	Int den = a.abs();
	while (absLargerEqual(num, den))
	{
		num = num - den;
		q.value = add(q.value, vector<int>(1, 1));
	}
	return q;*/
}
const Int Int::operator %(const Int a) const
{
	return *this - (*this / a * a);
}
const Int Int::operator ^(const Int a) const
{
	if (a == 0)
		return Int(1);
	if (!a.sign)
		return Int(0);
	//if a > 0
	if (a % 2 == 0)
		return ((*this) ^ (a / 2)) * ((*this) ^ (a / 2));
	else
		return (*this) * ((*this) ^ (a / 2)) * ((*this) ^ (a / 2));
}
const Int Int::operator -() const
{
	if ((*this) == 0)
		return (*this);
	Int n = *this;
	n.sign = !n.sign;
	return n;
}
bool Int::operator==(const Int rhs) const
{
	return sign == rhs.sign && value == rhs.value;
}
bool Int::operator>=(const Int rhs) const
{
	if (sign ^ rhs.sign)
	{
		if (sign)//(+), 0 > (-)
			return true;
		else//(-) < (+), 0
			return false;
	}
	bool compare = absLargerEqual(*this, rhs);
	if (sign)//+, 0 vs +, 0
		return compare;
	else//- -
		return !compare;
}
bool Int::operator>(const Int rhs) const
{
	if (!(*this == rhs) && (*this >= rhs))
		return true;
	else
		return false;
}
const Int Int::Fac() const
{
	if (*this == 0 || *this == 1)
		return Int(1);
	Int result(1);
	Int temp = *this;
	while (absLargerEqual(temp, 2))
	{
		result = result * temp;
		temp = temp - 1;
	}
	return result;
}
Int Int::abs() const
{
	Int a = *this;
	if (!a.sign)
		a.sign = true;
	return a;
}
ostream& operator<<(ostream& strm, const Int& a)
{
	if (!a.sign)
		strm << '-';
	for (int i = a.value.size() - 1; i >= 0; i--)
	{
		strm << a.value[i];
	}
	return strm;
}
istream& operator>>(istream& strm, Int& a)
{
	string input;
	strm >> input;
	a = Int(input);
	return strm;
}
vector<int> add(const vector<int>& a, const vector<int>& b)
{
	vector<int> longer = a;
	vector<int> shorter = b;
	vector<int> s;
	if (longer.size() < shorter.size())
		swap(longer, shorter);
	int carry = 0, i;
	for (i = 0; i < shorter.size(); i++)
	{
		int sum = carry + shorter[i] + longer[i];
		s.push_back(sum % 10);
		carry = sum / 10;
	}
	for (int j = i; j < longer.size(); j++)
	{
		int sum = carry + longer[j];
		s.push_back(sum % 10);
		carry = sum / 10;
	}
	if (carry)
		s.push_back(carry);
	return s;
}
void nineCom(vector<int>& v)
{
	for (int& i : v)
	{
		i = 9 - i;
	}
}
void tenCom(vector<int>& v)
{
	for (int& i : v)
	{
		i = 9 - i;
	}
	v = add(v, vector<int>(1, 1));
}
bool absLargerEqual(Int a, Int b)
{
	vector<int> left, right;
	left = a.value;
	right = b.value;
	if (left.size() > right.size())
		return true;
	if (left.size() < right.size())
		return false;
	for (int i = left.size() - 1; i >= 0; i--)
	{
		if (left[i] > right[i])
			return true;
		if (left[i] < right[i])
			return false;
	}
	return true;
}
int absCompare(Int a, Int b)
{
	vector<int> left, right;
	left = a.value;
	right = b.value;
	if (left.size() > right.size())
		return 1;
	if (left.size() < right.size())
		return -1;
	for (int i = left.size() - 1; i >= 0; i--)
	{
		if (left[i] > right[i])
			return 1;
		if (left[i] < right[i])
			return -1;
	}
	return 0;
}
void removeZero(vector<int>& v, bool remainLastZero)
{
	for (int i = v.size() - 1; i > 0; i--)
	{
		if (v[i] != 0)
			return;
		else
			v.pop_back();
	}
	if (v[0] == 0 && !remainLastZero)
		v.pop_back();
	return;
}