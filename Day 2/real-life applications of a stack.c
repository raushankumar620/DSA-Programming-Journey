#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
struct Stack {
    int top;
    char arr[MAX];
};

// Initialize stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push operation
void push(struct Stack* stack, char ch) {
    if (!isFull(stack)) {
        stack->arr[++stack->top] = ch;
    }
}

// Pop operation
char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top--];
    }
    return '\0';  // Return null character if stack is empty
}

// Peek operation
char peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top];
    }
    return '\0';
}

// Function to check for balanced parentheses
int areParenthesesBalanced(char* exp) {
    struct Stack stack;
    initStack(&stack);

    for (int i = 0; i < strlen(exp); i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            push(&stack, exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(&stack)) return 0;
            char top = pop(&stack);
            if ((exp[i] == ')' && top != '(') ||
                (exp[i] == '}' && top != '{') ||
                (exp[i] == ']' && top != '[')) {
                return 0;
            }
        }
    }
    return isEmpty(&stack);
}

// Function to reverse a string using stack
void reverseString(char* str) {
    struct Stack stack;
    initStack(&stack);
    
    // Push characters onto stack
    for (int i = 0; i < strlen(str); i++) {
        push(&stack, str[i]);
    }
    
    // Pop characters to reverse the string
    for (int i = 0; i < strlen(str); i++) {
        str[i] = pop(&stack);
    }
}

int main() {
    // Example 1: Check for balanced parentheses
    char expression[] = "{(a+b) * [c-d]}";
    if (areParenthesesBalanced(expression)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are not balanced.\n");
    }
    
    // Example 2: Reverse a string using stack
    char str[] = "Hello, World!";
    printf("Original String: %s\n", str);
    reverseString(str);
    printf("Reversed String: %s\n", str);
    
    return 0;
}
