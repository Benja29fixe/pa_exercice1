#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex3_p1.h"

CelluleLDC *creerCellule(int i, int j)
{
  CelluleLDC *nc=(CelluleLDC *)malloc(sizeof(CelluleLDC));
  
  if(nc==NULL){
    printf("Probleme d'allocation.\n");
    return NULL;
  }

  nc->i=i;
  nc->j=j;
  nc->prec=NULL;
  nc->suiv=NULL;

  return nc;
}

void LDCInitialise(LDC *ldc)
{
  ldc->premier=NULL;
  ldc->dernier=NULL;
}

int LDCVide(LDC *ldc)
{
  if(ldc->premier==NULL){
    return 1;
  }else{
    return 0;
  }
}
