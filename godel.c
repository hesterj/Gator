#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<vector>
#include"gmp.h"
#include<string.h>
#include<iostream>
#include"godel.h"

using namespace std;

Symbol::Symbol() {
	arity = 0;
	rep = '\0';
}
Symbol::Symbol(char r,int a) {
	arity = a;
	rep = r;
}
FSymbol::FSymbol(char r,int a) {
	arity = a;
	rep = r;
}
LSymbol::LSymbol(char r,int a) {
	arity = a;
	rep = r;
}
PSymbol::PSymbol(char r,int a) {
	arity = a;
	rep = r;
}

Disjunction::Disjunction() {
	arity = 2;
	rep = 'V';
}
/*
Existential::Existential() {
	arity = 1;
}

Existential::Existential(VTerm subject) {
	arity = 1;
			// NOT IMPLEMENTED
}
*/
Designator::Designator() {
	u = Symbol();
}
Designator::Designator(Symbol u1, std::vector<Designator> tail1) {
	u=u1;
	tail=tail1;
}
string Designator::getRep() {
	return rep;
}

Formula::Formula(){
	
}

VTerm::VTerm() {
	
}

void associative(char *a) { // (AVB)VC FROM AV(BVC), not implemented yet dont use
	int i,parenstart,parenend;
	char  *pch;
	if((pch = strchr(a,'(')) == NULL) return;
	parenstart = pch-a;
}


void disjunction(char *a,char *b) { // changes a to aVb
	strcat(a,"V");
	strcat(a,b);
}

void contraction(char *a) {  //if a = bVb for some b, reduces a to b
	int i;
	int la = strlen(a);
	int result;
	const char *ptr;
	if ((la & 1)==0) return;
	if ((ptr=strchr(a,'V'))== NULL) return;
	result = ptr-a;  // position of V in a
	char first[result],last[result];
	for (i=0;i<result;i++) last[i]=a[result+i+1];
	strncpy(first,a,result);
	if (strcmp(first,last)==0) a[result]='\0';
}


void encode(char *expr, mpz_t *t, int length) {  //encodes the godel numbering for expr in t
	int i=0;
	int powers;
	mpz_init(*t);
	mpz_set_ui(*t,1);
	mpz_t holder;
	mpz_t base;
	mpz_init(holder);
	mpz_init(base);
	mpz_set_ui(base,2);
	int temp=0;
	mpz_set_ui(*t,1);
	for (i=0;i<length;i++) {
		if (expr[i]=='0') powers=1;
		if (expr[i]=='=') powers=2;
		if (expr[i]=='S') powers=3;
		if (expr[i]=='V') powers=4;
		if (expr[i]=='-') powers=5;
		if (expr[i]=='x') powers=6;
		if (expr[i]=='y') powers=7;
		if (expr[i]=='z') powers=8;
		if (expr[i]=='+') powers=9;
		if (expr[i]=='E') powers=10;
		if (expr[i]=='[') powers=11;
		if (expr[i]==']') powers=12;
		if (expr[i]=='\0') break;
		mpz_pow_ui(holder,base,powers);
		mpz_mul(*t,*t,holder);
		mpz_nextprime(base,base);
	}
	mpz_clear(holder);
	mpz_clear(base);
	return;
}

void decode(unsigned long int *powers, int length, char *longexpression) {  // takes the array of exponents powers and decodes it into longexpression
	int i=0;
	for (i=0;i<length;i++) {
		if (powers[i]==1) longexpression[i]='0';
		if (powers[i]==2) longexpression[i]='=';
		if (powers[i]==3) longexpression[i]='S';
		if (powers[i]==4) longexpression[i]='V';
		if (powers[i]==5) longexpression[i]='-';
		if (powers[i]==6) longexpression[i]='x';
		if (powers[i]==7) longexpression[i]='y';
		if (powers[i]==8) longexpression[i]='z';
		if (powers[i]==9) longexpression[i]='+';
		if (powers[i]==10) longexpression[i]='E';	
		if (powers[i]==11) longexpression[i]='[';	
		if (powers[i]==12) longexpression[i]=']';	
	}
	return;
}

int factorize(mpz_t input, unsigned long int *exponents) {  //Factorizes input by trial division, stores resulting exponents in exponents
	int basecount=0;
	int prime = mpz_probab_prime_p(input,25);
	if (prime>=1) {
		printf("%s", "\nInput is (probably) a prime number.\n");
		return 0;
	}
	else {
		mpz_t prime;
		mpz_init_set_ui(prime, 2);
		mpz_t temp;
		mpz_init_set(temp, input);
		mpz_t sqrtinp;
		mpz_init_set(sqrtinp, input);
		mpz_sqrt(sqrtinp,input);
		int i=0;
		while(mpz_cmp(prime, sqrtinp)<=0) {
			if (mpz_cmp_ui(prime,7919)>0) break;  //More than 1000 characters, break...
			unsigned long int smoothness;
			smoothness = mpz_remove(temp, temp,prime);  
			if (smoothness==0) {
				mpz_nextprime(prime,prime);
				continue;
			}
			exponents[i]=smoothness;  
			mpz_nextprime(prime,prime);
			i++;
			basecount++;
		}
	}
	return basecount;
}

string numToString(mpz_t t) {
	int basecount=0;
	unsigned long int exponents[100];
	basecount = factorize(t,exponents);
	unsigned long int finalexponents[basecount];
	for (int j=0;j<basecount;j++) {
		finalexponents[j]=exponents[j];
	}
	char expression[basecount];
	decode(finalexponents,basecount,expression);
	string end(expression);
	return end;
}
