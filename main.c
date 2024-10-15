// CRETU Dan Andrei 315CB
#include "functions.h"

int main (int argc, char *argv[]) {
    FILE *input;
    FILE *output;

    TArbore arb = NULL;

    if (strcmp(argv[1], "-d")) {
        int factor = atoi(argv[2]);
        input = fopen(argv[3], "rb");
        output = fopen(argv[4], "wb");

        arb = InitArb();

        unsigned int size, max;
        char *useless = malloc (3 * sizeof(char));
        
        fread(useless, sizeof(char), 3, input);
        fscanf(input, "%d", &size);
        fscanf(input, "%d", &size);
        fscanf(input, "%d", &max);
        fread(useless, sizeof(char), 1, input);

        TInfo **matrix = (TInfo**) malloc (size * sizeof(TInfo*));
        for (int i = 0; i < size; i++) {
            matrix[i] = (TInfo*) malloc (size * sizeof(TInfo));
        }

        for (int i = 0; i < size; i++) {	//introduc datele din fisier in matrice
            for (int j = 0; j < size; j++) {
                fread(&matrix[i][j].red, sizeof(unsigned char), 1, input);      
                fread(&matrix[i][j].green, sizeof(unsigned char), 1, input); 
                fread(&matrix[i][j].blue, sizeof(unsigned char), 1, input); 
            }
        }

        arb = ArbIntro(matrix, size, factor, 0, 0);	//creez arborele imaginii
        
        if (!strcmp(argv[1], "-c1")) {	//pentru calcularea statisticilor
            fprintf(output, "%d", max_depth(arb));	//numarul de nivele
            fprintf(output, "%s", "\n");
            fprintf(output, "%d", frunze(arb));	//numarul de noduri ce contin date rgb
            fprintf(output, "%s", "\n");
            fprintf(output, "%d", find_zone(arb, size));	//latura celui mai mare bloc de o singura culoare
            fprintf(output, "%s", "\n");
        }

        if (!strcmp(argv[1], "-c2")) {	//compresia arborelui
            fwrite(&size, sizeof(int), 1, output);
            compresie(arb, output);
        }

        for (int i = 0; i < size; i++) {
            free(matrix[i]);
        }
        free(matrix);
        free(useless);
        fclose(input);
        fclose(output);
    }

    if (!strcmp(argv[1], "-d")) {       //decompresie
        input = fopen(argv[2], "rb");
        output = fopen(argv[3], "wb");

        int size;
        fread(&size, sizeof(int), 1, input);

        fprintf(output, "P6\n%d %d\n255\n", size, size);

        TInfo **matrix = (TInfo**) malloc (size * sizeof(TInfo*));
        for (int i = 0; i < size; i++) {
            matrix[i] = (TInfo*) malloc (size * sizeof(TInfo));
        }

        arb = citire_arb(input);	//creez arborele cu informatiile din fisier
        fclose(input);
        citire_matrix(arb, 0, 0, size, matrix);	//introduc datele din arbore in matrice

        decompresie(matrix, size, output);	//printez matricea

        for (int i = 0; i < size; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }

    dealloc(arb);
}