#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3
using namespace std;

char *prog; /* pointer to the test expression */
char token[80];
char tok_type;

double vars[26] = { /* custom variables 26 ,  A-Z */
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0
                  };

void eval_exp(double *answer), 
eval_exp2(double *answer)/*Addition or subtraction*/;
void eval_exp1(double *result);
//Multiplication or division function
void eval_exp3(double *answer),
eval_exp4(double *answer) /* Exponentiation process */;
void eval_exp5(double *answer), 
/*Function for working with processing of expression in brackets*/eval_exp6(double *answer);

//Getting the value of a number or variable
void atom(double *answer);
//getting next token
void get_token(void), 
/*return tokens*/putback(void);
//error processing
void serror(int error);
double find_var(char *s);
int isdelim(char c);

/* The entry point of the Analyzer */
void eval_exp(double *answer)
{
    get_token();
    if(!*token) {
        serror(2);
        return;
    }
    eval_exp1(answer);
    if(*token) serror(0); /* latest token must be zero */
}

/* The processing of the assignment */
void eval_exp1(double *answer)
{
    int slot;
    char ttok_type;
    char temp_token[80];
    
    if(tok_type == VARIABLE) {
        /* Save the old token */
        strcpy(temp_token, token);
        ttok_type = tok_type;
        /* calculate the index variable */
        slot = toupper(*token) - 'A';
        
        get_token();
        if(*token != '=') {
            cin.putback(ttok_type); /* return the current token
             restore the old token -  it is not assignment */
            strcpy(token, temp_token);
            tok_type = ttok_type;
        }
        else {
            get_token(); /* get next subexpression */
            eval_exp2(answer);
            vars[slot] = *answer;
            return;
        }
    }
    eval_exp2(answer);
}

/* Addition or subtraction of two terms. */
void eval_exp2(double *answer)
{
    register char op;
    double temp;
    
    eval_exp3(answer);
    while((op = *token) == '+' || op == '-') {
        get_token();
        eval_exp3(&temp);
        switch(op) {
        case '-':
            *answer -= temp;
            break;
        case '+':
            *answer += temp;
            break;
        }
    }
}

/* Multiplication or division of two factors. */
void eval_exp3(double *answer)
{
    register char op;
    double temp;
    
    eval_exp4(answer);
    while((op = *token) == '*' || op == '/' || op == '%') {
        get_token();
        eval_exp4(&temp);
        switch(op) {
        case '*':
            *answer *= temp;
            break;
        case '/':
            if(temp == 0.0) {
                serror(3); /* Division by zero */
                *answer = 0.0;
            } else *answer /= temp;
            break;
        case '%':
            *answer = (int) *answer % (int) temp;
            break;
        }
    }
}

/* Exponentiation process */
void eval_exp4(double *answer)
{
    double temp, ex;
    register int t;
    
    eval_exp5(answer);
    if(*token == '^') {
        get_token();
        eval_exp4(&temp);
        ex = *answer;
        if(temp==0.0) {
            *answer = 1.0;
            return;
        }
        for(t=temp-1; t>0; --t)
            *answer *= (double)ex;
    }
}

/* The calculation of the unary + and -. */
void eval_exp5(double *answer)
{
    register char  op;
    
    op = 0;
    if((tok_type == DELIMITER) && *token=='+' || *token == '-') {
        op = *token;
        get_token();
    }
    eval_exp6(answer);
    if(op == '-') *answer = -(*answer);
}

/* Processing of expression in brackets. */
void eval_exp6(double *answer)
{
    if((*token == '(')) {
        get_token();
        eval_exp2(answer);
        if(*token != ')')
            serror(1);
        get_token();
    }
    else atom(answer);
}

/* Get the value of a number or variable.*/
void atom(double *answer)
{
    switch(tok_type) {
    case VARIABLE:
        *answer = find_var(token);
        get_token();
        return;
    case NUMBER:
        *answer = atof(token);
        get_token();
        return;
    default:
        serror(0);
    }
}

/* Return the tokens in the input stream. */
void putback(void)
{
    char *t;
    t = token;
    for(; *t; t++) prog--;
}

/* Display a syntax error. */
void serror(int error)
{
    static char *e[]= {
        "Syntax error",
        "Unbalanced parentheses",
        "No expression",
        "Division by zero"
    };
    cout << "%s\n" << e[error] << endl;
}

/* Get next token. */
void get_token(void)
{
    register char *temp;
    
    tok_type = 0;
    temp = token;
    *temp = '\0';
    
    if(!*prog) return; /* End of the expression */
    
    while(*prog!='\n'&& isspace(*prog)) ++prog; /* Skip white space,
                                                tabs, and an empty string */
    
    if(strchr("+-*/%^=()", *prog)){
        tok_type = DELIMITER;
        /* move to next character */
        *temp++ = *prog++;
    }
    else if(isalpha(*prog)) {
        while(!isdelim(*prog)) *temp++ = *prog++;
        tok_type = VARIABLE;
    }
    else if(isdigit(*prog)) {
        while(!isdelim(*prog)) *temp++ = *prog++;
        tok_type = NUMBER;
    }
    
    *temp = '\0';
}

/* Return true if c is a separator. */
int isdelim(char c)
{
    if(strchr(" +-/*%^=()", c) || c==9 || c=='\r' || c==0)
        return 1;
    return 0;
}

/* Get the value of a variable. */
double find_var(char *s)
{
    if(!isalpha(*s)){
        serror(1);
        return 0.0;
    }
    return vars[toupper(*token)-'A'];
}

int main(void)
{
    double answer;
    char *p;
    
    p = (char *) malloc(100);
    if(!p) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    /* Processing of expressions to enter an empty string. */
    do {
        prog = p;
        cout << "Please, enter the expression: ";
        gets(prog);
        if(!*prog) break;
        eval_exp(&answer);
        cout << "The result is: " << answer << endl;
    } while(*p);
    return 0;
}
