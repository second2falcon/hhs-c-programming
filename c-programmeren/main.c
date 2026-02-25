#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#pragma warning(disable : 4996)

#define SCHIJF1GRENS 38883
#define SCHIJF1TARIEF 0.3575
#define SCHIJF2GRENS 78426
#define SCHIJF2TARIEF 0.3756
#define SCHIJF3TARIEF 0.495

#define deelcijferArraySize 100

#define MAX_WORPEN_PER_BEURT 10
#define MAX_BEURTEN 10
#define MAX_PINS (MAX_BEURTEN * MAX_WORPEN_PER_BEURT + 2)

float belastingBerekenen(int inkomen)
{
    if (inkomen < SCHIJF1GRENS) {
        return inkomen * SCHIJF1TARIEF;
    } else if (inkomen < SCHIJF2GRENS) {
        return (SCHIJF1GRENS * SCHIJF1TARIEF) + ((inkomen - SCHIJF1GRENS) * SCHIJF2TARIEF);
    } else {
        return (SCHIJF1GRENS * SCHIJF1TARIEF) + ((SCHIJF2GRENS - SCHIJF1GRENS) * SCHIJF2TARIEF) + ((inkomen - SCHIJF2GRENS) * SCHIJF3TARIEF);
    }
}
int opdracht1(void)
{
    int inkomen;
    printf("Inkomen invoeren: \n");
    scanf("%d", &inkomen);
    float belasting = belastingBerekenen(inkomen);
    printf("De te betalen belasting is: %.2f\n", belasting);
    return 0;
}

int maakRandomGetal(int onder, int boven)
{
    return rand() % (boven - onder + 1) + onder;
}
void opdracht2(void)
{
    srand(time(NULL));

    char opnieuw = 'j';

    while (opnieuw == 'j')
    {
        int onder;
        int boven;
        int maxBeurten;
        printf("Ondergrens: ");
        scanf("%d", &onder);
        printf("Bovengrens: ");
        scanf("%d", &boven);
        printf("Aantal beurten: ");
        scanf("%d", &maxBeurten);

        int geheim = maakRandomGetal(onder, boven);

        int gokken[100];   // opslag voor ingevoerde getallen
        int goed = 0;

        for (int i = 0; i < maxBeurten; i++)
        {
            printf("Gok %d: ", i + 1);
            scanf("%d", &gokken[i]);

            if (gokken[i] < geheim)
            {
                printf("Hoger\n");
            }
            else if (gokken[i] > geheim)
            {
                printf("Lager\n");
            }
            else
            {
                printf("Goed geraden!\n");
                goed = 1;
                maxBeurten = i + 1; // voor juiste print later
                break;
            }
        }
        if (!goed)
        {
            printf("Helaas! Het getal was: %d\n", geheim);
        }
        printf("Ingevoerde getallen: ");
        for (int i = 0; i < maxBeurten; i++)
        {
            printf("%d ", gokken[i]);
        }
        printf("\n");
        printf("Nog een keer spelen? (j/n): ");
        scanf(" %c", &opnieuw);
    }
}

float avgCijfer(float deelcijfers[], int aantalDeelcijfers) {
    float sum = 0;
    for (int i = 0; i < aantalDeelcijfers; i++) {
        sum += deelcijfers[i];
    }
    return sum / aantalDeelcijfers;
}
int teLageCijfers(float deelcijfers[], int aantalDeelcijfers) {
    int count = 0;
    for (int i = 0; i < aantalDeelcijfers; i++) {
        if (deelcijfers[i] < 4.0) {
            count++;
        }
    }
    return count;
}
void opdracht3(void) {
	bool geenLof = false;
    bool behaald = false;
    int aantalDeelcijfers;
    printf("Aantal deelcijfers: ");
    scanf("%d", &aantalDeelcijfers);
    if (aantalDeelcijfers > deelcijferArraySize) {
        printf("Fout: het aantal deelcijfers is groter dan dat de array toelaat.\n");
        printf("Maximaal aantal deelcijfers is %d\n", deelcijferArraySize);
        return;
    }
    float deelcijfers[deelcijferArraySize];
    for (int i = 0; i < aantalDeelcijfers; i++) {
        printf("Deelcijfer %d: ", i + 1);
        while (scanf("%f", &deelcijfers[i]) != 1) {
            printf("Ongeldige invoer, probeer opnieuw: ");
            while (getchar() != '\n'); // buffer leegmaken
        }
        if (deelcijfers[i] < 7.0) {
			geenLof = true;
        }
    }

    float gemiddelde = avgCijfer(deelcijfers, aantalDeelcijfers);
    if (teLageCijfers(deelcijfers, aantalDeelcijfers) <= 1 && gemiddelde >= 5.5) {
        behaald = true;
    }
    printf("Het gemiddelde cijfer is: %.2f\n", gemiddelde);
    if (geenLof == false && gemiddelde >= 7.5) {
        printf("Gefeliciteerd! Je hebt lof behaald!\n");
    }
    else if (behaald) {
        printf("Goed gedaan! Je hebt het gehaald!\n");
        if (gemiddelde < 7.5) {
            printf("Toelichting: gemiddelde te laag voor lof (%.2f < 7.5)\n", gemiddelde);
        }
        else {
            printf("Toelichting: een of meer cijfers onder de 7, dus geen lof.\n");
        }
    }
    else {
        printf("Helaas, je hebt het niet gehaald.\n");
        if (gemiddelde < 5.5) {
            printf("Toelichting: gemiddelde te laag (%.2f < 5.5)\n", gemiddelde);
        }
        if (teLageCijfers(deelcijfers, aantalDeelcijfers) > 1) {
            printf("Toelichting: meer dan 1 cijfer onder de 4.\n");
        }
	}
    
}

int leesGeldigGetal(const char* prompt) {
    int waarde;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &waarde)) return waarde;
        scanf("%*[^\n]");
        printf("Dat is geen geldig getal!\n");
    }
}
void opdracht4(void) {
    int worpenPerBeurt;
    int aantalBeurten = 10;
    int aantalSpelers = 2;

    printf("Hoeveel worpen per beurt? ");
    scanf("%d", &worpenPerBeurt);

    for (int speler = 0; speler < aantalSpelers; speler++) {
        printf("\n=== Speler %d is aan de beurt ===\n", speler + 1);

        int pins[MAX_PINS];
        int puntenPerBeurt[MAX_BEURTEN];
        int totaal = 0;
        int worp = 0;

        for (int beurt = 0; beurt < aantalBeurten; beurt++) {
            puntenPerBeurt[beurt] = 0;
            int pinsDezeBeurt = 0;
            int worpInBeurt = 0;

            while (worpInBeurt < worpenPerBeurt) {
                int staandePins = 10 - pinsDezeBeurt;
                char prompt[50];
                sprintf(prompt, "Beurt %d, worp %d (max %d): ", beurt + 1, worpInBeurt + 1, staandePins);
                int gegooid = leesGeldigGetal(prompt);

                while (gegooid < 0 || gegooid > staandePins) {
                    printf("Ongeldig! Je kunt maximaal %d pins omgooien.\n", staandePins);
                    gegooid = leesGeldigGetal(prompt);
                }

                pins[worp] = gegooid;
                pinsDezeBeurt += gegooid;
                worp++;
                worpInBeurt++;

                int isStrike = worpInBeurt == 1 && gegooid == 10;
                int isSpare = worpInBeurt == worpenPerBeurt && pinsDezeBeurt == 10;

                puntenPerBeurt[beurt] = pinsDezeBeurt;

                if (isStrike || isSpare) {
                    puntenPerBeurt[beurt] = 10;
                    while (worpInBeurt < worpenPerBeurt) {
                        pins[worp] = -1;
                        worp++;
                        worpInBeurt++;
                    }
                    worpInBeurt = worpenPerBeurt; // lus beëindigen
                }
            }
        }

        // Bonusworpen bij spare of strike in beurt 10
        int bonus1 = 0, bonus2 = 0;
        int beurt10Start = (aantalBeurten - 1) * worpenPerBeurt;
        int wasStrike = pins[beurt10Start] == 10;
        int wasSpare = !wasStrike && puntenPerBeurt[aantalBeurten - 1] == 10;

        if (wasStrike) {
            bonus1 = leesGeldigGetal("Bonusworp 1 (max 10): ");
            while (bonus1 < 0 || bonus1 > 10) {
                printf("Ongeldig! Maximaal 10 pins.\n");
                bonus1 = leesGeldigGetal("Bonusworp 1 (max 10): ");
            }
            int maxBonus2 = (bonus1 == 10) ? 10 : 10 - bonus1;
            char prompt[50];
            sprintf(prompt, "Bonusworp 2 (max %d): ", maxBonus2);
            bonus2 = leesGeldigGetal(prompt);
            while (bonus2 < 0 || bonus2 > maxBonus2) {
                printf("Ongeldig! Maximaal %d pins.\n", maxBonus2);
                bonus2 = leesGeldigGetal(prompt);
            }
        }
        else if (wasSpare) {
            bonus1 = leesGeldigGetal("Bonusworp 1 (max 10): ");
            while (bonus1 < 0 || bonus1 > 10) {
                printf("Ongeldig! Maximaal 10 pins.\n");
                bonus1 = leesGeldigGetal("Bonusworp 1 (max 10): ");
            }
        }

        // Bereken bonuspunten voor spares en strikes (beurten 1-9)
        for (int beurt = 0; beurt < aantalBeurten - 1; beurt++) {
            int wasStrikeDezeBeurt = pins[beurt * worpenPerBeurt] == 10;
            int isSpareOfStrike = puntenPerBeurt[beurt] == 10;

            if (isSpareOfStrike) {
                int volgendeStart = (beurt + 1) * worpenPerBeurt;

                if (wasStrikeDezeBeurt) {
                    int echteWorpen[2];
                    int gevonden = 0;
                    int idx = volgendeStart;

                    while (gevonden < 2) {
                        int buiten = idx >= worp;
                        int placeholder = !buiten && pins[idx] == -1;

                        echteWorpen[gevonden] = buiten * ((gevonden == 0) ? bonus1 : bonus2)
                            + !buiten * !placeholder * pins[idx];
                        gevonden += !placeholder;
                        idx += !buiten;
                    }
                    puntenPerBeurt[beurt] += echteWorpen[0] + echteWorpen[1];
                }
                else {
                    int idx = volgendeStart;
                    while (pins[idx] == -1) idx++;
                    puntenPerBeurt[beurt] += pins[idx];
                }
            }
        }

        // Bonusworp toevoegen aan beurt 10
        puntenPerBeurt[aantalBeurten - 1] += bonus1 + bonus2;

        for (int beurt = 0; beurt < aantalBeurten; beurt++) {
            totaal += puntenPerBeurt[beurt];
        }

        printf("Speler %d heeft totaal: %d punten!\n", speler + 1, totaal);
    }
}

int main(void)
{
    /*opdracht1();*/
	/*opdracht2();*/
    /*opdracht3();*/
    opdracht4();
    return 0;
}