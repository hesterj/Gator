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
		void setValid();
		Formula();
		Formula(Designator inp);  //  Use only if we know inp is a formula!
};

class NegFormula: public Formula {
	public:
		NegFormula();
};

class DisFormula: public Formula {
	public:
		DisFormula();
};

class ExisFormula: public Formula {
	public:
		ExisFormula();
};

class AFormula: public Formula {
	public:
		PSymbol u;
		std::vector<Term> tail;
};


bool isFormula(Formula a);
bool isTerm(Term a);
Formula fNegation(Formula a);
DisFormula fExpansion(Formula a, Formula b);
Formula fContraction(DisFormula a);
Formula fAssociative(Formula a);
Formula fCut(Formula a, Formula b);
Formula fexIntroduction(Formula a,VTerm b);
Formula equals(Term a, Term b);

void associative(char *a);  // not implemented
void disjunction(char *a,char *b);
void contraction(char *a);
void encode(char *expr, mpz_t *t, int length);
void decode(unsigned long int *powers, int length, char *longexpression);
int factorize(mpz_t input, unsigned long int *exponents);
string numToString(mpz_t t);

#endif
