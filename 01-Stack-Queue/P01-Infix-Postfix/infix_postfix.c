#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int evalStack[MAX];
int evalTop = -1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

int precedence(char ch)
{
    if(ch == '^')
        return 3;
    else if(ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    for(i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if(isdigit(ch) || isalpha(ch))
        {
            postfix[j++] = ch;
        }
        else if(ch == '(')
        {
            push(ch);
        }
        else if(ch == ')')
        {
            while(top != -1 && stack[top] != '(')
                postfix[j++] = pop();

            pop();
        }
        else
        {
            while(top != -1 && stack[top] != '(' &&
                  precedence(stack[top]) >= precedence(ch))
                postfix[j++] = pop();

            push(ch);
        }
    }

    while(top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

int power(int a, int b)
{
    int result = 1, i;

    for(i = 0; i < b; i++)
        result *= a;

    return result;
}

int evaluatePostfix(char postfix[])
{
    int i, a, b;
    char ch;

    evalTop = -1;

    for(i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if(isdigit(ch))
        {
            evalStack[++evalTop] = ch - '0';
        }
        else
        {
            b = evalStack[evalTop--];
            a = evalStack[evalTop--];

            switch(ch)
            {
                case '+':
                    evalStack[++evalTop] = a + b;
                    break;

                case '-':
                    evalStack[++evalTop] = a - b;
                    break;

                case '*':
                    evalStack[++evalTop] = a * b;
                    break;

                case '/':
                    evalStack[++evalTop] = a / b;
                    break;

                case '%':
                    evalStack[++evalTop] = a % b;
                    break;

                case '^':
                    evalStack[++evalTop] = power(a, b);
                    break;
            }
        }
    }

    return evalStack[evalTop];
}

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    printf("Evaluated result: %d\n",
           evaluatePostfix(postfix));

    return 0;
}