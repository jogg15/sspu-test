#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE  "casy.txt"
#define OUTPUT_FILE "odpoledne.txt"

typedef struct
{
    int hours;
    int minutes;
    int seconds;
} Time;

int timeToSeconds(Time t)
{
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

int convertTo12Hour(int hour)
{
    if (hour == 0)
        return 12;
    if (hour > 12)
        return hour - 12;

    return hour;
}

int isValidTime(Time t)
{
    return t.hours >= 0 && t.hours <= 23 &&
           t.minutes >= 0 && t.minutes <= 59 &&
           t.seconds >= 0 && t.seconds <= 59;
}

void printHeader(FILE *file)
{
    fprintf(file, " No. | 24-hour  | 12-hour   | Seconds |\n");
    fprintf(file, "---------------------------------------\n");
}

void printRow(FILE *file, int number, Time t, int totalSeconds, int hour12, char period[])
{
    fprintf(file,
            "%3d. | %02d:%02d:%02d | %02d:%02d:%02d %s | %7d |\n",
            number,
            t.hours, t.minutes, t.seconds,
            hour12, t.minutes, t.seconds, period,
            totalSeconds);
}

int main()
{
    FILE *input;
    FILE *output;

    Time t;

    int totalRead = 0;
    int countAll = 0;
    int countPM = 0;

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

    printf("TIME DATA\n\n");
    printHeader(stdout);

    fprintf(output, "AFTERNOON TIMES\n\n");
    printHeader(output);

    while (fscanf(input, "%d %d %d", &t.hours, &t.minutes, &t.seconds) == 3)
    {
        if (!isValidTime(t))
        {
            printf("Invalid time: %02d:%02d:%02d\n",
                   t.hours, t.minutes, t.seconds);
            continue;
        }

        totalRead++;
        countAll++;

        int totalSeconds = timeToSeconds(t);
        int hour12 = convertTo12Hour(t.hours);

        char period[3];

        if (t.hours >= 12)
            sprintf(period, "PM");
        else
            sprintf(period, "AM");

        printRow(stdout, countAll, t, totalSeconds, hour12, period);

        if (t.hours >= 12)
        {
            countPM++;
            printRow(output, countPM, t, totalSeconds, hour12, period);
        }
    }

    printf("\nRead from file: %d records\n", totalRead);
    printf("File %s was created.\n", OUTPUT_FILE);

    fprintf(output, "\nWritten records: %d\n", countPM);

    fclose(input);
    fclose(output);

    return 0;
}