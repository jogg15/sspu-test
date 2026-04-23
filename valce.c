#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE  "cisla.txt"
#define OUTPUT_FILE "hladiny.txt"
#define PI 3.141592653589793

double cylinderVolume(int radius, int height)
{
    return (PI * radius * radius * height) / 1000.0;
}

double waterLevel(int radius, int water)
{
    return (water * 1000.0) / (PI * radius * radius);
}

int main()
{
    FILE *input;
    FILE *output;

    int radius, height, water;
    int countScreen = 0;
    int countFile = 0;

    input = fopen(INPUT_FILE, "r");
    if (input == NULL)
    {
        printf("Cannot open file %s\n", INPUT_FILE);
        return 1;
    }

    output = fopen(OUTPUT_FILE, "w");
    if (output == NULL)
    {
        printf("Cannot open file %s\n", OUTPUT_FILE);
        fclose(input);
        return 1;
    }

    printf("CYLINDERS\n\n");
    printf("No. Radius Height Volume Water\n");
    printf("----------------------------------\n");

    fprintf(output, "VALID CYLINDERS\n\n");
    fprintf(output, "No. Radius Height Volume Water Level\n");
    fprintf(output, "------------------------------------------\n");

    while (fscanf(input, "%d %d %d", &radius, &height, &water) == 3)
    {
        if (radius <= 0 || height <= 0 || water < 0)
        {
            printf("Invalid values: %d %d %d\n", radius, height, water);
            continue;
        }

        countScreen++;

        double volume = cylinderVolume(radius, height);

        printf("%2d. %5d %6d %7.2f %5d\n",
               countScreen, radius, height, volume, water);

        if (volume >= water)
        {
            countFile++;

            double level = waterLevel(radius, water);

            fprintf(output, "%2d. %5d %6d %7.2f %5d %7.2f\n",
                    countFile, radius, height, volume, water, level);
        }
    }

    fclose(input);
    fclose(output);

    printf("\nFile %s was created.\n", OUTPUT_FILE);

    return 0;
}