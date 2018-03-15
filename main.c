#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex1_p1.h"
#include "fonctions_ex3_p1.h"

int main(int argc,char**argv){
  
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i,j;
 
  int nb9, nb10, nb11, nb12, nb13;
  LDC ldc;

  if(argc!=5){
    printf("usage: %s <nb_lignes> <nb_colonnes> <nb_couleur> <graine>\n",argv[0]);
    return 1;
  }

  G.m=atoi(argv[1]);
  G.n=atoi(argv[2]);
  
  if (G.m>G.n){
    printf("Il doit y avoir plus de colonnes que de lignes.\n");
    exit(1);
  }
  G.nbcoul=atoi(argv[3]);
  if (G.nbcoul>G.m*G.n){
    printf("Il ne doit pas y avoir plus de couleurs que de cases.\n");
    exit(1);
  }
  
  graine=atoi(argv[4]);

  /* Generation de l'instance */

  Grille_allocation(&G);
  
  Gene_Grille(&G,graine);

  Solution_init(&S);

  /*Premier affichage de la grille sur le terminal*/
  affichage(G.m, G.n, G);
  
  RechercheCaseNaif_c(&G, 1, 0, 0, &nb9, &nb10);
  printf("\n\n<%d %d>\n", nb9, nb10);
  
  
  nb13=RechercheCaseNaif_nn(&G, 0, 0, &nb11, &nb12);
  printf("\n1ere case nn et piece nn : <%d %d>\ncpt : %d\n", nb11, nb12, nb13);


  printf("\n");

  algo_naif(&G, &S);
  Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  /*Après algo_naif, affichage de la grille sur le terminal*/
  affichage(G.m, G.n, G);

  /* Affiche le nombre de pas et le chemin */
  Affiche(&S);


  LDCInitialise(&ldc);
  printf("\nliste vide : %d\n", LDCVide(&ldc));


  
  return 0;  
}
