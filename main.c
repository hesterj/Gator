#include"gmp.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include <time.h>
#include "godel.h"

using namespace std;

int main(int argc, char **argv) {
	if (argv[1] == "-d") {
		
	}
	if (argv[1] == "-e") {
		
	}
	VTerm w = VTerm("w");
	VTerm x = VTerm("x");
	VTerm y = VTerm("y");
	VTerm z = VTerm("z");
	

	/*  CUT RULE EXAMPLE
	Formula a = equals(x,x);
	Formula b = equals(w,z);
	Formula c = equals(x,z);
	Formula temp = fNegation(a);
	temp = fExpansion(temp,c);
	temp = fNegation(temp);
	
	Formula f = fExpansion(a,b);
	f = fNegation(f);
	f = fExpansion(f,temp);
	f = fNegation(f);	
	f = fCut(f);   */
	
	 /*  INSTANTIATION RULE EXAMPLE
	Formula a = equals(x,x);
	Formula b = equals(w,z);
	Formula c = equals(x,z);
	a = fexIntroduction(a,x);
	b = fNegation(b);
	Formula f = fExpansion(a,b);
	f = fDisSwitch(f);  
	f = fEintroductionRule(f,x);	*/
	//
	
	Formula a = equals(x,x);
	Formula b = equals(w,z);
	Formula c = equals(x,z);
	a = fexIntroduction(a,x);
	b = fNegation(b);
	Formula f = fExpansion(a,b);
	f = fDisSwitch(f);  
	f = fEintroductionRule(f,x);
	srand (time(NULL));
	for (int i=0;i<1000; i++) {
		int other = 0;
		int choice = 0;
		choice = rand()%5;
		printf("%d\n", choice);
		if (choice == 0) {
			other = rand()%3;
			if (other == 0) {
				f = fExpansion(f,a);
			}
			if (other == 1) {
				f = fExpansion(f,b);
			}
			if (other == 2) {
				f = fExpansion(f,c);
			}
		}
		if (choice == 1) {
			f = fAssociative(f);
		}
		if (choice == 2) {
			f = fContraction(f);
		}
		if (choice == 3) {
			f = fEintroductionRule(f,x);
			f = fEintroductionRule(f,y);
			f = fEintroductionRule(f,z);
		}
		if (choice == 4) {
			f = fCut(f);
		}
		
		cout << f.getRep() << endl;
		string repe = f.getRep();
		//cout << repe << endl;
		char *e = new char[repe.length()+1];
		strcpy(e,repe.c_str());
		mpz_t t;
		mpz_init(t);
		
		encode(e,&t,repe.length()+1);
		//mpz_out_str(stdout,10,t);
		puts("");
		
		string end = numToString(t);
		//cout << end << endl;
	}
	cout << f.getRep() << endl;
	return 0;
}
