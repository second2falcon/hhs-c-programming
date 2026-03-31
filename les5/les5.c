#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#pragma warning(disable : 4996)

#define ROWS 9
#define COLS 9

void opdracht1a(int sudoku[ROWS][COLS], const char* bestandsnaam)
{
    FILE* fp = fopen(bestandsnaam, "r");
    if (fp == NULL)
    {
        printf("Fout: bestand %s niet gevonden.\n", bestandsnaam);
        return;
    }
    for (int r = 0; r < ROWS; r++)
        for (int j = 0; j < COLS; j++)
            fscanf(fp, "%d", &sudoku[r][j]);
    fclose(fp);
    for (int r = 0; r < ROWS; r++)
    {
        for (int j = 0; j < COLS; j++)
            printf("%d ", sudoku[r][j]);
        printf("\n");
    }
}

bool opdracht1b(int sudoku[ROWS][COLS]/*,bool rijmetfouten[9]*/)
{
    bool geldig = true;
    for (int r = 0; r < ROWS; r++)
    {
        int som = 0;
        for (int c = 0; c < COLS; c++)
            som += sudoku[r][c];
        if (som != 45)
        {
            // printf("Fout in rij %d (som = %d)\n", r + 1, som);
            geldig = false;
        }
    }
    return geldig;
}

bool opdracht1c(int sudoku[ROWS][COLS])
{
    bool geldig = true;
    for (int c = 0; c < COLS; c++)
    {
        int som = 0;
        for (int r = 0; r < ROWS; r++)
            som += sudoku[r][c];
        if (som != 45)
        {
            // printf("Fout in kolom %d (som = %d)\n", c + 1, som);
            geldig = false;
        }
    }
    return geldig;
}

bool opdracht1d(int sudoku[ROWS][COLS])
{
    bool geldig = true;
    for (int blokRij = 0; blokRij < 3; blokRij++)
    {
        for (int blokKol = 0; blokKol < 3; blokKol++)
        {
            int som = 0;
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    som += sudoku[blokRij * 3 + r][blokKol * 3 + c];
            if (som != 45)
            {
                // printf("Fout in blok (%d,%d) (som = %d)\n", blokRij + 1, blokKol + 1, som);
                geldig = false;
            }
        }
    }
    // if (geldig)
    //     printf("Alle blokken correct (som = 45)\n");
    return geldig;
}

void opdracht1(void)
{
    int sudoku[ROWS][COLS];
    opdracht1a(sudoku, "sudoku_fout_blok.txt");
    printf("\n");
    
    // Rijen check
    bool rijenOk = opdracht1b(sudoku);
    if (rijenOk)
        printf("Alle rijen correct (som = 45)\n");
    else
        printf("Fout in rij (som != 45)\n");
        
    // Kolommen check
    bool kolommenOk = opdracht1c(sudoku);
    if (kolommenOk)
        printf("Alle kolommen correct (som = 45)\n");
    else
        printf("Fout in kolom (som != 45)\n");
        
    // Blokken check
    bool blokkenOk = opdracht1d(sudoku);
    if (blokkenOk)
        printf("Alle blokken correct (som = 45)\n");
    else
        printf("Fout in blok (som != 45)\n");
}

int main()
{
    opdracht1();
    return 0;
}