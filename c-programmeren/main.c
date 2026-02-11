#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable : 4996)

#define SCHIJF1GRENS 38883
#define SCHIJF1TARIEF 0.3575
#define SCHIJF2GRENS 78426
#define SCHIJF2TARIEF 0.3756
#define SCHIJF3TARIEF 0.495

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

void opdracht2(void)
{
    char inputGetal;
	printf("Voer een getal in: \n");
	scanf("%c", &inputGetal);
    srand(time(NULL));
}

int main(void)
{
    /*opdracht1();*/
    return 0;
}