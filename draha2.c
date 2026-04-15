#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE  "cisla.txt"
#define OUTPUT_FILE "prevody.txt"

float calculate_kmh(int km, int m, int min, int sec) {
    double total_hours = (min / 60.0) + (sec / 3600.0);
    double total_km = km + (m / 1000.0);
    return (float)(total_km / total_hours);
}

float calculate_ms(int km, int m, int min, int sec) {
    int total_meters = (km * 1000) + m;
    int total_seconds = (min * 60) + sec;
    return (float)total_meters / total_seconds;
}

int main() {
    FILE *in = fopen(INPUT_FILE, "r");
    FILE *out = fopen(OUTPUT_FILE, "w");

    if (in == NULL || out == NULL) {
        return 1;
    }

    int km, m, min, sec;
    int count = 0;
    int saved_count = 0;
    double total_distance_sum = 0;

    printf("%-7s %-15s %-20s %-10s\n", "poradi", "draha", "cas", "rychlost");

    while (fscanf(in, "%d %d %d %d", &km, &m, &min, &sec) == 4) {
        count++;
        float kmh = calculate_kmh(km, m, min, sec);
        float ms = calculate_ms(km, m, min, sec);
        int total_m = (km * 1000) + m;
        int total_s = (min * 60) + sec;

        total_distance_sum += total_m;

        printf("%2d. %4d km %3d m %3d minut %2d sekund %7.2f km/h\n", 
               count, km, m, min, sec, kmh);

        if (kmh > 20.0) {
            saved_count++;
            if (saved_count == 1) {
                fprintf(out, "%-7s %-15s %-15s %-10s\n", "poradi", "draha", "cas", "rychlost");
            }
            fprintf(out, "%5d. %7d metru %5d sekund %7.2f m/s\n", 
                    saved_count, total_m, total_s, ms);
        }
    }

    float avg_distance = (count > 0) ? (float)(total_distance_sum / count) : 0;

    printf("\nZe souboru %s bylo precteno %d ctveric cisel.\n", INPUT_FILE, count);
    printf("Soubor %s byl vytvoren.\n", OUTPUT_FILE);

    fprintf(out, "\nPrumerna delka drahy je %.2f metru.\n", avg_distance);
    fprintf(out, "\nDo souboru %s bylo zapsano %d polozek.\n", OUTPUT_FILE, saved_count);

    fclose(in);
    fclose(out);

    return 0;
}
