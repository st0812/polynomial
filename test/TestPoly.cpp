#include "CppUTest/TestHarness.h"
extern "C" {
 #include "Poly.h"
 #include "GF.h"
}


TEST_GROUP(Poly)
{
	void setup(){
		GF_Init(0x13);
	}
	void teardown(){

	}
};





TEST(Poly, Add_Min)
{	
	unsigned int coef_a[1] = {0};
	unsigned int coef_b[1] = {0};
	Poly a = Poly_Init(coef_a,1);
	Poly b = Poly_Init(coef_b,1);
	Poly c = Poly_Add(a,b);
	LONGS_EQUAL(0,Poly_GetCoef(c,0));
};

TEST(Poly, Add_Typ1)
{	
	unsigned int coef_a[2] = {7,5};
	unsigned int coef_b[3] = {7,3,14};
	Poly a = Poly_Init(coef_a,2);
	Poly b = Poly_Init(coef_b,3);
	Poly c = Poly_Add(a,b);
	LONGS_EQUAL(0,Poly_GetCoef(c,0));
	LONGS_EQUAL(6,Poly_GetCoef(c,1));
	LONGS_EQUAL(14,Poly_GetCoef(c,2));
};

TEST(Poly, Add_Max)
{	
	unsigned int coef_a[1] = {0x0F};
	unsigned int coef_b[1] = {0x0F};
	Poly a = Poly_Init(coef_a,1);
	Poly b = Poly_Init(coef_b,1);
	Poly c = Poly_Add(a,b);
	LONGS_EQUAL(0,Poly_GetCoef(c,0));
};


TEST(Poly, Mul)
{	
	unsigned int coef_a[2] = {6,8};
	unsigned int coef_b[2] = {4,9};
	Poly a = Poly_Init(coef_a,2);
	Poly b = Poly_Init(coef_b,2);
	Poly c = Poly_Mul(a,b);
	LONGS_EQUAL(11,Poly_GetCoef(c,0));
	LONGS_EQUAL(5,Poly_GetCoef(c,1));
	LONGS_EQUAL(4,Poly_GetCoef(c,2));
};

TEST(Poly, Mul2)
{	
	unsigned int coef_a[2] = {0,1};
	unsigned int coef_b[3] = {0,0,1};
	Poly a = Poly_Init(coef_a,2);
	Poly b = Poly_Init(coef_b,3);
	Poly c = Poly_Mul(a,b);
	LONGS_EQUAL(0,Poly_GetCoef(c,0));
	LONGS_EQUAL(0,Poly_GetCoef(c,1));
	LONGS_EQUAL(0,Poly_GetCoef(c,2));
	LONGS_EQUAL(1,Poly_GetCoef(c,3));
};

TEST(Poly, Mod)
{	
	unsigned int coef_a[2] = {9,12};
	unsigned int coef_b[2] = {3,5};
	Poly a = Poly_Init(coef_a,2);
	Poly b = Poly_Init(coef_b,2);
	Poly c = Poly_Mod(a,b);
	LONGS_EQUAL(13,Poly_GetCoef(c,0));
};


TEST(Poly, Mod2)
{	
	unsigned int coef_a[3] = {0,0,12};
	unsigned int coef_b[2] = {0,5};
	Poly a = Poly_Init(coef_a,3);
	Poly b = Poly_Init(coef_b,2);
	Poly c = Poly_Mod(a,b);
	LONGS_EQUAL(0,Poly_GetCoef(c,0));
};

TEST(Poly, Substitute1)
{
	unsigned int coef_a[1] = {5};
	Poly a = Poly_Init(coef_a,1);
	LONGS_EQUAL(5,Poly_Substitute(a,10));
}

TEST(Poly, Substitute2)
{
	unsigned int coef_a[2] = {1,1};
	Poly a = Poly_Init(coef_a,2);
	LONGS_EQUAL(4,Poly_Substitute(a,5));
}











