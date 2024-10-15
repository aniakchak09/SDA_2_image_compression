// CRETU Dan Andrei 315CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

TArbore InitArb() {
    TArbore aux = (TArbore) malloc(sizeof(struct arbore));

    aux->fiu_1 = NULL;
    aux->fiu_2 = NULL;
    aux->fiu_3 = NULL;
    aux->fiu_4 = NULL;

    return aux;
}

TInfo GetValue(TInfo **matrix, int x, int y, int size) {	//calculeaza mediile de culori din matricea primita ca argument
    TInfo value;
    unsigned long long red = 0, green = 0, blue = 0;
    
    for (int i = x; i < size + x; i++) {
        for (int j = y; j < size + y; j++) {
            red += matrix[i][j].red;
            green += matrix[i][j].green;
            blue += matrix[i][j].blue;
        }
    }

    value.red = red / (size * size);
    value.green = green / (size * size);
    value.blue = blue / (size * size);

    return value;
}

unsigned long long GetMean(TInfo RGB, int x, int y, int size, TInfo **matrix) {	//calculeaza media de culoare a matriei
    unsigned long long mean = 0;

    for (int i = x; i < size + x; i++) {
        for (int j = y; j < size + y; j++) {
            mean += (RGB.red - matrix[i][j].red) * (RGB.red - matrix[i][j].red);
            mean += (RGB.green - matrix[i][j].green) * (RGB.green - matrix[i][j].green);
            mean += (RGB.blue - matrix[i][j].blue) * (RGB.blue - matrix[i][j].blue);
        }
    }

    mean = mean / (3 * size * size);
}

TArbore ArbIntro (TInfo **matrix, int size, int factor, int x, int y) {	//comprima imaginea intr-un arbore
    TInfo RGB = GetValue(matrix, 0, 0, size);

    TArbore arb = InitArb();

    unsigned long long mean = GetMean(RGB, 0, 0, size, matrix);

    int half_size = size / 2;
    
    TInfo **top_left = (TInfo**) malloc (half_size * sizeof(TInfo*));	//aloc noile matrice in care voi imparti matricea primita ca argument
    for (int i = 0; i < half_size; i++) {
        top_left[i] = (TInfo*) malloc (half_size * sizeof(TInfo));
    }

    TInfo **top_right = (TInfo**) malloc (half_size * sizeof(TInfo*));
    for (int i = 0; i < half_size; i++) {
        top_right[i] = (TInfo*) malloc (half_size * sizeof(TInfo));
    }

    TInfo **bottom_left = (TInfo**) malloc (half_size * sizeof(TInfo*));
    for (int i = 0; i < half_size; i++) {
        bottom_left[i] = (TInfo*) malloc (half_size * sizeof(TInfo));
    }

    TInfo **bottom_right = (TInfo**) malloc (half_size * sizeof(TInfo*));
    for (int i = 0; i < half_size; i++) {
        bottom_right[i] = (TInfo*) malloc (half_size * sizeof(TInfo));
    }

    if (mean > factor) {	//daca media de culoare este mai mare decat factorul primit
        for (int i = 0; i < size; i++) {	//divizam matricea primita in 4 matrici mai mici
            for (int j = 0; j < size; j++) {
                if (i < half_size && j < half_size) {
                    top_left[i][j] = matrix[i][j];
                } else if (i < half_size && j >= half_size) {
                    top_right[i][j - half_size] = matrix[i][j];
                } else if (i >= half_size && j < half_size) {
                    bottom_left[i - half_size][j] = matrix[i][j];
                } else {
                    bottom_right[i - half_size][j - half_size] = matrix[i][j];
                }
            }
        }

        arb->type = 0;	//setez tipul nodului la 0, la fel ca pe celelalte valori
        arb->info.red = 0;
        arb->info.green = 0;
        arb->info.blue = 0;

        arb->fiu_1 = ArbIntro(top_left, half_size, factor, x, y);	//reapelez functia pentru fiii nodului intern
        arb->fiu_2 = ArbIntro(top_right, half_size, factor, x, y + half_size);
        arb->fiu_3 = ArbIntro(bottom_left, half_size, factor, x + half_size, y + half_size);
        arb->fiu_4 = ArbIntro(bottom_right, half_size, factor, x + half_size, y);
    } else {	//daca nodul e frunza, ii setez tipul la 1 si introduc in el mediile de culoare
        arb->type = 1;
        arb->info.red = RGB.red;
        arb->info.green = RGB.green;
        arb->info.blue = RGB.blue;
    }

    return arb;
}

int max_depth (TArbore arb) {
    if (!arb) {
        return 0;
    }

    int depth_1 = max_depth(arb->fiu_1);	//calculez toate adancimile posibile
    int depth_2 = max_depth(arb->fiu_2);
    int depth_3 = max_depth(arb->fiu_3);
    int depth_4 = max_depth(arb->fiu_4);

    int depth = depth_1;	//calculez care e cea mai mare

    if (depth_2 > depth) depth = depth_2;
    if (depth_3 > depth) depth = depth_3;
    if (depth_4 > depth) depth = depth_4;

    return depth + 1;	//si o returnez
}

int frunze (TArbore arb) {
    if (arb == NULL) {
        return 0;
    }

    if (arb->type) {
        return 1;
    }

    int count_1 = frunze(arb->fiu_1);
    int count_2 = frunze(arb->fiu_2);
    int count_3 = frunze(arb->fiu_3);
    int count_4 = frunze(arb->fiu_4);

    return count_1 + count_2 + count_3 + count_4;
}

int find_zone(TArbore arb, int size) {	//latura celui mai mare bloc de culoare uniforma
    if (!arb) return size;

    if (arb->type) return size;

    int size_1 = find_zone(arb->fiu_1, size / 2);	//asemanator calcularii nivelelor
    int size_2 = find_zone(arb->fiu_2, size / 2);
    int size_3 = find_zone(arb->fiu_3, size / 2);
    int size_4 = find_zone(arb->fiu_4, size / 2);

    int max_size = size_1;

    if(size_2 > max_size) max_size = size_2;
    if(size_3 > max_size) max_size = size_3;
    if(size_4 > max_size) max_size = size_4;

    return max_size;
}

TCoada InitQ () {
    TCoada c;
    c = malloc(1 * sizeof(struct coada));
    if (!c) return NULL;             

    c->inc = c->sf = NULL;
    return c;        
}

void IntrQ(TCoada coada, TArbore arb) {        
    TLista aux = malloc (sizeof(struct celula));

    aux->nod = arb;
    aux->urm = NULL;

    if ((coada)->inc != NULL) {         
        (coada)->sf->urm = aux;
    } else {                           
        (coada)->inc = aux;
    }                    
    (coada)->sf = aux; 
}

void ExtrQ (TCoada coada) { 
    TLista aux;

    if ((coada)->inc == NULL){
        return;
    }

    if (coada->inc) {
        aux = coada->inc;

        coada->inc = coada->inc->urm;
        free(aux);
    }
}

void compresie(TArbore arb, FILE *output) {	//introduc datele din arbore intr-un fisier
    TCoada coada = InitQ();

    IntrQ(coada, arb);	//introduc in coada root-ul arborelui

    while (coada->inc) {	//cat timp coada nu e vida
        TArbore aux = coada->inc->nod;	//creez un nod auxiliar ce pointeaza la nodul din inceputul cozii, adica la root pentru inceput
        ExtrQ(coada);

        if (aux->type) {	//in functie de tipul nodului, scrie informatiile necesare in fisier
            fwrite(&(aux->type), sizeof(unsigned char), 1, output);
            fwrite(&(aux->info.red), sizeof(unsigned char), 1, output);
            fwrite(&(aux->info.green), sizeof(unsigned char), 1, output);
            fwrite(&(aux->info.blue), sizeof(unsigned char), 1, output);
        } else {
            fwrite(&(aux->type), sizeof(unsigned char), 1, output);

            if (aux->fiu_1) IntrQ(coada, aux->fiu_1);	//iar apoi, daca nodul este intern, introduce fiii lui in coada
            if (aux->fiu_2) IntrQ(coada, aux->fiu_2);
            if (aux->fiu_4) IntrQ(coada, aux->fiu_4);
            if (aux->fiu_3) IntrQ(coada, aux->fiu_3);
        }
    }

    free(coada);
}

TArbore citire_arb(FILE *file) {	//creez un arbore din fisierul binar
    TArbore arb = InitArb();

    TCoada coada = InitQ();
    fread(&arb->type, sizeof(unsigned char), 1, file);	//citesc datele root-ului din fisier
    if (arb->type) {	//si daca e frunza, introduc in el culorile
        fread(&arb->info.red, sizeof(unsigned char), 1, file);
        fread(&arb->info.green, sizeof(unsigned char), 1, file);
        fread(&arb->info.blue, sizeof(unsigned char), 1, file);
    }

    IntrQ(coada, arb);	//apoi il introduc in coada

    while (coada->inc) {	//cat timp coada nu e vida
        if (!coada->inc->nod->type) {	//daca nodul e intern
            coada->inc->nod->fiu_1 = InitArb();	//aloc fiecare dintre fiii sai
            coada->inc->nod->fiu_2 = InitArb();
            coada->inc->nod->fiu_3 = InitArb();
            coada->inc->nod->fiu_4 = InitArb();

            fread(&coada->inc->nod->fiu_1->type, sizeof(unsigned char), 1, file);	//citesc tipul pentru fiecare fiu

            if (coada->inc->nod->fiu_1->type) {	//si daca fiul e frunza, introduc datele in el
                fread(&coada->inc->nod->fiu_1->info.red, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_1->info.green, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_1->info.blue, sizeof(unsigned char), 1, file);
            }

            fread(&coada->inc->nod->fiu_2->type, sizeof(unsigned char), 1, file);

            if (coada->inc->nod->fiu_2->type) {
                fread(&coada->inc->nod->fiu_2->info.red, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_2->info.green, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_2->info.blue, sizeof(unsigned char), 1, file);
            }

            fread(&coada->inc->nod->fiu_3->type, sizeof(unsigned char), 1, file);

            if (coada->inc->nod->fiu_3->type) {
                fread(&coada->inc->nod->fiu_3->info.red, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_3->info.green, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_3->info.blue, sizeof(unsigned char), 1, file);
            }

            fread(&coada->inc->nod->fiu_4->type, sizeof(unsigned char), 1, file);

            if (coada->inc->nod->fiu_4->type) {
                fread(&coada->inc->nod->fiu_4->info.red, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_4->info.green, sizeof(unsigned char), 1, file);
                fread(&coada->inc->nod->fiu_4->info.blue, sizeof(unsigned char), 1, file);
            }

            IntrQ(coada, coada->inc->nod->fiu_1);	//apoi, daca fiul e nod intern, il introduc in coada
            IntrQ(coada, coada->inc->nod->fiu_2);
            IntrQ(coada, coada->inc->nod->fiu_3);
            IntrQ(coada, coada->inc->nod->fiu_4);
        }
        ExtrQ(coada);
    }
    
    free(coada);
    return arb;
}

void citire_matrix(TArbore arb, int x, int y, int size, TInfo **matrix) {	//creez matricea pornind de la datele din arbore
    if (arb->type) {
        for (int i = y; i < size + y; i++) {
            for (int j = x; j < size + x; j++) {
                matrix[i][j].red = arb->info.red;
                matrix[i][j].green = arb->info.green;
                matrix[i][j].blue = arb->info.blue;
            }
        }
    } else {
        int half_size = size / 2;

        citire_matrix(arb->fiu_1, x, y, half_size, matrix);     
        citire_matrix(arb->fiu_2, x + half_size, y, half_size, matrix);
        citire_matrix(arb->fiu_3, x + half_size, y + half_size, half_size, matrix);
        citire_matrix(arb->fiu_4, x, y + half_size, half_size, matrix);
    }
}

void decompresie(TInfo **matrix, int size, FILE *file) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fwrite(&matrix[i][j].red, sizeof(unsigned char), 1, file);
            fwrite(&matrix[i][j].green, sizeof(unsigned char), 1, file);
            fwrite(&matrix[i][j].blue, sizeof(unsigned char), 1, file);
        }
    }

    fclose(file);
}

void dealloc (TArbore arb) {
    if (arb) {
        dealloc(arb->fiu_1);
        dealloc(arb->fiu_2);
        dealloc(arb->fiu_3);
        dealloc(arb->fiu_4);

        free(arb);
    }
}
