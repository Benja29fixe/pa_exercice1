#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
  int num_algo;
 
  int nb1, nb2, nb3, nb4, nb5;
  int k, l;
  LDC ldc;

  if(argc!=6){
    printf("usage: %s <nb_lignes> <nb_colonnes> <nb_couleur> <graine> <choix de l'algo>\n",argv[0]);
    printf("+--- Choix de l'algo ----------------------+\n");
    printf("|1 : algorithme naif                       |\n");
    printf("|2 : algorithme circulaire                 |\n");
    printf("|3 : algorithme par couleur                |\n");
    printf("|4 : algorithme AVL                        |\n");
    printf("+------------------------------------------+\n");
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
  num_algo=atoi(argv[5]);

  /* Generation de l'instance */

  Grille_allocation(&G);
  Gene_Grille(&G,graine);
  Solution_init(&S);

  /*Premier affichage de la grille sur le terminal*/
  affichage(G.m, G.n, G);

  printf("+------------------------------------------+\n");
  printf("|1 : algorithme naif                       |\n");
  printf("|2 : algorithme circulaire                 |\n");
  printf("|3 : algorithme par couleur                |\n");
  printf("|4 : algorithme AVL                        |\n");
  printf("+------------------------------------------+\n");
 
  printf("\n");

  switch(num_algo)
    {

    case 1:
      printf("ALGO NAIF \n");
      printf("========= \n");
      RechercheCaseNaif_c(&G, 1, 0, 0, &nb1, &nb2);
      printf("<%d %d>\n", nb1, nb2);
  
  
      nb5=RechercheCaseNaif_nn(&G, 0, 0, &nb3, &nb4);
      printf("\n1ere case nn et piece nn : <%d %d>\ncpt : %d\n", nb3, nb4, nb5);

      printf("\n");
  
      /**** EXERCICE 1 : ALGO NAIF ****/
      algo_naif(&G, &S);
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  
      /*Après algo_naif, affichage de la grille sur le terminal*/
      affichage(G.m, G.n, G);

      /* Affiche le nombre de pas et le chemin */
      Affiche(&S);
      break;
      
      /***********************************/
      /**** EXERCICE 3 : ALGO COULEUR ****/
      /***********************************/
    case 3:
      printf("ALGO PAR COULEUR \n");
      printf("================ \n");
  
      LDCInitialise(&ldc);
      printf("\nliste vide : %d\n", LDCVide(&ldc));

      LDCInsererEnFin(&ldc, 3, 5);
      LDCInsererEnFin(&ldc, 4, 32);
      LDCInsererEnFin(&ldc, 9, 10);
      LDCInsererEnFin(&ldc, 51, 78);
  
      /*Affichage de la liste ldc */
      LDCafficher(&ldc);

      CelluleLDC *c1=LDCrechercherPlusProcheCase(&ldc, 50, 78);

      printf("case la p proche : %d %d\n", c1->i, c1->j);

      algo_parcouleur(&G, &S);

      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  
      /*Après algo_naif, affichage de la grille sur le terminal*/
      affichage(G.m, G.n, G);

      /* Affiche le nombre de pas et le chemin */
      Affiche(&S);

      
      break;
      
      return 0;
    }
}

   
