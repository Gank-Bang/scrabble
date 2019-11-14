#include<stdio.h>
#include "../lib/libgraphique.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define N_JOUEURS 2
#define FILEDICO "../dictionnaire_fr_ss_accents" // chemin du fichier dico
#define SIZEDICO 319000                         // taille large du dico
#define MAXMOTSCREES 8                          // nb maximum de mots crées 
#define MAXLENMOT 15 		                  // taille du mot max
#define TAILLE_DICO 318897
#define DEBUT_PLATEAU_X 375
#define DEBUT_PLATEAU_Y 25
#define DEBUT_BOARD_X 575
#define DEBUT_BOARD_Y 800
#define TAILLE_JETON 49
#define TAILLE_CASE 50
#define PLATEAU_TAILLE 750
#define RESX 1500
#define RESY 900
#define COTE_CASES 15

enum{REPIOCHE, PLACE_UN_MOT};

typedef struct {
    char name[30];
    char board[7];
    int points;
    int lettres_restantes;
    int action_choisie;
} Joueur;

void affichage();
void afficher_board(char board[7]);
void joueur_joue(Joueur);
char point_in_board(Point p, Point tab[7]);
char point_in_plateau(Point p, Point tab[175]);
int RetourArriere (Point p2,Joueur j);

char mots_crees(char mot_crees[8][COTE_CASES], char lettres_placees[COTE_CASES][COTE_CASES]);                                  
int chargeDico(char *filedico);
int is_mot_in_dico(char mot[MAXLENMOT]); 
int mots_tab_existe(char tab_mots[MAXMOTSCREES][MAXLENMOT]); // renvoie 1 si tous les mots font parti du dictionnaire
int distribution(int, int, char board_joueur[8], char pioche[103]);
char * int_to_str(int x);
Joueur action(Joueur j);
char mots_crees(char mot_crees[8][COTE_CASES], char lettres_placees[COTE_CASES][COTE_CASES]);

