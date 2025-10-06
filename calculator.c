#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    PREC_NONE = 0,
    PREC_ADD_SUB = 1,
    PREC_MUL_DIV = 2
} Precedence;

Precedence get_precedence(char op) {
    if (op == '*' || op == '/') {
        return PREC_MUL_DIV;
    }
    if (op == '+' || op == '-') {
        return PREC_ADD_SUB;
    }
    return PREC_NONE;
}

int apply_op(int a, int b, char op, bool *error) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero.\n");
                *error = true;
                return 0;
            }
            return a / b;
    }
    return 0;
}

int main() {
    char expression[256];

    printf("Enter expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    bool has_error = false;

    int values[100];
    int values_top = -1;

    char ops[100];
    int ops_top = -1;

    for (int i = 0; expression[i] != '\0' && !has_error; i++) {
        if (isspace((unsigned char)expression[i])) {
            continue;
        }

        if (isdigit((unsigned char)expression[i])) {
            int num = 0;
            while (isdigit((unsigned char)expression[i])) {
                num = (num * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            
            values[++values_top] = num;

        } else if (strchr("+-*/", expression[i])) {
            while (ops_top != -1 && get_precedence(ops[ops_top]) >= get_precedence(expression[i])) {
                int val2 = values[values_top--];
                int val1 = values[values_top--];
                char op = ops[ops_top--];
                
                values[++values_top] = apply_op(val1, val2, op, &has_error);
                
                if (has_error) break;
            }
            ops[++ops_top] = expression[i];

        } else {
            if (expression[i] != '\n') {
                 printf("Error: Invalid character in expression: %c\n", expression[i]);
                 has_error = true;
            }
        }
    }
    
    if (!has_error) {
        while (ops_top != -1) {
            int val2 = values[values_top--];
            int val1 = values[values_top--];
            char op = ops[ops_top--];

            values[++values_top] = apply_op(val1, val2, op, &has_error);
            if (has_error) break;
        }
    }
    
    if (has_error) {
        return 1;
    }

    if (values_top != 0) {
        printf("Error: Invalid expression format.\n");
        return 1;
    }

    printf("Result: %d\n", values[0]);

    return 0;
}
