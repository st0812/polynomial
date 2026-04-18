#include "GF.h"
#include <assert.h>
#include "Poly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct PolyStruct{
	unsigned int* coef;
	size_t len;
};
static int Poly_IsZero(const Poly);
static Poly Poly_Scale(const Poly p, unsigned int scalar);
static Poly Poly_Shift(const Poly p, unsigned int degree);

Poly Poly_Init(const unsigned int* coef, unsigned int len){
	assert(coef);
	assert(len>0);

	Poly poly = NULL;
	poly = (Poly)malloc(sizeof(struct PolyStruct));
	if(!poly)goto cleanup;
	//配列長の正規化 
	size_t new_len=0;
	for(size_t i=len;i-->0;){
		if(coef[i] != 0 ){
			new_len = i+1;
			break;
		}
	}
	if(new_len==0)new_len=1;
	poly->len = new_len;
	poly->coef = (unsigned int*)malloc(sizeof(unsigned int)*poly->len);
	if(!(poly->coef))goto cleanup;
	memcpy(poly->coef, coef, poly->len*sizeof(unsigned int));
	return poly;

cleanup:
	Poly_Free(poly);
	return NULL;
}

void Poly_Free(Poly p){
	if(!p)return;
	free(p->coef);
	free(p);
}

size_t Poly_Length(const Poly p){
	assert(p);
	return p->len;
}
const unsigned int * Poly_Data(const Poly p){
	assert(p);
	return p->coef;
}

Poly Poly_Add(const Poly a, const Poly b){
	assert(a);
	assert(b);

	unsigned int len = MAX(a->len,b->len);
	unsigned int* coef;
	Poly c = NULL;

	coef = (unsigned int*)malloc(sizeof(unsigned int)*len);
	if(!coef)return NULL;

	for (unsigned int i = 0; i < len; i++) {
    		unsigned int ac = (i < a->len) ? a->coef[i] : 0;
    		unsigned int bc = (i < b->len) ? b->coef[i] : 0;
    		coef[i] = GF_Add(ac, bc);
	}
	c = Poly_Init(coef,len);
	free(coef);
	if(!c)return NULL;
	return c;
}

Poly Poly_Sub(const Poly a, const Poly b){
	return Poly_Add(a,b);
}

Poly Poly_Mul(const Poly a, const Poly b){
	assert(a);
	assert(b);

	Poly c = NULL;
	unsigned int len = a->len + b->len - 1;
	unsigned int* coef;

	coef = (unsigned int*)malloc(sizeof(unsigned int)*len);
	if(!coef)return NULL;
	memset(coef,0,len*sizeof(unsigned int));
	for(unsigned int i = 0 ; i< a->len; i++){
		for(unsigned int j = 0 ; j< b->len; j++){
			coef[i+j] = GF_Add(coef[i+j],GF_Mul(a->coef[i],b->coef[j]));
		}
	}
	c = Poly_Init(coef,len);
	free(coef);
	if(!c)return NULL;
	return c;
}

Poly Poly_Mod(const Poly a, const Poly b){
	assert(a);
	assert(b);
	assert(!Poly_IsZero(b));

	Poly r= NULL, new_r=NULL, tmp=NULL, tmp2 =NULL;
	r = Poly_Copy(a);
	if(!r)goto cleanup;
	while(r->len>=b->len){
		unsigned int coef=GF_Div(r->coef[r->len-1],b->coef[b->len-1]);
		unsigned int degree = r->len-b->len;
		tmp=Poly_Scale(b,coef);
		if(!tmp)goto cleanup;
		tmp2 = Poly_Shift(tmp,degree);
		Poly_Free(tmp);
		tmp=NULL;
		if(!tmp2)goto cleanup;
		new_r = Poly_Sub(r,tmp2);
		Poly_Free(tmp2);
		tmp2=NULL;
		if(!new_r)goto cleanup;
		Poly_Free(r);
		r=new_r;
	}
	return r;
cleanup:
	Poly_Free(r);
	Poly_Free(new_r);
	Poly_Free(tmp);
	Poly_Free(tmp2);
	return NULL;
}

unsigned int Poly_Eval(const Poly p, unsigned int a){
	assert(p);

	unsigned int ans = 0;
	for(size_t i=p->len;i-- >0;){
		//ホーナー法
		ans = GF_Add(GF_Mul(ans,a),p->coef[i]);
	}
	return ans;
}

static Poly Poly_Scale(const Poly p, unsigned int scalar){
	assert(p);

	Poly tmp=Poly_Init(&scalar,1);
	if(!tmp)return NULL;
	Poly result=Poly_Mul(p,tmp);
	Poly_Free(tmp);
	return result;
}

static Poly Poly_Shift(const Poly p, unsigned int degree){
	assert(p);

  	Poly result = NULL;
        unsigned int* coefs = (unsigned int *)malloc(sizeof(unsigned int)*(degree+p->len));
        if(!coefs)return NULL;
        memset(coefs,0,sizeof(unsigned int)*degree);
	memcpy(coefs+degree,p->coef,sizeof(unsigned int)*p->len);
        result= Poly_Init(coefs, degree+p->len);
        free(coefs);
        if(!result)return NULL;
        return result;	
}

static int Poly_IsZero(const Poly p){
	assert(p);

	return (p->len == 1 && p->coef[0]==0);
}

 Poly Poly_Copy(const Poly p){
	assert(p);

	return Poly_Init(p->coef,p->len);
}
