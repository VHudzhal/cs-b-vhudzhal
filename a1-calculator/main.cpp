#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3
using namespace std;

char *prog; /* holds expression to be analyzed */
char token[80];
char tok_type;

double vars[26] = { /* 26 user variables,  A-Z */
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0
                  };

void eval_exp(double *result), eval_exp2(double *result);
void eval_exp1(double *result);
void eval_exp3(double *result), eval_exp4(double *result);
void eval_exp5(double *result), eval_exp7(double *result);
//void eval_exp6(double *result), eval_exp5(double *result);
void eval_exp7(double *result), eval_exp5(double *result);
void atom(double *result);
void get_token(void), putback(void);
void serror(int error);
double find_var(char *s);
double factorial(int operand);
int isdelim(char c);

/* Точка входа анализатора. */
void eval_exp(double *result)
{
    get_token();
    if(!*token) {
        serror(2);
        return;
    }
    eval_exp1(result);
    if(*token) serror(0); /* последня лексема должна быть нулем */
}

/* Обработка присваивания. */
void eval_exp1(double *result)
{
    int slot;
    char ttok_type;
    char temp_token[80];

    if(tok_type == VARIABLE) {
        /* сохранить старую лексему */
        strcpy(temp_token, token);
        ttok_type = tok_type;
        /* вычислить индекс переменной */
        slot = toupper(*token) - 'A';

        get_token();
        if(*token != '=') {
            cin.putback(ttok_type); /* вернуть текущую лексему */
            /* восстановить старую лексему - это не присваивание */
            strcpy(token, temp_token);
            tok_type = ttok_type;
        }
        else {
            get_token(); /* получить следующую часть выражения */
            eval_exp2(result);
            vars[slot] = *result;
            return;
        }
    }
    eval_exp2(result);
}

/* Сложение или вычитание двух слагаемых. */
void eval_exp2(double *result)
{
    register char op;
    double temp;

    eval_exp3(result);
    while((op = *token) == '+' || op == '-') {
        get_token();
        eval_exp3(&temp);
        switch(op) {
        case '-':
            *result-= temp;
            break;
        case '+':
            *result+= temp;
            break;
        }
    }
}

/* Умножение или деление двух множителей. */
void eval_exp3(double *result)
{
    register char op;
    double temp;

    eval_exp4(result);
    while((op = *token) == '*' || op == '/' || op == '%') {
        get_token();
        eval_exp4(&temp);
        switch(op) {
        case '*':
            *result*= temp;
            break;
        case '/':
            if(temp == 0.0) {
                serror(3); /* деление на ноль */
                *result= 0.0;
            } else *result/= temp;
            break;
        case '%':
            *result= (int) *result% (int) temp;
            break;
        }
    }
}

/* Возведение в степень */
void eval_exp4(double *result)
{
    double temp, ex;
    register int t;

    eval_exp5(result);
    if(*token == '^') {
        get_token();
        eval_exp4(&temp);
        ex = *result;
        if(temp==0.0) {
            serror(4);
        }
        for(t=temp-1; t>0; --t)
            *result*= (double)ex;
    }
}

/* Вычисление унарного + и -. */
void eval_exp5(double *result)
{
    register char  op;

    op = 0;
    if(((tok_type == DELIMITER) && *token=='+') || *token == '-') {
        op = *token;
        get_token();
    }
    eval_exp7(result);
    if(op == '-') *result= -(*result);

}
/*Вычисление кореня числа*/
void eval_exp6(double *result)
{
    double temp;
    register char op = *token;
    eval_exp6(result);
    while(op  == 'sqrt' || op == 'sin' || op == 'cos' ||op == 'log' || op == 'tan') {
        get_token();
        eval_exp6(&temp);
        while(true) {
            if(op == 'sqrt'){
                if(temp < 0.0) {
                    serror(4); /*  */
                }
                *result= sqrt(temp);}
            else if(op == 'sin')
            {
                *result = sin(temp);

            }
            else if(op == 'cos')
            {
                *result = cos(temp);
            }
            else  if(op == 'tan')
            {
                *result = tan(temp);
            }
            else  if(op == '!')
            {

                *result = factorial((int)temp);
            }
            else  if(op == 'log')
            {

                *result = log2(temp);
            }
        }
    }
}

/* Обработка выражения в скобках. */
void eval_exp7(double *result)
{
    if((*token == '(')) {
        get_token();
        eval_exp2(result);
        if(*token != ')')
            serror(1);
        get_token();
    }
    else atom(result);
}

double factorial(int operand) {
    /* Calculate factorial */
    if(operand==0){
        return 0;
    }
    for(int i = operand-1;i!=0;i--){
        operand *= i;
    }
    return (double) operand;
}
/* Получение значения числа или переменной. */
void atom(double *result)
{
    switch(tok_type) {
    case VARIABLE:
        *result= find_var(token);
        get_token();
        return;
    case NUMBER:
        *result= atof(token);
        get_token();
        return;
    default:
        serror(0);
    }
}

/* Возврат лексемы во входной поток. */
void putback(void)
{
    char *t;

    t = token;
    for(; *t; t++) prog--;
}

/* Отображение сообщения о синтаксической ошибке. */
void serror(int error)
{
    const char *e[]= {
        "Syntax error",
        "Unbalanced parentheses",
        "No expression",
        "Division by zero",
        "Root value is less than zero"

    };
    printf("%s\n", e[error]);
}

/* Получение очередной лексемы. */
void get_token(void)
{
    register char *temp;

    tok_type = 0;
    temp = token;
    *temp = '\0';

    if(!*prog) return; /* конец выражения */

    while(*prog!='\n'&& isspace(*prog)) ++prog; /* пропустить пробелы,
                  символы табуляции и пустой строки */

    if(strchr("+-*/%^=()_", *prog) || strchr("s",*prog) || strchr("c", *prog)){
        tok_type = DELIMITER;
        /* перейти к следующему символу */
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

// Возвращение значения ИСТИНА, если с является разделителем.
int isdelim(char c)
{
    if(strchr(" +-/*%^=()_", c) || strchr("s",*prog) || strchr("c", *prog)|| c==9 || c=='\r' || c==0)
        return 1;
    return 0;
}
// Get the value of a variable.
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
    double result;
    char *p;

    p = (char *) malloc(100);
    if(!p) {
        cout << "Ошибка при выделении памяти.\n";
        exit(1);
    }

    /* Обработка выражений до ввода пустой строки. */
    do {
        prog = p;
        cout << "Please, enter the expression: ";
        gets(prog);
        if(!*prog) break;
        eval_exp(&result);
        cout << "The result is: " << result<< endl;
    } while(*p);

    return 0;
}
