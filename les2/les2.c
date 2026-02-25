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
    printf("Voer een brandstof in: \n");
	char invoer[100];
	char key[100];
	char value[100];
    scanf("%99[^\n]", invoer);
    /*printf(invoer);*/
    sscanf(invoer, "%s : %s", key, value);
    if (!(strcmp(value, "kerosine")) || !(strcmp(value, "lpg")) || !(strcmp(value, "benzine")) || !(strcmp(value, "diesel"))) {
        //printf(value);
        printf("Geldige brandstof: %s \n", value);
    } else {
		printf("Ongeldige brandstof. Voer een geldige brandstof in.\n");
    }
}

void opdracht4() {

}

int main()
{
    opdracht3();
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
