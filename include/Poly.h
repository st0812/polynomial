#ifndef POLY_H
#define POLY_H
#include <stddef.h>
typedef struct PolyStruct* Poly;
Poly Poly_Init(const unsigned int* coefs,unsigned int len);
void Poly_Free(Poly p);
size_t Poly_Length(const Poly p);
const unsigned int * Poly_Data(const Poly p);
Poly Poly_Add(const Poly a, const Poly b);
Poly Poly_Sub(const Poly a, const Poly b);
Poly Poly_Mul(const Poly a, const Poly b);
Poly Poly_Mod(const Poly a, const Poly b);
unsigned int Poly_Eval(const Poly p, unsigned int a);
#endif
