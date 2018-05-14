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

void RechercheCaseCirculaire_c3(Grille *G, int c, int i, int j, int *k, int *l){
	int n = G->n;
	int m= G->m;
	CCase **T=G->T;
	int L;

	for(L=0;L<m+n;L++){
		printf("0\n");
		int k1=i-L;
		int lg=j;
		int ld=j;
		for(k1;k1<=i;k1++){
			printf("1\n");
			/*printf("k1:%d,lg:%d\n",k1,lg);
			printf("k1:%d,ld:%d\n",k1,ld);*/
			if (exist(k1,lg,G) && (T[k1][lg].fond)==c){
				printf("1a\n");
				*k=k1;
				*l=lg;
				//printf("k:%d\n",*k);
				return;
			}
			lg=lg-1;
			if (exist(k1,ld,G) && (T[k1][ld].fond)==c){
				printf("1b\n");
				*k=k1;
				*l=ld;
				//printf("k:%d\n",*k);
				return;
				//L=distance(i,j,*k,*l);
			}
			ld=ld+1;
			
		}
		k1=i+1;
		lg=j-L+1;
		ld=j+L-1;
		for(k1;k1<=i+L;k1++){
			printf("2\n");
			/*printf("k2:%d,lg:%d\n",k1,lg);
			printf("k2:%d,ld:%d\n",k1,ld);*/
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
void  RechercheCaseCirculaire_c2(Grille *G,int c,int i,int j,int *k,int *l){
  int x=j,y=i;
  int L=0;
  int h=G->m;
  int w=G->n;
  int ind=0;
  for(ind=0;ind<h+w-1;ind++){
    int tete;
    L=ind;
    
    for(tete=y;tete>=y-L;tete-=1){
      int xl, xr;
      xl=x-(L-(y-tete));
      xr=x+(L-(y-tete));
      if(tete < 0)break;
            
      if(xl >= 0)
	if(G->T[tete][xl].fond == c && G->T[tete][xl].piece != c){
	  *k=tete;
	  *l=xl;
	  return;
	}
      if(xr < w)
	if(G->T[tete][xr].fond == c && G->T[tete][xr].piece != c){
	  *k=tete;
	  *l=xr;
	  return;
	}
      
    }

    int tail;
    for(tail=y;tail<=y+L;tail++){
      int xl,xr;
      xl=x-(L-(tail-y));
      xr=x+(L-(tail-y));
      if(tail >= h)break;
      
      
       if(xl >= 0)
	if(G->T[tail][xl].fond == c && G->T[tail][xl].piece != c){
	  *k=tail;
	  *l=xl;
	  return;
	}
       
       if(xr < w)
	 if(G->T[tail][xr].fond == c && G->T[tail][xr].piece != c){
	   *k=tail;
	   *l=xr;
	   return;
	 }
    }
    
  }
}

void RechercheCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l){
	//initialiser L à zéro ? i.e. considérer qu'on étudie la case de départ aussi ? 
	int L=0;  //la longueur du parcours entre (i,j) et les cases qu'on recherche
	int max=G->n+G->m;  //le chemin le plus long sera de (0,0) à (G->n,G->m), et avec l'algorithme optimisé, on sait qu'il sera de longueur n+m
	int b, lg, ld;

	//On lance le parcours circulaire jusqu'à trouver la première case qui correspond
	for(L; L<max; L++){ 
		b=i-L;    //initialisation des valeurs à étudier
		lg=j; 
		ld=j;
		while(b<=i){
			if(exist(b,lg,G)&&(!CaseEstNoire(G,b,lg))&&(G->T[b][lg].fond==c)){    //si la case est dans la grille, qu'elle n'est pas noire et est de couleur c
				*k=b;     //on met à jour k et l
				*l=lg;
				return;   //on interrompt ici la recherche
			}

			lg--;
			if(exist(b,ld,G)&&(!CaseEstNoire(G,b,ld))&&(G->T[b][ld].fond==c)){    //ad. lib.
				*k=b;
				*l=ld;
				return;
			}
			ld++;
			b++;
		}

		b=i+1;
		lg=j-L+1;
		ld=j+L-1;

		while(b<=i+L){
			if(exist(b,lg,G)&&(!CaseEstNoire(G,b,lg))&&(G->T[b][lg].fond==c)){    //si la case est dans la grille, qu'elle n'est pas noire et est de couleur c
				*k=b;     //on met à jour k et l
				*l=lg;
				return;   //on interrompt ici la recherche
			}
			lg++;
			if(exist(b,ld,G)&&(!CaseEstNoire(G,b,ld))&&(G->T[b][ld].fond==c)){    //ad. lib.
				*k=b;
				*l=ld;
				return;
			}
			ld--;
			b++;
		}
	}
	//Faire un return dans le cas où il n'y a pas de case de cette couleur ? Cas de figure impossible, non ?
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
			/*printf("1\n");
			printf("k1:%d,lg:%d\n",k1,lg);
			printf("k1:%d,ld:%d\n",k1,ld);*/
			
			
			if (exist(k1,lg,G) && !CaseEstNoire(G, k1, lg) && !(T[k1][lg].piece==-1)/*&& L>distance(i,j,k1,lg)*/){
				*k=k1;
				*l=lg;
				//printf("k:%d\n",*k);
				return;
			}
			lg=lg-1;
			if (exist(k1,ld,G) && !CaseEstNoire(G, k1, ld) && !(T[k1][ld].piece==-1)){
				*k=k1;
				*l=ld;
				//printf("k:%d\n",*k);
				return;
			}
			ld=ld+1;
			
			
		}
		k1=i+1;
		lg=j-L+1;
		ld=j+L-1;
		for(k1;k1<=i+L;k1++){
			/*printf("2\n");
			printf("k2:%d,lg:%d\n",k1,lg);
			printf("k2:%d,ld:%d\n",k1,ld);*/
			
			
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
	//Affiche(S);
	while(G->cptr_noire < (G->m*G->n) ){	//modif
		
		x=G->ir;
		y=G->jr;
		//Affiche(S);
		if(RobotPortePieceCouleur(G)==0){
			
			RechercheCaseCirculaire_nn(G, x, y, &k, &l);
			printf("%d %d",k,l);
			PlusCourtChemin(S, x, y, k, l); 
			changement_case(G, k, l);
			swap_case(G);
			Ajout_action(S,'S');	//modif (ajout)
			//Affiche(S);
		}else{

			//swap_case(G);
			c=(G->T[x][y]).robot;	//modif
			RechercheCaseCirculaire_c(G, c, x, y, &k, &l);
			PlusCourtChemin(S, x, y, k, l);
			changement_case(G,k,l);
			swap_case(G);
			Ajout_action(S,'S');	//modif
			//Affiche(S);
			
		}
		//AffGrille_redessine_case(&AG,&G,i,j);
		//AffGrille_reaffiche_Grille(); 
		
	}
}
	
	
