/* Header file for the Hockey Teams struct
 *     Contains struct definition for a Hockey Team record (HockeyTeam)
 *     and enums for the divisions and conferences.
 */

#ifndef HOCKEY_TEAM_H
#define HOCKEY_TEAM_H

typedef enum NHL_Conference {
    Eastern = 0,
    Western = 1
} NHLConference;

typedef enum NHL_Division {
    Atlantic = 0,
    Metropolitan = 1,
    Central = 2,
    Pacific = 3
} NHLDivision;

typedef struct Hockey_Team {
    char TeamName[128];
    int TeamConference;
    int TeamDivision;
    int YearFounded;
    char ArenaName[128];
    double SeasonWinPct;
} HockeyTeam;

// Technically this isn't quite right, but making life easier here for the purpose of the class.
char *ConferenceNames[2] = {"Eastern", "Western"};
char *DivisionNames[4] = {"Atlantic", "Metropolitan", "Central", "Pacific"};

#endif