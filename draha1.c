#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE  "cisla.txt"
#define OUTPUT_FILE "prevody.txt"

float get_mps(int meters, int seconds) {
    if (seconds == 0) return 0;
    return (float)meters / seconds;
}

float get_kmh(int meters, int seconds) {
    if (seconds == 0) return 0;
    float mps = (float)meters / seconds;
    return mps * 3.6f;
}

int main() {
    FILE *input = fopen(INPUT_FILE, "r");
    FILE *output = fopen(OUTPUT_FILE, "w");

    if (input == NULL || output == NULL) {
        return 1;
    }

    int meters, seconds;
    int total_count = 0;
    int written_count = 0;
    double sum_distance = 0;

    printf("%-10s %-20s %-15s %-10s\n", "poradi", "draha", "cas", "rychlost");

    while (fscanf(input, "%d %d", &meters, &seconds) == 2) {
        total_count++;
        sum_distance += meters;
        float speed_ms = get_mps(meters, seconds);

        printf("%3d. %6d metru %5d sekund %7.2f m/s\n", 
               total_count, meters, seconds, speed_ms);

        if (speed_ms > 10.0f) {
            written_count++;
            float speed_kmh = get_kmh(meters, seconds);
            
            int km = meters / 1000;
            int rem_meters = meters % 1000;
            int minutes = seconds / 60;
            int rem_seconds = seconds % 60;

            if (written_count == 1) {
                fprintf(output, "%-8s %-20s %-20s %-10s\n", "poradi", "draha", "cas", "rychlost");
            }

            fprintf(output, "%3d. %3d km %3d metru %3d minut %2d sekund %7.2f km/h\n",
                    written_count, km, rem_meters, minutes, rem_seconds, speed_kmh);
        }
    }

    float avg_dist = (total_count > 0) ? (float)(sum_distance / total_count) : 0;

    printf("\nPrumerna delka drahy je %.2f metru.\n", avg_dist);
    printf("Ze souboru %s bylo precteno %d dvojic cisel.\n", INPUT_FILE, total_count);
    printf("Soubor %s byl vytvoren.\n", OUTPUT_FILE);

    fprintf(output, "\nDo souboru %s bylo zapsano %d dvojic cisel.\n", OUTPUT_FILE, written_count);

    fclose(input);
    fclose(output);

    return 0;
}
