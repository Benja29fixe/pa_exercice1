/**************************/
/* structure celluleLDC ***/
/**************************/
typedef struct celluleLDC{
  int i;
  int j;
  struct celluleLDC *prec;
  struct celluleLDC *suiv; 
}CelluleLDC;

/**************************/
/* structure LDC **********/
/**************************/
typedef struct{
  struct celluleLDC *premier;
  struct celluleLDC *dernier;
}LDC;

/**************************/
/*                        */
/**************************/
CelluleLDC *creerCellule(int i ,int j);
// qui alloue et retourne une cellule

void LDCInitialise(LDC *ldc);
// qui initialise une liste

int LDCVide(LDC *ldc);
// qui teste si la liste est vide
/*
void LDCInsererEnFin(LDC *ldc,int i, int j); //qui insere une nouvelle cellule en fin

void LDC_enleverCellule(LDC *ldc ,CelluleLDC *cel);
// qui supprime une cellule a partir d un pointeur sur la cellule

void LDCafficher(LDC *ldc);
// un affichage en cas de besoin pour debugage

void LDCdesalloue(LDC *ldc);
// qui desalloue toute la liste (si elle n est pas vide a la fin)

*/