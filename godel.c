#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"gmp.h"


void factorize(mpz_t input, int *exponents) {
	
	int prime = mpz_probab_prime_p(input,25);
	
	if (prime>=1) {
		printf("%s", "\nInput is (probably) a prime number.\n");
		return;
		
	}

	else {
		
		mpz_t prime;
		mpz_init_set_ui(prime, 2);
		mpz_t temp;
		mpz_init_set(temp, input);
		mpz_t bound;
		mpz_init_set(bound, prime);
		mpz_sqrt(bound, temp);
		
		int i=0;
		
		while(mpz_cmp(prime,bound)<=0) {
			
			int smoothness;
			smoothness=mpz_remove(temp, temp,prime);
			
			if (smoothness==0) {
				mpz_nextprime(prime,prime);
				continue;
			}
			
			exponents[i]=smoothness;
			mpz_out_str(stdout,10,prime);
			
			printf("%s","^");
			printf("%d",exponents[i]);
			printf("%s","*");
			
			mpz_set(bound,temp);
			mpz_nextprime(prime,prime);
			i++;
			
		}
		
		mpz_clear(bound);
		mpz_clear(temp);
		mpz_clear(prime);
	}
	
}

int main() {
	
	int input = 0;
	printf("Enter 1 to decode an integer, or 0 to encode a string.\n");
	scanf("%d", &input);
	
	if(input==1) {
		
		char *inputstr;
		scanf("%s", inputstr);
		
		mpz_t input;
		mpz_set_str(input,inputstr,10);
		//mpz_out_str(stdout,10,input);
		
		int exponents[100];
		exponents[0]=0;
		
		factorize(input, exponents);
		
		if (exponents[0]==0) {
			return 0;
		}
		
	}
	
	return 0;
	
}
