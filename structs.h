// CRETU Dan Andrei 315CB
#include <stdio.h>
#include <stdlib.h>

typedef struct info {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} TInfo;

typedef struct arbore {
    unsigned char type;
    TInfo info;
    struct arbore *fiu_1;
    struct arbore *fiu_2;
    struct arbore *fiu_3;
    struct arbore *fiu_4;
} TNod, *TArbore;

typedef struct celula {
  TArbore nod;
  struct celula *urm;
} TCelula, *TLista;

typedef struct coada {
  TLista inc, sf;
} *TCoada;