#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct Carte{
	int valeur;
	char type;
};
typedef struct Carte Carte;

struct element{
	Carte carte;
	struct element *suiv;
};


int main(){
	printf("hello jamilati");
	return 0;
}
