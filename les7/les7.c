#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define MAX_WAARDEN 100

struct studieResultaat
{
    int id;
    char vak[12];
    int ECTS;
    double cijfer;
};

int vergelijkOpVak(const void* a, const void* b)
{
    struct studieResultaat* resultaatA = (struct studieResultaat*)a;
    struct studieResultaat* resultaatB = (struct studieResultaat*)b;
    return strcmp(resultaatA->vak, resultaatB->vak);
}

int vergelijkOpECTSdanVak(const void* a, const void* b)
{
    struct studieResultaat* resultaatA = (struct studieResultaat*)a;
    struct studieResultaat* resultaatB = (struct studieResultaat*)b;
    if (resultaatA->ECTS != resultaatB->ECTS)
        return resultaatA->ECTS - resultaatB->ECTS;
    return strcmp(resultaatA->vak, resultaatB->vak);
}

int vergelijkOpCijferAflopend(const void* a, const void* b)
{
    struct studieResultaat* resultaatA = (struct studieResultaat*)a;
    struct studieResultaat* resultaatB = (struct studieResultaat*)b;
    if (resultaatB->cijfer - resultaatA->cijfer > 0) return 1;
    if (resultaatB->cijfer - resultaatA->cijfer < 0) return -1;
    return 0;
}

void drukAf(struct studieResultaat* lijst, int aantal)
{
    int i;
    for (i = 0; i < aantal; i++)
        printf("id=%-3d  vak=%-12s  ECTS=%-3d  cijfer=%.1f\n",
            lijst[i].id, lijst[i].vak, lijst[i].ECTS, lijst[i].cijfer);
    printf("\n");
}

void sorteerEnDrukAf(struct studieResultaat* lijst, int aantal, const char* label,
    int (*vergelijk)(const void*, const void*))
{
    printf("--- %s ---\n", label);
    qsort(lijst, aantal, sizeof(struct studieResultaat), vergelijk);
    drukAf(lijst, aantal);
}

void opdracht1()
{
    struct studieResultaat resultaten[] =
    {
        {1, "ProfSkills",  5, 7.5},
        {2, "Netwerken", 2, 8.0},
        {3, "C-Prog",    1, 6.5},
        {4, "Embedded",        4, 9.0},
        {5, "Project",   6, 7.0}
    };
    int aantal = sizeof(resultaten) / sizeof(resultaten[0]);

    sorteerEnDrukAf(resultaten, aantal, "Gesorteerd op vaknaam", vergelijkOpVak);
    sorteerEnDrukAf(resultaten, aantal, "Gesorteerd op ECTS, dan vaknaam", vergelijkOpECTSdanVak);
    sorteerEnDrukAf(resultaten, aantal, "Gesorteerd op cijfer (hoog naar laag)", vergelijkOpCijferAflopend);
}

double g_waarden[MAX_WAARDEN];
int g_aantal = 0;

double fahrenheit_naar_celsius(double f)
{
    return (f - 32.0) * 5.0 / 9.0;
}

// 0V = -20C, 5V = 80C  ->  20 graden per volt, offset -20
double volt_naar_celsius(double v)
{
    return v * 20.0 - 20.0;
}

void lees_meetwaarden(const char* bestandsnaam)
{
    FILE* fp;
    fp = fopen(bestandsnaam, "r");
    if (fp == NULL)
    {
        printf("Kan bestand '%s' niet openen.\n", bestandsnaam);
        g_aantal = 0;
        return;
    }
    g_aantal = 0;
    while (g_aantal < MAX_WAARDEN && fscanf(fp, "%lf", &g_waarden[g_aantal]) == 1)
        g_aantal++;
    fclose(fp);
}

void kopieer_met_conversie(double (*conversie)(double))
{
    int i;
    for (i = 0; i < g_aantal; i++)
        printf("Origineel: %8.2f  ->  Celsius: %.2f\n",
            g_waarden[i], conversie(g_waarden[i]));
}

void opdracht2()
{
    printf("=== Fahrenheit bestand ===\n");
    lees_meetwaarden("fahrenheit.txt");
    kopieer_met_conversie(fahrenheit_naar_celsius);

    printf("\n=== Volt bestand ===\n");
    lees_meetwaarden("volt.txt");
    kopieer_met_conversie(volt_naar_celsius);
}

int main(void)
{
    opdracht1();
    opdracht2();
    return 0;
}