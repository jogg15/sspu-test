#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE  "cisla.txt"
#define OUTPUT_FILE "hladiny.txt"
#define PI 3.14159265358979323846

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

double cylinderVolume(int r, int h) {
    return (PI * r * r * h) / 1000.0;
}

double waterLevel(int r, int water) {
    return (water * 1000.0) / (PI * r * r);
}

void printScreenHeader(void) {
    printf("V A L C E\n\n");
    printf("  %-10s %-10s %-20s %-15s\n", "polomer", "vyska", "objem valce", "mnozstvi vody");
    printf("  %-10s %-10s %-20s %-15s\n", "(cm)", "(cm)", "(dm krychlove)", "(litry)");
    printf("  ------------------------------------------------------------\n");
}

void printFileHeader(FILE *f) {
    fprintf(f, "V A L C E   S   V Y H O V U J I C I M   O B J E M E M\n\n");
    fprintf(f, "  %-10s %-10s %-20s %-15s %-15s\n",
            "polomer", "vyska", "objem valce", "mnozstvi vody", "vyska hladiny");
    fprintf(f, "  %-10s %-10s %-20s %-15s %-15s\n",
            "(cm)", "(cm)", "(dm krychlove)", "(litry)", "(cm)");
    fprintf(f, "  ------------------------------------------------------------------------\n");
}

int main(void) {
    FILE *input  = openFile(INPUT_FILE,  "r");
    FILE *output = openFile(OUTPUT_FILE, "w");

    int r, h, water;
    int order     = 0;
    int orderFile = 0;

    printScreenHeader();
    printFileHeader(output);

    while (fscanf(input, "%d %d %d", &r, &h, &water) == 3) {
        if (r <= 0 || h <= 0 || water < 0) {
            printf("Neplatne hodnoty: %d %d %d\n", r, h, water);
            continue;
        }

        order++;
        double vol = cylinderVolume(r, h);

        printf("%3d. %4d cm   %4d cm   %8.2f dm   %6d l\n", order, r, h, vol, water);

        if (vol >= water) {
            orderFile++;
            double level = waterLevel(r, water);
            fprintf(output, "%3d. %4d cm   %4d cm   %8.2f dm   %6d l   %8.2f cm\n",
                    orderFile, r, h, vol, water, level);
        }
    }

    printf("  ------------------------------------------------------------\n");
    fprintf(output, "  ------------------------------------------------------------------------\n");

    printf("\nSoubor %s byl vytvoren.\n", OUTPUT_FILE);

    closeFile(input);
    closeFile(output);

    return 0;
}
