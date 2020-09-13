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
	char img;// icon
	char * label; // table of characters for display K - A - J - 8
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

//prototype of functions
Element* newNode(Card );
Card newCard(int , char );
int isEmpty(Element* );
void insert(Element**, Card);//push
void pop(Element**);
Card peek(Element*);
void displayCard(Card);
void display(Element**, char *);
Element * generateDeck();
void displayVert(Element **);
void displayHeader(Element **, Element**);
void createColumn(Element**,Element *);
void moveCard(Element **, Element **);
int moveCardRest(Element **, Element **);
Element * getHead(Element **);
int validZone1(char c1, char * col);//validate the choice of the column if exists in zone 1
int validZone2(char c1, char * col);//
int validZone3(char c1, char * col);

int main(){
	srand(time(0));//initialize random numbers
	system("color a5");// background color of the window
    color(15, 10);// 15 : color of font  10: background of font
    
    //declaration
    Element *zone1[8]={NULL}, *zone2[4]={NULL}, *zone3[4]={NULL}, *deck = NULL;
    int moves=0, i,flags;// moves performed
	int c1Index,c2Index,c1zone,c2zone;// index of choice in the zone - c1zone is the zone concerned for the move
	char c1,c2; // choice stored in char
	char Columns[]= {'Q','W','E','R','T','Y','U','I'};// chars in zone1
	char choices[]= {'A','B','C','D','Z','L','F'};// chars of other choices
	
	//creating deck of 52 shuffled cards 
	deck = generateDeck();
	//generate 8 columns 7 for the first 4 columns and 6 for the last 4 columns
	createColumn(zone1,deck);

	do{
		//code for display
		color(15, 10);//maintaining color 
		displayHeader(zone2, zone3);//displaying zone 2 and zone 3
    	color(15, 10);
		display(zone1,Columns);//displaying zone 1
		color(15, 10);
		
		//displaying possible choices
		printf("\t Choices: Q-W-E-R-T-Y-U-I - A-B-C-D - Z(Zone3) - F(Fin) - L(New) \n\n");
		
		do{
			flags=0;// flags to stop while loop when F character is chosed
			c1zone=0;
			color(15, 10);
			printf("Choose ur card position : ");
			c1 = getch();//get character from user
			printf("%c",c1);
			if(validZone1(c1,Columns)!=-1){//-1 means the character doesn't exist
				c1zone=1;//determines the zone of character 
				c1Index = validZone1(c1,Columns);//retrieve index of column in the zone
				flags=1;//triggered when a valid 
			}
			else if(validZone2(c1,choices)!=-1 || validZone2(c1,choices)!=4){
			//if the character is in zone 2 and not in zone3 because we cant move from zone 3 (see game rules)
				c1Index = validZone2(c1,Columns);//retrieve index of column in the zone
				c1zone=2;
				flags=1;
			}
			else{
				printf("\nplease choose again\n");
			}	
		}while(flags==0);//loops until flags is 1 which means valid character
		if(c1=='F')//end of game
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
		
		if(c1zone==1 && c2zone==1){
			moveCard(&zone1[c1Index],&zone1[c2Index]);
			moves++;
			printf("card moved\n");												
		}
		else if(c1zone==1 && c2zone==2){
			moveCard(&zone1[c1Index],&zone2[c2Index]);
			moves++;
		}
		else if(c1zone==1 && c2zone==3){
			if(moveCardRest(&zone1[c1Index],zone3)==1)
				moves++;//incrementing in case the move was successful
			else
				printf("invalid move\n");		
		}
		else if(c1zone==2 && c2zone==1)
			moveCard(&zone2[c1Index],&zone1[c2Index]);
		else if(c1zone==2 && c2zone==2)
			moveCard(&zone2[c1Index],&zone2[c2Index]);
		else if(c1zone==2 && c2zone==3){
			if(moveCardRest(&zone2[c1Index],zone3)==1)//
				moves++;//
			else
				printf("invalid move\n");
		}
		
		system("cls");//clear the text in window
	}while(c1!='F');

	printf("your moves : %d\n", moves);
	
	
	return 0;
}

Element* newNode(Card data){
	//memory allocation
	Element* element = (Element*)malloc(sizeof(Element)); 
    //assinging card to stack
	element->data = data;    
    element->next = NULL; 
    return element;
};

int isEmpty(Element* element){
	return !element;//checking if empty
}

Card newCard(int value, char type){
	Card c;
	c.value = value;
	c.type = type;
	if(c.value<10 && c.value!=1)
		c.label = c.value + '0';//making integer readable as char
	else{
		//some unusual values in the games gets replaced by followed character
		if(c.value==1) c.label="A";
		if(c.value==10) c.label="10";
		if(c.value==11) c.label="J";
		if(c.value==12) c.label="Q";
		if(c.value==13) c.label="K";
	}
	//checking the type of card to give the right color and shape
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
	//creation 52 cards
	Element * deck = NULL;
	Card Pack[52]; // container of 52 cards 
	int flags[52]={0}; // checking if card in index is checked
    int j;
    for(j=0; j<13; j++)	Pack[j] = newCard(j+1, 'h');//initialising 13 cards with same type
    for(j=0; j<13; j++) Pack[13+j] = newCard(j+1, 'c');
    for(j=0; j<13; j++) Pack[13*2+j] = newCard(j+1, 'd');
    for(j=0; j<13; j++) Pack[13*3+j] = newCard(j+1, 's');

	//generation of random 
    int remaining = 52;//remaining cards
    int randNum,i,cpt=0;
    while(remaining!=0){
    	randNum = rand()%remaining;//generate random number
    	cpt=0;
    	for(i=0;i<52;i++){
    		if(flags[i]==0){
    			if(randNum == cpt){
    				insert(&deck, Pack[i]);//insertion of card in the linked list
					flags[i]=1;
    				remaining--;
					break;    				
				}						
				cpt++;
			}
		}
	}
	return deck;
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
//	display(e[0]);

}
  
void pop(Element** root) { 
    if (isEmpty(*root)){
//		Card c= {0};
//		return c;     	
		return ;     	
	} 

    Element* temp = *root; 
    *root = (*root)->next; 
//    Card popped = temp->data; 
    free(temp); 
  
//    return popped; 
} 
  
Card peek(Element* root) { 
    if (isEmpty(root)) {
		Card c= {0};//returning card of value equals 0
        return c;
	}
    Card card = root->data;
    return card;
} 

void displayCard(Card c){
	//giving red color white background for red cards
	if(c.color=='r')
		color(12, 15);
	else
		color(0, 15);//assigning black color white background for black cards
	if(c.value<10 && c.value!=1)
		printf("%c     %c\t", c.label, c.img);//displaying numbers
	else
		printf("%s    %c\t", c.label, c.img);//displaying caracters
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

void display(Element ** root, char * t){
	int i;
	Card c;
	Element * e;
	for(i=0;i<8;i++){//looping through the elements of zone 1
		e = root[i];
		printf("   %c  \t", t[i]);

		if(isEmpty(e)){//checking whether if null or not
			printf("\n\n");
			return;		
		}
		else{
			do{
				c=e->data;
				displayCard(c);
				e=e->next;
			}while(!isEmpty(e));					
		}
		color(15, 10);
		printf("\n\n");
	}
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
			//check if peeked card is not null
		//	if((peek(d)).value!=0){
				insert(&c[i], peek(d));	
				pop(&d);						
		//	}
		}
	}
	
	for(i=4;i<8;i++){
		//last 4 columns with 6 places
		for(j=0;j<6;j++){
			 //if((peek(d)).value!=0){
				insert(&c[i], peek(d));
				pop(&d);
		//	}
		}
	}
}

void moveCard(Element ** s, Element ** d){
	Card c = peek(*s);
	pop(s);	
	printf("\n \n");
	displayCard(c);
	color(15, 10);
	printf("\n\n");
	insert(d,c);
}
//&s s *s **s
int moveCardRest(Element ** s, Element ** d){//moving card to zone 3 
	Card c = peek(*s);//creation of a structure of type Card and assigning the head of the stack to it
	pop(s);//remove card from zone
	color(15, 10);
	printf("\n \n");
	//displayCard(c);
	if(c.type=='h'){
		if(d[0]!=NULL){
			if(d[0]->data.value==c.value-1){// check if the moved card is following the head of zone 3
				insert(&d[0],c);
				return 1;
			}
				
		}
		else if(c.value==1){// check if the zone is empty
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
	else if(c.type=='s'){
		if(d[2]!=NULL){
			if(d[2]->data.value==c.value-1){
				insert(&d[2],c);
				return 1;				
			}
		}
		else if(c.value==1){
			insert(&d[2],c);
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
