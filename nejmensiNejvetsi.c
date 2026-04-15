#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE  "cisla.txt"
#define OUTPUT_FILE "vystup.txt"

FILE *openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Nelze otevrit '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void closeFile(FILE *file) {
    if (fclose(file) != 0) {
        printf("Nelze zavrit soubor\n");
        exit(EXIT_FAILURE);
    }
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    int d = gcd(a, b);
    return (d == 0) ? 0 : abs(a) / d * abs(b);
}

void printScreenHeader(void) {
    printf("Vypis cisel ze souboru %s\n", INPUT_FILE);
    printf("%-8s %-8s %-8s %-8s %-8s\n", "poradi", "cislo1", "cislo2", "nsn", "nsd");
    printf("----------------------------------------\n");
}

void printFileHeader(FILE *f) {
    fprintf(f, "Vypis delitelnych cisel ze souboru %s\n", INPUT_FILE);
    fprintf(f, "----------------------------------------\n");
    fprintf(f, "%-8s %-8s %-8s %-8s %-8s\n", "poradi", "cislo1", "cislo2", "nsn", "nsd");
    fprintf(f, "----------------------------------------\n");
}

int main(void) {
    FILE *input  = openFile(INPUT_FILE,  "r");
    FILE *output = openFile(OUTPUT_FILE, "w");

    int a, b;
    int order       = 0;
    int orderFile   = 0;
    long sumAll     = 0;
    long sumFile    = 0;

    printScreenHeader();
    printFileHeader(output);

    while (fscanf(input, "%d %d", &a, &b) == 2) {
        order++;
        int n = lcm(a, b);
        int d = gcd(a, b);

        printf("%5d. %6d %6d %8d %5d\n", order, a, b, n, d);
        sumAll += a;

        if (d > 1) {
            orderFile++;
            fprintf(output, "%5d. %6d %6d %8d %5d\n", orderFile, a, b, n, d);
            sumFile += a;
        }
    }

    printf("----------------------------------------\n");
    printf("Prumer cisel v prvnim sloupci je %.2f.\n",
           order > 0 ? (double)sumAll / order : 0.0);
    printf("Soubor %s obsahuje %d dvojic cisel.\n", INPUT_FILE, order);
    printf("Byl vytvoren soubor %s.\n", OUTPUT_FILE);

    fprintf(output, "----------------------------------------\n");
    fprintf(output, "Prumer cisel v prvnim sloupci je %.2f.\n",
            orderFile > 0 ? (double)sumFile / orderFile : 0.0);
    fprintf(output, "Soubor %s obsahuje %d dvojic cisel.\n", OUTPUT_FILE, orderFile);

    closeFile(input);
    closeFile(output);

    return 0;
}
