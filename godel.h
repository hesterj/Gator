#ifndef GODEL_H_
#define GODEL_H_
#endif

using namespace std;

class Symbol {
	public:
		char rep;
		int arity;
		Symbol(char rep, int arity);
		Symbol();
};

class FSymbol: public Symbol {
	public:
		FSymbol(char rep, int arity);
};

class PSymbol: public Symbol {
	public:
		PSymbol(char rep, int arity);
};

class LSymbol: public Symbol {
	public:
		LSymbol(char rep, int arity);
};

class Negation: public LSymbol {
	Negation();
};

class Disjunction: public LSymbol {
	Disjunction();
};
/*  TROUBLE
class Existential: public LSymbol {
	VTerm variable;
	Existential();
	Existential(VTerm subject);
};
*/

class Designator {
	public:
		string rep;
		string getRep();
		Symbol u;
		std::vector<Designator> tail;
		int getArity();
		Designator(Symbol u, std::vector<Designator> tail);
		Designator();
};

class Term: public Designator {
	public:
};

class FTerm: public Term {
	public:
		FSymbol u;
		std::vector<Term> tail;
};

 class VTerm: public Term {
	 public:
		char vrep;
		VTerm();
 };

class Formula: public Designator {
	public:
		int valid;
		Formula();
};

class NegFormula: public Formula {
	public:
	
};

class DisFormula: public Formula {
	public:
};

class ExisFormula: public Formula {
	public:
};

class AFormula: public Formula {
	public:
		PSymbol u;
		std::vector<Term> tail;
};

Formula fExpansion(Formula a, Formula b);
Formula fContraction(Formula a);
Formula fAssociative(Formula a);
Formula fCut(Formula a, Formula b);
Formula exIntroduction(Formula a);

void associative(char *a);  // not implemented
void disjunction(char *a,char *b);
void contraction(char *a);
void encode(char *expr, mpz_t *t, int length);
void decode(unsigned long int *powers, int length, char *longexpression);
int factorize(mpz_t input, unsigned long int *exponents);
string numToString(mpz_t t);
