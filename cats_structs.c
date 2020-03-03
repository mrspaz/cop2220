#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct cat_struct {
    char *catName;
    char *furColor;
    char gender;
    int catAge;
    double weight;
    bool likesPets;
};

void initCat(struct cat_struct *catToInit, char *catName, char *furColor, char gender, int catAge, double weight, bool likesPets) {
    catToInit->catName = malloc(strlen(catName)+1);
    strcpy(catToInit->catName, catName);

    catToInit->furColor = malloc(strlen(furColor)+1);
    strcpy(catToInit->furColor, furColor);

    catToInit->gender = gender;
    catToInit->catAge = catAge;
    catToInit->weight = weight;
    catToInit->likesPets = likesPets;
}

void writeCat(FILE *catFile, struct cat_struct *catOut) {
    int nameLen = (int)strlen(catOut->catName);
    int furLen = (int)strlen(catOut->furColor);

    fwrite(&nameLen, 1, sizeof(nameLen), catFile);
    fwrite(catOut->catName, 1, nameLen, catFile);
    fwrite(&furLen, 1, sizeof(furLen), catFile);
    fwrite(catOut->furColor, 1, furLen, catFile);
    fwrite(&catOut->gender, 1, sizeof(catOut->gender), catFile);
    fwrite(&catOut->catAge, 1, sizeof(catOut->catAge), catFile);
    fwrite(&catOut->weight, 1, sizeof(catOut->weight), catFile);
    fwrite(&catOut->likesPets, 1, 1, catFile);
}

void readCat(FILE *catFile, struct cat_struct *catIn) {
    int nameLen = 0;
    int furLen = 0;

    fread(&nameLen, sizeof(nameLen), 1, catFile);
    catIn->catName = calloc((nameLen+1), sizeof(char));
    fread(catIn->catName, nameLen, 1, catFile);
    fread(&furLen, sizeof(furLen), 1, catFile);
    catIn->furColor = calloc((furLen+1), sizeof(char));
    fread(catIn->furColor, furLen, 1, catFile);
    fread(&catIn->gender, sizeof(catIn->gender), 1, catFile);
    fread(&catIn->catAge, sizeof(catIn->catAge), 1, catFile);
    fread(&catIn->weight, sizeof(catIn->weight), 1, catFile);
    fread(&catIn->likesPets, 1, 1, catFile);
}

void freeCat(struct cat_struct *catToFree) {
    free(catToFree->catName);
    free(catToFree->furColor);
}

int main(void) {
    int catCount = 4; //Not zero indexed!
    int readCatCount = 0;
    struct cat_struct *myCats = malloc(catCount * sizeof(struct cat_struct));
    struct cat_struct *copyCats = NULL;

    FILE *catsFile;
    catsFile = fopen("cats.dat.out", "w");
    if (catsFile == NULL) {
        printf("Couldn't open cat file. Exiting.");
        return 1;
    }

    initCat(&myCats[0], "Taffy", "Tabby", 'M', 18, 9.0, true);
    initCat(&myCats[1], "Meathead", "Calico", 'F', 10, 15.5, true);
    initCat(&myCats[2], "Monkey", "Fluffy Orange", 'F', 8, 7.2, false);
    initCat(&myCats[3], "Furface", "Silver Tabby", 'F', 15, 8.0, true);

    // printf("I have %lo cats.\n", (sizeof(myCats)/sizeof(myCats[0]))+1);
    // Realized this wouldn't work anymore since the records are dynamic sizes. Have to use a counter var instead.
    printf("I have %d cats.\n", catCount);
    fwrite(&catCount, 1, sizeof(catCount), catsFile);

    for (int iloopvar = 0; iloopvar < catCount; iloopvar++) {
        writeCat(catsFile, &myCats[iloopvar]);
        printf("Cat %d's name is %s. Gender is %c. It is %d years old, and weighs %0.2lf lbs.\n", (iloopvar+1), myCats[iloopvar].catName, myCats[iloopvar].gender, myCats[iloopvar].catAge, myCats[iloopvar].weight);
        printf("%s %s to be petted.\n\n", myCats[iloopvar].catName, (myCats[iloopvar].likesPets < 1 ? "hates":"loves"));
    }

    fclose(catsFile);
    catsFile = NULL;

    printf("I also have some copycats. They're in a file!\n");
    catsFile = fopen("cats.dat.out", "r");
    if (catsFile == NULL) {
        printf("Couldn't open cat file. Exiting.");
        return 1;
    }
    fread(&readCatCount, sizeof(readCatCount), 1, catsFile);
    copyCats = malloc(readCatCount * sizeof(struct cat_struct));

    printf("There's %d copycats in here.\n", readCatCount);
    for (int iloopvar = 0; iloopvar < readCatCount; iloopvar++) {
        readCat(catsFile, &copyCats[iloopvar]);
    }

    for (int iloopvar = 0; iloopvar < readCatCount; iloopvar++) {
        printf("Cat %d's name is %s. Gender is %c. It is %d years old, and weighs %0.2lf lbs.\n", (iloopvar+1), copyCats[iloopvar].catName, copyCats[iloopvar].gender, copyCats[iloopvar].catAge, copyCats[iloopvar].weight);
        printf("%s %s to be petted.\n\n", copyCats[iloopvar].catName, (copyCats[iloopvar].likesPets < 1 ? "hates":"loves"));
    }

    fclose(catsFile);

    for (int iloopvar = 0; iloopvar < catCount; iloopvar++) {
        freeCat(&myCats[iloopvar]);
    }

    for (int iloopvar = 0; iloopvar < readCatCount; iloopvar++) {
        freeCat(&copyCats[iloopvar]);
    }

    free(myCats);
    free(copyCats);

    return 0;
}