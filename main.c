#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "structures.h"


#define NBMAX 100// ie nbmax sera le nb max de côtés qu'on donne à notre programme pour après obtenir un polygone aléatoire
#define MAX 1000 // nb qui définie la majoration de l'intervalle dans lequel on définit les nbs aléatoires



// à partir des structures définies dans le file structures.h on initialise le polygon comme suit:


void initialize_polygone(Noeud *poly)
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




// on définira un point extérerieur de coordonnées (xmax,ymax) à partir des points composant le polygone
int point_exterieur(Noeud *poly)
{
    int i = 0;
    int j = 0;
    double xmax;
    double ymax;


    // pour xmax
    for (j=0; j<(poly->nbpoints); j++)
    {
        double x0,x1;
        x0 = poly->vert[j].x;
        x1 = poly->vert[j+1].x;

        if (x0 < x1)
        {
            xmax = x1;
        }

        else
        {
            xmax = x0;
        }
    }

    // pour ymax
    for (i=0; i<(poly->nbpoints); i++)
    {
        double y0,y1;
        y0 = poly->vert[i].y;
        y1 = poly->vert[i+1].y;

        if (y0 < y1)
        {
            ymax = y1;
        }

        else
        {
            ymax = y0;
        }
    }


    // on définie le point extérieur comme
    Vertex pointext;

    pointext.x = xmax;
    pointext.y = ymax;


    return 0;

    // return pointext -> pointtest est crée

}


// vérifier si le droite l1 avec (xo1,yo1) comme pt de départ et (xf1,yf1) comme pt d'arrivée coupe la droite l2 avec (xo2,yo2) comme pt de départ et (xf2,yf2) comme pt d'arrivé
// si alpha1 et alpha2 sont valeurs y compris entre 0 et 1, les droites se coupent, en cas contraire delta vaut 0 et les droites ne se coupent pas

// la fct retourne 1 si les droites se coupent et 0 s'elles ne se coupent pas
int intersection_droites(Cotes l1, Cotes l2)
{
    //
    double delta, alpha1, alpha2;
    int r =0;

    // droite l1
    double xo1 = l1.pdepart.x;
    double yo1 = l1.pdepart.y;
    double xf1 = l1.parrive.x;
    double yf1 = l1.parrive.y;

    // droite l2
    double xo2 = l2.pdepart.x;
    double yo2 = l2.pdepart.y;
    double xf2 = l2.parrive.x;
    double yf2 = l2.parrive.y;

    // delta
    delta = (yf1 - yo1)*(xo2 - xf2) - (xf1 - xo1)*(yo2-yf2);

    // alpha


    if (fabs(delta) > 0.001)  // si delta différent de 0 (o très proche)
    {
        alpha1 = ((xf2 - xo2)*(yo1 - yo2) - (xo1 - xo2)*(yf2 - yo2)) / delta;
        alpha2 = ((xf1 - xo1)*(yo1 - yo2) - (xo1 - xo2)*(yf1 - yo1)) / delta;

        if (alpha1 >= 0 && alpha1 <= 1 && alpha2 >= 0 && alpha2 <= 1)
        {
            r = 1;
        }
    }

    return r;

}



//  on vérifie l'appartenance d'un pt à l'intérieur du polygone si en traçant une ligne dans n'importe quelle direction avec origine dans le point et longueur infini,
// le nb d'intersections avec les côtés du polygone est un numéro impair
//  comme on peut pas définir des droites de longueur infini, on supposera que pour vérifier si le point (xp,yp) est intérieur à un polygone, il faudrait vérifier combien de
// fois coupe la droite avec origine en (xp,yp)  et final en (xp+1000, yp) aux côtés du polygone


// la fct reçois comme argument la liste (de pts) qui répresente le polygone et une structure type point contenant (xp,yp)
int point_inside_polygon(Noeud *poly, Vertex pointtest)
{

    int i = 0;
    int j = 0;
    int cpt = 0; // compteur


    // on défini la droite test
    Cotes ltest;

    // je définie le point de depart de la droite test
    ltest.pdepart = pointtest;

    // je définie le point d'arrivée de la droite test comme suit:
    ltest.parrive = pointtest.x;
    ltest.parrive = pointtest.y + 1000;

    Noeud *p = poly;
    // Noeud p;
    // p = &poly;



    // on définie chaque droite composant le polygone
    Cotes droite;

    while (i<=nbpoints)
    {
        droite.pdepart.x = poly->vert[i].x;
        droite.pdepart.y = poly->vert[i].y;

        droite.parrive.x = poly->vert[i+1].x;
        droite.parrive.y = poly->vert[i+1].y;


        if (intersection_droites(droite,ltest))  // if (condicion) = 1 ie hay interseccion
        {
            cpt++;
        }

        i++;

    }


    if (cpt%2 == 1) // if cpt est impair
    {
        return 1;
        printf("Super! Le point de coordonnées %d %d appartient à l'intérieur du polygone", pointtest.x, pointtest.y);
    }
    else
    {
        return 0;
        printf("Malheureusement le point de coordonnées %d %d n'appartient pas à l'intérieur du polygone", pointtest.x, pointtest.y);
    }


}

int main(int argc, char **argv)
{
    int i,j = 0;
    int x,y = 0;
    int x0, y0 = 0;
    int nbmaxcotes = 0;
    int init = 0;


    Noeud poly;
    Vertex vert;
    Vertex pointtest;
    initialize_polygone(&poly);

    // on définie de forme aléatoire le polygone
    srand(time(NULL));

    nbmaxcotes = rand() % NBMAX;
    poly->nbcotes = nbmaxcotes;

    for (i=0; i<nbmaxcotes; i++)
    {
        x = rand() % MAX;
        poly->vert[i].x = x;
        y = rand() % MAX;
        poly->vert[i].y = y;
    }

    // on définie alétoirement le point à tester l'appartenance
    // Vertex *pointttest = NULL;
    x0 = rand() % MAX;
    pointtest.x = x0;
    y0 = rand() % MAX;
    pointtest.y = y0;


    // on commence la fct
    printf("\n\nBienvenue au programme: Vérifier appartennance du point au polygone\n\n");
    printf("\n Voulez-vous tester le programme? Tappe 1 en cas affirmative et sinon 0 en cas contraire\n");
    scanf("%d", &init);


    if (init = 1)
    {
        point_inside_polygon(&poly, &pointtest);
    }

    return 0;
}






