/*
 * Exercise VI - Question 1
 * Extends Exercise IV - 3(e) "SCS 1301 Scientific Calculator" menu program.
 * Every menu option (1-14) is invoked through a FUNCTION POINTER stored in
 * an array (opFuncs[]), instead of a long if/else or switch chain.
 *
 * Also keeps the earlier requirements from Exercise IV - 3(e):
 *   iii. loops until the user exits (option 15)
 *   iv.  option 16 prints the history of operations performed
 *   v.   division has a sub-menu (Integer Division / Normal Division)
 *   vi.  results are printed as whole numbers when they are exact,
 *        and as decimals otherwise
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define MAX_HISTORY 100

/* ---------- history record ---------- */
typedef struct {
    char operation[20];
    double operand1;
    double operand2;
    double result;
} HistoryRecord;

HistoryRecord history[MAX_HISTORY];
int historyCount = 0;

/* ---------- function pointer type ----------
 * Every calculator operation is made to fit this common signature so that
 * all of them can be stored in a single array of function pointers.
 * Operations that only need one value (Sine, Cosine, Inverse, Odd/Even...)
 * simply ignore the second parameter.
 */
typedef double (*CalcFunc)(double, double);

/* ---------- the 14 operations ---------- */
double additionFunc(double a, double b)       { return a + b; }
double subtractionFunc(double a, double b)    { return a - b; }
double multiplicationFunc(double a, double b) { return a * b; }

double divisionFunc(double a, double b) {
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

double powerFunc(double a, double b) { return pow(a, b); }

int gcdInt(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

double lcmFunc(double a, double b) {
    int ia = (int)a, ib = (int)b;
    int g = gcdInt(ia, ib);
    if (g == 0) return 0;
    return (double)abs(ia * ib) / g;
}

double gcdFunc(double a, double b) {
    return (double)gcdInt((int)a, (int)b);
}

double sineFunc(double a, double b)    { (void)b; return sin(a * PI / 180.0); }
double cosineFunc(double a, double b)  { (void)b; return cos(a * PI / 180.0); }
double tangentFunc(double a, double b) { (void)b; return tan(a * PI / 180.0); }

double inverseFunc(double a, double b) {
    (void)b;
    if (a == 0) {
        printf("Error: Cannot invert zero.\n");
        return 0;
    }
    return 1.0 / a;
}

double remainderFunc(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero.\n");
        return 0;
    }
    return fmod(a, b);
}

/* returns 1 for Odd, 0 for Even (second operand unused) */
double oddEvenFunc(double a, double b) {
    (void)b;
    long n = (long)a;
    return (n % 2 == 0) ? 0.0 : 1.0;
}

double percentageFunc(double a, double b) { return (a * b) / 100.0; }

/* ---------- names + function pointer table ---------- */
const char *opNames[14] = {
    "Addition", "Subtraction", "Multiplication", "Division", "Power",
    "LCM", "GCD", "Sine", "Cosine", "Tangent",
    "Inverse", "Remainder", "Odd or Even", "Percentage"
};

CalcFunc opFuncs[14] = {
    additionFunc, subtractionFunc, multiplicationFunc, divisionFunc, powerFunc,
    lcmFunc, gcdFunc, sineFunc, cosineFunc, tangentFunc,
    inverseFunc, remainderFunc, oddEvenFunc, percentageFunc
};

/* ---------- helpers ---------- */
void printMenu(void) {
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

/* prints a whole number without a decimal point, otherwise as a decimal (vi) */
void printResult(double result) {
    if (result == (long long)result)
        printf("Result: %lld\n", (long long)result);
    else
        printf("Result: %.4f\n", result);
}

void addHistory(const char *name, double a, double b, double result) {
    if (historyCount >= MAX_HISTORY) return;
    HistoryRecord rec;
    snprintf(rec.operation, sizeof(rec.operation), "%s", name);
    rec.operand1 = a;
    rec.operand2 = b;
    rec.result = result;
    history[historyCount++] = rec;
}

void printHistory(void) {
    if (historyCount == 0) {
        printf("No operations performed yet.\n");
        return;
    }
    printf("\n----- History of Operations -----\n");
    for (int i = 0; i < historyCount; i++) {
        printf("%d. %-15s operand1=%.2f operand2=%.2f -> result=%.4f\n",
               i + 1, history[i].operation, history[i].operand1,
               history[i].operand2, history[i].result);
    }
}

/* ---------- main ---------- */
int main(void) {
    int choice;

    while (1) {
        printMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n'); /* clear bad input */
            continue;
        }

        if (choice == 15) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        if (choice == 16) {
            printHistory();
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

        /* dispatch through the function pointer table */
        CalcFunc chosenFunc = opFuncs[choice - 1];
        double result = chosenFunc(a, b);

        printResult(result);
        addHistory(opNames[choice - 1], a, b, result);
    }

    return 0;
}
