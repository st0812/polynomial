#include "GF.h"
#include <assert.h>
#include "Poly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
struct PolyStruct{
	unsigned int* coef;
	unsigned int len;
};

static int Poly_IsZero(const Poly);

Poly Poly_Init(unsigned int* coef, unsigned int len){
	assert(coef);
	assert(len>0);

	Poly poly = NULL;
	poly = (Poly)malloc(sizeof(struct PolyStruct));
	if(!poly)goto cleanup;
	unsigned int new_len=0;
	for(unsigned int i=len;i-->0;){
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

Poly Poly_Add(const Poly a, const Poly b){
	assert(a);
	assert(b);

	unsigned int len = MAX(a->len,b->len);
	unsigned int* coef;
	Poly c = NULL;

	coef = (unsigned int*)malloc(sizeof(unsigned int)*len);
	if(!coef)return NULL;
	memset(coef,0,len*sizeof(unsigned int));
	for(unsigned int i = 0 ; i< a->len; i++){
		coef[i] = GF_Add(coef[i],a->coef[i]);
	}
	for(unsigned int i = 0 ; i< b->len; i++){
		coef[i] = GF_Add(coef[i],b->coef[i]);
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

	Poly r= NULL, new_r=NULL, tmp=NULL, q=NULL;
	r = Poly_Copy(a);
	if(!r)goto cleanup;
	while(r->len>=b->len){
		unsigned int coef=GF_Div(r->coef[r->len-1],b->coef[b->len-1]);
		unsigned int degree = r->len-b->len;
		q = Poly_CreateMono(coef,degree);
		if(!q)goto cleanup;
		tmp = Poly_Mul(q,b);
		if(!tmp)goto cleanup;
		Poly_Free(q);
		q=NULL;
		new_r = Poly_Sub(r,tmp);
		if(!new_r)goto cleanup;
		Poly_Free(tmp);
		tmp=NULL;
		Poly_Free(r);
		r=new_r;
	}
	return r;
cleanup:
	Poly_Free(r);
	Poly_Free(new_r);
	Poly_Free(tmp);
	Poly_Free(q);
	return NULL;
}

Poly Poly_CreateMono(unsigned int coef, unsigned int degree){
	Poly p = NULL;
	unsigned int* coefs = (unsigned int *)malloc(sizeof(unsigned int)*(degree+1));
	if(!coefs)return NULL;
	memset(coefs,0,sizeof(unsigned int)*(degree+1));
	coefs[degree]=coef;
	p= Poly_Init(coefs, degree+1);
	free(coefs);
	if(!p)return NULL;
	return p;
}



unsigned int Poly_Substitute(const Poly p, unsigned int a){
	assert(p);
	unsigned int ans = 0;
	for(unsigned int i=p->len;i-- >0;){
		//ホーナー法
		ans = GF_Add(GF_Mul(ans,a),p->coef[i]);
	}
	return ans;
}
unsigned int Poly_Degree(const Poly p){
	return p->len-1;
}
void Poly_Coefs(const Poly p, unsigned int * coefs){
	memcpy(coefs, p->coef, p->len*sizeof(unsigned int));

}

Poly Poly_Copy(const Poly p){
	assert(p);
	return Poly_Init(p->coef,p->len);

}

void Poly_Free(Poly p){
	if(!p)return;
	free(p->coef);
	free(p);
}

static int Poly_IsZero(const Poly p){
	assert(p);
	return (p->len == 1 && p->coef[0]==0);
}


