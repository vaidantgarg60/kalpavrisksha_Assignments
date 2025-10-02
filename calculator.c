#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int get_precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

int apply_op(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            return a / b;
    }
    return 0;
}

int main() {
    char expression[256];

    printf("Enter expression: ");
    fgets(expression, sizeof(expression), stdin);

    int values[100];
    int v_top = -1;

    char ops[100];
    int o_top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isspace(expression[i])) {
            continue;
        }

        if (isdigit(expression[i])) {
            int num = 0;
                while (isdigit(expression[i])) {
                    num = (num * 10) + (expression[i] - '0');
                    i++;
            }
            i--;
            
            values[++v_top] = num;

        } else if (strchr("+-*/", expression[i])) {
            while (o_top != -1 && get_precedence(ops[o_top]) >= get_precedence(expression[i])) {
                int val2 = values[v_top--];
                int val1 = values[v_top--];
                char op = ops[o_top--];
                values[++v_top] = apply_op(val1, val2, op);
            }
            ops[++o_top] = expression[i];

        } else {
            printf("Error: Invalid expression.\n");
            return 1;
        }
    }

    while (o_top != -1) {
        int val2 = values[v_top--];
        int val1 = values[v_top--];
        char op = ops[o_top--];
        values[++v_top] = apply_op(val1, val2, op);
    }

    if (v_top != 0) {
        printf("Error: Invalid expression.\n");
        return 1;
    }

    printf("Result: %d\n", values[0]);

    return 0;
}