#include <stdio.h>
#include <stdlib.h>

/*Définition du type s_tableau*/ 

struct s_tableau{
  int **t; /*On travaille avec un tableau d'int, les int négatifs sont réservés aux bombes*/
  int hauteur;
  int largeur;
};

typedef struct s_tableau tableau;

/*@requires: Une case correspondant bien à une bombe (ligne i et colonne j)
@assigns:
@ensures: Fait exploser les bonnes cases du tableau*/

void explose(int bombe, tableau tab, int i, int j){ /*On cherche quel type de bombe est traité puis on procède aux explosions selon le type */
  if(bombe==-1){ /*Cas d'une bombe + */
    tab.t[i][j]=0;
    if(i!=0)tab.t[i-1][j]=0;
    if(i!=tab.hauteur-1)tab.t[i+1][j]=0;
    if(j!=0)tab.t[i][j-1]=0;
    if(j!=tab.largeur-1)tab.t[i][j+1]=0;
  }
  else if(bombe==-2){ /*Cas d'une bombe x */
    tab.t[i][j]=0;
    if(i!=0)tab.t[i-1][j-1]=0;
    if(i!=0 && j!=tab.largeur-1)tab.t[i-1][j+1]=0;
    if(i!=tab.hauteur-1 && j!=0)tab.t[i+1][j-1]=0;
    if(i!=tab.hauteur-1 && j!=tab.largeur-1)tab.t[i+1][j+1]=0;
  }
  else if(bombe=-4){ /*Cas d'une bombe * */
    tab.t[i][j]=0;
    if(i!=0)tab.t[i-1][j-1]=0;
    if(i!=0 && j!=tab.largeur-1)tab.t[i-1][j+1]=0;
    if(i!=tab.hauteur-1 && j!=0)tab.t[i+1][j-1]=0;
    if(i!=tab.hauteur-1 && j!=tab.largeur-1)tab.t[i+1][j+1]=0;
    if(i!=0)tab.t[i-1][j]=0;
    if(i!=tab.hauteur-1)tab.t[i+1][j]=0;
    if(j!=0)tab.t[i][j-1]=0;
    if(j!=tab.largeur-1)tab.t[i][j+1]=0;
    
  }

}

/*@requires: tbombe est un tableau de compteurs de bombes et tjeu est un tableau de jeu
@assigns:
@ensures: Incrémente tous les compteurs de bombe et fait exploser une bombe en fin de vie */

void check_bombe(tableau tbombe, tableau tjeu){
  int i,j;
  for (i=0;i<tbombe.hauteur;i=i+1){ /* Incrémentation de 1 de tous les éléments du tableau de bombes car on considère le round fini */
    for (j=0;j<tbombe.largeur;j=j+1){
      if (tbombe.t[i][j]!=0){
	tbombe.t[i][j]=tbombe.t[i][j]+1;
      }
      if (tbombe.t[i][j]==8){ /* Explosion si un compteur est à 8 car au bout de 8 rounds les bombes explosent automatiquement */
	explose(tjeu.t[i][j], tjeu, i, j);
	tbombe.t[i][j]=0;
      }
    }
  }
}
    
