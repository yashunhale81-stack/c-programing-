#include <stdio.h>

int main()
 {
    char operator;
    double num1, num2, result;

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator); // Note the space before %c to clear any leftover newline character

    printf("Enter two numbers: ");
    scanf("%lf %lf", &num1, &num2);

    switch (operator)
     {
        case '+':
            result = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '-':
            result = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '*':
            result = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
            
        case '/':
            if (num2 != 0.0) 
            {
                result = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else
             {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error! '%c' is an invalid operator.\n", operator);
    }

    return 0;
}
