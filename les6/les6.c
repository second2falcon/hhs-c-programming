#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define MAX_VAKKEN 10

struct vak
{
    char naam[20];
    int ECTS;
};

struct node
{
    int waarde;
    struct node* volgende;
};

// opdracht 1

   // 1e
void vervangVak(struct vak vakken[], int index, const char* nieuweNaam, int nieuweECTS)
{
    strcpy(vakken[index].naam, nieuweNaam);
    vakken[index].ECTS = nieuweECTS;
}

// 1f
void vervangVakPtr(struct vak* vakken[], int index, const char* nieuweNaam, int nieuweECTS)
{
    if (vakken[index] != NULL)
        free(vakken[index]);

    vakken[index] = (struct vak*)malloc(sizeof(struct vak));
    if (vakken[index] == NULL)
    {
        printf("Fout bij geheugen allocatie.\n");
        return;
    }
    strcpy(vakken[index]->naam, nieuweNaam);
    vakken[index]->ECTS = nieuweECTS;
}

void opdracht1a(void)
{
    struct vak vakken[MAX_VAKKEN];
    printf("\n--- Opdracht 1a ---\n");

    /* c) sizeof direct na declaratie - array van structs */
    printf("Gereserveerde ruimte (array van structs): %zu bytes\n", sizeof(vakken));
    printf("Uitleg: %zu structs x %zu bytes per struct = %zu bytes totaal\n",
        (size_t)MAX_VAKKEN, sizeof(struct vak), sizeof(vakken));

    int aantal = 0;
    printf("\nHoeveel vakken wil je invoeren? (max %d): ", MAX_VAKKEN);
    scanf("%d", &aantal);

    if (aantal < 0)          aantal = 0;
    if (aantal > MAX_VAKKEN) aantal = MAX_VAKKEN;

    for (int i = 0; i < aantal; i++)
    {
        printf("\nVak %d:\n", i + 1);
        printf("Naam: ");
        scanf(" %19[^\n]", vakken[i].naam);
        printf("ECTS: ");
        scanf("%d", &vakken[i].ECTS);
    }

    printf("\n--- Overzicht ---\n");
    for (int i = 0; i < aantal; i++)
        printf("Vak %d: %s | ECTS: %d\n", i + 1, vakken[i].naam, vakken[i].ECTS);

    /* e) vraag de gebruiker welk vak te vervangen en roep vervangVak aan */
    int keuze;
    printf("\nWil je een vak vervangen? (1 = Ja, 0 = Nee): ");
    scanf("%d", &keuze);

    if (keuze != 1) return;

    int index;
    printf("Welk vaknummer (1 t/m %d) wil je vervangen?: ", aantal);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= aantal)
    {
        printf("Ongeldig vaknummer.\n");
        return;
    }

    char nieuweNaam[20];
    int nieuweECTS;
    printf("Nieuwe naam: ");
    scanf(" %19[^\n]", nieuweNaam);
    printf("Nieuw aantal ECTS: ");
    scanf("%d", &nieuweECTS);

    vervangVak(vakken, index, nieuweNaam, nieuweECTS);

    printf("\n--- Aangepast overzicht ---\n");
    for (int i = 0; i < aantal; i++)
        printf("Vak %d: %s | ECTS: %d\n", i + 1, vakken[i].naam, vakken[i].ECTS);
}

void opdracht1b(void)
{
    struct vak* vakken[MAX_VAKKEN] = { NULL };
    printf("\n--- Opdracht 1b ---\n");

    /* c) sizeof direct na declaratie - array van pointers */
    printf("Gereserveerde ruimte (array van pointers): %zu bytes\n", sizeof(vakken));
    printf("Uitleg: %zu pointers x %zu bytes per pointer = %zu bytes totaal\n",
        (size_t)MAX_VAKKEN, sizeof(struct vak*), sizeof(vakken));

    int aantal = 0;
    printf("\nHoeveel vakken wil je invoeren? (max %d): ", MAX_VAKKEN);
    scanf("%d", &aantal);

    if (aantal < 0)          aantal = 0;
    if (aantal > MAX_VAKKEN) aantal = MAX_VAKKEN;

    for (int i = 0; i < aantal; i++)
    {
        vakken[i] = (struct vak*)malloc(sizeof(struct vak));
        if (vakken[i] == NULL)
        {
            printf("Fout bij geheugen allocatie.\n");
            return;
        }
        printf("\nVak %d:\n", i + 1);
        printf("Naam: ");
        scanf(" %19[^\n]", vakken[i]->naam);
        printf("ECTS: ");
        scanf("%d", &vakken[i]->ECTS);
    }

    printf("\n--- Overzicht ---\n");
    for (int i = 0; i < aantal; i++)
        if (vakken[i] != NULL)
            printf("Vak %d: %s | ECTS: %d\n", i + 1, vakken[i]->naam, vakken[i]->ECTS);

    /* f) vraag de gebruiker welk vak te vervangen en roep vervangVakPtr aan */
    int keuze;
    printf("\nWil je een vak vervangen via pointers? (1 = Ja, 0 = Nee): ");
    if (scanf("%d", &keuze) != 1 || keuze != 1)
    {
        for (int i = 0; i < MAX_VAKKEN; i++)
            if (vakken[i] != NULL) { free(vakken[i]); vakken[i] = NULL; }
        return;
    }

    int index;
    printf("Welk vaknummer (1 t/m %d) wil je vervangen?: ", aantal);
    if (scanf("%d", &index) != 1)
    {
        for (int i = 0; i < MAX_VAKKEN; i++)
            if (vakken[i] != NULL) { free(vakken[i]); vakken[i] = NULL; }
        return;
    }
    index--;

    if (index < 0 || index >= aantal)
    {
        printf("Ongeldig vaknummer.\n");
        for (int i = 0; i < MAX_VAKKEN; i++)
            if (vakken[i] != NULL) { free(vakken[i]); vakken[i] = NULL; }
        return;
    }

    char nieuweNaam[20];
    int nieuweECTS;
    printf("Nieuwe naam: ");
    scanf(" %19[^\n]", nieuweNaam);
    printf("Nieuw aantal ECTS: ");
    scanf("%d", &nieuweECTS);

    vervangVakPtr(vakken, index, nieuweNaam, nieuweECTS);

    printf("\n--- Aangepast overzicht ---\n");
    for (int i = 0; i < aantal; i++)
        if (vakken[i] != NULL)
            printf("Vak %d: %s | ECTS: %d\n", i + 1, vakken[i]->naam, vakken[i]->ECTS);

    for (int i = 0; i < MAX_VAKKEN; i++)
        if (vakken[i] != NULL) { free(vakken[i]); vakken[i] = NULL; }
}


// opdracht 2

struct node* array_naar_lijst(int arr[], int lengte)
{
    struct node* hoofd = NULL;
    struct node* staart = NULL;

    for (int i = 0; i < lengte; i++)
    {
        struct node* nieuw = (struct node*)malloc(sizeof(struct node));
        if (nieuw == NULL) return hoofd;
        nieuw->waarde = arr[i];
        nieuw->volgende = NULL;

        if (hoofd == NULL)
        {
            hoofd = nieuw;
            staart = nieuw;
        }
        else
        {
            staart->volgende = nieuw;
            staart = nieuw;
        }
    }
    return hoofd;
}

void print_lijst(struct node* hoofd)
{
    struct node* huidig = hoofd;
    while (huidig != NULL)
    {
        printf("%d", huidig->waarde);
        if (huidig->volgende != NULL) printf(" -> ");
        huidig = huidig->volgende;
    }
    printf("\n");
}

void verwijder_op_plek(struct node** hoofd, int plek)
{
    if (*hoofd == NULL || plek < 1) return;

    struct node* temp = *hoofd;
    if (plek == 1)
    {
        *hoofd = temp->volgende;
        free(temp);
        return;
    }
    struct node* vorige = NULL;
    for (int i = 1; i < plek && temp != NULL; i++)
    {
        vorige = temp;
        temp = temp->volgende;
    }
    if (temp == NULL) return;
    vorige->volgende = temp->volgende;
    free(temp);
}

void verwijder_eerste_negatief(struct node** hoofd)
{
    if (*hoofd == NULL) return;

    struct node* temp = *hoofd;
    struct node* vorige = NULL;

    while (temp != NULL)
    {
        if (temp->waarde < 0)
        {
            if (vorige == NULL)
                *hoofd = temp->volgende;
            else
                vorige->volgende = temp->volgende;
            free(temp);
            return;
        }
        vorige = temp;
        temp = temp->volgende;
    }
}

void verwijder_alle_negatief(struct node** hoofd)
{
    while (*hoofd != NULL && (*hoofd)->waarde < 0)
    {
        struct node* temp = *hoofd;
        *hoofd = (*hoofd)->volgende;
        free(temp);
    }

    struct node* huidig = *hoofd;
    while (huidig != NULL && huidig->volgende != NULL)
    {
        if (huidig->volgende->waarde < 0)
        {
            struct node* temp = huidig->volgende;
            huidig->volgende = temp->volgende;
            free(temp);
        }
        else
        {
            huidig = huidig->volgende;
        }
    }
}

void invoegen_op_plek(struct node** hoofd, int plek, int waarde)
{
    struct node* nieuw = (struct node*)malloc(sizeof(struct node));
    if (nieuw == NULL) return;
    nieuw->waarde = waarde;
    nieuw->volgende = NULL;

    if (plek <= 1 || *hoofd == NULL)
    {
        nieuw->volgende = *hoofd;
        *hoofd = nieuw;
        return;
    }

    struct node* huidig = *hoofd;
    for (int i = 1; i < plek - 1 && huidig->volgende != NULL; i++)
        huidig = huidig->volgende;

    nieuw->volgende = huidig->volgende;
    huidig->volgende = nieuw;
}

void toevoegen_achteraan(struct node** hoofd, int waarde)
{
    struct node* nieuw = (struct node*)malloc(sizeof(struct node));
    if (nieuw == NULL) return;
    nieuw->waarde = waarde;
    nieuw->volgende = NULL;

    if (*hoofd == NULL)
    {
        *hoofd = nieuw;
        return;
    }

    struct node* huidig = *hoofd;
    while (huidig->volgende != NULL)
        huidig = huidig->volgende;
    huidig->volgende = nieuw;
}

void verwijder_eerste(struct node** hoofd)
{
    if (*hoofd == NULL) return;
    struct node* temp = *hoofd;
    *hoofd = (*hoofd)->volgende;
    free(temp);
}

void verwijder_lijst(struct node** hoofd)
{
    while (*hoofd != NULL)
        verwijder_eerste(hoofd);
}

void opdracht2(void)
{
    printf("\n--- Opdracht 2a: array naar linked list ---\n");
    int arr[] = { 3, 7, -2, 5, -8, 1, 4 };
    int lengte = sizeof(arr) / sizeof(arr[0]);
    struct node* lijst = array_naar_lijst(arr, lengte);
    print_lijst(lijst);

    printf("\n--- Opdracht 2b: verwijder node op plek 3 ---\n");
    verwijder_op_plek(&lijst, 3);
    print_lijst(lijst);

    printf("\n--- Opdracht 2c: verwijder eerste negatief getal ---\n");
    verwijder_eerste_negatief(&lijst);
    print_lijst(lijst);

    printf("\n--- Opdracht 2d: verwijder alle negatieve getallen ---\n");
    verwijder_alle_negatief(&lijst);
    print_lijst(lijst);

    printf("\n--- Opdracht 2e: invoegen op plek 2 ---\n");
    invoegen_op_plek(&lijst, 2, 99);
    print_lijst(lijst);

    printf("\n--- Opdracht 2f: toevoegen achteraan ---\n");
    toevoegen_achteraan(&lijst, 42);
    print_lijst(lijst);

    printf("\n--- Opdracht 2g: verwijder eerste node ---\n");
    verwijder_eerste(&lijst);
    print_lijst(lijst);

    printf("\n--- Opdracht 2h: queue demonstratie ---\n");
    printf("Enqueue 10, 20, 30:\n");
    toevoegen_achteraan(&lijst, 10);
    toevoegen_achteraan(&lijst, 20);
    toevoegen_achteraan(&lijst, 30);
    print_lijst(lijst);
    printf("Dequeue (verwijder eerste):\n");
    verwijder_eerste(&lijst);
    print_lijst(lijst);
    verwijder_lijst(&lijst);
}

int main()
{
    opdracht1a();
    opdracht1b();
    opdracht2();
    return 0;
}