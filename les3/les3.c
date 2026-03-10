#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#pragma warning(disable : 4996)

#define ARRAY_SIZE 100

void print_array(double arr[], int lengte) {
    printf("[");
    for (int i = 0; i < lengte; i++) {
        printf("%.2f", arr[i]);
        if (i < lengte - 1) {   // niet na het laatste getal
            printf(", ");
        }
    }
    printf("]\n");
}
void opdracht1() {
    double array1[] = { 5.89, 6.20, -2.13 };
    double array2[] = { 3.14 };
    double array3[] = { 1.0, 2.5, 3.333, -99.9 };

    print_array(array1, 3);
    print_array(array2, 1);
    print_array(array3, 4);

}

void generateRandomArray(double arr[], int lengte) {  // void, want geen return ivm pointer
    for (int i = 0; i < lengte; i++) {
        arr[i] = (double)rand() / RAND_MAX * 200.0 - 100.0;
    }
}
void opdracht2c(double arr1[], double arr2[], double result[], int lengte) {
    for (int i = 0; i < lengte; i++) {
        if (arr1[i] > arr2[i]) {
            result[i] = arr1[i];
        }
        else {
            result[i] = arr2[i];
        }
    }
}
void opdracht2() {
    int lengte;
    printf("Voer de lengte van de array in: ");
	scanf("%d", &lengte);
    if (lengte > 100) {
        printf("Lengte mag niet groter zijn dan 100.\n");
        return;
	}
 //   double array21[ARRAY_SIZE];
 //   double array22[ARRAY_SIZE];
	//double result[ARRAY_SIZE];
    double *array21 = malloc(lengte * sizeof(double));
    double *array22 = malloc(lengte * sizeof(double));
    double *result = malloc(lengte * sizeof(double));
    generateRandomArray(array21, lengte);
    generateRandomArray(array22, lengte);

	print_array(array21, lengte);
	print_array(array22, lengte);
	opdracht2c(array21, array22, result, lengte);
    print_array(result, lengte);

    free(array21);
    free(array22);
    free(result);
}

struct vak
{
    char naam[20];
    int ECTS;
};

void opdracht3b(struct vak *v, int size) {
    printf("Wilt u de naam van een vak, of de aantal te behalen ECTS veranderen? [Y/n] ");
    char input[2];
    scanf("%1s", input);
    if (!(strcmp(input, "Y"))) {
        printf("Voer de index in van het vak dat u wilt aanpassen (0-2): ");
        int keuzeIndex;
        scanf("%1d", &keuzeIndex);
        if (keuzeIndex > (size - 1)) {
            printf("Deze index bestaat niet. Voer een geldige index in.\n");
            return;
        }
        printf("De huidige vak  naam: ");
        printf(v[keuzeIndex].naam);
        printf("\n");
        printf("Voer de nieuwe vak naam in: ");
        scanf("%s", v[keuzeIndex].naam);

        printf("Het huidige aantal te behalen ECTS: ");
        printf("%d\n", v[keuzeIndex].ECTS);
        printf("\n");
        printf("Voer het nieuwe aantal te behalen ECTS in: ");
        getchar();
        scanf("%d", &v[keuzeIndex].ECTS);
    }
}
void opdracht3c(struct vak *v) {
    printf("De huidige vaknaam: %s\n", v->naam);
    printf("Voer de nieuwe vaknaam in: ");
    scanf(" %s", v->naam);

    printf("Het huidige aantal ECTS: %d\n", v->ECTS);
    printf("Voer het nieuwe aantal ECTS in: ");
    scanf(" %d", &v->ECTS);
}
void opdracht3() {
    struct vak Vakken[3];
    strcpy(Vakken[0].naam, "MC Programming");
    Vakken[0].ECTS = 25;
    strcpy(Vakken[1].naam, "C Programming");
    Vakken[1].ECTS = 25;
    strcpy(Vakken[2].naam, "Prof Skills");
    Vakken[2].ECTS = 15;

    //opdracht3b(Vakken, 3);

    int keuzeIndex;
    printf("Voer de index in van het vak dat u wilt aanpassen (0-2): ");
    scanf(" %d", &keuzeIndex);
    if (keuzeIndex < 0 || keuzeIndex > 2) {
        printf("Ongeldige index.\n");
        return;
    }
    opdracht3c(&Vakken[keuzeIndex]);

    printf("De vakken zijn nu/waren: \n");
    for (int i = 0; i < 3; i++) {
        printf("Vak: %s (%d ECTS)\n", Vakken[i].naam, Vakken[i].ECTS);
    }
}

struct teamlid {
    int id;
    char naam[20];
    char opleiding[10];
};

int generatieId() {
    static int id = 1000;
    return id++;
}

void voegTeamlidToe(struct teamlid* lid) {
    lid->id = generatieId();
    printf("Naam: ");
    scanf(" %s", lid->naam);
    printf("Opleiding: ");
    scanf(" %s", lid->opleiding);
}

void zoekOpOpleiding(struct teamlid* team, int size) {
    char zoekOpleiding[10];
    printf("Voer de opleiding in om op te zoeken: ");
    scanf(" %s", zoekOpleiding);

    printf("Teamleden met opleiding %s:\n", zoekOpleiding);
    int gevonden = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(team[i].opleiding, zoekOpleiding) == 0) {
            printf("ID: %d | Naam: %s | Opleiding: %s\n", team[i].id, team[i].naam, team[i].opleiding);
            gevonden = 1;
        }
    }
    if (!gevonden) {
        printf("Geen teamleden gevonden met opleiding %s.\n", zoekOpleiding);
    }
}

void opdracht4() {
    int aantalLeden;
    printf("Hoeveel teamleden wilt u toevoegen? ");
    scanf(" %d", &aantalLeden);

    struct teamlid* team = malloc(aantalLeden * sizeof(struct teamlid));
    for (int i = 0; i < aantalLeden; i++) {
        printf("\n--- Teamlid %d ---\n", i + 1);
        voegTeamlidToe(&team[i]);
    }

    printf("\nHet team:\n");
    for (int i = 0; i < aantalLeden; i++) {
        printf("ID: %d | Naam: %s | Opleiding: %s\n", team[i].id, team[i].naam, team[i].opleiding);
    }

    zoekOpOpleiding(team, aantalLeden);

    free(team);
}

int main()
{
    //opdracht1();
    //opdracht2();
    //opdracht3();
    //opdracht4();
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
