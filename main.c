 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex1_p1.h"
#include "fonctions_ex2_p1.h"
#include "fonctions_ex3_p1.h"
#include "fonctions_ex4_p1.h"

int main(int argc,char**argv){
  
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i,j, m;
  int num_algo;
  int nb1, nb2, nb3, nb4, nb5;
  LDC ldc;
  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu;
  FILE *f1, *f3;
  

  /* les différents arguments */
  
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

  /* Premier affichage de la grille sur le terminal*/
  affichage(G.m, G.n, G);

  /* Les 4 algorithmes de la partie 1 */
  printf("+---Choix de l'algorithme------------------+\n");
  printf("|1 : algorithme naif                       |\n");
  printf("|2 : algorithme circulaire                 |\n");
  printf("|3 : algorithme par couleur                |\n");
  printf("|4 : algorithme AVL                        |\n");
  printf("+------------------------------------------+\n");
 
  printf("\n");

  switch(num_algo)
    {

      /*****************************************/
      /**** EXERCICE 1 : ALGO NAIF *************/
      /*****************************************/
    case 1:
      printf("ALGO NAIF \n");
      printf("========= \n");

       /*******************************/
      f1=fopen("temps/algo_naif.temps", "a");
      /*******************************/
      /* Execution de l'algorithme naif */
       /*******************************/
      temps_initial=clock();
      /*******************************/
      algo_naif(&G, &S);
      /*******************************/
      temps_final=clock();
      temps_cpu =((double)(temps_final-temps_initial))/ CLOCKS_PER_SEC;
      fprintf(f1, "%d %d %d %f\n", G.m, G.n, G.nbcoul, temps_cpu);
      fclose(f1);
      /*******************************/
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  
      /* Après algo_naif, affichage de la grille sur le terminal */
      affichage(G.m, G.n, G);

      /* Affiche le nombre de pas et le chemin */
      Affiche(&S);
      break;

      /*****************************************/
      /**** EXERCICE 2 : ALGO CIRCULAIRE *******/
      /*****************************************/
    case 2:
      printf("ALGO CIRCULAIRE \n");
      printf("=============== \n");
     
      algorithme_circulaire(&G, &S);
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  
      /* Après algo circulaire, affichage de la grille sur le terminal */
      affichage(G.m, G.n, G);

      /* Affiche le nombre de pas et le chemin */
      Affiche(&S);

      break;
      
      /*****************************************/
      /**** EXERCICE 3 : ALGO COULEUR **********/
      /*****************************************/
    case 3:
      printf("ALGO PAR COULEUR \n");
      printf("================ \n");
  
      LDCInitialise(&ldc);

       /*******************************/
      f3=fopen("temps/algo_couleur.temps", "a");
      /*******************************/
      /* Execution de l'algorithme par couleur */
       /*******************************/
      temps_initial=clock();
      /*******************************/
      algo_parcouleur(&G, &S);
       /*******************************/
      temps_final=clock();
      temps_cpu =((double)(temps_final-temps_initial))/ CLOCKS_PER_SEC;
      fprintf(f3, "%d %d %d %f\n", G.m, G.n, G.nbcoul, temps_cpu);
      fclose(f3);
      /*******************************/

      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
  
      /*Après algo_parcouleur, affichage de la grille sur le terminal*/
      affichage(G.m, G.n, G);

      /* Affiche le nombre de pas et le chemin */
      Affiche(&S);
      
      break;

      /*****************************************/
      /**** EXERCICE 4 : ALGO AVL ***************/
      /******************************************/
    case 4:

      printf("-----------------------\n");
      printf("Test fonctions AVL\n");
      printf("==================\n");
      
     AVL *a1=creer(10, creer(9, NULL, NULL), creer(23, NULL,NULL));
    printf("\n");
    
    afficher(a1);
    printf("\nHauteur : %d >>> fg>[%d] fd>[%d] // %d \n", a1->haut, hauteur(a1->fg), hauteur(a1->fd), a1->content);


   
    srand(time(NULL));
    for(m=0; m<10; m++){
      a1=ins(a1, rand()%100);
      afficher(a1);
      printf("\nHauteur arbre: [%d] /hauteur->fg=%d / hauteur->fd=%d / racine : [%d] \n\n", a1->haut, hauteur(a1->fg), hauteur(a1->fd), a1->content);
    }

    
      printf("\n-----------------------\n");
	     
      break;
      
      return 0;
    }
}

   
