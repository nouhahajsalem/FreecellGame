#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

typedef struct Card Card;

struct Card{
	int value;
	char type;
	char color;
	char img;
	char * label;
};

typedef struct Element Element;

struct Element{
	Card data;
	Element *next;
};

typedef struct PileOfCard PileOfCard;

struct PileOfCard{
	int size;
	PileOfCard * top;
};

void color(int t, int f){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

void createColumn(Element**,Element *);
Element* newNode(Card );
Card newCard(int , char );
int isEmpty(Element* );
void insert(Element** , Card );
Card pop(Element** );
int peek(Element* );
void displayCard(Card );
void display(Element* );
Element * generateDeck();
void displayVert(Element **);
void displayHeader(Element **, Element**);

int main(){
	srand(time(0));
	system("color a5");
    color(15, 10);
    
    //declaration
    Element *zone1[8]={NULL}, *zone2[4]={NULL}, *zone3[4]={NULL}, *deck = NULL;
    int moves=0, i;
	char c1,c2,Columns[]= {'Q','W','E','R','T','Y','U','I'}, choices[]={'A','B','C','D','F','L','Z'};
	
	deck = generateDeck();	
	
	displayHeader(zone2, zone3);
    
	printf("\t");
	for (i = 0;i < 4;i++) printf("  %c \t", Columns[i]);
	for (i=4;i < 8;i++) printf("  %c \t", Columns[i]);
	printf("\n\n");
	
	createColumn(zone1,deck);
	
	displayVert(zone1);
	
	printf("\t Choices: Q-W-E-R-T-Y-U-I - A-B-C-D - Z(Zone3) - F(Fin) - L(New) ");
	printf("\n\n");
	byte flags=0;
	//doesnt work well
	
//	do{
//		printf("Choose ur card position : ");
//		c1 = getchar();
//		if(strstr(Columns,c1+'\0') || strstr(choices,c1+'\0')){
//			printf("valid\n");
//			flags=1;
//		}
////		else{
////			printf("please choose again\n");
////		}
////		getchar();			
//	}while(flags==0);
//	
//	printf("\n\n");
//	getchar();
//	printf("Choose ur card destination : ");
//	c2 = getchar();
	
//	for(i=0;i<8;i++){
//		display(zone1[i]);
//		printf("\n\n");		
//	}

	// we need code for moving cards

	
	
	return 0;
}

PileOfCard * newPile(){
	PileOfCard * pile = (PileOfCard*)malloc(sizeof(PileOfCard));
	pile->size=0;
	pile->top=NULL;
	return pile;
}

Element* newNode(Card data){
	Element* element = (Element*)malloc(sizeof(Element)); 
    element->data.color = data.color; 
    element->data.value = data.value; 
    element->data.type = data.type; 
    element->data.img = data.img; 
    element->data.label = data.label; 
    
    element->next = NULL; 
    return element;
};

int isEmpty(Element* element){
	return !element;	
}

Card newCard(int value, char type){
	Card c;
	c.value = value;
	c.type = type;
	if(c.value<10)
		c.label = c.value + '0';
	else{
		if(c.value==10) c.label="10";
		if(c.value==11) c.label="J";
		if(c.value==12) c.label="Q";
		if(c.value==13) c.label="K";
	}
	switch(type){
		case 's': 
			c.img = 5;
			c.color = 'b';
			break;
		case 'c':
			c.img = 6;
			c.color = 'b';
			break;
		case 'h': 
			c.img = 3;
			c.color = 'r';
			break;
		case 'd':
			c.img = 4;
			c.color = 'r';
			break;
	}
	return c;
}

Element *generateDeck(){
	
	Element * pile = NULL;
	Card Pack[52]; 
	int flags[52]={0};
    int j;
    for(j=0; j<13; j++)	Pack[j] = newCard(j+1, 'h');
    for(j=0; j<13; j++) Pack[13+j] = newCard(j+1, 'c');
    for(j=0; j<13; j++) Pack[13*2+j] = newCard(j+1, 'd');
    for(j=0; j<13; j++) Pack[13*3+j] = newCard(j+1, 's');

    int remaining = 52;
    int randNum,i,cpt=0;
    while(remaining!=0){
    	randNum = rand()%remaining;
//    	printf("%d\n", randNum);
    	cpt=0;
    	for(i=0;i<52;i++){
    		if(flags[i]==0){
    			if(randNum == cpt){
    				insert(&pile, Pack[i]);
					flags[i]=1;
    				remaining--;
					break;    				
				}						
				cpt++;
			}
		}
	}
	return pile;
}

void insert(Element** root, Card data) { 
    Element* stack = newNode(data); 
    stack->next = *root; 
    *root = stack; 
//    printf("%d pushed to stack\n", data); 
} 
  
void displayVert(Element **e){
	int i,flag=1;
	while(flag){
		flag=0;
		printf("\t");
		for(i=0;i<8;i++){
			if(e[i]!=NULL){
				displayCard((e[i])->data);
				e[i]=e[i]->next;
				flag=1;
			}
			else{
				printf("\t");
			}
		}
		printf("\n\n");
	}
}
  
Card pop(Element** root) { 
    if (isEmpty(*root)){
		Card c= {0};
		return c;     	
	} 

        
    Element* temp = *root; 
    *root = (*root)->next; 
    Card popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
int peek(Element* root) { 
    if (isEmpty(root)) 
        return INT_MIN; 
    Card card = root->data;
    
    return card.value; 
} 

void displayCard(Card c){
	if(c.color=='r')
		color(12, 15);
	else
		color(0, 15);		
	if(c.value<10)
		printf("[%c %c]\t", c.label, c.img);
	else
		printf("[%s %c]\t", c.label, c.img);
}

void displayHeader(Element ** z2, Element** z3){
	int i;
    printf("\n  A \t  B \t  C \t  D\t \t  %c\t  %c\t  %c\t  %c\n", 3, 4, 5, 6);

    for (i = 0;i < 4;i++) {
    	if(z2[i]!=NULL){
    		displayCard(z2[i]->data);
		}
		else{
			printf("[   ]\t");    	
		}
	}
   	printf("    \t");
	for (i = 0;i < 4;i++) {
    	if(z3[i]!=NULL){
    		displayCard(z3[i]->data);
		}
		else{
			printf("[   ]\t");    	
		}
	}
	printf("\n\n\n");	
}

void display(Element* root){
	
	Card c;
	if(isEmpty(root)){
		printf("is empty!!!\n");
		return;		
	}
	do{
		c=root->data;
		displayCard(c);
		root=root->next;
	}while(!isEmpty(root));
}

void createColumn(Element** c,Element * d){
	int i,j;
	for(i=0;i<4;i++){
		//first 4 columns with 7 places
		for(j=0;j<7;j++){
			insert(&c[i], pop(&d));			
		}
	}
	for(i=4;i<8;i++){
		//last 4 columns with 6 places
		for(j=0;j<6;j++){
			insert(&c[i], pop(&d));			
		}
	}
}

