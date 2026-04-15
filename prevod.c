#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE  "casy.txt"
#define OUTPUT_FILE "odpoledne.txt"

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

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

int timeToSeconds(Time t) {
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

int convertTo12Hour(int hour) {
    if (hour == 0)  return 12;
    if (hour > 12)  return hour - 12;
    return hour;
}

int isValidTime(Time t) {
    return t.hours   >= 0 && t.hours   <= 23 &&
           t.minutes >= 0 && t.minutes <= 59 &&
           t.seconds >= 0 && t.seconds <= 59;
}

void printRow(FILE *file, int num, Time t, int sec, int hour12, const char *period) {
    fprintf(file, "%7d. | %02d:%02d:%02d | %02d:%02d:%02d %-2s | %10d |\n",
            num,
            t.hours, t.minutes, t.seconds,
            hour12, t.minutes, t.seconds, period,
            sec);
}

void printHeader(FILE *file) {
    fprintf(file, " poradi casu | evropsky cas | anglicky cas    | sekundy od pulnoci |\n");
    fprintf(file, "-------------|--------------|-----------------|--------------------|\n");
}

int main(void) {
    FILE *input  = openFile(INPUT_FILE,  "r");
    FILE *output = openFile(OUTPUT_FILE, "w");

    Time t;
    int totalRead = 0;
    int orderAll  = 0;
    int orderPM   = 0;

    printf("          U D A J E   Z E   S O U B O R U\n\n");
    printHeader(stdout);

    fprintf(output, "                O D P O L E D N E\n\n");
    printHeader(output);

    while (fscanf(input, "%d %d %d", &t.hours, &t.minutes, &t.seconds) == 3) {
        if (!isValidTime(t)) {
            printf("Neplatny cas: %02d:%02d:%02d\n", t.hours, t.minutes, t.seconds);
            continue;
        }

        totalRead++;
        orderAll++;

        int seconds       = timeToSeconds(t);
        int hour12        = convertTo12Hour(t.hours);
        const char *period = (t.hours >= 12) ? "PM" : "AM";

        printRow(stdout, orderAll, t, seconds, hour12, period);

        if (t.hours >= 12) {
            orderPM++;
            printRow(output, orderPM, t, seconds, hour12, period);
        }
    }

    printf("\nZe souboru %s bylo precteno %d udaju o case.\n", INPUT_FILE, totalRead);
    printf("Byl vytvoren soubor %s.\n", OUTPUT_FILE);

    fprintf(output, "\nDo souboru %s bylo zapsano %d udaju o case.\n", OUTPUT_FILE, orderPM);

    closeFile(input);
    closeFile(output);

    return 0;
}
