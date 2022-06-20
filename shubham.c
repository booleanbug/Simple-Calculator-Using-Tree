// This uses struct based stack implimentation of Stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char data;
    struct node* left;
    struct node* right;
    struct node* next;
};

struct node *head=NULL;

struct node* newNode(char data)
{
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
     
    return (node);
}

// A structure to represent a stack 
struct Stack { 
    int top; 
    int maxSize;
    // we are storing string in integer array, this will not give error
    // as values will be stored in ASCII and returned in ASCII thus, returned as string again
    int* array; 
}; 

void pushTree(struct node* x)
{
    if(head==NULL)
    head = x;
    else
    {
        (x)->next = head;
        head  = x;
    }
}

struct node* popTree()
{
    struct node* p = head;
    head = head->next;
    return p;
}

struct Stack* create(int max) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->maxSize = max; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->maxSize * sizeof(int));
    return stack; 
} 

// Checking with this function is stack is full or not
// Will return true is stack is full else false 
//Stack is full when top is equal to the last index 
int isFull(struct Stack* stack) 
{ 
    if(stack->top == stack->maxSize - 1){
        printf("Will not be able to push maxSize reached\n");
    }
    // Since array starts from 0, and maxSize starts from 1
    return stack->top == stack->maxSize - 1; 
} 

// By definition the Stack is empty when top is equal to -1 
// Will return true if top is -1
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
}

// Push function here, inserts value in stack and increments stack top by 1
void push(struct Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
}

// Function to remove an item from stack.  It decreases top by 1 
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 

// Function to return the top from stack without removing it 
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 

// A utility function to check if the given character is operand 
int checkIfOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'); 
} 

// Fucntion to compare precedence
// If we return larger value means higher precedence 
int precedence(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 

    case '*': 
    case '/': 
        return 2; 

    case '^': 
        return 3; 
    } 
    return -1; 
} 

// The driver function for infix to postfix conversion 
int covertInfixToPostfix(char* expression) 
{ 
    int i, j; 

    // Stack size should be equal to expression size for safety  
    struct Stack* stack = create(strlen(expression)); 
    if(!stack) // just checking is stack was created or not  
        return -1 ; 

    for (i = 0, j = -1; expression[i]; ++i) 
    { 
        // Here we are checking is the character we scanned is operand or not
        // and this adding to to output. 
        if (checkIfOperand(expression[i])) 
            expression[++j] = expression[i]; 

        // Here, if we scan character ‘(‘, we need push it to the stack. 
        else if (expression[i] == '(') 
            push(stack, expression[i]); 

        // Here, if we scan character is an ‘)’, we need to pop and print from the stack  
        // do this until an ‘(‘ is encountered in the stack. 
        else if (expression[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                expression[++j] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return -1; // invalid expression              
            else
                pop(stack); 
        } 
        else // if an opertor
        { 
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack))) 
                expression[++j] = pop(stack); 
            push(stack, expression[i]); 
        } 

    } 

    // Once all inital expression characters are traversed
    // adding all left elements from stack to exp
    while (!isEmpty(stack)) 
        expression[++j] = pop(stack); 

    expression[++j] = '\0'; 
    printf( "%s", expression); 
} 

void printInorder(struct node* node)
{
    if (node == NULL)
        return;
    else{
        printInorder(node->left);
        printf("%c ", node->data);
        printInorder(node->right);
    }
}

int eval(struct node* root)
{
    if (!root)
        return 0;
 
    if (!root->left && !root->right){
        int c = root->data;
        return c-48;
    }
 
    int l_val = eval(root->left);
 
    int r_val = eval(root->right);
 
    if (root->data=='+')
        return l_val+r_val;
 
    if (root->data=='-')
        return l_val-r_val;
 
    if (root->data=='*')
        return l_val*r_val;
 
    return l_val/r_val;
}

int main()
{   
    // init the input and take the input
    char expression[100];

    while (1)
    {   
        int key;
        printf("\n1.for input()\n2.infixToPostfix()\n3.PostfixToTree\n4.Evaluate\n5.exit()\n");
        printf("Enter the key : ");
        scanf("%d",&key);

        if (key == 1)
        {
            printf("Enter the expression : ");
            gets(expression); 
        }

        else if (key == 2)
        {
            // convert it to postfix expression
            covertInfixToPostfix(expression); 
            printf("\nInfix to Postfix expresssion : %s\n",expression);
        }
        
        else if (key == 3)
        {
            // convert postfix to tree
            struct node *x, *y, *z;
            for (int i = 0; i < strlen(expression); i++) {
                if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
                    z = newNode(expression[i]);
                    x = popTree();
                    y = popTree();
                    z->left = y;
                    z->right = x;
                    pushTree(z);
                }
                else {
                    z = newNode(expression[i]);
                    pushTree(z);
                }
            }

             // inorder traversal
            printf("\n");
            printInorder(z);
            printf("\n");
        }
        
        else if (key == 4)
        {
            // evaluate
            printf("\n%d\n",eval(head));
        }
        
        else if (key ==5)
        {
            printf("\nTHANK YOU\n");
            return 0;
        }
        
    }


    return 0; 
}