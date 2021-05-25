#pragma once
#include "point.h"
#include "square.h"
#include "canvas.h"
#include "stack.h"
#include <cstdlib>
#include <string>

class TPlex : public TBase 
{
protected:
	TBase* left;
	TBase* right;
public:
	TPlex();
	TPlex(TPoint* a, TPoint* b);
	TPlex(char* s);
	TPlex(const TPlex& p);

	virtual void Print();
	virtual double GetVal(int i);
	virtual void SetVal(double val, int i);

	virtual TBase* GetChild(int i);
	virtual void SetChild(TBase* c, int i);
	virtual TBase* PrintAll();
	TBase* GetLeft();
	TBase* GetRight();
	TPlex* GetLeftPlex();
	TPlex* GetRightPlex();

	void SetLeft(TBase* x);
	void SetRight(TBase* x);
	bool AddLine(TPoint* a, TPoint* b);
	virtual double& operator[](char* name);
	virtual double& operator[](int i);
	virtual int GetChildCount();
	virtual TBase* Clone();

	friend std::ostream& operator<<(std::ostream& out, const TPlex& _plex);
};

TPlex::TPlex() 
{
	left = new TPoint();
	right = new TPoint();
}

TPlex::TPlex(char* s) 
{
	int numbers = 0;
	int cc = strlen(s);
	int j = 0;
	int num = 0;

	for (int i = 0; i < cc; i++)
	{
		if (s[i] != ' ' && s[i] != ',')
		{
			j = i + 1;
			while (s[j] != ' ' && s[j] != ',')
			{
				j++;
			}

			i = j + 1;
			numbers++;
		}

	}

	if (numbers % 2 != 0 && numbers < 4)
		throw - 1;

	double* array = new double[numbers];
	std::string n = "";
	j = 0;
	numbers = 0;

	for (int i = 0; i < cc; i++)
	{
		if (s[i] != ' ' && s[i] != ',')
		{
			n += s[i];
			j = i + 1;
			while (s[j] != ' ' && s[j] != ',')
			{
				n += s[j];
				num = atoi(n.c_str());
				j++;
			}

			array[numbers] = num;
			i = j + 1;
			n = "";
			numbers++;
		}
	}

	left = new TPoint(array[0], array[1]);
	right = new TPoint(array[2], array[3]);

	for (int i = 4; i < numbers; i++)
	{
		TPoint* temp_left = new TPoint(array[i - 2], array[i - 1]);
		TPoint* temp_right = new TPoint(array[i], array[i + 1]);

		this->AddLine(temp_left, temp_right);
		i++;
	}
}

TPlex::TPlex(TPoint* a, TPoint* b) 
{
	if (a != nullptr)
		left = a;

	if (b != nullptr)
		right = b;
}

TPlex::TPlex(const TPlex& p) 
{
	left = p.left->Clone();
	right = p.right->Clone();
}

void TPlex::Print()
{
	PrintAll();
};

TBase* TPlex::PrintAll()
{
	std::cout << *this << "\n";
	return 0;
}

double TPlex::GetVal(int i) {
	throw - 1;
}

void TPlex::SetVal(double val, int i) {
	throw - 1;
}

double& TPlex::operator[](char* name) {
	throw - 1;
}

double& TPlex::operator[](int i) {
	throw - 1;
}

TBase* TPlex::GetChild(int i) {
	if (i == 0)
		return left;
	else if (i == 1)
		return right;
	else
		throw - 1;
}

void TPlex::SetChild(TBase* c, int i)
{
	if (i == 0)
		left = c;
	else if (i == 1)
		right = c;
	else
		throw - 1;
}

TBase* TPlex::GetLeft()
{
	return left;
}

TBase* TPlex::GetRight()
{
	return right;
}

TPlex* TPlex::GetLeftPlex()
{
	return dynamic_cast<TPlex*>(left);
}

TPlex* TPlex::GetRightPlex()
{
	return dynamic_cast<TPlex*>(right);
}

void TPlex::SetLeft(TBase* x)
{
	left = x;
}

void TPlex::SetRight(TBase* x)
{
	right = x;
}

bool TPlex::AddLine(TPoint* a, TPoint* b)
{
	TStack<TBase*> stack(25);
	stack.Push(this);
	bool res = false;

	while (!stack.IsEmpty())
	{

		TBase* top = stack.Get();
		TBase* right = top->GetChild(0);
		TBase* left = top->GetChild(1);


		if (right->GetChildCount() != 0)
		{
			stack.Push(right);
		} 
		else if (right == a)
		{

			TPlex* new_plex = new TPlex(a, b);
			top->SetChild(new_plex, 0);
			res = true;
			break;
		}


		if (left->GetChildCount() != 0)
		{
			stack.Push(left);
		} 
		else if (left == b)
		{

			TPlex* new_plex = new TPlex(b, a);
			top->SetChild(new_plex, 1);
			res = true;
			break;
		}
	}
	return res;
}

inline int TPlex::GetChildCount()
{
	return 2;
}

TBase* TPlex::Clone()
{
	return new TPlex(*this);
}

std::ostream& operator<<(std::ostream& out, const TPlex& _plex)
{
	TBase* base = const_cast<TPlex*>(&_plex);
	TPoint* point_first = nullptr;
	TPoint* point_second = nullptr;

	TStack<TBase*> stack(100);
	stack.Push(base);

	while (!stack.IsEmpty())
	{
		base = stack.Get();

		while (point_first == nullptr)
		{
			TBase* base_left = base->GetChild(0);
			TPlex* plex = dynamic_cast<TPlex*>(base_left);
			if (plex == nullptr)
			{
				point_first = dynamic_cast<TPoint*>(base_left);
			}
			else
			{
				stack.Push(base);
				base = base_left;
			}
		}

		while (point_second == nullptr)
		{
			TBase* base_right = base->GetChild(1);
			TPlex* plex = dynamic_cast<TPlex*>(base_right);

			if (plex == nullptr)
				point_second = dynamic_cast<TPoint*>(base_right);
			else
			{
				stack.Push(base);
				base = base_right;
			}
		}

		if (point_first != nullptr && point_second != nullptr) 
		{
			out << "Plex: " << "\n";
			out << "Point left: " << *point_first << "\n";
			out << "Point right: " << *point_second << "\n\n";

			TBase* base_temp = point_second;
			
			if (!stack.IsEmpty()) 
			{
				base = stack.Get(); 
				point_second = nullptr;
				point_first = nullptr;
			}
		}
	}
	return out;
}