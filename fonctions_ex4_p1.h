#include <math.h>


typedef struct abr{
  int nombre;
  int hauteur;
  
  struct abr *gauche;
  struct abr *droite;
}AVL;

int max(int a, int b);

int hauteur_avl(AVL *ab);

AVL *creer_avl(int nb, AVL *fg, AVL *fd);

void affichage_infixe(AVL *ab);



void supprimer_arbre(AVL *ab);

AVL *exist_avl(AVL *ab, int val);

AVL *rotation_droite(AVL *ab);

AVL *rotation_gauche(AVL *ab);

void MAJ_hauteur(AVL *ab);


AVL *inserer_element_avl(AVL *ab, int val);

void eq(AVL*ab);

AVL *supprimer_elmt_avl(AVL *ab, int value);





