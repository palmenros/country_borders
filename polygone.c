#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"

// à partir des structures définies dans le file structures.h on initialise le polygon comme suit:

void initialize_polygone(Polygone *poly, int nbpoints) {
    // avec la flèche on accède à l'adresse
    poly->nbpoints = nbpoints;
    poly->vert = malloc(sizeof(Vertex) * nbpoints);
}

// on libère la mémoire pour ne la surcharger pas
void dispose_polygone(Polygone *poly) {
    free(poly->vert);
}

void write_poly(Polygone *poly, const char *f) {
    FILE *file = NULL;
    int i = 0;
    double x, y;

    file = fopen(f, "w"); // write

    while (i < poly->nbpoints) {
        x = poly->vert[i].x;
        y = poly->vert[i].y;
        fprintf(file, "%lf,%lf\n", x, y);
        i++;
    }

    fclose(file);
}

// on définira un point extérerieur de coordonnées (xmax,ymax) à partir des points composant le polygone
void point_exterieur(Polygone *poly, Vertex *pointext) {
    int i = 0;
    double xmax = -INFINITY, ymax = -INFINITY;

    // pour xmax
    for (i = 0; i < (poly->nbpoints); i++) {
        double x, y;
        x = poly->vert[i].x;
        y = poly->vert[i].y;

        if (x > xmax) {
            xmax = x;
        }

        if (y > ymax) {
            ymax = y;
        }
    }

    pointext->x = xmax;
    pointext->y = ymax;
}


// vérifier si le droite l1 avec (xo1,yo1) comme pt de départ et (xf1,yf1) comme pt d'arrivée coupe la droite l2 avec (xo2,yo2) comme pt de départ et (xf2,yf2) comme pt d'arrivé
// si alpha1 et alpha2 sont valeurs y compris entre 0 et 1, les droites se coupent, en cas contraire delta vaut 0 et les droites ne se coupent pas

// la fct retourne 1 si les droites se coupent et 0 s'elles ne se coupent pas
int intersection_droites(Cotes *l1, Cotes *l2) {
    double delta, alpha1, alpha2;
    int r = 0;

    // droite l1
    double xo1 = l1->pdepart.x;
    double yo1 = l1->pdepart.y;
    double xf1 = l1->parrive.x;
    double yf1 = l1->parrive.y;

    // droite l2
    double xo2 = l2->pdepart.x;
    double yo2 = l2->pdepart.y;
    double xf2 = l2->parrive.x;
    double yf2 = l2->parrive.y;

    // delta
    delta = (yf1 - yo1) * (xo2 - xf2) - (xf1 - xo1) * (yo2 - yf2);

    // alpha

    if (fabs(delta) > 0.001)  // si delta différent de 0 (o très proche)
    {
        alpha1 = ((xf2 - xo2) * (yo1 - yo2) - (xo1 - xo2) * (yf2 - yo2)) / delta;
        alpha2 = ((xf1 - xo1) * (yo1 - yo2) - (xo1 - xo2) * (yf1 - yo1)) / delta;

        if (alpha1 >= 0 && alpha1 <= 1 && alpha2 >= 0 && alpha2 <= 1) {
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

int is_point_inside_polygon(Polygone *poly, Vertex *pointtest) {

    int i = 0;
    int j = 0;
    int cpt = 0; // compteur

    // on défini la poly_cote test
    Cotes ltest;

    // je définie le point de depart de la poly_cote test
    ltest.pdepart.x = pointtest->x;
    ltest.pdepart.y = pointtest->y;

    point_exterieur(poly, &ltest.parrive);
    ltest.parrive.y += 10;

    // on définie chaque cote composant le polygone
    Cotes poly_cote;

    while (i < poly->nbpoints) {
        poly_cote.pdepart.x = poly->vert[i].x;
        poly_cote.pdepart.y = poly->vert[i].y;

        if (i == poly->nbpoints - 1) {
            poly_cote.parrive.x = poly->vert[0].x;
            poly_cote.parrive.y = poly->vert[0].y;
        } else {
            poly_cote.parrive.x = poly->vert[i + 1].x;
            poly_cote.parrive.y = poly->vert[i + 1].y;
        }

        if (intersection_droites(&poly_cote, &ltest)) {
            // if (condicion) = 1 ie hay interseccion
            cpt++;
        }

        i++;
    }

    return cpt % 2 == 1;
}