
void affichage(int ligne, int colonne, Grille G);

void PlusCourtChemin(Solution* S, int i, int j, int k, int l);

int CaseEstNoire(Grille* G,int i,int j);

int PieceEstPasNoire(Grille* G,int i, int j);

int RobotPortePieceCouleur(Grille* G);

int CouleurPorteeParRobot(Grille *G);

void RechercheCaseNaif_c(Grille *G,int c,int i, int j, int *k, int *l);

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

