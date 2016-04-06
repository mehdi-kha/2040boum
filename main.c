#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "deplacement.h" /*Contient les fonctions de deplacements qui sont assez longues*/
#include "affichage.h" /*Contient les fonctions d'affichage*/
#include "random.h" /*Contient les fonctions de génération de l'element aleatoire place aleatoirement*/
#include "bombe.h" /*Contient les fonctions d'explosion de bombe */

/*Définition du type s_tableau utilisé pour le tableau de jeu et le tableau de compteurs de bombes*/ 

struct s_tableau{
  int **t; /*On travaille avec un tableau d'int, les int négatifs sont réservés aux bombes*/
  int hauteur;
  int largeur;
};

typedef struct s_tableau tableau;

/*@requires: h et l positifs
@assigns: Un tableau de taille h*l entiers
@ensures: Définit un tableau de taille h*l */

tableau tabdef(int h, int l){
  tableau tab;
  tab.hauteur=h;
  tab.largeur=l;
  int k;
  tab.t=(int **)malloc(h*sizeof(int *));
  for (k=0;k<h;k=k+1){
    tab.t[k]=(int *)malloc(l*sizeof(int));
  }
  return tab;
}

/*@requires: t_bombe vaut 1 si le tableau initialisé n'est pas un tableau de bombes
@assigns:
@ensures: Met toutes les valeurs du tableau à 0 sauf pour une case déterminée aléatoirement */

void tabinit(tableau tab, int t_bombe){
  int i, j, randh, randl;
  for(i=0;i<tab.hauteur;i=i+1){
    for(j=0;j<tab.largeur;j=j+1){
      tab.t[i][j]=0;
    }
  }
  if(t_bombe==0){
    randh=aleainit(tab.hauteur); /*Utilisation de deux nombres aléatoires pour la ligne et la colonne qui contiendra le 1 de départ */
    randl=aleainit(tab.largeur);
    tab.t[randh][randl]=1;
  }
}
    

/*==============================================*/

int main(void){
  srand(time(NULL));
  int *max=malloc(sizeof(int)); /*Element de plus haute valeur contenu dans le tableau */
  tableau tjeu; /*Le tableau principal de jeu*/
  tableau tbombe; /*Le tableau contenant les compteurs des bombes*/
  int objectif; /*Utilisé pour stocker le score que le joueur souhaite atteindre*/
  int largeur; /*Utilisé pour stocker la largeur du tableau*/
  int hauteur; /*Utilisé pour stocker la hauteur du tableau*/
  char buffer2[2]; /*Utilisé pour stocker les caractères rentrés par l'utilisateur*/
  int ligne_b; /*Ligne des bombes sélectionnées*/
  int colonne_b; /*Colonne des bombes sélectionnées */
  *max=1; /*Le max vaut la valeur minimale au début du jeu */
  printf("Entrer le nombre de lignes du tableau puis appuyez sur \"Entree\" : ");
  scanf("%d",&hauteur);
  printf("Entrer le nombre de colonnes du tableau puis appuyez sur \"Entree\" : ");
  scanf("%d", &largeur);
  printf("Quel est votre objectif ?");
  scanf("%d",&objectif);
  tjeu=tabdef(hauteur,largeur); /*Definition du tableau avec les valeurs rentrees par l'utilisateur */
  tbombe=tabdef(hauteur,largeur); /*Definition du tableau des compteurs de bombes */
  tabinit(tjeu,0); /* Initialisation du tableau de jeu */
  tabinit(tbombe,1); /* Initialisation du tableau des compteurs de bombes */
  printf("Commandes: a chaque round vous sera demandee une direction puis une confirmation. Utilisez les fleches directionnelles representees par i, j, k ou l pour indiquer la direction. Pressez Entree puis confirmez en tapant \"y\" puis en pressant la touche Entree. \n");
  
  while(*max<objectif){ /*Cette boucle s'exécute tant que l'objectif n'est pas atteint. Cette boucle est finie car max augmente (ou stagne) à chaque round et une case est remplie aléatoirement à chaque round. Si le tableau est complètement rempli, on sort de la boucle */
    affichetab(tjeu,hauteur,largeur,-1,-1); /*Affichage du tableau de jeu. -1 par convention car il n'y a pas de bombe sélectionnée*/
    printf("Quelle est la nouvelle direction ou bombe ? Pour selectionner une bombe, entrez \'b\'\n");
    scanf("%1s",buffer2);
    if (buffer2[0]=='j'){ /*Déplacement à gauche sélectionné*/
	printf("Etes-vous sur de vouloir deplacer les elements a gauche (y/n) ?"); /*Demande de confirmation*/
	  scanf("%1s",buffer2);
	  if(buffer2[0]=='y'){	  
	    fleche('j'); /*Affichage d'une flèche indiquant la direction d'attraction*/
	    depgauche(tjeu,max,tbombe); /* Fonction de déplacement des tous les éléments du jeu à gauche */
 /* On applique aussi cette fonction au tableau des compteurs de bombes */
	    check_bombe(tbombe,tjeu); /*Incrémentation des chronos des bombes et explosion si fin de vie d'une bombe */
	    newelement(tjeu,max,tbombe); /*Apparition d'un nouvel élément en fin de round */
	  }
      }
      else if (buffer2[0]=='l'){ /*Déplacement à droite sélectionné*/
	printf("Etes-vous sur de vouloir deplacer les elements a droite (y/n) ?"); /*Demande de confirmation*/
	scanf("%1s",buffer2);
	if(buffer2[0]=='y'){	  
	  fleche('l');
	  depdroite(tjeu,max,tbombe);
	  check_bombe(tbombe,tjeu); /*Incrémentation des chronos des bombes et explosion si fin de vie d'une bombe*/
	  newelement(tjeu,max,tbombe);
	}
      }
      else if (buffer2[0]=='i'){ /*Déplacement en haut sélectionné*/
	printf("Etes-vous sur de vouloir deplacer les elements vers le haut (y/n) ?"); /*Demande de confirmation*/
	scanf("%1s",buffer2);
	if(buffer2[0]=='y'){	  
	  fleche('i');
	  dephaut(tjeu,max,tbombe);
	  check_bombe(tbombe,tjeu); /*Incrémentation des chronos des bombes et explosion si fin de vie d'une bombe*/
	  newelement(tjeu,max,tbombe);
	}
      }
      else if (buffer2[0]=='k'){ /*Déplacement en bas sélectionné*/
	printf("Etes-vous sur de vouloir deplacer les elements vers le bas (y/n) ?"); /*Demande de confirmation*/
	scanf("%1s",buffer2);
	if(buffer2[0]=='y'){	  
	  fleche('k');
	  depbas(tjeu,max,tbombe);
	  check_bombe(tbombe,tjeu); /*Incrémentation des chronos des bombes et explosion si fin de vie d'une bombe*/
	  newelement(tjeu,max,tbombe);
	}
      }
      else if (buffer2[0]=='b'){ /*Cas où une bombe a été sélectionnée */
	printf("Quelle est la ligne de la bombe a selectionner ? ");
	scanf("%i",&ligne_b);
	ligne_b=tjeu.hauteur-ligne_b; /*Affectation du numéro de ligne de la bombe sous forme d'indice de tableau*/
	printf("Quelle est la colonne de la bombe a selectionner ? ");
	scanf("%i",&colonne_b);
	colonne_b=colonne_b-1; /*Affectation du numéro de colonne de la bombe sous forme d'indice de tableau */
	if(tjeu.t[ligne_b][colonne_b]==-1 || tjeu.t[ligne_b][colonne_b]==-2 || tjeu.t[ligne_b][colonne_b]==-4 ){ /*On vérifie que l'objet sélectionné est bien une bombe avant de le faire exploser */
	  affichetab(tjeu,hauteur,largeur,ligne_b,colonne_b); /*Affichage du tableau avec la bombe sélectionnée soulignée de manière claire*/
	  /*Demandons ensuite confirmation avant l'explosion*/
	  printf("Etes-vous sur de vouloir faire exploser la bombe {%c} situee en (%i;%i) ? (y/n) ",correspondance(tjeu.t[ligne_b][colonne_b]),tjeu.hauteur-ligne_b,colonne_b+1); /*correspondance est une fonction qui traduit une bombe par un char*/
	  scanf("%1s",buffer2);
	  if(buffer2[0]=='y'){ /*S'il y a eu confirmation, l'explosion a lieu*/	  
	  explose(tjeu.t[ligne_b][colonne_b], tjeu, ligne_b, colonne_b);
	  }
	}
	else{
	  printf("L'element que vous avez choisi n'est pas une bombe, reessayez ! \n");
	}
      }
	
      else{ /*Cas où la commande rentrée par le joueur n'est pas conforme */
	printf("Vous avez du vous tromper dans la direction/selection de bombe, veuillez reessayer\n");
      }
    if(*max>=objectif){ /*Cas où l'objectif est atteint, fin du jeu*/
printf("Bravo, vous avez atteint votre objectif !\n");
}
    }
  return 0;
}
