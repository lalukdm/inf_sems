#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CITY_FILE "city_db.txt"

typedef struct City {
    char name[50];
    int population;
    struct City *next;
} City;

City *hashTable[100] = {NULL};

int hash(char *name) {
    int index = strlen(name) % 100;
    return index;
}

void loadCitiesFromFile(){
    FILE *fp = fopen(CITY_FILE, "r");
    if (fp == NULL){
        printf("Error opening file %s\n", CITY_FILE);
        return;
    }
    char name[50];
    int population;

    while (fscanf(fp, "%s %d", name, &population) != EOF)
        add(name, population);

    fclose(fp);
}

void saveCitiesToFile(){
    FILE *fp = fopen(CITY_FILE, "w");
    if (fp == NULL){
        printf("Error opening file %s\n", CITY_FILE);
        return;
    }
    for (int i = 0; i < 100; i++) {
        City *currCity = hashTable[i];
        while (currCity != NULL) {
            fprintf(fp, "%s %d\n", currCity->name, currCity->population);
            currCity = currCity->next;
        }
    }
    fclose(fp);
}

void add(char *name, int population) {
    City *newCity = (City*) malloc(sizeof(City));
    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->next = NULL;

    int index = hash(name);
    if (hashTable[index] == NULL)
        hashTable[index] = newCity;
    else {
        City *currCity = hashTable[index];
        while (currCity->next != NULL) {
            if (strcmp(currCity->name, name) == 0) {
                currCity->population = population;
                return;
            }
            currCity = currCity->next;
        }
        currCity->next = newCity;
    }

    saveCitiesToFile();
}

void removeCity(char *name) {
    int index = hash(name);
    if (hashTable[index] == NULL)
        printf("City not found\n");
    else {
        City *currCity = hashTable[index];
        City *prevCity = NULL;
        while (currCity != NULL) {
            if (strcmp(currCity->name, name) == 0) {
                if (prevCity == NULL)
                    hashTable[index] = currCity->next;
                else
                    prevCity->next = currCity->next;

                free(currCity);
                printf("City removed\n");
                saveCitiesToFile();
                return;
            }
            prevCity = currCity;
            currCity = currCity->next;
        }
        printf("City not found\n");
    }
}

void listCities() {
    printf("List of cities:\n");
    for (int i = 0; i < 100; i++) {
        City *currCity = hashTable[i];
        while (currCity != NULL) { 
            printf("%s - %d\n", currCity->name, currCity->population); 
            currCity = currCity->next; 
        } 
    } 
}

int main() { 
    int choice; 
    char name[50]; 
    int population;

    loadCitiesFromFile();

    while(1) {
        printf("\nCity program menu:\n");
        printf("1. Add a city\n"); 
        printf("2. Remove a city\n"); 
        printf("3. List all cities\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        
        scanf("%d", &choice); 
        getchar();

        switch(choice) {
            case 1:
                printf("Enter city name: ");
                fgets(name, 50, stdin);
                name[strlen(name)-1] = '\0';
                printf("Enter city population: ");
                scanf("%d", &population);
                add(name, population);
                break;
            case 2:
                printf("Enter city name: ");
                fgets(name, 50, stdin);
                name[strlen(name)-1] = '\0';
                removeCity(name);
                break;
            case 3:
                listCities();
                break;
            case 4:
                saveCitiesToFile();
                exit(0);
            default:
                printf("Invalid choice. Please try again\n"); 
        } 
    }

    return 0;
}
