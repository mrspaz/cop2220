#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


void birdMaker(FILE *birdFile, FILE *outFile, char *birdTypes[], int birdnumber);

int main(void) {
    FILE *base_html;
    FILE *bird_def;
    FILE *html_out;
    static char *fline_read = NULL;
    static size_t fread_len = 0;
    static __ssize_t fbyte_read;
    char *bird_sounds[6] = {"Caw","Tweet","Chirp","Cheep","Skree","Coo"};
    char *bird_types[10] = {"loon", "tern", "duck", "finch", "lark", "egret", "sparrow", "starling", "thrasher", "heron"};
    int birdcounter = 1;


    srand(time(NULL));
    base_html = fopen("svg_html_base.in", "r");
    bird_def = fopen("svg_html_bird.in", "r");
    html_out = fopen("little_birds.html", "w");

    if ((base_html == NULL) || (bird_def == NULL) || (html_out == NULL)) {
        exit(EXIT_FAILURE);
    }

    // Write the initial HTML
    for (int iloopvar = 1; iloopvar < 94; iloopvar++) {
        fbyte_read = getline(&fline_read, &fread_len, base_html);
        fputs(fline_read, html_out);
    }

    // Write the title line
    fprintf(html_out, "%s! %s! %s!\n", bird_sounds[(rand()%6)], bird_sounds[(rand()%6)], bird_sounds[(rand()%6)]);

    // Write the table def.
    for (int iloopvar = 1; iloopvar < 4; iloopvar++) {
        fbyte_read = getline(&fline_read, &fread_len, base_html);
        fputs(fline_read, html_out);        
    }

    // Add the birds, rows
    for (int iloopvar = 1; iloopvar < 4; iloopvar++) {
        fprintf(html_out, "<tr class=\"birdrow%d\">\n", iloopvar);
        // Add the birds, columns
        for (int bloopvar = 1; bloopvar < 4; bloopvar++) {
            fprintf(html_out, "<td id=\"row%dcage%d\" class=\"cage\">", iloopvar, bloopvar);
            // Make bird
            birdMaker(bird_def, html_out, bird_types, birdcounter);
            fprintf(html_out, "</td>");
            birdcounter++;
        }
        fprintf(html_out, "</tr>\n");
    }

    // Finish the file
    while ((fbyte_read = getline(&fline_read, &fread_len, base_html)) != -1) {
        fputs(fline_read, html_out);
    }

    fclose(base_html);
    fclose(bird_def);
    fclose(html_out);
    free(fline_read);

}

void birdMaker(FILE *birdFile, FILE *outFile, char *birdTypes[], int birdnumber) {
    int birdBodyR = (rand()%191) + 63;
    int birdBodyG = (rand()%191) + 63;
    int birdBodyB = (rand()%191) + 63;
    int birdStrokeR = 0;
    int birdStrokeG = 0;
    int birdStrokeB = 0;
    bool birdFat = rand()%2;
    bool birdWalks = rand()%2;
    int birdFlaps = rand()%3;
    int birdContour1 = (rand()%11) + 2;
    int birdContour2 = (rand()%16) + 2;
    int birdTail = (rand()%21) - 10;
    int birdBeak = (rand()%13) - 6;
    bool yellowBeak = rand()%2;
    bool brightEye = rand()%3;
    int birdWingTop = (rand()%6) + 2;
    int birdWingBottom = (rand()%11) + 2;
    char *bline_read = NULL;
    size_t bread_len = 0;
    __ssize_t bbyte_read;
    char outClassStr[512] = "";
    char birdName[512] = "";


    if ((birdBodyR * birdBodyG * birdBodyB) > 8290687) {
        birdStrokeR = birdBodyR * 1.25;
        birdStrokeG = birdBodyG * 1.25;
        birdStrokeB = birdBodyB * 1.25;
    } else {
        birdStrokeR = birdBodyR * 0.75;
        birdStrokeG = birdBodyG * 0.75;
        birdStrokeB = birdBodyB * 0.75;
    }

    // Return cursor to start of file
    fseek(birdFile, 0, SEEK_SET);

    // Long and tedious series of read-writes, since we are just subbing by line.
    // Reading the entire file as a string and regex would make this waaay easier. :P

    for (int cloopvar = 1; cloopvar < 72; cloopvar++) {
        bbyte_read = getline(&bline_read, &bread_len, birdFile);

        memset(outClassStr,'\0',512);
        switch (cloopvar) {
            case 2:
            case 4:
            case 15:
            case 26:
            case 28:
            case 37:
            case 39:
            case 46:
            case 48:
            case 57:
            case 61:
            case 63:
                fprintf(outFile, bline_read, birdnumber);
                break;
            
            case 13:
            case 24:
                if (birdWalks && (cloopvar == 13)) {
                    strcat(outClassStr, "leftleg ");
                } else if (birdWalks) {
                    strcat(outClassStr, "rightleg ");
                }
                if (birdFat) {
                    strcat(outClassStr, "pudgy ");
                }
                fprintf(outFile, bline_read, outClassStr);
                break;

            case 31:
                fprintf(outFile, bline_read, (60 + birdContour1), (45 - birdContour1), (25 - birdContour1), (45 - birdContour1) );
                break;

            case 32:
                fprintf(outFile, bline_read, (30 + birdTail));
                break;

            case 33:
                fprintf(outFile, bline_read, (25 + birdContour2), (55 + birdContour2), (65 - birdContour2), (55 + birdContour2) );
                break;

            case 35:
            case 55:
                if (birdFat) {
                    strcat(outClassStr, "pudgy ");
                } else {
                    strcat(outClassStr, "skinny ");
                }
                fprintf(outFile, bline_read, birdBodyR, birdBodyG, birdBodyB, birdStrokeR, birdStrokeG, birdStrokeB, outClassStr);
                break;
            
            case 42:
                fprintf(outFile, bline_read, (93 + birdBeak));
                break;
            
            case 44:
                if (birdFat) {
                    strcat(outClassStr, "pudgy ");
                } else {
                    strcat(outClassStr, "skinny ");
                }
                if (yellowBeak) {
                    fprintf(outFile, bline_read, 255, 255, 0, outClassStr);
                } else {
                    fprintf(outFile, bline_read, 0, 0, 0, outClassStr);
                }
                break;

            case 59:
                if (brightEye) {
                    fprintf(outFile, bline_read, 255, 255, 0);
                } else {
                    fprintf(outFile, bline_read, 0, 0, 0);
                }
                break;

            case 66:
                fprintf(outFile, bline_read, (58 - birdWingTop), (48 - birdWingTop), (30 + birdWingTop), (48 - birdWingTop) );
                break;

            case 67:
                fprintf(outFile, bline_read, (30 + birdWingBottom), (48 + birdWingBottom), (58 - birdWingBottom), (48 + birdWingBottom) );
                break;

            case 69:
                if (birdFat) {
                    strcat(outClassStr, "pudgy ");
                } else {
                    strcat(outClassStr, "skinny ");
                }

                switch(birdFlaps) {
                    case 1:
                        strcat(outClassStr, "flap ");
                        break;
                    case 2:
                        strcat(outClassStr, "flapfast ");
                        break;
                }

                fprintf(outFile, bline_read, birdBodyR, birdBodyG, birdBodyB, birdStrokeR, birdStrokeG, birdStrokeB, outClassStr);
                break;

            default:
                fputs(bline_read, outFile);
                break;
        }
    }

    if ((birdBodyR > birdBodyG) && (birdBodyR > birdBodyB)) {
        strcat(birdName, "Red");
    } else if ((birdBodyG > birdBodyR) && (birdBodyG > birdBodyB)) {
        strcat(birdName, "Green");
    } else if ((birdBodyB > birdBodyR) && (birdBodyB > birdBodyG)) {
        strcat(birdName, "Blue");
    } else {
        strcat(birdName, "Grey");
    }

    if (birdFat) { strcat (birdName, " pudgy"); }
    if (brightEye) { strcat(birdName, " bright"); }
    if (birdWalks) { strcat(birdName, " walking"); }

    strcat(birdName, " ");
    strcat(birdName, birdTypes[rand()%10]);
    fprintf(outFile, "<br><em>%s</em>", birdName);

    free(bline_read);
}