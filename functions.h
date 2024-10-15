// CRETU Dan Andrei 315CB
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

TArbore InitArb();

TInfo GetValue(TInfo **matrix, int x, int y, int size);
unsigned long long GetMean(TInfo RGB, int x, int y, int size, TInfo **matrix);

TArbore ArbIntro (TInfo **matrix, int size, int factor, int x, int y);

int max_depth(TArbore arb);
int frunze (TArbore arb);
int find_zone(TArbore arb, int size);

TCoada InitQ ();
void IntrQ(TCoada coada, TArbore arb);
void ExtrQ (TCoada coada);

void compresie(TArbore arb, FILE *output);

TArbore citire_arb(FILE *file);
void citire_matrix(TArbore arb, int x, int y, int size, TInfo **matrix);
void decompresie(TInfo **matrix, int size, FILE*file);

void dealloc (TArbore arb);