#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex1_p1.h"



//void PlusCourtCheminc(Solution *S, int i, int j, int k, int l);

void RechercheCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l);

//int distance(int i, int j, int k, int l);

int exist(int i, int j, Grille *G);

void RechercheCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l);

void algorithme_circulaire(Grille *G, Solution *S);
