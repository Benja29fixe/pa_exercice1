#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "fonctions_ex4_p1.h"

/****************************
 * Maximum
 */ 
int max(int a, int b)
{
  if(a<b)
    return b;
  else
    return a;
}

/****************************
 * Hauteur d'un arbre avl
 */ 
int hauteur(AVL *ab)
{
  if(ab==NULL)
    return -1;
  else
    return 1+max(hauteur(ab->fg), hauteur(ab->fd));
}

/****************************
 * Creer arbre AVL
 */ 
AVL *creer(int val, AVL *gauche, AVL *droite)
{
  AVL *nv=(AVL*)malloc(sizeof(AVL));

  nv->content=val;
  nv->haut=0;
  nv->fg=gauche;
  nv->fd=droite;

  return nv;
}

/****************************
 * affichage infixe
 */ 
void afficher(AVL *ab)
{
  if(ab!=NULL)
    {
      afficher(ab->fg);
      printf("%d ", ab->content);
      afficher(ab->fd);
    }
}

/****************************
 * Supprimer arbre AVL
 */ 
void supprimer_arbre(AVL *ab)
{
  if(ab !=NULL){
    supprimer_arbre(ab->fg);
    supprimer_arbre(ab->fd);
    free(ab);
  }
}

/****************************
 * Rechercher une valeur dans un arbre AVL
 */ 
AVL *exist_avl(AVL *ab, int val)
{
  if(ab==NULL) return NULL;
  
  if(ab->content==val) return ab;

  if(val<ab->content) return exist_avl(ab->fg, val);

  if(val>ab->content) return exist_avl(ab->fd, val);

}

/****************************
 * Rotation droite
 */ 
AVL *rot_droite(AVL *ab)
{
  AVL *nv=ab->fg;
  ab->fg=nv->fd;
  nv->fd=ab;

  maj(ab);
  maj(nv);

  return nv;
}

/****************************
 * Rotation gauche
 */ 
AVL *rot_gauche(AVL *ab)
{
  AVL *nv=ab->fd;
  ab->fd=nv->fg;
  nv->fg=ab;

  maj(ab);
  maj(nv);

  return nv;
}

/****************************
 * Mise à jour hauteur arbre AVL 
 */ 
void maj(AVL *ab)
{
  if(ab!=NULL)
    {
      ab->haut=1+max(hauteur(ab->fg), hauteur(ab->fd));
    }
}

/****************************
 * Insérer élément dans un arbre avl
 */ 
AVL *inserer(AVL *ab, int val)
{
  if(ab==NULL)
    {
      return creer(val, NULL, NULL);
    }

  if(ab->content>val)
    {
      if(ab->fg==NULL)
        {
	  AVL *temp=creer(val, NULL, NULL);
	  ab->fg=temp;
        }
      else
        {
	  ab->fg=inserer(ab->fg, val);
        }
    }
  else
    {
      if(ab->fd==NULL)
        {
	  AVL *temp=creer(val, NULL, NULL);
	  ab->fd=temp;
        }
      else
        {
	  ab->fd=inserer(ab->fd, val);
        }
    }

  maj(ab);

  return ab;
}

/****************************
 * Equilibrage de l'arbre AVL
 */ 
AVL *eq(AVL *ab)
{
  int hfg=hauteur(ab->fg);
  int hfd=hauteur(ab->fd);

  if(hfg-hfd == 2)
    {
      ab=rot_droite(ab);
    }

  if(hfg-hfd==-2)
    {
      ab=rot_gauche(ab);
    }

  return ab;
}

/****************************
 * Insérer valeur dans arbre AVL et équilibrer
 */ 
AVL *ins(AVL *ab, int val)
{
  ab=eq(inserer(ab, val));

  return ab;
}

/****************************
 * Suprimer élément
 */ 
AVL *supprimer_elmt_avl(AVL *ab, int value)
{
  AVL *resultat=ab;

  if(ab->content<value){
    ab->fg=supprimer_elmt_avl(ab->fg, value);

  }else if(ab->content>value){
    ab->fd=supprimer_elmt_avl(ab->fd, value);

  }else{
    if(ab->fg==NULL){
      resultat=ab->fd;
      free(ab);
    }
  }
  return resultat;
}
	
