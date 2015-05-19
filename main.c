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
	
	VTerm w = VTerm("w");
	VTerm x = VTerm("x");
	VTerm y = VTerm("y");
	VTerm z = VTerm("z");
	Formula a = equals(x,y);
	Formula b = equals(w,z);
	Formula c = fExpansion(a,b);
	
	string rep = c.getRep();
	char *e = new char[rep.length()+1];
	strcpy(e,rep.c_str());
	mpz_t t;
	mpz_init(t);
	
	encode(e,&t,rep.length()+1);
	mpz_out_str(stdout,10,t);
	puts("");
	
	string end = numToString(t);
	cout << end << endl;
	
}
