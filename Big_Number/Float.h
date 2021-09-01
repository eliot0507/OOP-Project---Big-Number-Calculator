#pragma once
#ifndef BASIC
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#endif
#define BASIC1
#include "Integer.h"
class Int;
class Float {
public:
	//string name;
	bool sign;//true->positive false->negative
	Int top;
	Int bottom;
	const char type = 'f';
	Float();
	Float(double x);
	Float(Int x);
	Float(const Float& rhs);
	Float(string value);
	//Float(string name,double value = 0.0);
	//Float(string name,Float value = 0.0);
	Float& operator =(Float rhs);
	friend Float operator +(const Float& value1, const Float& value2);
	friend Float operator -(const Float& value1, const Float& value2);
	friend Float operator *(const Float& value1, const Float& value2);
	friend Float operator /(const Float& value1, const Float& value2);
	friend Float operator ^(const Float& value1, const Float& n);
	Float operator -() const;
	friend ostream& operator<<(ostream& strm, const Float& a);
	friend istream& operator>>(istream& strm, Float& a);
	bool operator==(const Float rhs) const;
	bool operator>=(const Float rhs) const;
	Int Fac();
	Float abs();
};