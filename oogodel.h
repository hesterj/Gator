#ifndef GODEL_H_
#define GODEL_H_
#endif

using namespace std;

class Symbol {
	string rep;
};

class FSymbol: public Symbol {
	
};

class PSymbol: public Symbol {
	
};

class LSymbol: public Symbol {
	
};

class Designator {
	public:
		string rep;
		string getRep();
		
		int arity;
};

class Term: public Designator {
	
};

class Formula: public Designator {
	
};


char* strToArr(string input);
void associative(char *a);  // not implemented
void disjunction(char *a,char *b);
void contraction(char *a);
void encode(char *expr, mpz_t *t, int length);
void decode(unsigned long int *powers, int length, char *longexpression);
int factorize(mpz_t input, unsigned long int *exponents);
