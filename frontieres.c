#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "structures.h"
#include "main.c"

#define MAX 100000   // on établie une majoration pour ne surcharger ni dépasser le programme





// on va lire un fichier avec les coordonnées (x,y) de points composant le polygone
// ce fichier comportera seulement deux colonnes (comme une matrice), qui définiront une liste enchaînée (chaque point sera relié aux suivant et définira en conséquence les côtés du polygone)

void initialize_polygone(Noeud *poly) // la fct malloc sert à allouer de l'espace, et void ne retourne aucun résultat
{
     // avec la flèche on accède à l'adresse
        poly->nbpoints = 0;
        poly->vert = NULL;
}


// on libère la mémoire pour ne la surcharger pas
void dispose_polygone(Noeud *poly)
{
        free(nbpoints);
        free(poly->vert);
}


void write_poly(Noeud *poly, const char* f)
{
     FILE *file = NULL;
     file = fopen(f,"w"); // write

	int i = 0;
	double x,y;

	while (i<=(poly->nbpoints))
	{
		x = poly->vert[i].x;
		y = poly->vert[i].y;
		fprintf(file, "%lf %lf\n",x,y);
		i++;
	}


	fclose(file);

}



void read_polygon(Noeud *poly, const char* f)
{
        FILE *file;
        file = fopen(f,"r");  // "r" = read file

        // compteurs basiques
        int i = 0;
        int j = 0;

        // compteur nb points du polygone
        int point = 0;
        double pointsx[MAX];
        double pointsy[MAX];




        // on lit d'abord le nb de points qui définiront le polygon et on les trie en deux tableaux
        while (i <= MAX)
        for (point=0; point<MAX; point++)
        {
               fscanf(file, "%lf %lf", &pointsx[point], &pointsy[point]);
        }

        poly->vert = malloc(sizeof(Vertex)*point); // la fct malloc sert à allouer de l'espace, et void ne retourne aucun résultat
        poly->nbpoints = point;
        poly->nbcotes = point;

        for (i=0; i<=point; i++)
        {
               poly->vert[i].x = pointsx[i];
               poly->vert[i].y = pointsy[i];
        }


        fclose(file);

}




int main(int argc, char **argv)
{
     Noeud poly;
     Vertex vert;

     initialize_polygon(&poly, f);
     read_polygon(&poly, argv[]);



}
