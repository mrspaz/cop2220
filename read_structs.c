#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "hockeyteam.h"
#include "cars.h"


typedef struct LL_Cars_Item {
    car carData;
    struct LL_Cars_Item *nextRec;
} llCarItem;


llCarItem *addNewCarItem(llCarItem *initNode);
void printCarItem(llCarItem *printNode, FILE *tgtFile);
void freeAllCarItems(llCarItem *initNode);


int main(void) {
    FILE *inputFile;
    FILE *outputFile;
    struct stat fileStat;
    int fStatus;
    int lReadCount = 0;


    // Read and print out hockey teams, use an array to store read records.
    outputFile = fopen("hockeyteam.dat.txt", "w");
    inputFile = fopen("hockeyteam.dat","rb");

    if ((outputFile == NULL) || (inputFile == NULL)) {
        printf("Failed to open files for NHL teams in/output.\n");
        return 1;
    }

    fStatus = stat("hockeyteam.dat", &fileStat);
    if (fileStat.st_size >= sizeof(HockeyTeam)) {
        lReadCount = (fileStat.st_size / sizeof(HockeyTeam));
        HockeyTeam *teamList = malloc(sizeof(HockeyTeam) * lReadCount);

        for (int iloopvar = 0; iloopvar < lReadCount; iloopvar++) {
            fread(&teamList[iloopvar], sizeof(HockeyTeam), 1, inputFile);
        }

        fprintf(outputFile, "Hockey Team Data\n-------------\n\n");
        for (int iloopvar = 0; iloopvar < lReadCount; iloopvar++) {
            fprintf(outputFile, "Team: %s\n", teamList[iloopvar].TeamName);
            fprintf(outputFile, "Home Arena: %s\n", teamList[iloopvar].ArenaName);
            fprintf(outputFile, "Year Founded: %d\n", teamList[iloopvar].YearFounded);
            fprintf(outputFile, "Conference: %s\n", ConferenceNames[teamList[iloopvar].TeamConference]);
            fprintf(outputFile, "Division: %s\n", DivisionNames[teamList[iloopvar].TeamDivision]);
            fprintf(outputFile, "Season Win Percentage: %02.2lf%%\n", (teamList[iloopvar].SeasonWinPct * 100));
            fprintf(outputFile, "----------\n");
        }

        free(teamList);
    }

    fclose(inputFile);
    fclose(outputFile);


    // Read and print out NFL teams, use linked list to store records.
    outputFile = fopen("cars.dat.txt","w");
    inputFile = fopen("cars.dat","rb");

    if ((outputFile == NULL) || (inputFile == NULL)) {
        printf("Failed to open files for NFL teams in/output.\n");
        return 1;
    }

    // Check file size, make list.
    fStatus = stat("cars.dat", &fileStat);
    if (fileStat.st_size >= sizeof(car)) {
        lReadCount = (fileStat.st_size / sizeof(car));
        llCarItem *initCarNode = malloc(sizeof(llCarItem));
        llCarItem *workingNode = NULL;
        initCarNode->nextRec = NULL;

        for (int iloopvar = 0; iloopvar < lReadCount; iloopvar++) {
            if (iloopvar == 0) {
                fread(&initCarNode->carData, sizeof(car), 1, inputFile);
            } else {
                workingNode = addNewCarItem(initCarNode);
                fread(&workingNode->carData, sizeof(car), 1, inputFile);
            }
        }

        fprintf(outputFile, "Cars Data\n-------------\n\n");
        printCarItem(initCarNode, outputFile);
        workingNode = initCarNode->nextRec;
        while (!(workingNode == NULL)) {
            printCarItem(workingNode, outputFile);
            workingNode = workingNode->nextRec;
        }

        freeAllCarItems(initCarNode);

    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}


llCarItem *addNewCarItem(llCarItem *initNode) {
    llCarItem *nextCarItem = NULL;
    llCarItem *currentCarItem;
    llCarItem *newItem = malloc(sizeof(llCarItem));

    newItem->nextRec = NULL;
    currentCarItem = initNode;
    nextCarItem = currentCarItem->nextRec;

    while (!(nextCarItem == NULL)) {
        currentCarItem = nextCarItem;
        nextCarItem = currentCarItem->nextRec;
    }

    currentCarItem->nextRec = newItem;
    return newItem;

}

void printCarItem(llCarItem *printNode, FILE *tgtFile) {
    fprintf(tgtFile, "Model: %s\n", printNode->carData.model);
    fprintf(tgtFile, "Manufacturer: %s\n", printNode->carData.manufacturer);
    fprintf(tgtFile, "Year: %d\n", printNode->carData.year);
    fprintf(tgtFile, "Transmission: %s\n", printNode->carData.transmission);
    fprintf(tgtFile, "Color: %s\n", printNode->carData.color);
    fprintf(tgtFile, "Mileage: %0.2lf\n", printNode->carData.mileage);
    fprintf(tgtFile, "----------\n");
}

void freeAllCarItems(llCarItem *initNode) {
    llCarItem *thisNode = NULL;
    llCarItem *nextNode = NULL;

    thisNode = initNode;
    nextNode = thisNode->nextRec;
    free(thisNode);

    while(!(nextNode == NULL)) {
        thisNode = nextNode;
        nextNode = thisNode->nextRec;
        free(thisNode);
    }
}