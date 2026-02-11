#include <stddef.h>
#define SCHIJF1GRENS 38883
#define SCHIJF1TARIEF 0.3575
#define SCHIJF2GRENS 78426
#define SCHIJF2TARIEF 0.3756
#define SCHIJF3TARIEF 0.495
int main(void)
{
    int inkomen;
    printf("Inkomen invoeren: \n");
    scanf("%d", &inkomen);

    if (inkomen < SCHIJF1GRENS) {
        printf("Te betalen belasting: %.2f\n", inkomen * SCHIJF1TARIEF);
    } else if (inkomen < SCHIJF2GRENS) {
        printf("Te betalen belasting: %.2f\n", (SCHIJF1GRENS * SCHIJF1TARIEF) + ((inkomen - SCHIJF1GRENS) * SCHIJF2TARIEF));
    } else {
        printf("Te betalen belasting: %.2f\n", (SCHIJF1GRENS * SCHIJF1TARIEF) + ((SCHIJF2GRENS - SCHIJF1GRENS) * SCHIJF2TARIEF) + ((inkomen - SCHIJF2GRENS) * SCHIJF3TARIEF));
    }
    return 0;
}