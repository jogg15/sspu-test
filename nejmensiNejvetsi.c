#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "cisla.txt"
#define OUTPUT_FILE "vystup.txt"

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;

    return abs(a * b) / gcd(a, b);
}

void printHeader()
{
    printf("No.   A     B    LCM   GCD\n");
    printf("---------------------------\n");
}

void printFileHeader(FILE *file)
{
    fprintf(file, "No.   A     B    LCM   GCD\n");
    fprintf(file, "---------------------------\n");
}

int main()
{
    FILE *input, *output;

    int a, b;
    int count = 0, saved = 0;
    long sum = 0, sumSaved = 0;

    input = fopen(INPUT_FILE, "r");
    output = fopen(OUTPUT_FILE, "w");

    if (input == NULL || output == NULL)
    {
        printf("File error\n");
        return 1;
    }

    printHeader();
    printFileHeader(output);

    while (fscanf(input, "%d %d", &a, &b) == 2)
    {
        count++;

        int d = gcd(a, b);
        int n = lcm(a, b);

        printf("%2d. %4d %4d %5d %5d\n", count, a, b, n, d);

        sum += a;

        if (d > 1)
        {
            saved++;

            fprintf(output, "%2d. %4d %4d %5d %5d\n",
                    saved, a, b, n, d);

            sumSaved += a;
        }
    }

    printf("---------------------------\n");
    printf("Average: %.2f\n", (count > 0) ? (double)sum / count : 0);
    printf("Output file created: %s\n", OUTPUT_FILE);

    fprintf(output, "---------------------------\n");
    fprintf(output, "Average: %.2f\n",
            (saved > 0) ? (double)sumSaved / saved : 0);

    fclose(input);
    fclose(output);

    return 0;
}