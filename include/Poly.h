#ifndef POLY_H
#define POLY_H
typedef struct PolyStruct* Poly;
Poly Poly_Init(unsigned int* coefs,unsigned int len);
Poly Poly_Add(const Poly a, const Poly b);
Poly Poly_Sub(const Poly a, const Poly b);
Poly Poly_Mul(const Poly a, const Poly b);
Poly Poly_Mod(const Poly a, const Poly b);
Poly Poly_GetMono(unsigned int coef, unsigned int degree); 
unsigned int Poly_Substitute(const Poly p, unsigned int a);
unsigned int Poly_GetCoef(const Poly p, unsigned int i);
Poly Poly_Copy(const Poly p);
void Poly_Free(Poly p);
#endif
