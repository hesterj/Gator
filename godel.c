#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<string.h>
#include"gmp.h"

void encode(char *expr, mpz_t *t) {
	int i=0;
	int length = strlen(expr);
	int powers[length];
	mpz_init(*t);
	
	mpz_t holder;
	mpz_t base;
	
	mpz_init(holder);
	mpz_init(base);
	
	int temp=0;
	mpz_set_ui(*t,1);
	for (i=0;i<length;i++) {
		if (expr[i]=='0') powers[i]=1;
		if (expr[i]=='=') powers[i]=2;
		if (expr[i]=='S') powers[i]=3;
		if (expr[i]=='V') powers[i]=4;
		if (expr[i]=='-') powers[i]=5;
		if (expr[i]=='x') powers[i]=6;
		if (expr[i]=='y') powers[i]=7;
		if (expr[i]=='z') powers[i]=8;
		if (expr[i]=='+') powers[i]=9;
		if (expr[i]=='E') powers[i]=10;
		
	}
}

void decode(unsigned long int *powers, int length, char *longexpression) {
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
	}
}

int factorize(mpz_t input, unsigned long int *exponents) {  //This is a trial division algorithm. 
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

int main(int argc, char **argv) {
	
	int i=0;
	int j=0;
	int basecount=0;
	
	unsigned long int exponents[100];
	
	clock_t start, end;
	double cpu_time_used;
	
	start = clock();
	
	mpz_t input;
	mpz_init (input);
	
	mpz_set_str(input,argv[1],10);  

	basecount = factorize(input,exponents);
	
	unsigned long int finalexponents[basecount];
	
	for (j=0;j<basecount;j++) {
		finalexponents[j]=exponents[j];
	}
	puts("");

	end = clock();
	
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken: %f\n ",cpu_time_used);
	
	char expression[basecount];
	decode(finalexponents,basecount,expression);
	
	for (j=0;j<basecount;j++) {
		printf("%c",expression[j]);
	}
	
	
	return 0;
	
	}
