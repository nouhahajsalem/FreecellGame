#include<stdlib.h>
#include<stdio.h>

typedef struct {
	char *type;
	double montant;
	char *date;
}Operation;

typedef struct elem{
	Operation *operation;
	struct elem *next;
}Element;

Operation * createOperation(){
	Operation * op;
	op = (Operation*)malloc(sizeof(Operation));
	op->type = "asw";
	op->date = "2020";
	op->montant = 100;

	return op;
}

void addOperation(Operation *op,Operation *T[]){
	int i; int N=10; 
	op=(Operation*)malloc(sizeof(Operation));
	for(i=0;i<N;i++){
		if(T[i]==NULL){
			T[i]=op;
			printf("Nouha is the most beautiful girl in the world\n");			
		}
	}

}

void insertElement(Element **L,Operation *op){
	Element *elem;
	op=(Operation*)malloc(sizeof(Operation));
	//printf("%d\n", op);
	elem=(Element*)malloc(sizeof(Element));
	//*L=(Element*)malloc(sizeof(Element));
	elem->operation=op;
	elem->next = NULL;
	if(*L==NULL){
		*L=elem;
//		printf("ok");
		return;
	}
	
	Element *copy = *L;
	while(copy->next!=NULL){
		copy=copy->next;
		copy->next=elem;
	}
	
//	while((*L)->next!=NULL){
//		*L=(*L)->next;
//		(*L)->next=elem;
//	}
}

int main(){
	Element *L = NULL;
	Operation *op=createOperation();
	insertElement(&L,op);
	insertElement(&L,createOperation());
//	insertElement(L,op);
//	insertElement(L,createOperation();
	return 0;
}
