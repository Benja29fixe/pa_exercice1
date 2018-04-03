#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex1_p1.h"
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

/* Renvoie la case la plus proche d'un point de coordonnées (a,b) */
CelluleLDC *LDCrechercherPlusProcheCase(LDC *ldc, int a, int b)
{
  CelluleLDC *cel=ldc->premier;
  CelluleLDC *celMini=creerCellule(cel->i, cel->j);

  while(cel->suiv){
    
    if(( abs((cel->suiv->i)-a)+abs((cel->suiv->j)-b)) < ( abs((celMini->i)-a)+abs((celMini->j)-b))){

      celMini->i=cel->suiv->i;
      celMini->j=cel->suiv->j;
     
    }
    
    cel=cel->suiv;
  }

  return celMini;
}

/* Trouve le nombre de case noire dans une GRille */
int nbCaseNoire(Grille *G)
{
  int i, j;
  int cpt=0;

  for(i=0; i<G->m; i++){
    for(j=0; j<G->n; j++){
      if(CaseEstNoire(G, i, j)==1){
	cpt++;
      }
    }
  }
  return cpt;
}
      
/*************************************
Algo par couleur
*************************************/
void algo_parcouleur(Grille *G, Solution *S)
{
  int f, i, j, p, q;
  int k=0;
  int it=(G->m)*(G->n);
  int a=0;
  int b=0;
  int couleur_piece_robot;
  LDC nldc;
 
  /* Creation du tableau */
  LDC *TC=(LDC*)malloc((G->nbcoul)*sizeof(LDC));

  /* Initialisation des valeurs du tableau */
  for(f=0; f<G->nbcoul; f++){  
    LDCInitialise(&nldc);
    TC[f]=nldc;
  }

  printf("%d %d\n", TC[1], TC[9]);
  printf("nb ligne:%d nb colonne:%d\n", G->m, G->n);

  /* Rempli les cases du tableau avec les LDC */ 
  for(i=(G->n)-1; i>=0; i--){
    for(j=0; j<G->m; j++){
      
      if(LDCVide(&TC[G->T[j][i].fond]) && CaseEstNoire(G, j, i)==0){

	LDCInitialise(&TC[G->T[j][i].fond]);
	LDCInsererEnFin(&TC[G->T[j][i].fond], j, i);

      }else{
	if(CaseEstNoire(G, j, i)==0){
	  LDCInsererEnFin(&TC[G->T[j][i].fond], j, i);
	}
      }
    }
  }

  /* Affichage du tableau de LDC */
  for(f=0; f<G->nbcoul; f++){
    LDCafficher(&TC[f]);
  }
  
  printf("nb case noire dans Grille : %d \n",nbCaseNoire(G));
  
  
  while(it!=nbCaseNoire(G)){
    if((G->T[a][b].robot==-1) && (PieceEstPasNoire(G, a, b))==1){
   
      swap_case(G);
      Ajout_action(S, 'S');
      couleur_piece_robot=G->T[a][b].robot;
 
      CelluleLDC *cel=LDCrechercherPlusProcheCase(&TC[couleur_piece_robot], a, b);
      changement_case(G, cel->i, cel->j);
      PlusCourtChemin(S, a, b, cel->i, cel->j);
      swap_case(G);
      Ajout_action(S, 'S');
      LDC_enleverCellule(&TC[couleur_piece_robot], cel);

      a=cel->i;
      b=cel->j;

    }if((G->T[a][b].robot==-1) && (CaseEstNoire(G, a, b)==1)){
      RechercheCaseNaif_nn(G, a, b, &p, &q);
      changement_case(G, p, q);

      swap_case(G);
      Ajout_action(S, 'S');
      couleur_piece_robot=G->T[p][q].robot;
      CelluleLDC *cel=LDCrechercherPlusProcheCase(&TC[couleur_piece_robot], p, q);
      changement_case(G, cel->i, cel->j);
      PlusCourtChemin(S, a, b, cel->i, cel->j);
      swap_case(G);
      Ajout_action(S, 'S');
      LDC_enleverCellule(&TC[couleur_piece_robot], cel);

      a=cel->i;
      b=cel->j;

    }else{
      couleur_piece_robot=G->T[a][b].robot;
      CelluleLDC *cel=LDCrechercherPlusProcheCase(&TC[couleur_piece_robot], a, b);
     
      changement_case(G, cel->i, cel->j);
      PlusCourtChemin(S, a, b, cel->i, cel->j);
      swap_case(G);
      Ajout_action(S, 'S');
      LDC_enleverCellule(&TC[couleur_piece_robot], cel);

      a=cel->i;
      b=cel->j;
    }
  }  
}
      
    
    
    
