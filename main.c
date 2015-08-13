#include"gmp.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stack>
#include<string.h>
#include<iostream>
#include<vector>
#include <time.h>
#include "godel.h"

using namespace std;

int main(int argc, char **argv) {
	
	if (strcmp(argv[1],"-encode")==0) {  // string to number
		
	}
	
	else if (strcmp(argv[1],"--decode")==0) {  // number to string
		
	}
	
	else if (strcmp(argv[1],"-prefixtoinfix")==0) {
		VTerm w = VTerm("w");
		VTerm x = VTerm("x");
		VTerm y = VTerm("y");
		VTerm z = VTerm("z");
		Formula a = equals(x,x);
		Formula b = equals(y,y);
		Formula f = fExpansion(a,b);
		string result = PrefixToInfix(f);
		cout << result << endl;
	}
	
	else if (strcmp(argv[1],"-cut")==0) {  // cut rule examaple
		VTerm w = VTerm("w");
		VTerm x = VTerm("x");
		VTerm y = VTerm("y");
		VTerm z = VTerm("z");
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
		f = fCut(f);
	}
	
	else if (strcmp(argv[1],"-inst")==0) {  // instantiation rule 
		VTerm w = VTerm("w");
		VTerm x = VTerm("x");
		VTerm y = VTerm("y");
		VTerm z = VTerm("z");
		Formula a = equals(x,x);
		Formula b = equals(w,z);
		Formula c = equals(x,z);
		a = fexIntroduction(a,x);
		b = fNegation(b);
		Formula f = fExpansion(a,b);
		f = fDisSwitch(f);  
		f = fEintroductionRule(f,x);
	}
	
	else if (strcmp(argv[1],"-maze")==0) {  //depth first proof
		VTerm w = VTerm("w");
		VTerm x = VTerm("x");
		VTerm y = VTerm("y");
		VTerm z = VTerm("z");
		Formula a = equals(w,x);
		Formula b = equals(w,z);
		Formula c = equals(x,z);
		a = fexIntroduction(a,x);
		b = fNegation(b);
		Formula f = fExpansion(a,b);
		f = fDisSwitch(f);  
		f = fEintroductionRule(f,x);
		srand (time(NULL));
		string first = PrefixToInfix(f);
		cout << first << endl;
		for (int i=0;i<40; i++) {
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
			char *e = new char[repe.length()+1];
			strcpy(e,repe.c_str());
			mpz_t t;
			mpz_init(t);
			encode(e,&t,repe.length()+1);
			puts("");
			
			string end = numToString(t);
		}
		cout << f.getRep() << endl;
		puts("");
		string result = PrefixToInfix(f);
		cout << result << endl;
	}
	return 0;
}
