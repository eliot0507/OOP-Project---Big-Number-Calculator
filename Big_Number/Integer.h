#pragma once
#ifndef BASIC
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#endif
#define BASIC1
class Float;
class Int {
public:
	//string name;
	bool sign;//true->positive false->negative
	vector<int> value;
	const char type = 'i';
	Int();
	Int(int x);
	Int(const Int& rhs);
	Int(string str);
	Int(vector<int> v);
	const Int& operator =(const Int rhs);
	const Int operator +(const Int a) const;
	const Int operator -(const Int a) const;
	const Int operator *(const Int a) const;
	const Int operator /(const Int a) const;
	const Int operator ^(const Int a) const;
	const Int operator %(const Int a) const;
	const Int operator -() const;
	bool operator==(const Int rhs) const;
	bool operator>=(const Int rhs) const;
	bool operator>(const Int rhs) const;
	friend ostream& operator<<(ostream & strm,const Int& a);
	friend istream& operator>>(istream& strm, Int& a);
	const Int Fac() const;
	Int abs() const;
};



//ab+