#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex2_p1.h"

int exist(int i, int j, Grille *G){
  if (i<0 || i>=(G->m) || j<0 || j>=(G->n)){
    return 0;
  }
  return 1;
}

void RechercheCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l){
  int n = G->n;
  int m= G->m;
  CCase **T=G->T;
  int L;

  for(L=0;L<m+n;L++){
    int k1=i-L;
    int lg=j;
    int ld=j;
    
    for(k1;k1<=i;k1++){
      if (exist(k1,lg,G) && (T[k1][lg].fond)==c){
	*k=k1;
	*l=lg;
	return;
      }
      lg=lg-1;
      
      if (exist(k1,ld,G) && (T[k1][ld].fond)==c){
	*k=k1;
	*l=ld;
	return;
      }
      ld=ld+1;
			
    }
    k1=i+1;
    lg=j-L+1;
    ld=j+L-1;
    for(k1;k1<=i+L;k1++){
		
      if (exist(k1,lg,G) && (T[k1][lg].fond)==c ){
	*k=k1;
	*l=lg;
	return ;
      }
      lg=lg+1;
      if (exist(k1,ld,G) && (T[k1][ld].fond)==c){
	*k=k1;
	*l=ld;
				
	return ;
      }
      ld=ld-1;			
    }
  }		
}	



void RechercheCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l){
  int n = G->n;
  int m= G->m;
  CCase **T=G->T;
  int L;

  for(L=0;L<m+n;L++){
    int k1=i-L;
    int lg=j;
    int ld=j;
    
    for(k1;k1<=i;k1++){
		
      if (exist(k1,lg,G) && !CaseEstNoire(G, k1, lg) && !(T[k1][lg].piece==-1)){
	*k=k1;
	*l=lg;
			
	return;
      }
      lg=lg-1;
      if (exist(k1,ld,G) && !CaseEstNoire(G, k1, ld) && !(T[k1][ld].piece==-1)){
	*k=k1;
	*l=ld;
			
	return;
      }
      ld=ld+1;
			
    }
    k1=i+1;
    lg=j-L+1;
    ld=j+L-1;
    for(k1;k1<=i+L;k1++){
			
      if (exist(k1,lg,G) && !CaseEstNoire(G, k1, lg) && !(T[k1][lg].piece==-1)){
	*k=k1;
	*l=lg;
	return ;
      }
      lg=lg+1;
      if (exist(k1,ld,G) && !CaseEstNoire(G, k1, ld) && !(T[k1][ld].piece==-1)){
	*k=k1;
	*l=ld;
	return ;
			 	
      }
      ld=ld-1;
    }
  }
		
}	


void algorithme_circulaire(Grille *G, Solution *S){
	int x;
	int y;
	int k,l,c;

	while(G->cptr_noire < (G->m*G->n) ){
		x=G->ir;
		y=G->jr;

		if(RobotPortePieceCouleur(G)==0){
			RechercheCaseCirculaire_nn(G, x, y, &k, &l);
			printf("%d %d",k,l);
			PlusCourtChemin(S, x, y, k, l); 
			changement_case(G, k, l);
			swap_case(G);
			Ajout_action(S,'S');	
		
		}else{
			c=(G->T[x][y]).robot;	
			RechercheCaseCirculaire_c(G, c, x, y, &k, &l);
			PlusCourtChemin(S, x, y, k, l);
			changement_case(G,k,l);
			swap_case(G);
			Ajout_action(S,'S');
		
			
		}
	
		
	}
}
	
