#include <stdio.h>
#include <stdlib.h>

/*Définition du type s_tableau*/ 

struct s_tableau{
  int **t; /*On travaille avec un tableau d'int, les int négatifs sont réservés aux bombes*/
  int hauteur;
  int largeur;
};

typedef struct s_tableau tableau;

/*@requires:Un entier valant -1, -2 ou -4
@assigns:
@ensures: renvoie le caractère correspondant à la bombe*/

char correspondance(int bombe){
  char c;
  if(bombe==-1) c='+'; /*-1 est associé à la bombe + */
  else if(bombe==-2) c='x'; /*-2 est associé à la bombe x */
  else if(bombe==-4) c='*'; /*-4 est associé à la bombe * */
  else { /*Cas d'erreur */
    printf("Erreur: le numero de bombe envoye a la fonction correspondance est invalide\n");
  }
  return c;
}
  
  

/*====================Fonctions d'affichage====================*/
  

/*@requires: t ne doit comporter que des nombres à au plus 5 chiffres ou des bombes, colonne_b contient l'indice de la colonne de la bombe à souligner et doit donc être inférieur à l
@assigns:
@ensures: Affiche une ligne du tableau*/


void afficheligne(int *t, int l, int colonne_b){ /*Par convention colonne_b vaut -1 s'il n'y a aucune bome à souligner */
   int k;
  char c; /*Char utilisé pour l'affichage des bombes*/
  for (k=0;k<6*l+1;k=k+1){ /*On affichage la ligne de - du dessus*/
    printf("-");
  }
  printf("\n");
  for(k=0;k<l;k=k+1){ /*On laisse ensuite une ligne vide avec des séparateurs | */
    printf("|     ");
  }
  printf("|");
  printf("\n");
  for (k=0;k<l;k=k+1){ /*Affichage de la ligne comportant les nombres ou les bombes */
    printf("|");
    if(t[k]<0){ /*Cas où on doit afficher une bombe*/
      c=correspondance(t[k]);
      printf("  %c  ",c);
    }
    else{ /*Cas où on doit afficher un nombre*/
      if (t[k]!=0 && (t[k]-10)<0){ /*Nombre à 1 chiffre*/
	printf("  %i  ",t[k]);
      }
      else if(t[k]!=0 &&(t[k]-100<0)){ /*Nombre à 2 chiffres*/
	printf(" %i  ",t[k]);
      }
      else if(t[k]!=0 &&(t[k]-1000<0)){ /*Nombre à 3 chiffres*/
	printf(" %i ",t[k]);
      }
      else if(t[k]!=0 &&(t[k]-10000<0)){ /*Nombre à 4 chiffres*/
	printf("%i ",t[k]);
      }
      else if(t[k]!=0 &&(t[k]-100000<0)){ /*Nombre à 5 chiffres*/
	printf("%i",t[k]);
      }
      else { /*Cas de la case vide*/
	printf("     ");
      }
    }
  }
  printf("|");
  printf("\n");
  for(k=0;k<l;k=k+1){ /*On laisse ensuite une ligne vide avec des séparateurs | */
    if(k==colonne_b){ /*Correspond à la bombe qu'on souhaite souligner*/
      printf("|=====");
    }
    else printf("|     "); /*Les autres cases ne sont pas soulignées */
  }
  printf("|");
  printf("\n");
 }

/*@requires: ligne_b et colonne_b sont les indices de la ligne et de la colonne de la bombe sélectionnée et doivent donc nécessairemenet être inférieurs à h et l qui correspondent à la hauteur et à la largeur du tableau
@assigns:
@ensures: Affiche le tableau avec indication claire de la bombe sélectionnée si une bombe a été sélectionnée */

void affichetab(tableau tab, int h, int l, int ligne_b, int colonne_b){ /*Par convention on met -1 à ligne_b et colonne_b si il n'y a pas de bombe à afficher */
   int i;
   for(i=0;i<h;i=i+1){ /*On affiche chaque ligne l'une après l'autre*/
     if(i==ligne_b){ /*Si la ligne traitée est celle de la bombe*/
       afficheligne(tab.t[i], l, colonne_b);
     }
     else afficheligne(tab.t[i], l, -1);}
   for (i=0;i<6*l+1;i=i+1){ /*On met des - entre les lignes*/
       printf("-");
     }
   printf("\n");
 }

/*@requires: c doit valoir 'i' ou 'k' ou 'j' ou 'l' qui correspondent aux directions
@assigns:
@ensures: Affiche des flèches correspondant à la direction sélectionnée */

void fleche(char c){
  if (c=='i'){ /*HAUT*/
    printf("^^^^^\n");
    printf("|||||\n");
  }
  else if (c=='k'){ /*BAS*/
    printf("|||||\n");
    printf("vvvvv\n");
  }
  else if (c=='j'){ /*GAUCHE*/
    printf("<====\n");
    printf("<====\n");
    printf("<====\n");
  }
  else if (c=='l'){ /*DROITE*/
    printf("====>\n");
    printf("====>\n");
    printf("====>\n");
  }
  else printf("Le caractère envoyé à la fonction fleche n'est pas conforme\n");
}
