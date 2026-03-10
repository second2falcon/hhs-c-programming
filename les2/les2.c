#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#pragma warning(disable : 4996)

char* kopieerString(const char* bron, char* bestemming)
{
    char* result = bestemming;
    while (*bron != '\0') {
        *bestemming = *bron;
        bestemming++;
        bron++;
    }
    *bestemming = '\0';
    return result;
}
void opdracht1() {
	kopieerString("Hallo, wereld!", (char[20]) { 0 });
}

char* kopieerStringV2(const char* bron, char* bestemming, size_t bestemmingGrootte)
{
    if (bestemmingGrootte == 0) {
        return NULL;
    }
    
    char* result = bestemming;
    size_t i = 0;
    
    while (*bron != '\0' && i < bestemmingGrootte - 1) {
        *bestemming = *bron;
        bestemming++;
        bron++;
        i++;
    }
    *bestemming = '\0';
    return result;
}
void opdracht2() {
    char buffer[20] = { 0 };
    kopieerStringV2("Hallo, wereld!", buffer, sizeof(buffer));
}

void opdracht3() {
    char invoer[100];
    char key[100];
    char value[100];

    while (1) {
        printf("Voer iets in: \n");
        scanf(" %99[^\n]", invoer);
        sscanf(invoer, "%s : %s", key, value);

        float temp;
        if (sscanf(value, "%f", &temp) == 1) {
            printf("Geldige numerieke waarde: %.1f\n", temp);
            break;
        }

        if (strcmp(key, "Brandstof") == 0) {
            if (!(strcmp(value, "kerosine")) ||
                !(strcmp(value, "lpg")) ||
                !(strcmp(value, "benzine")) ||
                !(strcmp(value, "diesel"))) {
                printf("Geldige brandstof: %s\n", value);
                break;
            }
            else {
                printf("Ongeldige brandstof. Voer opnieuw in.\n");
            }
        }
        else {
            printf("Ongeldige invoer. Voer opnieuw in.\n");
        }
    }
}

void opdracht4() {
    struct Match {
        char location[6];    // "Thuis" of "Uit"
        int goals_for;
        int goals_against;
        char tegenstander[50];
    };
    struct Match matches[36];
    int count = 0;
    FILE* fp = fopen("uitslagen.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return;
    }
    while (fscanf(fp, "%s %d - %d %s",
        matches[count].location,
        &matches[count].goals_for,
        &matches[count].goals_against,
        matches[count].tegenstander) == 4) {
        count++;
    }
    fclose(fp);
    for(int i = 0; i < count; i++) {
        printf("Tegenstander: %s\n", matches[i].tegenstander);
    }
    typedef struct {
        int games;
        int points;
        int goals_for;
        int goals_against;
    } Stats;
    Stats stats = { 0, 0, 0, 0 };  // initialize everything to 0
    for (int i = 0; i < count; i++) {
        stats.games++;
        stats.goals_for += matches[i].goals_for;
        stats.goals_against += matches[i].goals_against;

        if (matches[i].goals_for > matches[i].goals_against) {
            stats.points += 3;  // win
        }
        else if (matches[i].goals_for == matches[i].goals_against) {
            stats.points += 1;  // draw
        }
        // loss = 0 points
    }
    printf("%d wedstrijden, %d punten en doelsaldo (%d-%d)\n",
        stats.games, stats.points,
        stats.goals_for, stats.goals_against);
    char search[50];
    printf("Voer een tegenstander in: ");
    scanf("%s", search);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(matches[i].tegenstander, search) == 0) {
            found = 1;
            if (matches[i].goals_for > matches[i].goals_against) {
                printf("Won against %s (%d-%d)\n", search,
                    matches[i].goals_for, matches[i].goals_against);
            }
            else if (matches[i].goals_for < matches[i].goals_against) {
                printf("Lost against %s (%d-%d)\n", search,
                    matches[i].goals_for, matches[i].goals_against);
            }
            else {
                printf("Draw against %s (%d-%d)\n", search,
                    matches[i].goals_for, matches[i].goals_against);
            }
            return;
        }
    }
    if (!found) {
        printf("Tegenstander '%s' bestaat niet.\n", search);
    }
}

int main()
{
	//opdracht1();
	//opdracht2();
    opdracht3();
	//opdracht4();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
