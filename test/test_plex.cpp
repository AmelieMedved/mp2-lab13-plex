#include <gtest.h>
#include "plex.h"

TEST(TPlex, can_create_empty_plex) 
{
  ASSERT_NO_THROW(TPlex A);
}

TEST(TPlex, can_create_non_empty_plex) 
{
	TPoint A(5, 15);
	TPoint B(25, 35);
	
  ASSERT_NO_THROW(TPlex q(&A, &B));
}

TEST(TPlex, can_create_plex_from_char) 
{
	TPoint A('a', 'b');
	TPoint B('c', 'd');

	ASSERT_NO_THROW(TPlex q(&A, &B));
}

TEST(TPlex, can_add_line_in_plex) 
{
	TPoint A(10, 15);
	TPoint B(25, 35);
	TPoint C(45, 55);

	TPlex pl(&A, &B);
	
  ASSERT_NO_THROW(pl.AddLine(&B, &C));
}

TEST(TLine, can_create_line)
{
	TPoint A(10, 25);
	TPoint B(35, 45);

	ASSERT_NO_THROW(TLine AB(A, B));
}

TEST(TSquare, can_create_square) 
{
	TPoint A(10, 15);
	TPoint B(25, 35);
	TPoint C(45, 55);
	TPoint D(60, 100);

	TLine AB(A, B);
	TLine BC(B, C);
	TLine CD(C, D);
	TLine DA(D, A);

	ASSERT_NO_THROW(TSquare sq(AB, BC, CD, DA));
}

TEST(TCanvas, can_get_empty_canvas)
{
	ASSERT_NO_THROW(TCanvas can);
}

TEST(TCanvas, can_get_canvas_from_plex) 
{
	TPoint A(5, 10);
	TPoint B(15, 25);

	TPlex pl(&A, &B);

	TCanvas can;
	ASSERT_NO_THROW(can.AddObj(&pl));
}

TEST(TCanvas, can_get_canvas_from_line)
{
	TPoint A(5, 10);
	TPoint B(15, 25);

	TLine AB(A, B);

	TCanvas can;
	ASSERT_NO_THROW(can.AddObj(&AB));
}

TEST(TCanvas, can_get_canvas_from_point)
{
	TPoint A(5, 10);

	TCanvas can;
	ASSERT_NO_THROW(can.AddObj(&A));
}

TEST(TCanvas, can_get_canvas_from_square)
{
	TPoint A(10, 15);
	TPoint B(25, 35);
	TPoint C(45, 55);
	TPoint D(60, 100);

	TLine AB(A, B);
	TLine BC(B, C);
	TLine CD(C, D);
	TLine DA(D, A);

	TSquare sq(AB, BC, CD, DA);

	TCanvas can;
	ASSERT_NO_THROW(can.AddObj(&sq));
}

TEST(Print, can_use_print_to_point)
{
	TPoint A(10, 15);
	ASSERT_NO_THROW(A.Print());
}

TEST(Print, can_use_print_to_plex)
{
	TPoint A(10, 15);
	TPoint B(25, 35);
	TPoint C(45, 55);
	TPoint D(60, 100);

	TPlex pl(&A, &B);
	ASSERT_NO_THROW(pl.Print());
}

TEST(Print, can_use_print_to_plex_char)
{
	char* str = "1, 2, 3, 4";

	TPlex pl(str);
	ASSERT_NO_THROW(pl.Print());
}


TEST(Print, can_use_print_to_line)
{
	TPoint A(10, 15);
	TPoint B(25, 35);

	TLine AB(A, B);
	ASSERT_NO_THROW(AB.Print());
}

