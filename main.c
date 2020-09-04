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

PileOfCard * newPile();
Element* newNode(Card );
Card newCard(int , char );
int isEmpty(Element* );
void push(PileOfCard**, Element *);
void insert(Element** , Card );
Card *pop(Element** );
int peek(Element* );
void displayCard(Card );
void display(Element* );
PileOfCard * generateDeck();

int main(){
	system("color a5");
    SetConsoleTitle("FREECELL BY NOUHA HAJ SALEM");
    color(15, 10);
    
	PileOfCard * p = NULL;
	p = generateDeck();

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
	switch(type){
		case 's': case 'c':
			c.color = 'b';
			break;
		case 'h': case 'd':
			c.color = 'r';
			break;
	}
	return c;
}

PileOfCard *generateDeck(){
	PileOfCard * pile = newPile();
	Card Pack[52]; 
	int flags[52]={0};
    int j;
    for(j=0; j<13; j++)	Pack[j] = newCard(j+1, 'h');
    for(j=0; j<13; j++) Pack[13+j] = newCard(j+1, 'c');
    for(j=0; j<13; j++) Pack[13*2+j] = newCard(j+1, 'd');
    for(j=0; j<13; j++) Pack[13*3+j] = newCard(j+1, 's');
//    print("%d", );
    int remaining = 52;
    int randNum,i,cpt=0;
    while(remaining!=0){
    	randNum = rand()%remaining;
    	printf("%d\n", randNum);
    	cpt=0;
    	for(i=0;i<52;i++){
    		if(flags[i]==0){
    			if(randNum == cpt){
    				Element * tmp = newNode(Pack[i]);
    				push(&pile, tmp);
					flags[i]=1;
    				remaining--;
					break;    				
				}						
				cpt++;
			}
		}
	}
	printf("done");
	return pile;
}

void push(PileOfCard ** pile,Element * root){
	PileOfCard * tmp = *pile;
	if(tmp->top==NULL){
		tmp->top=root;
	}
	else{
		root->next = tmp->top;
		tmp->top = root;
	}
	tmp->size++;
}

void insert(Element** root, Card data) { 
    Element* stack = newNode(data); 
    stack->next = *root; 
    *root = stack; 
    printf("%d pushed to stack\n", data); 
} 
  
  
Card *pop(Element** root) { 
    if (isEmpty(*root)) 
        return NULL;
        
    Element* temp = *root; 
    *root = (*root)->next; 
    Card popped = temp->data; 
    free(temp); 
  
    return &popped; 
} 
  
int peek(Element* root) { 
    if (isEmpty(root)) 
        return INT_MIN; 
    Card card = root->data;
    
    return card.value; 
} 

void displayCard(Card c){
	printf("%d:%c\n", c.value, c.type);
}

void displayPile(PileOfCard * p){
	
}

void display(Element* root){
	Card c;
	if(isEmpty(root))
		return;
	do{
		c=root->data;
		displayCard(c);
		root=root->next;
	}while(!isEmpty(root));
}
