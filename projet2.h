//
// Created by victo on 08/12/2017.
//

#ifndef PROJET2_PROJET2_H
#define PROJET2_PROJET2_H
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define TAILLE_MAX 10000



typedef struct // structure des personnes
{
     char* nom;
     char* prenom;
     int salaire;
     int index;
}infoPersonne;

typedef struct  // sous-tableau de personne avec le mm index
{
    int tailletab;
    infoPersonne* tabInfo;
    int index_struct;


}classePerso;

typedef struct  // structure du tableau contenant les pointeurs vers les sous tableau
{
    int base;
    int taille;
    classePerso* tableauComplet;

}structComplet;

char* comparaison( char* chaine1, char* chaine2);

structComplet* initialisation(int taille, int base);

void permuter(infoPersonne * pers1,infoPersonne * pers2);

int index(infoPersonne* perso,int base, int taille);

unsigned long long int puissance(int N, unsigned long long int resultat, int puiss);

void tri(classePerso* sous_tableau);

bool ajouter(char* nom, char* prenom, int salaire,structComplet* structComplete);

bool charger(structComplet* structComplete,int nombre);

char* demande();
void viderBuffer(char* chaine);

void afficher_salaire(structComplet* structureComplete);

void afficher_entre(structComplet* all, int nbrcharg);

int nombre_conflit(structComplet* all);

double taille_conflit_moyen(structComplet* all);

bool supprimer(structComplet* all);

bool supprimer_entre(structComplet* all);

#endif //PROJET2_PROJET2_H
