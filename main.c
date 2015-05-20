#include"gmp.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include "godel.h"
#include "symbols.h"
#include "designator.h"

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
	Formula a = equals(x,y);
	Formula b = equals(w,z);
	Formula c = fExpansion(a,a);
	Formula temp = fExpansion(c,c);
	temp = fNegation(temp);
	Formula f = temp;
	f = fContraction(f);
	f = fexIntroduction(f,x);
	f = fexIntroduction(f,y);
	f = fExpansion(f,a);
	f = fexIntroduction(f,x);
	f = fexIntroduction(f,y);
	f = fExpansion(f,f);
	f = fExpansion(f,f);
	f = fExpansion(f,f);
	f = fExpansion(f,f);
	f = fExpansion(f,f);

	string temprep = temp.getRep();
	string repe = f.getRep();
	cout << temprep << endl;
	cout << repe << endl;
	char *e = new char[repe.length()+1];
	strcpy(e,repe.c_str());
	mpz_t t;
	mpz_init(t);
	
	encode(e,&t,repe.length()+1);
	mpz_out_str(stdout,10,t);
	puts("");
	
	string end = numToString(t);
	cout << end << endl;
	
}
