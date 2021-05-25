#include <iostream>
#include "plex.h"

using namespace std;

int main()
{
	TPoint A(10, 15);
	TPoint B(25, 35);
	TPoint C(45, 55);
	TPoint D(60, 100);

	TLine AB(A, B);
	TLine BC(B, C);
	TLine CD(C, D);
	TLine DA(D, A);

	TCanvas can;

	TPlex pl(&A, &B);
	pl.AddLine(&B, &C);

	can.AddObj(&AB);

	cout << AB << endl;
	AB.Print();
	can.Print();
	pl.Print();

	TSquare sq(AB, BC, CD, DA);
	sq.Print();

	return 0;
}
