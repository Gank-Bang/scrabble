#include "./scrabble.h"
char tabdico[SIZEDICO][26];
char Plateau[COTE_CASES][COTE_CASES];
Point LettrePlacer[175];
int indice_lettre_placer = 0;
int main(void)

	{
	char pioche[103];
    sprintf(pioche, "__eeeeeeeeeeeeeeeaaaaaaaaaiiiiiiiinnnnnnoooooorrrrrrssssssttttttuuuuuullllldddmmmggbbccppffhhvvjqkwxyz");
	int n_pioche_restant = 102, i;
	int j_to_play = 0;
	char letter_to_points[2][27] = {{0}, {0,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,4,4,4,8,8,10,10,10,10,10}};
	sprintf(letter_to_points[0], "_einorstuldmgbcpfhvjqkwxyz");
	Joueur joueurs[N_JOUEURS];
	for(i=0;i<N_JOUEURS;i++)
	    {
	    joueurs[i].points = 0;
	    joueurs[i].lettres_restantes = 0;
	    joueurs[i].action_choisie = 0;
	    printf("Entrer le nom de joueur %d\n",i+1);
	    scanf("%s", joueurs[i].name);
	    }
	affichage();
	actualiser();
	Joueur actuel;
	while(n_pioche_restant>0)
	    {
		actualiser();
	    actuel = joueurs[j_to_play];
	    printf("nombre de jetons restants dans la pioche: %d\n", n_pioche_restant);
        n_pioche_restant = distribution(actuel.lettres_restantes, n_pioche_restant, actuel.board, pioche);
        printf("Vous, %s, avez maintenant: %s\n", actuel.name, actuel.board);
		joueur_joue(actuel);
        j_to_play = (j_to_play+1)%N_JOUEURS;
	    printf("Etat de la pioche: %s\n", pioche);
		actualiser();
        }

	attendre_clic();
	fermer_fenetre();
    return 0;
	}


/*
char * int_to_str(int x)
	{
	char [4];
	i = 1000;
	while (i != 0):
		char[x/i + 
		i\=10;
	}


*/










int distribution(int jetons_joueur_restant, int n_pioche_restant, char board_joueur[8], char pioche[102])
	{
	int i = 0, indice_char_tire;
	srand(time(NULL));
	while (n_pioche_restant > 0 && (jetons_joueur_restant+i)<=7)
	    {
	    do 
	        {
		    indice_char_tire = rand()%101;
	        //printf("%c\n", pioche[indice_char_tire]);
		    }
	    while (pioche[indice_char_tire] == ' ');
	    //printf("%c\n", pioche[indice_char_tire]);
	    board_joueur[jetons_joueur_restant-1+i] = pioche[indice_char_tire];
	    pioche[indice_char_tire] = ' ';
	    n_pioche_restant -= 1;
	    i++;
	    }
	return n_pioche_restant;
	}

//int compte_des_points();



















int chargeDico(char *filedico)
{
    FILE *f = fopen(filedico,"r"); // ouverture du fichier

    if (!f) // si ouverture ratée
        {
        fprintf(stderr,"fopen: problème d'ouverture du fichier '%s'\n'",filedico);
        return 0;
        }

    char line[MAXLENMOT]; // la ligne servant à la lecture du fichier

    int mots=0; // indice dans tabdico
    while(fgets(line,MAXLENMOT,f)) // tant que fgets ne renvoie pas nul (eof)
        {
        sscanf(line,"%s\n",tabdico[mots]); // je scanne line et écris dans tabdico
        mots++;
        }
    fclose(f); // fermeture du fichier

    return mots;
}















int is_mot_in_dico(char mot[MAXLENMOT])
	{
	int debut=0, fin=TAILLE_DICO-1, milieu, orientation, nb_comparaison=0;
	char mot_trouve = 0;
	while(!mot_trouve && debut<=fin)
		{
		milieu = (fin+debut)/2;
		printf("case %d: %s\n", milieu, tabdico[milieu]);
		orientation = strcmp(mot, tabdico[milieu]);
		if (orientation == 0)
			mot_trouve = 1;
		else if (orientation > 0)
			debut = milieu+1;
		else
			fin = milieu-1;
		nb_comparaison++;
		}
	if (mot_trouve)
	    {
		printf("le mot %s est bien un mot du dictionnaire\n", mot);
        return 1;
        }
	else
	    {
		printf("le mot %s n'est pas un mot du dictionnaire\n", mot);
		return 0;
		}
	}


















int mots_tab_existe(char tab_mots[8][MAXLENMOT])
    {
    int i = 0, ts_mots_existent = 1;
    while(tab_mots[i][0] != 0 && ts_mots_existent == 1)
        {
        printf("test pour mot %s\n", tab_mots[i]);
        ts_mots_existent = is_mot_in_dico(tab_mots[i]);
        i++;
        }
    if (ts_mots_existent == 0)
        return 0;
    else
        return 1;
    }
















//PARTIE GRAPHIQUE :

void affichage() //Fonction qui ouvre une fenetre graphique et affiche le tableau.[
{
	ouvrir_fenetre(RESX, RESY);
	
	Point k = {DEBUT_BOARD_X-5, DEBUT_BOARD_Y-5},l = {1200,650},m = {1245,680},coin = {DEBUT_PLATEAU_X,DEBUT_PLATEAU_Y};

	dessiner_rectangle(k, 353, 59, blanc);
	afficher_image("projet.bmp",coin);
	dessiner_rectangle(l,235,115,gris);
	afficher_texte("Validez",40,m,blanc);
	

}//]




void afficher_board(char board[7]) //Fonction d'affichage de la main du joueur.[ 
	{
	char path_to_file[6];
	sprintf(path_to_file, "$.bmp");
	Point a = {DEBUT_BOARD_X, DEBUT_BOARD_Y};
	int i;
	for(i=0;i<7;i++)
		{
		path_to_file[0] = board[i];
		afficher_image(path_to_file, a);
		printf("%s\n", path_to_file);
		a.x += TAILLE_JETON;
		}
	actualiser();
	}//]

void joueur_joue(Joueur j) // Action du joueur [
    {
	Point prenom = {80,50},p1 = {-500,-500};
	afficher_texte(j.name,50,prenom,blanc);
	afficher_board(j.board);
    //char action_finished = 0;
    Point p = {-500, -500}, p2,precP;
    char is_lettre_selectionnee = 0;
    Point tableau_des_points_selectionnes[7];
    int tableau_des_points_selectionnes_indice_actuel = 0, tour = 1,raz,cassepaslescouilles=indice_lettre_placer;
    char mot_crees[8][COTE_CASES];
    char lettres_placees[COTE_CASES][COTE_CASES] = {{0}};
    int indice_du_board_selectionne;
    char fichier[6];
    int c, l;
	sprintf(fichier, "$.bmp");
	Point test_point = {DEBUT_PLATEAU_X+PLATEAU_TAILLE + 100, DEBUT_PLATEAU_Y};
    dessiner_rectangle(test_point, 20, 20, red);
    actualiser(); // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa
    /*while (action_finished == 0)
        {*/
        while (1)// (!(p dans la zone du bouton repioche) && !(p dans la zone du bouton validate et mots existent et contient au moins 2 lettres))
            {
            while (is_lettre_selectionnee == 0)
            	{
		        p = attendre_clic();
				Point x = {p.x,p.y};
			
				for(raz=0;raz<8;raz++)
					tableau_des_points_selectionnes[raz]=p1;
				for(raz=cassepaslescouilles;raz<indice_lettre_placer;raz++)
					LettrePlacer[raz]=p1;
					
				if(p.x>1200 && p.x<1435 && p.y>650 && p.y<765)
					{					
					for(raz=0;raz<8;raz++)
						tableau_des_points_selectionnes[raz]=p1;
					for(raz=cassepaslescouilles;raz<indice_lettre_placer;raz++)
						LettrePlacer[raz]=p1;
					RetourArriere(p,j);
					}
				

							
					
				if (((p.x < DEBUT_BOARD_X) || (p.x > DEBUT_BOARD_X+7*TAILLE_JETON)) || ((p.y < DEBUT_BOARD_Y) || (p.y > DEBUT_BOARD_Y+TAILLE_JETON)) || point_in_board(p,tableau_des_points_selectionnes))
		        	printf("Vous n'avez pas selectionner un jeton\n");
		        else
					
		        	{
		        	indice_du_board_selectionne = (p.x - DEBUT_BOARD_X) / TAILLE_JETON;
		        	is_lettre_selectionnee = 1;
		        	}
            	}
            p.x = ((p.x - DEBUT_BOARD_X) / TAILLE_JETON) * TAILLE_JETON + DEBUT_BOARD_X;
        	p.y = ((p.y - DEBUT_BOARD_Y) / TAILLE_JETON) * TAILLE_JETON + DEBUT_BOARD_Y;
           	dessiner_rectangle(p, TAILLE_JETON, TAILLE_JETON, blanc);
           	tableau_des_points_selectionnes[tableau_des_points_selectionnes_indice_actuel] = p;
           	tableau_des_points_selectionnes_indice_actuel++;
           	actualiser();
            
            printf("la lettre selectionnée est %c\n", j.board[indice_du_board_selectionne]);
            do
            	{
            	printf("Selectionnez une case voisine\n");
            	p2 = attendre_clic();            	
            	// TESTING
				printf("%d, %d\n", (((p2.x - DEBUT_PLATEAU_X) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_X)+1, (((p2.y - DEBUT_PLATEAU_Y) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_Y)+1);
				printf("precedent %d, %d\n", precP.x, precP.y);
		        }
		   	while(p2.x < DEBUT_PLATEAU_X || p2.y < DEBUT_PLATEAU_Y || p2.x > DEBUT_PLATEAU_X+PLATEAU_TAILLE || p2.y > DEBUT_PLATEAU_Y+PLATEAU_TAILLE || point_in_plateau(p2, LettrePlacer));
			c = (p2.x - DEBUT_PLATEAU_X) / TAILLE_CASE;
			l = (p2.y - DEBUT_PLATEAU_Y) / TAILLE_CASE;
			
			//TEST : printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA: %d,%d\n", c, l);

			lettres_placees[l][c] = j.board[indice_du_board_selectionne];
			p2.x = (((p2.x - DEBUT_PLATEAU_X) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_X);
			p2.y = (((p2.y - DEBUT_PLATEAU_Y) / TAILLE_CASE) * TAILLE_CASE + DEBUT_PLATEAU_Y);
			LettrePlacer[indice_lettre_placer]=p2;
			indice_lettre_placer++;
			p2.x++;
			p2.y++;			
			is_lettre_selectionnee = 0;
			fichier[0] = j.board[indice_du_board_selectionne];
			afficher_image(fichier, p2);
			actualiser();
			tour++;
			precP.x = p2.x;
			precP.y = p2.y;
			if (mots_crees(mots_crees, lettres_placees))
				dessiner_rectangle(test_point, 20, 20, green);
			else
				dessiner_rectangle(test_point, 20, 20, red);
			actualiser();
		}
        /*if p dans la zone du bouton repioche
            {
            //printf("Le joueur %s repioche", j.name)
            // repioche --> distribution(jeton_joueur_restant = 0)
            //j.action_choisie = REPIOCHE
            }
        int i;
        else  // p dans la zone du bouton validate et mots existent et contient plus de 2 lettres
            {
            printf("le joueur %s a fait les mots:\n", j.name)
            while(i < 8 && strcmp(mot_crees[i], "") == 0)
                {
                printf("%s, ", mot_crees[i])
                i++;
                }
            j.action_choisie = PLACE_UN_MOT
            }
        */
     }


char point_in_board(Point p, Point tab[7])
	{
	char is_in = 0;
	int i = 0;
	while (i < 7 && is_in == 0)
		{
		if (p.x > tab[i].x && p.x < tab[i].x+TAILLE_JETON && p.y > DEBUT_BOARD_Y && p.y < DEBUT_BOARD_Y+49)
			is_in = 1;
		i++;
		}
	return is_in;
	}




char point_in_plateau(Point p, Point tab[175])
	{
	char is_in = 0;
	int i = 0;
	while (i < 175 && is_in == 0)
		{
		if (p.x > tab[i].x && p.x < tab[i].x+TAILLE_CASE && p.y > tab[i].y && p.y < tab[i].y+TAILLE_CASE)
			is_in = 1;
		i++;
		}
	return is_in;
	}










int RetourArriere (Point p2,Joueur j)
	{
	Point coin = {DEBUT_PLATEAU_X,DEBUT_PLATEAU_Y};
	int i=0;
	if(p2.x>1200 && p2.x<1435 && p2.y>650 && p2.y<765)
		{	
		afficher_image("projet.bmp",coin);
		afficher_board(j.board);
		return 1;
		}
	else
		i++;
		return 0;
	}
		








































char mots_crees(char mot_crees[8][COTE_CASES], char lettres_placees[COTE_CASES][COTE_CASES])
	{
	int i, j, k, ii, iii=0;
	int tab_pos_lettre_composant_mot_principal[6][2] = {{0}};
	int indice_tab_pos_lettre_composant_mot_principal = 0;
	char mot_principal_cree[COTE_CASES] = {{0}};
	char mot_already_created = 0;
	char works = 1;
	char boolean;
	for(i=0;i<COTE_CASES;i++)
		{
		for(j=0;j<COTE_CASES;j++)
			{
			for(ii=0;ii<7;ii++)
				{
				if (tab_pos_lettre_composant_mot_principal[ii][0] == i && tab_pos_lettre_composant_mot_principal[ii][1] == j)
					{
					// TEST : printf("%d,%d is part of a much bigger scheme\n", i, j);
					boolean = 1;
					}
				}
			// TEST : printf("at (%d,%d), lettre : %c\n", i, j, lettres_placees[i][j]);
			if (lettres_placees[i][j] != 0 && boolean == 0)
				{
				if (mot_already_created)
					works = 0;	

				k = 1;
				mot_already_created = 1;
				mot_principal_cree[0] = lettres_placees[i][j];

				if (lettres_placees[i+1][j] != 0)
					{
					printf("mot colonne\n");
					while (lettres_placees[i+k][j] != 0) // otre cond?
						{
						mot_principal_cree[k] = lettres_placees[i+k][j];
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][0] = i+k;
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][1] = j;
						k++;
						indice_tab_pos_lettre_composant_mot_principal++;
						}
					}
				else if (lettres_placees[i][j+1] != 0)
					{
					printf("mot colonne\n");
					while (lettres_placees[i][j+k] != 0) // otre cond?
						{
						mot_principal_cree[k] = lettres_placees[i][j+k];
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][0] = i;
						tab_pos_lettre_composant_mot_principal[indice_tab_pos_lettre_composant_mot_principal][1] = j+k;
						k++;
						indice_tab_pos_lettre_composant_mot_principal++;
						}
					}
				else
					printf("Le mot principal créé contient une lettre: %c\n", lettres_placees[i][j]);
				}

			boolean = 0;
			}
		}
	printf("Lettre chainées créées: ");
	while (iii < COTE_CASES && mot_principal_cree[iii] != 0)
		{
		//mot_crees[0][iii] = mot_principal_cree[iii];
		printf("%c", mot_principal_cree[iii]);
		iii++;
		}

	printf("\nworks? : %d\n", works);
	return works;
	}

/*
void reset_double_tab(char *tab, int ls, int cs)
	{
	int i, j;
	char[ls][cs] = &tab;
	for(i=0;i<ls;i++)
		for(j=0;j<cs;j++)
			&tab[i][j] = 0;
	}
*/
