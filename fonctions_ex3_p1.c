#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex3_p1.h"

/* Création d'une cellule de la liste doublement chainée */
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

/* Initialisation de la liste doublement chainée */
void LDCInitialise(LDC *ldc)
{
  ldc->premier=NULL;
  ldc->dernier=NULL;
}

/* On vérifie si la liste doublement chainée est nulle */
int LDCVide(LDC *ldc)
{
  if(ldc->premier==NULL){
    return 1;
  }else{
    return 0;
  }
}

/* Insérer cellule en fin de liste chainée */
void LDCInsererEnFin(LDC *ldc, int i, int j)
{
  CelluleLDC *nv=creerCellule(i, j);

  if(ldc->premier==NULL){
    ldc->premier=nv;
    ldc->dernier=nv;
  }else{
    ldc->dernier->suiv=nv;
    ldc->dernier=nv;
  }
}

/* Enlever une cellule */
void LDC_enleverCellule(LDC *ldc ,CelluleLDC *cel)
{
  CelluleLDC *celpremier=ldc->premier;
  
  if((celpremier->i==cel->i) && (celpremier->j==cel->j)){
    ldc->premier=ldc->premier->suiv;
  }
  else{
    while(celpremier->suiv){
      if((celpremier->suiv->i==cel->i) && (celpremier->suiv->j==cel->j)){
	celpremier->suiv=celpremier->suiv->suiv;
	break;
      }
      celpremier=celpremier->suiv;
    }
  }
}

/* Afficher la liste doublement chainée */
void LDCafficher(LDC *ldc)
{
  CelluleLDC *cel=ldc->premier;

  if(LDCVide(ldc)==1){
    printf("La liste est vide. \n");
  }

  while(cel){
    printf("[%d, %d] ", cel->i, cel->j);
    cel=cel->suiv;
  }
  printf("\n");
}

/* Desallouer toute la liste */
void LDCdesalloue(LDC *ldc)
{
  CelluleLDC *cel=ldc->premier;

  while(ldc->premier){
    cel=ldc->premier->suiv;
    free(ldc->premier);
    ldc->premier=cel;
  }
}
   
