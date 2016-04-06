#include <stdio.h>
#include <stdlib.h>

struct s_tableau{
  int **t; /*On travaille avec un tableau d'int, les int négatifs sont réservés aux bombes*/
  int hauteur;
  int largeur;
};

typedef struct s_tableau tableau;

/*====================Gauche====================*/

/*@requires: 0<=i<nombre de lignes du tableau, et tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace à gauche et passe à la valeur supérieure si besoin tous les éléments de la ligne i du tableau tab et met à jour le tableau de compteurs de bombes*/

void depgauche1(tableau tab,int i,tableau tbombe){
  int j, k;
int bloque=-1; /*Indice du dernier element qui a ete multiplie par deux. Je garde en mémoire cet indice pour que cet element bloque ne soit pas a nouveau multiplie par deux si dans la suite des elements a traiter il y a un element ayant la valeur de bloque. */
 for(j=1;j<tab.largeur;j=j+1){ /*On parcourt l'ensemble des éléments de la ligne*/
    
    k=j; /*k temporaire utilisé pour le déplacement de l'élément colonne j sans changer le numéro de colonne étudié */
    if(tab.t[i][j]!=0){ /*Si il y a un élément, il peut subir des changements */
      while (k>0){ /*Boucle finie car dans tous les cas, soit k décroit à chaque tour de boucle, soit k prend la valeur 0*/
	if(tab.t[i][k-1]==0){ /*Cas où la case située à gauche est vide*/
	  tab.t[i][k-1]=tab.t[i][k]; /*Déplacement de l'élément étudié à gauche*/
	  tab.t[i][k]=0;
	  tbombe.t[i][k-1]=tbombe.t[i][k]; /*Le déplacement s'effectue aussi dans le tableau contenant les compteurs de bombes */
	  tbombe.t[i][k]=0;
	  k=k-1; /*On décrémente k pour mettre à jour la position de l'élément étudié pour le prochain tour de boucle */
	}
	else if(tab.t[i][k-1]==tab.t[i][k] && tab.t[i][k-1]!=0 && bloque!=(k-1)){ /*Cas où l'élément à gauche vaut l'élément étudié, et où cet élément de gauche n'est pas le résultat d'une multiplication par 2 antérieure*/
	  tab.t[i][k-1]=2*tab.t[i][k]; /*Multiplication par 2 de l'élément de gauche*/
	  tab.t[i][k]=0; /*Suppression de l'élément étudié*/
	  if (tab.t[i][k-1]==-8){ /*Cas où deux bombes * se choquent, il y a explosion*/
	    explose(-8, tab, i, k-1);
	    tbombe.t[i][k-1]=0;
	    tbombe.t[i][k]=0;
	    tbombe.t[i][k+1]=0; /*t[i][k+1] est l'élément à droite de la bombe qui vaudra 0 après avoir glissé puis explosé. Sans cette ligne, cet élément n'aura pas explosé alors qu'une étoile a explosé */
	  }
	  else if(tab.t[i][k-1]<0){
	    tbombe.t[i][k-1]=1; /*Si c'est un nouveau type de bombe, on doit réinitialiser le compteur*/
	    tbombe.t[i][k]=0;
	  }
	  bloque=k-1; /*On met à jour l'indice de l'élément le plus à droite multiplié par 2 */
	  k=0;
	}
	  else{
	  k=0;
	}
      }
    }
  }
}

/*@requires: tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace à gauche et passe à la valeur supérieure si besoin tous les éléments du tableau tab. Met à jour tbombe */

  void depgauche(tableau tab, int* max, tableau tbombe){
  int i;
  int j;
  for(i=0;i<tab.hauteur;i=i+1){/*Pour chaque ligne du tableau, on applique le déplacement*/
    depgauche1(tab,i,tbombe);
    for(j=0;j<tab.largeur;j=j+1){ /*Après déplacement, on met à jour la valeur du max si un élément de valeur supérieure est apparu*/
      if (tab.t[i][j]>*max){
	  *max=tab.t[i][j];
	}
    }
  }
}



/*====================Droite====================*/


/*@requires: 0<=i<nombre de lignes du tableau, et tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace à droite et passe à la valeur supérieure si besoin tous les éléments de la ligne i du tableau tab et met à jour le tableau de compteurs de bombes*/

void depdroite1(tableau tab,int i,tableau tbombe){ /*Fonctionne de manière analogue à depgauche1*/
  int j;
  int k;
int bloque=-1; /*Indice du dernier element qui a ete multiplie par deux. Je garde en mémoire cet indice pour que cet element bloque ne soit pas a nouveau multiplie par deux si dans la suite des elements a traiter il y a un element ayant la valeur de bloque. */
  for(j=(tab.largeur)-2;j>=0;j=j-1){
    k=j; /*k temporaire utilisé pour le déplacement de l'élément colonne j sans changer le numéro de colonne étudié */
    if(tab.t[i][j]!=0){
     
      while (k<(tab.largeur)-1){
	if(tab.t[i][k+1]==0){ /*Cas où la case à droite est vide*/
	  tab.t[i][k+1]=tab.t[i][k];
	  tab.t[i][k]=0;
	  tbombe.t[i][k+1]=tbombe.t[i][k];
	  tbombe.t[i][k]=0;
	  k=k+1;
	}
	else if(tab.t[i][k+1]==tab.t[i][k] && tab.t[i][k+1]!=0 && bloque!=(k+1)){ /*Cas où la case à droite vaut la case traitée*/
	  tab.t[i][k+1]=2*tab.t[i][k];
	  tab.t[i][k]=0;
	  if (tab.t[i][k-1]==-8){
	    explose(-8, tab, i, k-1);
	    tbombe.t[i][k+1]=0;
	    tbombe.t[i][k]=0;
	    tbombe.t[i][k-1]=0; /*C'est l'élément à gauche de la bombe qui vaudra 0 après avoir glissé puis explosé. Sans cette ligne, cet élément n'aura pas explosé alors qu'une étoile a explosé */
	  }
	  else if(tab.t[i][k+1]<0){
	    tbombe.t[i][k+1]=1; /*Si c'est un nouveau type de bombe, on doit réinitialiser le compteur*/
	    tbombe.t[i][k]=0;
	  }
	  bloque=k+1;
	  k=(tab.largeur)-1;
	}
	else{
	    k=(tab.largeur)-1;
	}
      }
    }
  }
}
      
/*@requires: tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace à droite et passe à la valeur supérieure si besoin tous les éléments du tableau tab. Met à jour tbombe */

  void depdroite(tableau tab, int* max, tableau tbombe){
  int i;
  int j;
  for(i=0;i<tab.hauteur;i=i+1){ /*Pour chaque ligne du tableau, on applique le déplacement*/
    depdroite1(tab,i,tbombe);
    for(j=0;j<tab.largeur;j=j+1){ /*Après déplacement, on met à jour la valeur du max si un élément de valeur supérieure est apparu*/
      if (tab.t[i][j]>*max){
	  *max=tab.t[i][j];
	}
    }
  }
}


/*====================Haut====================*/


/*@requires: 0<=j<nombre de colonnes du tableau, et tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace en haut et passe à la valeur supérieure si besoin tous les éléments de la colonne j du tableau tab et met à jour le tableau de compteurs de bombes*/


  void dephaut1(tableau tab,int j, tableau tbombe){ /*Fonctionne de manière analogue à depgauche1*/
  int i;
  int k;
int bloque=-1; /*Indice du dernier element qui a ete multiplie par deux. Je garde en mémoire cet indice pour que cet element bloque ne soit pas a nouveau multiplie par deux si dans la suite des elements a traiter il y a un element ayant la valeur de bloque. */
  for(i=1;i<tab.hauteur;i=i+1){
    
    k=i; /*k temporaire utilisé pour le déplacement de l'élément ligne i sans changer le numéro i de ligne étudié */
    if(tab.t[i][j]!=0){
    
      while (k>0){
	if(tab.t[k-1][j]==0){ /*Cas où la case du dessus est vide*/
	  tab.t[k-1][j]=tab.t[k][j];
	  tab.t[k][j]=0;
	  tbombe.t[k-1][j]=tbombe.t[k][j];
	  tbombe.t[k][j]=0;
	  k=k-1;
	}
	else if(tab.t[k-1][j]==tab.t[k][j] && tab.t[k-1][j]!=0 && bloque!=(k-1)){ /*Cas où la case en haut vaut la case traitée*/
	  tab.t[k-1][j]=2*tab.t[k][j];
	  tab.t[k][j]=0;
	  if (tab.t[k-1][j]==-8){
	    explose(-8, tab, i, k-1);
	    tbombe.t[k-1][j]=0;
	    tbombe.t[k][j]=0;
	    tbombe.t[k+1][j]=0; /*C'est l'élément en bas de la bombe qui vaudra 0 après avoir glissé puis explosé. Sans cette ligne, cet élément n'aura pas explosé alors qu'une étoile a explosé */
	  }
	  else if(tab.t[k-1][j]<0){
	    tbombe.t[k-1][j]=1; /*Si c'est un nouveau type de bombe, on doit réinitialiser le compteur*/
	    tbombe.t[k][j]=0;
	  }
	  bloque=k-1;
	  k=0;
	}
	else{
	    k=0;
	}
      }
    }
  }
}
      
/*@requires: tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace vers le haut et passe à la valeur supérieure si besoin tous les éléments du tableau tab. Met à jour tbombe */

  void dephaut(tableau tab, int* max, tableau tbombe){
  int j;
  int i;
  for(j=0;j<tab.largeur;j=j+1){ /*Pour chaque colonne du tableau, on applique le déplacement*/
    dephaut1(tab,j,tbombe);
    for(i=0;i<tab.hauteur;i=i+1){ /*Après déplacement, on met à jour la valeur du max si un élément de valeur supérieure est apparu*/
      if (tab.t[i][j]>*max){
	  *max=tab.t[i][j];
	}
    }
  }
}


/*====================Bas====================*/


/*@requires: 0<=j<nombre de colonnes du tableau, et tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace en bas et passe à la valeur supérieure si besoin tous les éléments de la colonne j du tableau tab et met à jour le tableau de compteurs de bombes*/

  void depbas1(tableau tab,int j,tableau tbombe){ /*Fonctionne de manière analogue à depgauche1*/
  int i;
  int k;
int bloque=-1; /*Indice du dernier element qui a ete multiplie par deux. Je garde en mémoire cet indice pour que cet element bloque ne soit pas a nouveau multiplie par deux si dans la suite des elements a traiter il y a un element ayant la valeur de bloque. */
  for(i=(tab.hauteur)-2;i>=0;i=i-1){
    
    k=i; /*k temporaire utilisé pour le déplacement de l'élément ligne i sans changer le numéro i de ligne étudié */
    if(tab.t[i][j]!=0){
    
      while (k<(tab.hauteur)-1){
	if(tab.t[k+1][j]==0){ /*Cas où la case à droite est vide*/
	  tab.t[k+1][j]=tab.t[k][j];
	  tab.t[k][j]=0;
	  tbombe.t[k+1][j]=tbombe.t[k][j];
	  tbombe.t[k][j]=0;
	  k=k+1;
	}
	else if(tab.t[k+1][j]==tab.t[k][j] && tab.t[k+1][j]!=0 && bloque!=(k+1)){ /*Cas où la case à droite vaut la case traitée*/
	  tab.t[k+1][j]=2*tab.t[k][j];
	  tab.t[k][j]=0;
	  if (tab.t[k+1][j]==-8){
	    explose(-8, tab, i, k-1);
	    tbombe.t[k+1][j]=0;
	    tbombe.t[k][j]=0;
	    tbombe.t[k-1][j]=0; /*C'est l'élément en haut de la bombe qui vaudra 0 après avoir glissé puis explosé. Sans cette ligne, cet élément n'aura pas explosé alors qu'une étoile a explosé */
	  }
	  else if(tab.t[k+1][j]<0){
	    tbombe.t[k+1][j]=1; /*Si c'est un nouveau type de bombe, on doit réinitialiser le compteur*/
	    tbombe.t[k][j]=0;
	  }
	  bloque=k+1;
	  k=(tab.hauteur)-1;
	}
	else{
	  	  k=(tab.hauteur)-1;
	}
      }
    }
  }
}


/*@requires: tbombe un tableau de compteurs de bombes
@assigns:
@ensures: Déplace vers le bas et passe à la valeur supérieure si besoin tous les éléments du tableau tab. Met à jour tbombe */

  void depbas(tableau tab, int* max, tableau tbombe){
  int j;
  int i;
  for(j=0;j<tab.largeur;j=j+1){ /*Pour chaque colonne du tableau, on applique le déplacement*/
    depbas1(tab,j,tbombe);
    for(i=0;i<tab.hauteur;i=i+1){ /*Après déplacement, on met à jour la valeur du max si un élément de valeur supérieure est apparu*/
      if (tab.t[i][j]>*max){
	  *max=tab.t[i][j];
	}
    }
  }
}
