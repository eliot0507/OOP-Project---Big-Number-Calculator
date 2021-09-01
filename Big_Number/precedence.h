#include <stdio.h> 
#include <stdlib.h> 
#include<iostream>

using namespace std;
#define MAX 80

void inToPostfix(string&, string&); // infix to postfix
int priority(char); // operator priority

int main(void) {
    string infix;
    string postfix;

    printf("infix:");
    cin >> infix;
    inToPostfix(infix, postfix);

    cout << postfix;

    return 0;
}

void inToPostfix(string& infix, string& postfix) {
    char stack[80]{ '\0' };
    int i, j, top;
    for (i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch (infix[i]) {
    case '(':              // operator stack 
        stack[++top] = infix[i];
        break;
    case '+': case '-': case '*': case '/':
        while (priority(stack[top]) >= priority(infix[i])) {
            postfix.push_back(stack[top--]);
        }
        stack[++top] = infix[i]; // in stack
        break;
    case ')':
        while (stack[top] != '(') { // when encounter ) output to ( 
            postfix.push_back(stack[top--]);
        }
        top--;  // no output ( 
        break;
    default:  // directly output
        postfix.push_back(infix[i]);
    }
    while (top > 0) {
        postfix.push_back(stack[top--]);
    }
}

int priority(char op) {
    switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default:            return 0;
    }
}


