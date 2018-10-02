//
// Created by victo on 08/12/2017.
//

#include "projet2.h"


structComplet* initialisation(int taille, int base)
{
    structComplet* structComplete=(structComplet*)malloc(sizeof(structComplete));
    structComplete->taille=taille;
    structComplete->base=base;
    structComplete->tableauComplet=(classePerso*)malloc(sizeof(classePerso)*taille);


    for(int i=0; i<taille;i++)
    {
        structComplete->tableauComplet[i].tabInfo=(infoPersonne*)malloc(sizeof(infoPersonne));

        structComplete->tableauComplet[i].tailletab=0;
        structComplete->tableauComplet[i].index_struct=i;
        structComplete->tableauComplet[i].tabInfo->prenom=(char*)malloc(sizeof(char*)*70);
        structComplete->tableauComplet[i].tabInfo->nom=(char*)malloc(sizeof(char*)*70);
        structComplete->tableauComplet[i].tabInfo->salaire=0;
        structComplete->tableauComplet[i].tabInfo->index=i;

    }
    return structComplete;

}


unsigned long long int puissance( int N,unsigned long long int resultat, int puiss)
{
    if (puiss==0)
    {
        return resultat ;
    }
    else
    {
        return puissance(N,resultat*N,puiss-1);
    }
}
int index(infoPersonne* perso,int base, int taille)
{
    char* nom2=perso->nom;
    char* prenom2=perso->prenom;
    int index=0;

   unsigned long long  int somme=0;
   if (strlen(nom2)>=4)
   {

       for (int index1 = 0; index1 < 6; index1++) {
           if (index1 < 4) {
               somme +=  (nom2[index1] * puissance(base, 1, index1));
           } else {
               somme +=  (prenom2[index1-4] * puissance(base, 1,index1));

           }
       }
   }
   else
   {
       for(int i=0; i<strlen(nom2)+2;i++)
       {
           if(i<strlen(nom2))
           {
               somme+=(nom2[i] * puissance(base, 1, i));
           }
           else
           {
               somme +=  (prenom2[i-strlen(nom2)] * puissance(base, 1,i));
           }
       }
   }
    index=(int)(somme%taille);

    return index;
}

char* comparaison(char* chaine1, char* chaine2)
{
    char* result=NULL;

    int i=0;
    while ((chaine1[i]!='\0')||(chaine2[i]!='\0'))
    {
        if ((int)chaine1[i]>(int)chaine2[i])
        {
            result=(char*)malloc(sizeof(char));
            result=chaine1;
            break;

        }
        if ((int)chaine1[i]<(int)chaine2[i])
        {
            result=(char*)malloc(sizeof(char));
            result=chaine2;
            break;
        }
        if((int)chaine1[i]==(int)chaine2[i])
        {
            i++;
        }
    }

    return result;
}
void permuter(infoPersonne * pers1,infoPersonne * pers2)
{
    infoPersonne * perstemp =(infoPersonne*)malloc(sizeof(infoPersonne));
    perstemp->nom=pers1->nom;
    perstemp->prenom=pers1->prenom;
    perstemp->salaire=pers1->salaire;

    pers1->nom=pers2->nom;
    pers1->prenom=pers2->prenom;
    pers1->salaire=pers2->salaire;

    pers2->salaire=perstemp->salaire;
    pers2->nom=perstemp->nom;
    pers2->prenom=perstemp->prenom;

}

void tri(classePerso* sous_tableau)
{
    char* test;
    bool tab_en_ordre=false;
    while(!tab_en_ordre)
    {
        tab_en_ordre=true;
        for( int i=0; i<sous_tableau->tailletab-1;i++)
        {
            test=comparaison(sous_tableau->tabInfo[i].nom,sous_tableau->tabInfo[i+1].nom);
            if (test==NULL)
            {
                test=comparaison(sous_tableau->tabInfo[i].prenom,sous_tableau->tabInfo[i+1].prenom);
                if(test==NULL)
                {
                    printf("Doublon:%s %s\n",sous_tableau->tabInfo[i].nom, sous_tableau->tabInfo[i].prenom);
                }
                else
                {
                    if(test==(sous_tableau->tabInfo[i].prenom))
                    {
                        permuter(&(sous_tableau->tabInfo[i]),&(sous_tableau->tabInfo[i+1]));
                        tab_en_ordre=false;
                    }
                }
            }
            else
            {
                if (test == (sous_tableau->tabInfo[i].nom))
                {
                    permuter(&(sous_tableau->tabInfo[i]), &(sous_tableau->tabInfo[i + 1]));
                    tab_en_ordre=false;
                }
            }
        }
    }
}



bool ajouter(char* nom_new, char* prenom_new, int salaire_new,structComplet* structureComplete)
{

    bool result;
    infoPersonne* new1=(infoPersonne*)malloc(sizeof(infoPersonne));
    new1->nom=nom_new;

    new1->prenom=prenom_new;
    new1->salaire=salaire_new;
    new1->index=index(new1,structureComplete->base,structureComplete->taille);




    int new_taille=structureComplete->tableauComplet->tailletab;
    for(int i=0; i<structureComplete->taille;i++)
    {
        if(structureComplete->tableauComplet[i].index_struct==new1->index)
        {

            if(structureComplete->tableauComplet[i].tailletab!=0)
            {

                new_taille++;
                infoPersonne *new = (infoPersonne *) malloc(new_taille * sizeof(infoPersonne));
                for (int j = 0; j < new_taille - 1; j++) {
                    new[j].prenom = structureComplete->tableauComplet[i].tabInfo[j].prenom;
                    new[j].nom = structureComplete->tableauComplet[i].tabInfo[j].nom;
                    new[j].salaire = structureComplete->tableauComplet[i].tabInfo[j].salaire;
                    new[j].index = new1->index;

                }

                new[new_taille - 1].prenom = prenom_new;
                new[new_taille - 1].nom = nom_new;
                new[new_taille - 1].salaire = salaire_new;
                structureComplete->tableauComplet[i].tailletab = new_taille;
                structureComplete->tableauComplet[i].tabInfo = new;
                tri(&(structureComplete->tableauComplet[i]));
                break;
            }
            else
            {
                structureComplete->tableauComplet[i].tabInfo=(infoPersonne*)malloc(sizeof(classePerso));
                structureComplete->tableauComplet[i].tabInfo->index=new1->index;
                structureComplete->tableauComplet[i].tabInfo->salaire=new1->salaire;
                structureComplete->tableauComplet[i].tabInfo->nom=new1->nom;
                structureComplete->tableauComplet[i].tabInfo->prenom=new1->prenom;
                structureComplete->tableauComplet[i].tailletab=1;
                tri(&(structureComplete->tableauComplet[i]));
                break;

            }



        }

    }


    if (structureComplete->tableauComplet!=NULL)
    {
        result=true;
    }
    return result;
}

bool charger(structComplet* structComplete, int nombre)
{

    FILE * fichier=NULL;
    char line [TAILLE_MAX]="";

    fichier=fopen("C:\\Users\\victo\\Documents\\ESILV\\A3\\C\\PROJET2\\Chicago.txt","r");
    long int max;
    int i=0;



    while((fgets(line,TAILLE_MAX,fichier)!=NULL)&&(i<nombre))
    {
        char* nom=(char*)malloc(sizeof(char)*128);
        char* prenom=(char*)malloc(sizeof(char)*128);
        int salaire=0;
        fscanf(fichier,"%s %s %d",nom,prenom,&salaire);
        //printf("%s, %s,%d \n",nom, prenom, salaire);
        ajouter(nom,prenom,salaire,structComplete);
        i++;
    }
    return true;

}
char* demande()
{

    char* chaine=(char*)malloc(sizeof(char)*128);

    scanf("%s",chaine);
    return chaine;
}

void viderBuffer(char* chaine)
{
    chaine=NULL;
    free(chaine);
    int c;
    do
    {
            c = getchar();
    } while (c != EOF && c != '\n');
}

void afficher_salaire(structComplet* structureComplete) {
    printf("Nom?\n");
    char *nom = demande();
    viderBuffer(nom);
    printf("Prenom?\n");
    char *prenom = demande();
    viderBuffer(prenom);
    infoPersonne *perso = (infoPersonne *) malloc(sizeof(infoPersonne));
    perso->prenom = prenom;
    perso->nom = nom;
    perso->index = index(perso, structureComplete->base, structureComplete->taille);
    for (int i = 0; i < structureComplete->taille; i++) {

        if (structureComplete->tableauComplet[i].index_struct == perso->index) {

            for (int j = 0; j < structureComplete->tableauComplet[i].tailletab; j++) {
                printf("tpd");
                if (perso->nom == structureComplete->tableauComplet[i].tabInfo[j].nom) {
                    printf("tpd2");
                    while (perso->prenom != structureComplete->tableauComplet[i].tabInfo[j].prenom) {
                        j++;
                    }
                    printf("%d", structureComplete->tableauComplet[i].tabInfo[j].salaire);


                }
            }
        }
    }
}


/*void menu(structComplet * all)
{
    int choix;
    printf("____________MENU___________\n \n");
    printf("1. Consulter un salaire.\n");
    printf("2.Ajouter un fonctionnaire.\n");
    printf("3.Afficher entre deux index.  \n");
    printf("4.Nombre de conflits. \n");
    printf("5.Taille moyenne des conflits. \n");
    printf("6.Supprimer un fonctionnaire. \n");
    printf("7.Supprimer entre deux index.  \n");
    printf("8.Quitter \n \n");
    scanf("%d",choix);

    if(choix == 1)
    {
        printf("Fonction non viable, se référer au compte-rendus");
        //afficher_salaire(all);
        menu(all);
    }
    if(choix == 2)
    {
        printf("Nom?\n");
        char *nom = demande();
        viderBuffer(nom);
        printf("Prenom?\n");
        char *prenom = demande();
        viderBuffer(prenom);
        printf("Salaire?\n");
        int *salaire = (int *) malloc(sizeof(int));
        scanf("%d", salaire);

        ajouter(nom,prenom,*salaire,all);
        menu(all);
    }
    if (choix == 3)
    {
       // afficher_entre(all,nbrcharg);
        menu(all);
    }
    if (choix == 4)
    {
        nombre_conflit(all);
        menu(all);
    }
    if (choix == 5)
    {
        taille_conflit_moyen(all);
        menu(all);
    }
    if (choix == 6)
    {
        supprimer(all);
        menu(all);
    }
    if (choix == 7 )
    {
        supprimer_entre(all);
        menu(all);
    }if (choix == 8 )
    {
        printf("vous avez quitté");
    }
}*/

void afficher_entre(structComplet* all, int nbrcharg)
{
    if (nbrcharg<=100) {
        printf("entre quels indexes voulez vous afficher ?");
        printf("tapez l'index de debut");
        int *debut = (int *) malloc(sizeof(int));
        scanf("%d", debut);
        printf("tapez l'index de sortie");
        int *fin = (int *) malloc(sizeof(int));
        scanf("%d", fin);
        for (*debut; *debut < *fin; (*debut)++) {
            printf("Indice :%d \n", *debut);
            for (int i = 0; i < all->tableauComplet[*debut].tailletab; i++) {

                printf("%s ", all->tableauComplet[*debut].tabInfo[i].nom);
                printf("%s ", all->tableauComplet[*debut].tabInfo[i].prenom);
                printf("%d ", all->tableauComplet[*debut].tabInfo[i].salaire);
                printf("\n");
            }
            printf("\n");
        }
    }else
    {
        printf("Affichage impossible, se referer au compte-rendu");
    }
}


bool supprimer(structComplet* all)
{
    bool verif=false;

    printf("Nom?\n");
    char *nom = demande();
    viderBuffer(nom);
    printf("Prenom?\n");
    char *prenom = demande();
    viderBuffer(prenom);
    infoPersonne *perso = (infoPersonne *) malloc(sizeof(infoPersonne));
    perso->prenom = prenom;
    perso->nom = nom;
    perso->index = index(perso, all->base, all->taille);
    for(int i=0;i<all->taille;i++)
    {
        if(all->tableauComplet[i].index_struct==perso->index) {
            if (all->tableauComplet[i].tailletab != 0) {

                int new_taille = all->tableauComplet[i].tailletab - 1;
                infoPersonne *new = (infoPersonne *) malloc(new_taille * sizeof(infoPersonne));
                for (int j = 0; j < new_taille; j++) {
                    if ((all->tableauComplet[i].tabInfo[j].prenom != perso->prenom) &&
                        (all->tableauComplet[i].tabInfo[j].nom != perso->nom)) {
                        new[j].prenom = all->tableauComplet[i].tabInfo[j].prenom;
                        new[j].nom = all->tableauComplet[i].tabInfo[j].nom;
                        new[j].salaire = all->tableauComplet[i].tabInfo[j].salaire;
                        new[j].index = perso->index;
                    }

                }
                all->tableauComplet[i].tailletab = new_taille;
                all->tableauComplet[i].tabInfo = new;
                verif=true;

            }
        }
    }
    return verif;
}
int nombre_conflit(structComplet* all)
{

    int result=0;
    for (int i=0;i<all->taille;i++)
    {
        if(all->tableauComplet[i].tailletab>1)
        {
            (result)++;
        }

    }
    return result;
}
double taille_conflit_moyen(structComplet* all)
{
    int result=0;
    for(int i=0;i<all->taille;i++)
    {
        if (all->tableauComplet[i].tailletab>1)
        {
            result+=all->tableauComplet[i].tailletab;
        }

    }
    return (double)(result/nombre_conflit(all));
}
bool supprimer_entre(structComplet* all)
{
    bool verif=false;
    printf("entre quels indexes voulez vous supprimer ?");
    printf("tapez l'index de debut");
    int *debut = (int *) malloc(sizeof(int));
    scanf("%d", debut);
    printf("tapez l'index de sortie");
    int *fin = (int *) malloc(sizeof(int));
    scanf("%d", fin);
    for (*debut; *debut < (*fin)+1; (*debut)++)
    {
        for(int i=0; i<all->tableauComplet[*debut].tailletab;i++)
        {
            all->tableauComplet[*debut].tabInfo[i].nom="";
            all->tableauComplet[*debut].tabInfo[i].prenom="";
            all->tableauComplet[*debut].tabInfo[i].salaire=0;
            verif=true;
        }
    }
    return verif;

}

void programme_general()
{

}

