#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

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

void color(int t, int f){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

Element* newNode(Card );
Card newCard(int , char );
int isEmpty(Element* );
void insert(Element**, Card);
Card pop(Element**);
int peek(Element*);
void displayCard(Card);
void display(Element*);
Element * generateDeck();
void displayVert(Element **);
void displayHeader(Element **, Element**);
void createColumn(Element**,Element *);
void moveCard(Element **, Element **);
int moveCardRest(Element **, Element **);
Element * getHead(Element **);
int validZone1(char c1, char * col);
int validZone2(char c1, char * col);
int validZone3(char c1, char * col);

int main(){
	srand(time(0));
	system("color a5");
    color(15, 10);
    
    //declaration
    Element *zone1[8]={NULL}, *zone2[4]={NULL}, *zone3[4]={NULL}, *deck = NULL;
    int moves=0, i,c1Index,c2Index,c1zone,c2zone;
	char c1,c2,Columns[]= {'Q','W','E','R','T','Y','U','I'}, choices[]={'A','B','C','D','Z','L','F'};
	
	//
	deck = generateDeck();
	createColumn(zone1,deck);

	do{
		color(15, 10);
		displayHeader(zone2, zone3);
    	color(15, 10);
		printf("\t");
		for (i = 0;i < 4;i++) printf("  %c \t", Columns[i]);
		for (i=4;i < 8;i++) printf("  %c \t", Columns[i]);
		printf("\n\n");	
//		display(zone1[1]);
		printf("\n\n");
		
	//	displayCard((getHead(zone1[1]))->data);
	//	insert(&zone1[1],newCard(1,'h'));
		
	//	moveCard(zone1,zone3);
			
	//	displayVert(zone1);
		
		color(15, 10);
		printf("\t Choices: Q-W-E-R-T-Y-U-I - A-B-C-D - Z(Zone3) - F(Fin) - L(New) ");
		printf("\n\n");
		byte flags=0;
		//doesnt work well
		
		do{
			c1zone=0;
			color(15, 10);
			printf("Choose ur card position : ");
			c1 = getch();
			printf("%c",c1);
			if(validZone1(c1,Columns)!=-1){
				c1zone=1;
				c1Index = validZone1(c1,Columns);
				flags=1;
			}
			else if(validZone2(c1,choices)!=-1 || validZone2(c1,choices)!=4){
				c1Index = validZone2(c1,Columns);
				if(c1Index<4)			
					c1zone=2;
				flags=1;
			}
			else{
				printf("\nplease choose again\n");
			}	
		}while(flags==0);
		if(c1=='F')
			break;
		do{
			c2zone=0;
			printf("\nChoose ur card destination : ");
			c2 = getch();
			printf("%c",c2);
			if(validZone1(c2,Columns)!=-1){
				c2zone=1;
				c2Index = validZone1(c2,Columns);
				flags=1;
			}
			else if(validZone2(c2,choices)!=-1){
				printf("\nyour  : %d \n", validZone2(c2,choices));
				c2Index = validZone2(c2,choices);
				if(c2Index<4)			
					c2zone=2;
				if(c2Index==4)
					c2zone=3;
				flags=1;
			}
			else{
				printf("\n please choose again\n");
			}
		}while(flags==0);
		//printf("\nyour c1 : %d c2 : %d\n", c1zone, c2zone);
		
		//pls refactor this
		
		if(c1zone==1 && c2zone==1){
			moveCard(&zone1[c1Index],&zone1[c2Index]);
			printf("card moved \n");														
		}
		else if(c1zone==1 && c2zone==2)
			moveCard(&zone1[c1Index],&zone2[c2Index]);
		else if(c1zone==1 && c2zone==3){
			if(moveCardRest(&zone1[c1Index],zone3)==1)
				moves++;
			else
				printf("invalid move\n");
						
		}
		else if(c1zone==2 && c2zone==1)
			moveCard(&zone2[c1Index],&zone1[c2Index]);
		else if(c1zone==2 && c2zone==2)
			moveCard(&zone2[c1Index],&zone2[c2Index]);
		else if(c1zone==2 && c2zone==3){
			if(moveCardRest(&zone2[c1Index],zone3)==1)
				moves++;
			else
				printf("invalid move\n");
		}
		
//		system("cls");
	}while(c1!='F');

	printf("your moves : %d\n", moves);
	
	
	return 0;
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
} 
  
void displayVert(Element **e){
	int i,flag=1;
	Element *copy[8];
	
	for(i=0;i<8;i++){
		
	}

//	printf("\n\n");
//	display(e[0]);
//	printf("\n\n");
//	display(e[1]);
//	printf("\n\n");

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
	
	printf("\n\n");
	display(e[0]);

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
		printf("%c     %c\t", c.label, c.img);
	else
		printf("%s    %c\t", c.label, c.img);
}

void displayHeader(Element ** z2, Element** z3){
	int i;
	color(15, 10);
	printf("\n  A \t  B \t  C \t  D\t \t  %c\t  %c\t  %c\t  %c\n", 3, 4, 5, 6);
	color(15, 10);
    
    for (i = 0;i < 4;i++) {
    	if(z2[i]!=NULL){
    		displayCard(z2[i]->data);
		}
		else{
			printf("   \t");    	
		}
		color(15, 10);
	}
   	printf("    \t");
	for (i = 0;i < 4;i++) {
    	if(z3[i]!=NULL){
    		displayCard(z3[i]->data);
		}
		else{
			printf("[   ]\t");    	
		}
		color(15, 10);
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

Element * getHead(Element ** elmnt){
	Element * e = *elmnt;
	if(e==NULL)
		return NULL;
	while(e->next==NULL)
		e=e->next;
	return e;
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

void moveCard(Element ** s, Element ** d){
	
//	printf("ddssd\n");
//	displayCard((*s)->data);
	Card c = pop(s);	
	printf("\n \n");
	displayCard(c);
	color(15, 10);
	printf("\n\n");
	insert(d,c);
}

int moveCardRest(Element ** s, Element ** d){
	printf("ddssd\n");
//	displayCard((*s)->data);
	Card c = pop(s);
	printf("\n \n");
	displayCard(c);
	if(c.type=='h'){
		if(d[0]!=NULL){
			if(d[0]->data.value==c.value-1){
				insert(&d[0],c);
				return 1;
			}
				
		}
		else if(c.value==1){
			insert(&d[0],c);
			return 1;		
		}		
	}
	else if(c.type=='d'){
		if(d[1]!=NULL){
			if(d[1]->data.value==c.value-1){
				insert(&d[1],c);
				return 1;				
			}
		}
		else if(c.value==1){
			insert(&d[1],c);
			return 1;
		}		
	}	
	else if(c.type=='c'){
		if(d[1]!=NULL){
			if(d[1]->data.value==c.value-1){
				insert(&d[1],c);
				return 1;				
			}
		}
		else if(c.value==1){
			insert(&d[1],c);
			return 1;
		}		
	}
	else if(c.type=='s'){
		if(d[3]!=NULL){
			if(d[3]->data.value==c.value-1){
				insert(&d[3],c);
				return 1;				
			}
		}
		else if(c.value==1){
			insert(&d[3],c);
			return 1;
		}		
		
	}

	
	printf("\n\n");
//	insert(&d[1],c);
	return 0;
}

int validZone1(char c, char * t){
	int i;
	for(i=0;i<8;i++){
		if(t[i]==c)
			return i;
	}
	return -1;
}

int validZone2(char c, char * t){
	int i;
	for(i=0;i<7;i++){
		if(t[i]==c)
			return i;
	}
	return -1;
}

int validZone3(char c, char * t){
	int i;
	for(i=0;i<4;i++){
		if(t[i]==c)
			return i;
	}
	return -1;
}
