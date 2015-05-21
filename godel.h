#ifndef GODEL_H_
#define GODEL_H_

using namespace std;

class Container {
	public:
		int arity;
		int getArity();
		void setArity(int inp);
		string getRep();
		void setRep(string inp);
		string rep;
};

class Symbol: public virtual Container {
	public:
		Symbol(string rep, int arity);
		Symbol();
};

class FSymbol: public Symbol {
	public:
		FSymbol(string rep, int arity);
};

class PSymbol: public Symbol {
	public:
		PSymbol(string rep, int arity);
		PSymbol();
};

class Equals: public PSymbol {
	public:
		Equals();
};

class LSymbol: public Symbol {
	public:
		LSymbol(string rep, int arity);
		LSymbol();
};

class Negation: public LSymbol {
	public: 
		Negation();
};

class Disjunction: public LSymbol {
	public:
		Disjunction();
};

class Existential: public LSymbol {
	public:
		Existential();
		Existential(string var);
};

class Designator: public virtual Container {
	public:
		Symbol u;
		int tag;  // 0, 1 if DisFormula, 2 if negation, 3 if existential statement
		std::vector<Designator> tail;
		Designator(Symbol u, std::vector<Designator> tail);
		Designator();
};

class Term: public Designator {
	public:
		Term();
};

class FTerm: public Term {
	public:
		FTerm();
};

 class VTerm: public Term, public Symbol {
	 public:
		VTerm();
		VTerm(string rep);
 };

class Formula: public Designator {
	public:
		int valid;
		int tag;  // 0, 1 if DisFormula
		void setValid();
		Formula();
		Formula(Designator inp);  //  Use only if we know inp is a formula!
};

class NegFormula: public Formula {
	public:
		NegFormula();
		std::vector<Formula> tail;
};

class DisFormula: public Formula {
	public:
		DisFormula();
		std::vector<Formula> tail;
};

class ExisFormula: public Formula {
	public:
		ExisFormula();
		std::vector<Formula> tail;
};

class AFormula: public Formula {
	public:
		PSymbol u;
		std::vector<Term> tail;
};


int isFormula(Formula a);
int isTerm(Term a);
int freeInA(Formula A, VTerm x);  // 1 if x free in A, 0 otherwise

Formula fNegation(Formula a); // returns -a
Formula fExpansion(Formula a, Formula b);
Formula fContraction(Formula a);
Formula fAssociative(Formula a);  // only works one way
Formula fCut(Formula a, Formula b);  
Formula fDisSwitch(Formula a);	// switches a and b if disjunction
Formula fexIntroduction(Formula a,VTerm b); // returns EbA
Formula equals(Term a, Term b); // returns a=b

void associative(char *a);  
void disjunction(char *a,char *b);
void contraction(char *a);
void encode(char *expr, mpz_t *t, int length);
void decode(unsigned long int *powers, int length, char *longexpression);
int factorize(mpz_t input, unsigned long int *exponents);
string numToString(mpz_t t);

#endif
