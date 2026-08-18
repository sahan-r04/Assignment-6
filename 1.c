#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define MAXHISTORY 100

typedef struct {
    char operation[20];
    double operand1;
    double operand2;
    double result;
} Record;

Record history[MAXHISTORY];
int historycount = 0;

typedef double (*Calc)(double, double);

double addition(double a, double b)       { return a + b; }
double subtraction(double a, double b)    { return a - b; }
double multiplication(double a, double b) { return a * b; }

double division(double a, double b) {
    int choice;
    if (b == 0) {
        printf("Error: Division by zero.\n");
        return 0;
    }
    printf("##########################\n");
    printf("##########################\n");
    printf("## 1. Integer Division  ##\n");
    printf("## 2. Normal Division   ##\n");
    printf("##########################\n");
    printf("##########################\n");
    printf("Choose division type: ");
    scanf("%d", &choice);
    if (choice == 1)
        return (double)((long)a / (long)b);
    else
        return a / b;
}

double power(double a, double b) { return pow(a, b); }

int findgcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

double lcm(double a, double b) {
    int ia = (int)a, ib = (int)b;
    int g = findgcd(ia, ib);
    if (g == 0) return 0;
    return (double)abs(ia * ib) / g;
}

double gcd(double a, double b) {
    return (double)findgcd((int)a, (int)b);
}

double sine(double a, double b) { (void)b; return sin(a * M_PI / 180.0); }
double cosine(double a, double b) { (void)b; return cos(a * M_PI / 180.0); }
double tangent(double a, double b) { (void)b; return tan(a * M_PI / 180.0); }

double inverse(double a, double b) {
    (void)b;
    if (a == 0) {
        printf("Error: Cannot invert zero.\n");
        return 0;
    }
    return 1.0 / a;
}

double remainder(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero.\n");
        return 0;
    }
    return fmod(a, b);
}


double oddeven(double a, double b) {
    (void)b;
    long n = (long)a;
    return (n % 2 == 0) ? 0.0 : 1.0;
}

double percentage(double a, double b) { return (a * b) / 100.0; }

const char *names[14] = {
    "Addition", "Subtraction", "Multiplication", "Division", "Power",
    "LCM", "GCD", "Sine", "Cosine", "Tangent",
    "Inverse", "Remainder", "Odd or Even", "Percentage"
};

Calc funcs[14] = {
    addition, subtraction, multiplication, division, power,
    lcm, gcd, sine, cosine, tangent,
    inverse, remainder, oddeven, percentage
};

void showmenu(void) {
    printf("\n##########################################\n");
    printf("##  SCS 1301 - Scientific Calculator   ##\n");
    printf("##              by <your name>          ##\n");
    printf("##########################################\n");
    printf("##########################################\n");
    printf("# 1. Addition          8. Sine           #\n");
    printf("# 2. Subtraction       9. Cosine         #\n");
    printf("# 3. Multiplication   10. Tangent        #\n");
    printf("# 4. Division         11. Inverse        #\n");
    printf("# 5. Power            12. Remainder      #\n");
    printf("# 6. LCM              13. Odd or Even    #\n");
    printf("# 7. GCD              14. Percentage     #\n");
    printf("#                                        #\n");
    printf("# 16. Show History                       #\n");
    printf("# 15. Exit                                #\n");
    printf("##########################################\n");
    printf("##########################################\n");
}

void showresult(double result) {
    if (result == (long long)result)
        printf("Result: %lld\n", (long long)result);
    else
        printf("Result: %.4f\n", result);
}

void addhistory(const char *name, double a, double b, double result) {
    if (historycount >= MAXHISTORY) return;
    Record rec;
    snprintf(rec.operation, sizeof(rec.operation), "%s", name);
    rec.operand1 = a;
    rec.operand2 = b;
    rec.result = result;
    history[historycount++] = rec;
}

void showhistory(void) {
    if (historycount == 0) {
        printf("No operations performed yet.\n");
        return;
    }
    printf("\n----- History of Operations -----\n");
    for (int i = 0; i < historycount; i++) {
        printf("%d. %-15s operand1=%.2f operand2=%.2f -> result=%.4f\n",
               i + 1, history[i].operation, history[i].operand1,
               history[i].operand2, history[i].result);
    }
}

int main(void) {
    int choice;

    while (1) {
        showmenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (choice == 15) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        if (choice == 16) {
            showhistory();
            continue;
        }

        if (choice < 1 || choice > 14) {
            printf("Invalid choice, try again.\n");
            continue;
        }

        double a, b;
        printf("Enter first operand: ");
        scanf("%lf", &a);
        printf("Enter second operand (enter 0 if not needed): ");
        scanf("%lf", &b);

        Calc chosen = funcs[choice - 1];
        double result = chosen(a, b);

        showresult(result);
        addhistory(names[choice - 1], a, b, result);
    }

    return 0;
}
