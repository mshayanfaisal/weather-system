#include <stdio.h>
#include <stdlib.h> //using this library for using memory allocations functions

//Defining the structure as provided in the question
struct WeatherRecord {
    int day;
    float temperature;
    float humidity;
    float precipitation;
};

//Defining functions
void inputWeatherData(struct WeatherRecord **records, int *numRecords); //using double asterik to modify the original pointer
void calculateAverageValues(struct WeatherRecord *records, int numRecords);
void displayWeatherStatistics(struct WeatherRecord *records, int numRecords);
void saveWeatherRecords(struct WeatherRecord *records, int numRecords);
void loadWeatherRecords(struct WeatherRecord **records, int *numRecords);

int main(void) {

    struct WeatherRecord *weather = NULL; //initialised to NULL because pointer is not pointing to anything initially.

    int numRecords = 0;
    int choice;

    printf("Welcome to SZABIST Weather forecast system.\n");

    do {
        printf("Enter your choice for the following.\n");
        printf("1. Input daily weather data.\n2. Calculate Average weather values.\n3. Display weather Statistics.\n4. Exit the program.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //taking choice from the user
        switch (choice) {
            case 1:
                inputWeatherData(&weather, &numRecords); // address used to modify the original variable.
                break;
            case 2:
                calculateAverageValues(weather, numRecords);
                break;
            case 3:
                displayWeatherStatistics(weather, numRecords);
                break;
            case 4:
                saveWeatherRecords(weather, numRecords);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Enter a valid choice.\n");
        }

    } while (choice != 4);


    free(weather); //clearing the pointer value in memory

    return 0;
}

void inputWeatherData(struct WeatherRecord **records, int *numRecords) {
    int newRecords;
    printf("Enter the number of daily weather records to input: ");
    scanf("%d", &newRecords);

    // Reallocating memory for new records
    *records = realloc(*records, (*numRecords + newRecords) * sizeof(struct WeatherRecord));

    for (int i = 0; i < newRecords; ++i) {
        printf("Enter data for day %d:\n", *numRecords + i + 1);
        (*records)[*numRecords + i].day = *numRecords + i + 1;  // Add day input
        printf("Temperature: ");
        scanf("%f", &(*records)[*numRecords + i].temperature);
        printf("Humidity: ");
        scanf("%f", &(*records)[*numRecords + i].humidity);
        printf("Precipitation: ");
        scanf("%f", &(*records)[*numRecords + i].precipitation);
    }

    *numRecords += newRecords;
}

void calculateAverageValues(struct WeatherRecord *records, int numRecords) {
    if (numRecords == 0) {
        printf("No weather records available.\n");
        return;
    }

    float avgTemperature = 0.0;
    float avgHumidity = 0.0;
    float avgPrecipitation = 0.0;

    for (int i = 0; i < numRecords; ++i) {
        avgTemperature += records[i].temperature;
        avgHumidity += records[i].humidity;
        avgPrecipitation += records[i].precipitation;
    }

    avgTemperature /= numRecords;
    avgHumidity /= numRecords;
    avgPrecipitation /= numRecords;

    printf("Average Temperature: %.2f\n", avgTemperature);
    printf("Average Humidity: %.2f\n", avgHumidity);
    printf("Average Precipitation: %.2f\n", avgPrecipitation);
}

void displayWeatherStatistics(struct WeatherRecord *records, int numRecords) {
    if (numRecords == 0) {
        printf("No weather records available.\n");
        return;
    }

    printf("\nWeather Statistics:\n");
    printf("%-5s%-15s%-15s%-15s\n", "Day", "Temperature", "Humidity", "Precipitation");

    for (int i = 0; i < numRecords; ++i) {
        printf("%-5d%-15.2f%-15.2f%-15.2f\n",
               records[i].day, records[i].temperature, records[i].humidity, records[i].precipitation);
    }
}

void saveWeatherRecords(struct WeatherRecord *records, int numRecords) {
    FILE *file = fopen("weather_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numRecords; ++i) {
        fprintf(file, "%d %.2f %.2f %.2f\n",
                records[i].day, records[i].temperature, records[i].humidity, records[i].precipitation);
    }

    fclose(file);
}

void loadWeatherRecords(struct WeatherRecord **records, int *numRecords) {
    FILE *file = fopen("weather_records.txt", "r");
    if (file == NULL) {
        printf("No existing weather records file found.\n");
        return;
    }

    while (fscanf(file, "%d %f %f %f", &(*records)[*numRecords].day,
                  &(*records)[*numRecords].temperature, &(*records)[*numRecords].humidity,
                  &(*records)[*numRecords].precipitation) == 4) {
        (*numRecords)++;
        *records = realloc(*records, (*numRecords + 1) * sizeof(struct WeatherRecord));
    }

    fclose(file);
}
