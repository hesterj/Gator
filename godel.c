#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<vector>
#include"gmp.h"
#include<string.h>
#include<iostream>
#include"godel.h"
#include "symbols.h"
#include "designator.h"

using namespace std;

Symbol::Symbol() {
	arity = -1;
	rep = '\0';
}
Symbol::Symbol(string r,int a) {
	arity = a;
	rep = r;
}
void Container::setArity(int a) {
	arity = a;
}
int Container::getArity() {
	return arity;
}
void Container::setRep(string a) {
	rep = a;
}
string Container::getRep() {
	return rep;
}
FSymbol::FSymbol(string r,int a) {
	arity = a;
	rep = r;
}
LSymbol::LSymbol(string r,int a) {
	arity = a;
	rep = r;
}
PSymbol::PSymbol(string r,int a) {
	arity = a;
	rep = r;
}
PSymbol::PSymbol() {}
Equals::Equals() {
	arity = 2;
	rep = "=";
}
LSymbol::LSymbol() {
	arity = -1;
	rep = "\0";
}
Negation::Negation() {
	arity = 1;
	rep = "-";
}
Disjunction::Disjunction() {
	arity = 2;
	rep = "V";
}
Existential::Existential() {
	arity = 2;
	rep = "E";
}
Designator::Designator() {
	u = Symbol();
}
Designator::Designator(Symbol u1, std::vector<Designator> tail1) {
	u=u1;
	tail=tail1;
}
Formula::Formula(){
	valid = -1;
	tag = 0;
	}
DisFormula::DisFormula(){
	valid = -1;
	tag = 1;
	}
void Formula::setValid() {valid = 1;}
Formula::Formula(Designator inp) {
	u = inp.u;
	if (u.rep == "V") tag = 1;
	tail = inp.tail;
	valid = 0;
	rep = inp.rep;
}
VTerm::VTerm() {
	arity = 0;
	rep = "x";
}
VTerm::VTerm(string inp) {
	arity = 0;
	rep = inp;
	u=Symbol(rep,0);
}
Term::Term() {}

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
		if (expr[i]=='w') powers=13;
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
		if (powers[i]==13) longexpression[i]='w';
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
	unsigned long int exponents[1000];
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

Formula equals(Term a, Term b) {
	Formula r = Formula();
	r.u = Equals();
	r.tail.push_back(a);
	r.tail.push_back(b);
	r.rep = r.u.getRep() + a.getRep() + b.getRep();
	return r;
}

Formula fExpansion(Formula a, Formula b) {
	Formula r = Formula();
	r.u = Disjunction();
	if ((a.valid==1) || (b.valid==1)) r.setValid();
	r.tail.push_back(a);
	r.tail.push_back(b);
	r.tag = 1;  // mark as disjunction
	r.rep = r.u.getRep() + a.getRep() + b.getRep();
	return r;
}

Formula fNegation(Formula a) {  
	Formula r = Formula();
	r.u = Negation();
	r.tail.push_back(a);
	r.rep = r.u.getRep() + a.getRep();
	r.tag = 2;
	return r;
}

Formula fexIntroduction(Formula a,VTerm b) { // not *fully* tested
	Formula r = Formula();
	r.u = Existential();
	r.tail.push_back(b);
	r.tail.push_back(a);
	r.rep = r.u.getRep()+ b.getRep() + a.getRep();
	return r;
}

Formula fContraction(Formula a) {  
	Formula r = Formula();
	if (a.u.rep != "V") return a;
	if (a.tail.at(0).tag==1) a.tail.at(0) = fContraction(a.tail.at(0));
	if (a.tail.at(1).tag==1) a.tail.at(1) = fContraction(a.tail.at(1));
	if (a.tag == 1) {
		if (a.tail.at(0).rep == a.tail.at(1).rep) {
			r = Formula(a.tail.at(0));
			if (a.valid==1) r.setValid();
			return r;
		}
	}
	return a;
}
			
Formula fAssociative(Formula a) {  
	Formula r = Formula();
	if (a.valid==1) r.valid =1;
	if (a.u.rep != "V") return a;
	if ((a.tail.at(1).u.rep!="V")&&(a.tail.at(1).u.rep!="V")) return a;
	r.u = a.u;
	r.tail.clear();
	r.tail.push_back(a.tail.at(1));
	r.tail.push_back(a.tail.at(0));
	r.rep = r.u.getRep() + r.tail.at(0).getRep() + r.tail.at(1).getRep();
	return r;
}

Formula fDisSwitch(Formula a) { //untested
	if (a.u.rep == "V") {
		Formula r = Formula();
		r.valid = a.valid;
		r.tail.clear();
		r.tail.push_back(a.tail.at(1));
		r.tail.push_back(a.tail.at(0));
		r.rep = r.u.getRep() + r.tail.at(0).getRep() + r.tail.at(1).getRep();
		return r;
	}
	return a;
}

Formula fCut(Formula a) {	// untested
	if (a.u.rep != "-") return a;
	if (a.tail.at(0).u.rep != "V") return a;
	if (a.tail.at(0).tail.at(0).u.rep != "-") return a;
	if (a.tail.at(0).tail.at(1).u.rep != "-") return a;
	if (a.tail.at(0).tail.at(1).tail.at(0).u.rep != "V") return a;
	if (a.tail.at(0).tail.at(0).tail.at(0).u.rep != "V") return a;
	if (a.tail.at(0).tail.at(1).tail.at(0).tail.at(0).u.rep != "-") return a;
	if (a.tail.at(0).tail.at(0).tail.at(0).tail.at(0).rep != a.tail.at(0).tail.at(1).tail.at(0).tail.at(0).tail.at(0).rep) return a;
	Formula r = Formula();
	r.u = Disjunction();
	r.tail.push_back(a.tail.at(0).tail.at(0).tail.at(0).tail.at(1));
	r.tail.push_back(a.tail.at(0).tail.at(1).tail.at(0).tail.at(1));
	r.rep = r.u.getRep() + r.tail.at(0).getRep() + r.tail.at(1).getRep();
	return r;
}

int boundInA(Formula a, VTerm x) {
	int tlength = a.tail.size();
	if (tlength == 0) return 0;
	else {
		if (a.u.rep == "E") {
			if (a.tail.at(0).rep == x.rep) return 1;
		}
	}
	int search = 0;
	for (int i = 0; i<tlength; i++) {
		search = boundInA(a.tail.at(i),x);
		if (search == 1) return 1;
	}
	return search;
}

Formula fEintroductionRule(Formula a, VTerm x) {  // untested
	if (a.u.rep != "V") return a;
	if (a.tail.at(0).u.rep != "-") return a;
	if ( boundInA(a.tail.at(1),x)==1) {
		Formula r = Formula(a);
		r = fexIntroduction(a,x);
		return r;
	}
	return a;
}
