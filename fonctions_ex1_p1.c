#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex1_p1.h"

void affichage(int ligne, int colonne, Grille G)
{
  int i, j;
  
  for(i=0; i<ligne; i++){
    for(j=0; j<colonne; j++){
      printf("<%d %d %d> ", G.T[i][j].fond, G.T[i][j].piece, G.T[i][j].robot);
    }
    printf("\n");
  }
}

/***********************************
Fonction plus court chemin :
ajoute une séquence de caracteres à Solution
part de (i,j) pour aller à (k,l)
***********************************/
void PlusCourtChemin(Solution* S, int i, int j, int k, int l)
{
  int a=0;
  int b=0;

  for(a=0; a<abs(j-l); a++){
    if(l<j){
      Ajout_action(S,'L');
    }else if(j<l){
      Ajout_action(S,'R');
    }
  }
     
  for(b=0; b<abs(k-i); b++){
    if(i<k){
      Ajout_action(S,'D');
    }else if(i>k){
      Ajout_action(S,'U');
    }
  }
}

/***********************************
Verifie si case est noire
***********************************/
int CaseEstNoire(Grille* G, int i, int j)
{
  CCase c=G->T[i][j];
  if(c.fond==c.piece){ 
    return 1;
  }else{ 
    return 0;
  }
}

/***********************************
Verifie si piece est non noire
***********************************/
int PieceEstPasNoire(Grille* G, int i, int j)
{
  CCase c=G->T[i][j];
  if(c.piece>-1 && CaseEstNoire(G, i, j)==0){ 
    return 1;
  }
  else{ 
    return 0;
  }
}

/***********************************
Verifie si robot porte une piece de couleur
***********************************/
int RobotPortePieceCouleur(Grille* G){ 
  CCase c=G->T[G->ir][G->jr];
  return c.robot;
}

/***********************************
Recherche la case de couleur c la plus proche
d'un point donné
***********************************/
void RechercheCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l)
{
  int x, y;
  int cpt=0;
  int a, b;
  int *tab;
  int p=0;

  int min=(G->m)*(G->n);

  for(x=0; x<(G->m); x++){
    for(y=0; y<(G->n); y++){
      if((G->T[x][y].fond==c)){
	cpt++;
      }
    }
  }

  tab=(int*)malloc(cpt*sizeof(int));

  for(a=0; a<G->m; a++){
    for(b=0; b<G->n; b++){
      
      if((G->T[a][b].fond==c)){
	if(CaseEstNoire(G, a, b)==0){
    
	  tab[p]=abs(a-i)+abs(b-j);
	  if(tab[p]<min){
	    min=tab[p];
	    *k=a;
	    *l=b;
	  }
	
	  p++;
	}
      }
    }
  }
}

/***********************************
Recherche la première case non-noire
la plus proche d'un point donné
***********************************/
int RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l)
{
  int x, y;
  int cpt=0;
  int a, b;
  int *tab;
  int p=0;
  int min=(G->m)*(G->n);

  for(x=0; x<(G->m); x++){
    for(y=0; y<(G->n); y++){
      if((PieceEstPasNoire(G, x, y)==1) && ((x!=i) || (y!=j))){
	cpt++;
      }
    }
  }

  tab=(int*)malloc(cpt*sizeof(int));

  for(a=0; a<G->m; a++){
    for(b=0; b<G->n; b++){
      
      if((PieceEstPasNoire(G, a, b)==1) && ((a!=i) || (b!=j))){

	tab[p]=abs(a-i)+abs(b-j);
	if(tab[p]<min){
	  min=tab[p];
	  *k=a;
	  *l=b;
	}

	p++;
      }
    }
  }
  return cpt;
}

/***********************************
Résolution de la grille de jeu
grace à l'algo naif 
***********************************/

void algo_naif(Grille *G, Solution *S)
{
  int i=0;
  int j=0;
  int k, l;

  while((RechercheCaseNaif_nn(G, i, j, &k, &l))>0){
    if((G->T[i][j].robot==-1)){
      swap_case(G);
      Ajout_action(S,'S');
      RechercheCaseNaif_c(G, G->T[i][j].robot, i, j, &k, &l);
      PlusCourtChemin(S,i,j,k,l);
      changement_case(G, k, l);
      swap_case(G);
      Ajout_action(S,'S');
      i=k;
      j=l;
      
    }else{
      RechercheCaseNaif_c(G, G->T[i][j].robot, i, j, &k, &l);
      PlusCourtChemin(S,i,j,k,l);
      changement_case(G, k, l);
      swap_case(G);
      Ajout_action(S,'S');
      i=k;
      j=l;
    }
  }
  
  RechercheCaseNaif_c(G, G->T[i][j].robot, i, j, &k, &l);
  PlusCourtChemin(S,i,j,k,l);
  changement_case(G, k, l);
  Ajout_action(S,'S');
  swap_case(G);
}

