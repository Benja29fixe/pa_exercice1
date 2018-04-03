#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex4_p1.h"

/* Maximum */
int max(int a, int b)
{
  if(a<b){
    return b;
  }else{
    return a;
  }
}

/* Hauteur d'un arbre AVL */
int hauteur_avl(AVL *ab)
{
  if(ab==NULL){
    return -1;
  }else{
  return 1+max(hauteur_avl(ab->gauche), hauteur_avl(ab->droite));
  }
}

/* Création d'un AVL */
AVL *creer_avl(int nb, AVL *fg, AVL *fd)
{
  AVL *nv=(AVL*)malloc(sizeof(AVL));
  
  if(nv==NULL){
    printf("Probleme d'allocation.\n");
    return NULL;
  }

  nv->nombre=nb;
  nv->hauteur=1+max(hauteur_avl(fg), hauteur_avl(fd));

  nv->gauche=fg;
  nv->droite=fd;

  return nv;
}

/* Affichage des nombres parcours infixe */
void affichage_infixe(AVL *ab)
{
  
  if(ab != NULL){
    affichage_infixe(ab->gauche);
    printf("%d ", ab->nombre);
    affichage_infixe(ab->droite);
  }

}



/* Supprimer un arbre AVL */
void supprimer_arbre(AVL *ab)
{
  if(ab !=NULL){
    supprimer_arbre(ab->gauche);
    supprimer_arbre(ab->droite);
    free(ab);
  }
}

/* Rechercher une valeur dans un arbre AVL */
AVL *exist_avl(AVL *ab, int val)
{
  if(ab==NULL) return NULL;
  
  if(ab->nombre==val) return ab;

  if(val<ab->nombre) return exist_avl(ab->gauche, val);

  if(val>ab->nombre) return exist_avl(ab->droite, val);

}

/* Equilibrage et rotation à droite */
AVL *rotation_droite(AVL *ab)
{
  AVL *nab=ab->gauche;
  ab->gauche=nab->droite;
  nab->droite=ab;

  MAJ_hauteur(ab);
  MAJ_hauteur(nab);

  return nab;
}

/* Equilibrage et rotation à droite */
AVL *rotation_gauche(AVL *ab)
{
  AVL *nab=ab->droite;
  ab->droite=nab->gauche;
  nab->gauche=ab;

  MAJ_hauteur(ab);
  MAJ_hauteur(nab);

  return nab;
}

/* Mise à jour hauteur */
void MAJ_hauteur(AVL *ab)
{
  if(ab !=NULL){
    ab->hauteur=1+max(hauteur_avl(ab->gauche), hauteur_avl(ab->droite));
  }
}

/* Inserer élément avl */
AVL *inserer_element_avl(AVL *ab, int val)
{   
  if(ab == NULL) {
    return creer_avl(val, NULL, NULL);
  }
    
  if (ab->nombre > val) {
    if(ab->gauche==NULL){
      AVL *nv=creer_avl(val, NULL, NULL);
      ab->gauche=nv;
    } else {
      inserer_element_avl(ab->gauche, val);
    }
    
  } else {
    if(ab->droite==NULL){
      AVL *nv=creer_avl(val, NULL, NULL);
      ab->droite=nv;
    } else {
      inserer_element_avl(ab->droite, val);
    }
  }

  //MAJ HAUTEUR
  MAJ_hauteur(ab);

  //EQUILIBRAGE DE L'ARBRE
  eq(ab);
 
  return ab;  
}

/* Fonction d'équilibrage de l'arbre */
void eq(AVL*ab)
{
  int hgauche=hauteur_avl(ab->gauche);
  int hdroite=hauteur_avl(ab->droite);

  if(hgauche-hdroite == 2){
    if (hauteur_avl(ab->gauche->gauche)<hauteur_avl(ab->gauche->droite))
      rotation_gauche(ab->gauche);
    rotation_droite(ab);

  }else{
    if(hgauche-hdroite==-2){
      if(hauteur_avl(ab->droite->droite)<hauteur_avl(ab->droite->gauche))
	rotation_droite(ab->droite);
      rotation_gauche(ab);
    }
  }
}

AVL *supprimer_elmt_avl(AVL *ab, int value)
{
  AVL *resultat=ab;

  if(ab->nombre<value){
    ab->gauche=supprimer_elmt_avl(ab->gauche, value);

  }else if(ab->nombre>value){
    ab->droite=supprimer_elmt_avl(ab->droite, value);

  }else{
    if(ab->gauche==NULL){
      resultat=ab->droite;
      free(ab);
    }
  }
  return resultat;
}
	
