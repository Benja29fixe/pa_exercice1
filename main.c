#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions.h"

 
int main(int argc,char**argv){
  
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i,j;
  int nb1;
  int nb2;
  int nb3;
  int nb4, nb5, nb6, nb7, nb8, nb9, nb10, nb11, nb12;

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

  /*premier affichage de la grille */
  
  affichage(G.m, G.n, G);

  
  
  /*
  printf("1/coordonnées de depart : ");
  scanf("%d %d", &nb1, &nb2);
   printf("coordonnées d'arrivee : ");
   scanf("%d %d", &nb3, &nb4);

  PlusCourtChemin(&S, nb1, nb2, nb3, nb4);

  Affiche(&S);
  */
  /*
   printf("2/ coordonnées pour verifier si case noire : ");
  scanf("%d %d", &nb5, &nb6);
  if(CaseEstNoire(&G, nb5, nb6)==1) {
    printf("Case NOIRE \n");
  }else{ printf("Case coloree!\n");
  }
  */
  /*
   printf("3/ coordonnées pour verifier si PIECE pas noire : ");
  scanf("%d %d", &nb7, &nb8);
  if(PieceEstPasNoire(&G, nb7, nb8)==1) {
    printf("Piece pas NOIRE \n");
  }else{
    printf("Piece noire!\n");
  }
  */
  
  /*  printf("4/ couleur à trouver la plus proche de (0,0) : ");
      scanf("%d", &nb11);*/
  
  RechercheCaseNaif_c(&G, 1, 0, 0, &nb9, &nb10);
  printf("\n\n<%d %d>\n", nb9, nb10);
  
  
  RechercheCaseNaif_nn(&G, 0, 0, &nb11, &nb12);
  printf("\n1ere case nn et piece nn : <%d %d>\n", nb11, nb12);
  
  
  return 0;
}
