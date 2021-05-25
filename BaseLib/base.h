#pragma once
#include <iostream>
#include <vector>

class TBase 
{
public:
	TBase() {};

	virtual void Print() = 0;
	virtual double GetVal(int i) = 0;
	virtual void SetVal(double val, int i) = 0;
	virtual TBase* GetChild(int i) = 0;
	virtual void SetChild(TBase* c, int i) = 0;
	virtual int GetChildCount();
	virtual TBase* PrintAll();
	virtual TBase* Clone() = 0;

	virtual double& operator[](char* name) = 0;
	virtual double& operator[](int i) = 0;
};

int TBase::GetChildCount()
{
	return 0;
}

TBase* TBase::PrintAll()
{
	return this;
}
