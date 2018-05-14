#include <math.h>

typedef struct arbre
{
    int content;
    int haut;
    struct arbre *fg;
    struct arbre *fd;
} AVL;

int max(int a, int b);

int hauteur(AVL *ab);

AVL *creer(int val, AVL *gauche, AVL *droite);

void afficher(AVL *ab);

void supprimer_arbre(AVL *ab);

AVL *exist_avl(AVL *ab, int val);

AVL *rot_droite(AVL *ab);

AVL *rot_gauche(AVL *ab);

void maj(AVL *ab);

AVL *inserer(AVL *ab, int val);

AVL *eq(AVL *ab);

AVL *ins(AVL *ab, int val);


AVL *supprimer_elmt_avl(AVL *ab, int value);





