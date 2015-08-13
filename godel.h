

#pragma once
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
		int lsymbol;  //bs
		int psymbol;  //bs
		int type;   // 0 variable term, 1 otherwise (for now), 2 axiom
		int getLSymbol();
		int getPSymbol();
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

//AXIOMS

class IdentityAxiom: public DisFormula {
	public:
		IdentityAxiom(VTerm x);
		IdentityAxiom();
};

class PropositionalAxiom: public DisFormula {
	public:
		PropositionalAxiom(Formula a);
		PropositionalAxiom();
};

class SubstitutionAxiom: public DisFormula {  // not done
	public:
		SubstitutionAxiom(Formula a, VTerm x);
		SubstitutionAxiom();
};

class EqualityAxiom: public AFormula {  // not done
	public:
		EqualityAxiom(vector<VTerm> x, vector<VTerm> y, FSymbol f); 
		EqualityAxiom(vector<VTerm> x, vector<VTerm> y, PSymbol p); 
		EqualityAxiom(vector<VTerm> x, vector<VTerm> y); // p is "="
		EqualityAxiom();
};

// END CLASSES

int isFormula(Formula a);
int isTerm(Term a);
int boundInA(Formula A, VTerm x);  // 1 if x free in A, 0 otherwise

Formula fNegation(Formula a); // returns -a
Formula fExpansion(Formula a, Formula b); // inference rule
Formula fContraction(Formula a); // inference rule
Formula fAssociative(Formula a);  // only works one way, inference rulse ***** needsto go other direction
Formula fCut(Formula a);   // inference rule
Formula fDisSwitch(Formula a);	// switches a and b if disjunction
Formula fexIntroduction(Formula a,VTerm b); // adds existential  without checking if not free
Formula equals(Term a, Term b); // returns a=b
Formula fEintroductionRule(Formula a, VTerm x);  // inference rule, checks if x not free, INFERENCE RULE
PSymbol PSymbolize(Formula a);  //Turns formula into predicate symbol!  Free variables are parameters

void associative(char *a);  
void disjunction(char *a,char *b);
void contraction(char *a);
void encode(char *expr, mpz_t *t, int length);
void decode(unsigned long int *powers, int length, char *longexpression);
int factorize(mpz_t input, unsigned long int *exponents);

string numToString(mpz_t t);
string InfixToPrefix(string rep);  //Not done!!  
string PrefixToInfix(Formula a);
string PreToInfix(string rep);
void stringToNum(string input, mpz_t *t);

#endif
