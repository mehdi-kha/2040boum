#include <stdlib.h>
#include <stdio.h>

/*Définition du type tableau*/ 

struct s_tableau{
  int **t; /*On travaille avec un tableau d'int, les int négatifs sont réservés aux bombes*/
  int hauteur;
  int largeur;
};

typedef struct s_tableau tableau;

/*====================Fonction de placement aléatoire du nouveau numéro====================*/

/*@requires: a non nul et positif
@assigns:
@ensures: Renvoie un nombre aléatoire compris entre 0 et a-1*/

int aleainit(int a){
  int nb_alea;
  nb_alea=rand()%a;
  return (nb_alea);
}

/*@requires: 
@assigns: Un entier
@ensures: Retourne la valeur de l'objet à placer en fin de round */

int aleaobj(int* max){
  int nb_alea=rand()%100;
  if (*max<64){ /*Cas où le nombre maximal dans le tableau est inférieur à 64*/
    return 1;
  }
  if (64<=*max && *max<256){ /*Cas où le nombre maximal dans le tableau est contenu entre 64 et 256 */
    if (nb_alea<20){ /* 20% de chance que 2 apparaisse */
      return 2;
    }
    else if(nb_alea<30){ /* 10% de chance que la bombe + apparaisse */
      return -1; /*-1 est associé à la bombe + */
    }
    else {
      return 1; /* 70% de chance que 1 apparaisse */
    }
  }
  else{              /*Autres cas*/
    if(nb_alea<25){ /* 25% de chance que 2 apparaisse */
      return 2;
    }
    else if(nb_alea<35){ /* 10% de chance que la bombe + apparaisse */
      return -1;
    }
    else if(nb_alea<40){ /* 5% de chance que la bombe x apparaisse */
      return -2;
    }
    else{ /* 60% de chance que 1 apparaisse */
      return 1;
    }
  }
}

/*@requires:
@assigns: Un entier
@ensures: Retourne 1 si il y a une place de vide et 0 sinon */

int vacuite(tableau tab){
  int i,j,k;
  k=0;
   for (i=0;i<tab.hauteur;i=i+1){
      for (j=0;j<tab.largeur;j=j+1){
	if (tab.t[i][j]==0){
	  k=1;
	}
      }
  }
   return k;
}

/*@requires:tab est le tableau de jeu et tbombe le tableau de compteurs de bombes
@assigns:
 @ensures: Place aléatoirement l'élément à placer en fin de round */

void newelement(tableau tab, int* max, tableau tbombe){
  int i,j,nb,randh,randl; /*Compteurs utiles après*/
  if (vacuite(tab)==1){ /*On vérifie d'abord qu'il y a une case vide */
    nb=aleaobj(max); /*nb est l'objet aléatoire qui va être placé */
    randh=aleainit(tab.hauteur); /*Choix aléatoire d'une case dans le tableau */
    randl=aleainit(tab.largeur);
    if (tab.t[randh][randl]==0){ /*Si la case choisie est vide, c'est bon on peut placer l'element */
      tab.t[randh][randl]=nb;
      if(nb<0){ /*Cas où c'est une bombe que l'on place, on ajoute un compteur à 1 */
	tbombe.t[randh][randl]=1;
    }
    }
	  
    else{ /*Si la case choisie aléatoirement est pleine, on réitère l'opération de sélection aléatoire d'une case, puisqu'on sait qu'au moins une case est vide */
      newelement(tab,max,tbombe);  
    }
  }
  else{ /*Si aucune case n'est vide, c'est pourquoi la boucle while de la fonction main dans main.c se termine si le tableau est complet*/
    printf("GAME OVER, dommage ! Retentez votre chance !\n");
    exit(0);
 
  }
}
