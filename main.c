#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct Card{
	int value;
	char type;
};
typedef struct Card Card;

struct Element{
	Card data;
	struct Element *next;
};

struct Element* newNode(Card data){
	struct Element* stack = (struct Element*)malloc(sizeof(struct Element)); 
    stack->data = data; 
    stack->next = NULL; 
    return stack;
};

int isEmpty(struct Element* element){
	return !element;	
}

void push(struct Element** root, Card data) 
{ 
    struct Element* stack = newNode(data); 
    stack->next = *root; 
    *root = stack; 
    printf("%d pushed to stack\n", data); 
} 
  
Card *pop(struct Element** root) 
{ 
    if (isEmpty(*root)) 
        return NULL;
        
    struct Element* temp = *root; 
    *root = (*root)->next; 
    Card popped = temp->data; 
    free(temp); 
  
    return &popped; 
} 
  
int peek(struct Element* root) 
{ 
    if (isEmpty(root)) 
        return INT_MIN; 
    Card card = root->data;
    
    return card.value; 
} 

void displayCard(struct Card c){
	printf("%d:%c\n", c.value, c.type);
}

void display(struct Element* root){
	Card c;
	if(isEmpty(root))
		return;
	do{
		c=root->data;
		displayCard(c);
		root=root->next;
	}while(!isEmpty(root));
}

void main(){
	// init a struct ----what to do: generate a function to initialize 52 card automatically 
	Card card1 = {1, 'd'};
	Card card2 = {2, 'h'};
	Card card3 = {3, 'd'};
	// show instance of struct 
	displayCard(card1);
	
	//next steps
	//1-creating 3 zones(stacks)
	//2-picking numbers randomly from the deck (52 cards)
	//moving cards from zone to zone
	
	
	struct Element* root = NULL; 
  
    push(&root, card1); 
    push(&root, card2); 
    push(&root, card3); 
    display(root);
  	Card* c = pop(&root);
    printf("%d %c popped from stack\n", c->value, c->type); 
  
    printf("Top element is %d\n", peek(root)); 
	return;
}
