#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int i,n;
void gotoxy(int x, int y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}
void fileopen(char *filename, int linex,int liney)
{
    FILE *ptr;
    ptr= fopen(filename,"r");
    if(ptr==NULL)
    {
        printf("ERROR: The file was not found");
        exit(1);
    }
    int i=0;
    char a[100];
    Sleep(2000);
    while(fgets(a,sizeof(a),ptr)!= NULL)
    {
        gotoxy(linex,liney+i);
        printf("%s",a);
        Sleep(200);
        i++;
    }
    fclose(ptr);
}
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;      // cursor size (not very important here)
    info.bVisible = FALSE;  // FALSE = invisible, TRUE = visible
    SetConsoleCursorInfo(consoleHandle, &info);
}
void showcursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;   // TRUE = visible
    SetConsoleCursorInfo(consoleHandle, &info);
}


void setColor(int attr)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, attr);
}


void clear()
{
    system("cls");
}
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define HOT_PINK"\033[38;2;255;105;180m"
#define BLUE    "\033[94m"
#define C 1
#define F 2
#define K 3
struct History {
    float input;
    float output;
    const char* from;
    const char* to;    };
struct History history[50];
int hcount = 0;
//FUNCTION PROTOTYPE DECLARATION
float convertTemp(float value, int from, int to);
void addHistory(float in, float out,const char* from,const char* to);
void showHistory(void);

const char* unitCharT(int unit)
{   if (unit == C) return "C";
    if (unit == F) return "F";
        return "K";     }

void temp()
{
    int choice, from, to;
    float value, result;

printf(CYAN "\n=====================================\n      ");
        char temp[25]= {"TEMPERATURE CONVERTER"};
    for(i=0; i<25; i++)
    {
        printf("%c",temp[i]);
        Sleep(40);
    }

        printf("\n=====================================\n" RESET);
    while (1)
    {
        printf(YELLOW "\nMenu\n" RESET);
        printf("1. Celsius <--> Fahrenheit\n");
        printf("2. Celsius <--> Kelvin\n");
        printf("3. Kelvin <--> Fahrenheit\n");
        printf("4. View History\n");
        printf("5. Exit\n");

        printf(YELLOW "Enter choice: " RESET);
        scanf("%d", &choice);

        if (choice == 5)
            break;

        if (choice == 4)
        {   showHistory();
            continue;   }

        if (choice == 1)
            printf("1. Celsius\n2. Fahrenheit\n");
        else if (choice == 2)
            printf("1. Celsius\n2. Kelvin\n");
        else if (choice == 3)
            printf("1. Kelvin\n2. Fahrenheit\n");
        else
        {   printf(RED "Invalid choice entered.\n" RESET);
            continue;   }

        printf("\nSelect FROM unit: ");
        scanf("%d", &from);
        if(from==1)
        to=2;
        else if(from==2)
        to=1;
        if (from < 1 || from > 2 || to < 1 || to > 2)
        {   printf(RED "Invalid unit selection.\n" RESET);
            continue;   }

        printf(BLUE"Enter temperature value: "RESET);
        scanf("%f", &value);

        if (choice == 1)                // C <--> F
        {   from = (from == 1) ? C : F;
            to   = (to   == 1) ? C : F; }
        else if (choice == 2)           //C <--> K
        {   from = (from == 1) ? C : K;
            to   = (to   == 1) ? C : K; }
        else                            //K <--> F
        {   from = (from == 1) ? K : F;
            to   = (to   == 1) ? K : F; }

        result = convertTemp(value, from, to);

        addHistory(value, result, unitCharT(from), unitCharT(to)); //FUNCTION CALL
        struct History *h = &history[hcount - 1];
        printf(GREEN "Result: %.2f %s = %.2f %s\n" RESET,
               h->input, h->from,
               h->output, h->to);   }
    return;   }

float convertTemp(float value, int from, int to)
{   float celsius;

    if (from == C)
        celsius = value;
    else if (from == F)
        celsius = (value - 32) * 5 / 9;
    else
        celsius = value - 273.15;

    if (to == C)
        return celsius;
    else if (to == F)
        return (celsius * 9 / 5) + 32;
    else
        return celsius + 273.15;  }


#define INR 1
#define USD 2
#define EUR 3
#define JPY 4
#define GBP 5
float usd_rate = 89.60;
float eur_rate = 104.99;
float gbp_rate = 120.01;
float jpy_rate = 0.57;

float convertCUR(float value, int from, int to)
{
    float cur=0;

    // Convert FROM currency to INR
    if (from == INR)
        cur = value;
    else if (from == USD)
        cur = value * usd_rate;
    else if (from == EUR)
        cur = value * eur_rate;
    else if (from == GBP)
        cur = value * gbp_rate;
    else
        cur = value * jpy_rate;

    if (to == INR)
        return cur;
    else if (to == USD)
        return cur / usd_rate;
    else if (to == EUR)
        return cur / eur_rate;
    else if (to == GBP)
        return cur / gbp_rate;
    else
        return cur / jpy_rate;
}

const char* unitCharC(int unit){
    if (unit == INR) return "INR";
    if (unit == USD) return "USD";
    if (unit == JPY) return "JPY";
    if (unit == GBP) return "GBP";
    return "EUR";}
int currency()
{
    int choice, from, to;
    float value, result;

printf(CYAN "\n=====================================\n       ");
        char temp[25]= {"CURRENCY CONVERTER"};
    for(i=0; i<25; i++)
    {
        printf("%c",temp[i]);
        Sleep(40);
    }

        printf("\n=====================================\n" RESET);
    while (1)
    {
        printf(YELLOW "\nMenu\n" RESET);
        printf("1. Indian Rupee <--> United States Dollar\n");
        printf("2. Indian Rupee <--> Euro\n");
        printf("3. Indian Rupee <--> Great British Pound\n");
        printf("4. Indian Rupee <--> Japanese Yen\n");
        printf("5. View History\n");
        printf("6. Exit\n");

        printf(YELLOW "Enter choice: " RESET);
        scanf("%d", &choice);

        if (choice == 6)
            break;

        if (choice == 5)
        {   showHistory();
            continue;   }

        if (choice == 1)
            printf("1. Indian Rupee\n2. United States Dollar\n");
        else if (choice == 2)
            printf("1. Indian Rupee\n2. Euro\n");
        else if (choice == 3)
            printf("1. Indian Rupee\n2. Great British Pound\n");
        else if (choice == 4)
            printf("1. Indian Rupee\n2. Japanese Yen\n");
        else
        {   printf(RED "Invalid choice entered.\n" RESET);
            continue;   }

        printf("\nSelect FROM unit: ");
        scanf("%d", &from);
        if(from==1)
        to=2;
        else if(from==2)
        to=1;
        if (from < 1 || from > 2 || to < 1 || to > 2)
        {   printf(RED "Invalid unit selection.\n" RESET);
            continue;   }

        printf(BLUE"Enter currency value: "RESET);
        scanf("%f", &value);

       if (choice == 1)
        {   from = (from == 1) ? INR : USD;
            to   = (to   == 1) ? INR : USD; }
        else if (choice == 2)
        {   from = (from == 1) ? INR : EUR;
            to   = (to   == 1) ? INR : EUR; }
        else if (choice == 3)
        {   from = (from == 1) ? INR : GBP;
            to   = (to   == 1) ? INR : GBP; }
        else
        {   from = (from == 1) ? INR : JPY;
            to   = (to   == 1) ? INR : JPY; }

        result = convertCUR(value, from, to);

        addHistory(value, result, unitCharC(from), unitCharC(to)); //FUNCTION CALL
        struct History *h = &history[hcount - 1];
        printf(GREEN "Result: %.2f %s = %.2f %s\n" RESET,
               h->input, h->from,
               h->output, h->to);   } //while closing
    return 0;   }

void addHistory(float in, float out,const char* from,const char* to)
{   if (hcount >= 50)
        return;
    history[hcount++] = (struct History){ in, out, from, to };      }

void showHistory(void)
{int i;
    if (hcount == 0)
    {   printf(RED "\nNo history available.\n" RESET);
        return;     }

    printf(HOT_PINK "\n--- Conversion History ---\n" RESET);
    for (i = 0; i < hcount; i++)
    {   printf("%d) %.2f %s = %.2f %s\n",
               i + 1,
               history[i].input, history[i].from,
               history[i].output, history[i].to);
               Sleep(1000);
               }
}

#define MAX_HISTORY 100

struct History1 {
    char category[20];
    float input;
    float output;
    char fromUnit[10];
    char toUnit[10];
};

struct History1 history1[MAX_HISTORY];
int histCount = 0;

void addHistory1(char category[], float in, float out, char from[], char to[]);
void showHistory1();

void lengthMenu();
void massMenu();
void timeMenu();
void speedMenu();
void energyMenu();

void unit() {
    int choice;
      printf(CYAN "\n=====================================\n        ");
        char temp[25]= {"UNIT CONVERTER SYSTEM"};
    for(i=0; i<25; i++)
    {
        printf("%c",temp[i]);
        Sleep(40);
    }

        printf("\n=====================================\n" RESET);

    while (1) {
        printf(YELLOW"\n Menu \n"RESET);
        printf("1. Length\n");
        printf("2. Mass\n");
        printf("3. Time\n");
        printf("4. Speed\n");
        printf("5. Energy / Power\n");
        printf("6. View History\n");
        printf("7. Exit\n");

        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: lengthMenu(); break;
            case 2: massMenu(); break;
            case 3: timeMenu(); break;
            case 4: speedMenu(); break;
            case 5: energyMenu(); break;
            case 6: showHistory1(); break;
            case 7:
                printf(GREEN "\nProgram exited successfully.\n" RESET);
                return ;
            default:
                printf(RED "Invalid option entered.\n" RESET);
        }
    }
}

void addHistory1(char category[], float in, float out, char from[], char to[]) {
    if (histCount >= MAX_HISTORY)
        return;

    strcpy(history1[histCount].category, category);
    history1[histCount].input = in;
    history1[histCount].output = out;
    strcpy(history1[histCount].fromUnit, from);
    strcpy(history1[histCount].toUnit, to);
    histCount++;
}

void showHistory1() {
    int i;
    char lastCategory[20] = "";

    if (histCount == 0) {
        printf(RED "\nNo history available.\n" RESET);
        return;
    }

    printf(HOT_PINK "\n===== CONVERSION HISTORY =====\n" RESET);

    for (i = 0; i < histCount; i++) {

        /* print category heading only once */
        if (strcmp(lastCategory, history1[i].category) != 0) {
            printf("\n%s\n", history1[i].category);
            strcpy(lastCategory, history1[i].category);
        }

        /* required format */
        printf("%.2f %s = %.2f %s\n",
               history1[i].input,
               history1[i].fromUnit,
               history1[i].output,
               history1[i].toUnit);
    }
}

void lengthMenu() {
    int from, to;
    float val, m, res;
    char *units[] = {"cm", "m", "km", "mi", "in", "ft"};

    printf("\nLength Units:\n");
    printf("1. Centimeter (cm)\n2. Meter (m)\n3. Kilometer (km)\n");
    printf("4. Mile (mi)\n5. Inch (in)\n6. Foot (ft)\n");

    printf(YELLOW "Enter FROM unit: " RESET);
    scanf("%d", &from);
    printf(YELLOW "Enter TO unit: " RESET);
    scanf("%d", &to);

    if (from < 1 || from > 6 || to < 1 || to > 6) {
        printf(RED "Invalid option entered.\n" RESET);
        return;
    }

    printf(GREEN "Enter value: " RESET);
    scanf("%f", &val);

    switch (from) {
        case 1: m = val / 100; break;
        case 2: m = val; break;
        case 3: m = val * 1000; break;
        case 4: m = val * 1609.34; break;
        case 5: m = val * 0.0254; break;
        case 6: m = val * 0.3048; break;
    }

    switch (to) {
        case 1: res = m * 100; break;
        case 2: res = m; break;
        case 3: res = m / 1000; break;
        case 4: res = m / 1609.34; break;
        case 5: res = m / 0.0254; break;
        case 6: res = m / 0.3048; break;
    }

    printf(CYAN "Result: %.2f %s\n" RESET, res, units[to - 1]);
    addHistory1("Length", val, res, units[from - 1], units[to - 1]);
}

void massMenu() {
    int from, to;
    float val, kg, res;
    char *units[] = {"kg", "g", "mg", "lb", "oz"};

    printf("\nMass Units:\n");
    printf("1. Kilogram (kg)\n");
    printf("2. Gram (g)\n");
    printf("3. Milligram (mg)\n");
    printf("4. Pound (lb)\n");
    printf("5. Ounce (oz)\n");

    printf(YELLOW "Enter FROM unit: " RESET);
    scanf("%d", &from);
    printf(YELLOW "Enter TO unit: " RESET);
    scanf("%d", &to);

    if (from < 1 || from > 5 || to < 1 || to > 5) {
        printf(RED "Invalid option entered.\n" RESET);
        return;
    }

    printf(GREEN "Enter value: " RESET);
    scanf("%f", &val);

    switch (from) {
        case 1: kg = val; break;
        case 2: kg = val / 1000; break;
        case 3: kg = val / 1e6; break;
        case 4: kg = val * 0.453592; break;
        case 5: kg = val * 0.0283495; break;
    }

    switch (to) {
        case 1: res = kg; break;
        case 2: res = kg * 1000; break;
        case 3: res = kg * 1e6; break;
        case 4: res = kg / 0.453592; break;
        case 5: res = kg / 0.0283495; break;
    }

    printf(CYAN "Result: %.2f %s\n" RESET, res, units[to - 1]);
    addHistory1("Mass", val, res, units[from - 1], units[to - 1]);
}
void timeMenu() {
    int from, to;
    float val, sec, res;
    char *units[] = {"s", "min", "h", "day"};

    printf("\nTime Units:\n");
    printf("1. Second (s)\n");
    printf("2. Minute (min)\n");
    printf("3. Hour (h)\n");
    printf("4. Day (day)\n");

    printf(YELLOW "Enter FROM unit: " RESET);
    scanf("%d", &from);
    printf(YELLOW "Enter TO unit: " RESET);
    scanf("%d", &to);

    if (from < 1 || from > 4 || to < 1 || to > 4) {
        printf(RED "Invalid option entered.\n" RESET);
        return;
    }

    printf(GREEN "Enter value: " RESET);
    scanf("%f", &val);

    switch (from) {
        case 1: sec = val; break;
        case 2: sec = val * 60; break;
        case 3: sec = val * 3600; break;
        case 4: sec = val * 86400; break;
    }

    switch (to) {
        case 1: res = sec; break;
        case 2: res = sec / 60; break;
        case 3: res = sec / 3600; break;
        case 4: res = sec / 86400; break;
    }

    printf(CYAN "Result: %.2f %s\n" RESET, res, units[to - 1]);
    addHistory1("Time", val, res, units[from - 1], units[to - 1]);
}

void speedMenu() {
    int from, to;
    float val, mps, res;
    char *units[] = {"m/s", "km/h", "mph"};

    printf("\nSpeed Units:\n");
    printf("1. Meter per second (m/s)\n");
    printf("2. Kilometer per hour (km/h)\n");
    printf("3. Mile per hour (mph)\n");

    printf(YELLOW "Enter FROM unit: " RESET);
    scanf("%d", &from);
    printf(YELLOW "Enter TO unit: " RESET);
    scanf("%d", &to);

    if (from < 1 || from > 3 || to < 1 || to > 3) {
        printf(RED "Invalid option entered.\n" RESET);
        return;
    }

    printf(GREEN "Enter value: " RESET);
    scanf("%f", &val);

    switch (from) {
        case 1: mps = val; break;
        case 2: mps = val / 3.6; break;
        case 3: mps = val * 0.44704; break;
    }

    switch (to) {
        case 1: res = mps; break;
        case 2: res = mps * 3.6; break;
        case 3: res = mps / 0.44704; break;
    }

    printf(CYAN "Result: %.2f %s\n" RESET, res, units[to - 1]);
    addHistory1("Speed", val, res, units[from - 1], units[to - 1]);
}

void energyMenu() {
    int from, to;
    float val, joule, res;
    char *units[] = {"J", "kJ", "eV", "W", "kW", "hp"};

    printf("\nEnergy / Power Units:\n");
    printf("1. Joule (J)\n2. Kilojoule (kJ)\n3. Electron volt (eV)\n");
    printf("4. Watt (W)\n5. Kilowatt (kW)\n6. Horsepower (hp)\n");

    printf(YELLOW "Enter FROM unit: " RESET);
    scanf("%d", &from);
    printf(YELLOW "Enter TO unit: " RESET);
    scanf("%d", &to);

    if (from < 1 || from > 6 || to < 1 || to > 6) {
        printf(RED "Invalid option entered.\n" RESET);
        return;
    }

    printf(GREEN "Enter value: " RESET);
    scanf("%f", &val);

    if (from <= 3 && to <= 3) {
        switch (from) {
            case 1: joule = val; break;
            case 2: joule = val * 1000; break;
            case 3: joule = val * 1.602e-19; break;
        }

        switch (to) {
            case 1: res = joule; break;
            case 2: res = joule / 1000; break;
            case 3: res = joule / 1.602e-19; break;
        }
    } else {
        switch (from) {
            case 4: joule = val; break;
            case 5: joule = val * 1000; break;
            case 6: joule = val * 745.7; break;
        }
        res = joule;
    }

    printf(CYAN "Result: %.2f %s\n" RESET, res, units[to - 1]);
    addHistory1("Energy / Power", val, res, units[from - 1], units[to - 1]);
}
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

#define LOG10 5
#define LN 6
#define FACT 7

#define POWER 8
#define SQRT 9

#define SIN 10
#define COS 11
#define TAN 12


struct History2 {
    char expression[100];
    float result;
};

struct History2 history2[50];
int ccount = 0;
float calculate(int choice, float a, float b);
void showHistory2(void);
int factorial(int n);
void saveHistory(const char *expr, float result)
{
    if (ccount >= 50)
        return;

    strcpy(history2[ccount].expression, expr);
    history2[ccount].result = result;
    ccount++;
}

void basic(){
float result, num;
    char op;
     char expr[100];
    char temp[20];

    printf(CYAN "\n--- Everyday Maths Calculator ---\n" RESET);
    printf("Instructions:\n");
    printf("Enter operators followed by numbers\n");
    printf("Supported operators: +  -  *  /\n");
    printf("Press 'q' to quit and see final result\n\n");

    printf("Enter first number: ");
    scanf("%f", &result);
sprintf(expr, "%.2f", result);
    while (1)
    {
        scanf(" %c", &op);

        if (op == 'q' || op == 'Q')
            break;

        scanf("%f", &num);
        sprintf(temp, " %c %.2f", op, num);
        strcat(expr, temp);

        if (op == '+')
            result += num;
        else if (op == '-')
            result -= num;
        else if (op == '*')
            result *= num;
        else if (op == '/')
        {
            if (num == 0)
                continue;
            result /= num;
        }
        else
        {printf(RED "Invalid operator. Try again .\n"RESET);
        continue;}

        printf(GREEN "%.2f\n" RESET, result);
saveHistory(expr, result);

    }

    printf(HOT_PINK "\nFinal Result: "RESET " %.2f\n", result);

}
void scientificCalculator()
{
    int choice;
    float a, b, result;
    printf(CYAN "\n=====================================\n        ");
        char temp[25]= {"SCIENTIFIC CALCULATOR"};
    for(i=0; i<25; i++)
    {
        printf("%c",temp[i]);
        Sleep(40);
    }

        printf("\n=====================================\n" RESET);


    while (1)
    {
        printf(YELLOW "\nMenu\n" RESET);
        printf("1. Everyday Maths\n");
        printf("2. Logs & Factorial\n");
        printf("3. Powers & Roots\n");
        printf("4. Trigonometry\n");
        printf("5. View History\n");
        printf("6. Exit\n");

        printf(YELLOW "Enter choice: " RESET);
        scanf("%d", &choice);

        if (choice == 6){
        printf(GREEN"History saved successfully.\n"RESET);
        break;
        }

        if (choice == 5)
        {
            showHistory2();

            continue;
        }
char exp[50];
        switch (choice)
        {
        case 1:
        basic();
        break;

        case 2:
            printf("1. log10(x)\n2. ln(x)\n3. Factorial\n");
            printf(YELLOW"Select operation: "RESET);
            scanf("%d", &choice);

            if (choice == 3)
            {
                int n;
                printf(BLUE "Enter number: " RESET);
                scanf("%d", &n);
                if(n<0)
                {printf(RED"Negative number not accepted.\n"RESET);
                continue;
                }result = factorial(n);
sprintf(exp, "%d!", n);
saveHistory(exp, result);

                printf(GREEN "Result = %.2f\n"RESET, result);
                continue;
            }

            printf(BLUE"Enter number: "RESET);
            scanf("%f", &a);
            result = calculate(choice + 4, a, 0);
            sprintf(exp, choice==1 ? "log10(%.2f)" : "ln(%.2f)", a);
            saveHistory(exp, result);
            printf(GREEN "Result: %.2f\n"RESET,result);
            break;

        case 3:
            printf("1. Power\n2. Square Root\n");
            printf(YELLOW"Select operation: "RESET);
            scanf("%d", &choice);

            if (choice == 1)
            {
                printf(BLUE"Enter base and power: "RESET);
                scanf("%f %f", &a, &b);
                result = pow(a, b);
sprintf(exp, "%.2f ^ %.2f", a, b);
saveHistory(exp, result);
}
            else
            {
                printf(BLUE"Enter number: "RESET);
                scanf("%f", &a);
                result = sqrt(a);
sprintf(exp, "%.2f ^ 0.5", a);
saveHistory(exp, result);
            }
            printf(GREEN"Result = %.2f\n"RESET, result);
            continue;

        case 4:
            printf("1. sin(x)\n2. cos(x)\n3. tan(x)\n");
            printf(YELLOW "Select operation: "RESET);
            scanf("%d", &choice);
            printf(BLUE"Enter angle in degrees: "RESET);
            scanf("%f", &a);
            a = a * (3.14159 / 180);
            result = calculate(choice + 9, a, 0);
if (choice==1)sprintf(exp, "sin(%.2f)", a);
if (choice==2)sprintf(exp, "cos(%.2f)", a);
if (choice==3)sprintf(exp, "tan(%.2f)", a);
saveHistory(exp, result);

printf(GREEN "Result: %.2f\n"RESET,result);

            break;

        default:
            printf(RED "Invalid choice\n" RESET);
           continue;
          Sleep(1500);
          clear();

        }
    }
}
float calculate(int choice, float a, float b)
{
    switch (choice)
    {
    case ADD: return a + b;
    case SUB: return a - b;
    case MUL: return a * b;
    case DIV: return b != 0 ? a / b : 0;

    case LOG10: return log10(a);
    case LN: return log(a);

    case SIN: return sin(a);
    case COS: return cos(a);
    case TAN: return tan(a);

    default: return 0;
    }
}
int factorial(int n)
{
    int f = 1;
    int i;
    for (i = 1; i <= n; i++)
        f *= i;
    return f;
}
void showHistory2()
{
    int i;

    if (ccount == 0)
    {
        printf(RED "\nNo history available\n" RESET);
        return;
    }

    printf(HOT_PINK "\n--- Calculation History ---\n" RESET);
    for (i = 0; i < ccount; i++)
    {
        printf("%d) %s = %.2f\n",
               i + 1,
               history2[i].expression,
               history2[i].result);
        Sleep(500);
    }
}
void end()
{
    clear();
    setColor(10);
    fileopen("thankyou.txt",43,9);
    Sleep(100);
    setColor(11);
    fileopen("face.txt",45,25);
    gotoxy(55,26);
    char c[50]= {"I hope you had a great time, come back soon"};
    for(i=0; i<sizeof(c); i++)
    {
        printf("%c",c[i]);
        Sleep(100);
    }
    gotoxy(65,27);
    char b[30]= {"I'll be waiting!"};
    for(i=0; i<sizeof(b); i++)
    {
        printf("%c",b[i]);
        Sleep(100);
    }
    setColor(7);
    Sleep(1000);
    clear();
}
void page1()
{
    setColor(8);
    char wel[100]= {"WELCOME"};
    for(i=0; i<70; i++)
    {
        printf("*");
    }
    setColor(10);
    for(i=0; i<10; i++)
    {
        printf("%c",wel[i]);
        Sleep(40);
    }
    setColor(8);
    for(i=0; i<70; i++)
    {
        printf("*");
    }
    Sleep(2000);
    setColor(14);
    gotoxy(18,3);
    printf("CLAC - Console Logic And Calculation ");
    setColor(6);
    printf("is a C-based console program for performing common calculations in one place.");
    gotoxy(30,4);
    printf("It focuses on a clear text interface so anyone can use it comfortably from the console.\n\n");
    Sleep(10000);
    setColor(11);
    gotoxy(35,6);
    printf("#  Hope you enjoy using CLAC as much as we enjoyed while creating it.  #\n\n");
    Sleep(4000);
    setColor(7);
}
void intro()
{
    hidecursor();
    setColor(12);
    fileopen("text.txt",63,9);
    Sleep(100);
    gotoxy(63,17);
    printf("Console Logic And Calculator");
    setColor(11);
    gotoxy(62,19);
    printf("Developed by: Adrika And Purva");
    gotoxy(71,38);
    printf("Version 1.0");
    Sleep(9000);
    clear();
    setColor(10);
    gotoxy(68,9);
    printf("__________________");
    gotoxy(67,10);
    printf("|                  |");
    gotoxy(67,11);
    printf("|                  |");
    gotoxy(68,11);
    printf("__________________");
    showcursor();
    gotoxy(68,13);
    char c[22]= {"Loading .........."};
    for(i=0; i<20; i++)
    {
        printf("%c",c[i]);
        Sleep(100);
    }
    hidecursor();
    Sleep(600);
    clear();
}
void menu()
{
    n=0;
    printf("Features:\n");
    printf("  1. Temperature conversion\n");
    printf("  2. Unit conversion\n");
    printf("  3. Scientific calculator\n");
    printf("  4. Currency conversion\n\n");
    printf("Type an option to begin.\n");
    scanf("%d",&n);
    clear();
    switch(n)
    {
    case 1:
        temp();
        break;
    case 2:
        unit();
        break;
    case 3:
        scientificCalculator();
        break;
    case 4:
        currency();
        break;
    }
    clear();
}
int main()
{
   intro();
    page1();
    menu();
    Sleep(2000);
    int c;
    while(1)
    {
    setColor(11);
    printf("\n=== BACK TO MAIN MENU ===\n");
    setColor(14);
    printf("Wish to continue? (1=Yes / 0=No): ");
    setColor(7);
    scanf("%d",&c);
    if(c==1)
    {
    menu();
    }
    else
    break;
    }
    end();
}
