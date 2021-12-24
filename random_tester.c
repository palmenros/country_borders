#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "structures.h"

#define NBMAX 100 // ie nbmax sera le nb max de côtés qu'on donne à notre programme pour après obtenir un polygone aléatoire
#define MAX 6 // nb qui définie la majoration de l'intervalle dans lequel on définit les nbs aléatoires

//FIXME: Change name
#define AVERAGE_RADIUS 5.0
#define POLYGON_CENTER_X 0
#define POLYGON_CENTER_Y 0

//FIXME: Change function names
double clip(double x, double lower, double upper) {
    if (x < lower)
        return lower;
    else if (x > upper)
        return upper;
    else
        return x;
}

//FIXME: Change function names
double random_uniform(double lower, double upper) {
    return lower + ((double) rand() / (RAND_MAX / (upper - lower)));
}

//FIXME: Change function names
void generate_random_point(Vertex *point) {
    point->x = random_uniform(-MAX, MAX);
    point->y = random_uniform(-MAX, MAX);
}

//FIXME: Change function names
void generate_random_polygone(Polygone *poly) {
    int nbpoints;
    int i;

    nbpoints = rand() % NBMAX;

    initialize_polygone(poly, nbpoints);

    for (i = 0; i < nbpoints; i++) {
        generate_random_point(&poly->vert[i]);
    }
}

//FIXME: Change function names
void generate_random_simple_polygone(Polygone *poly) {
    int nbpoints = rand() % NBMAX;

    double irregularity = 0.9 * 2 * M_PI / nbpoints;
    double spikeyness = 0.25 * AVERAGE_RADIUS;

    double *angleSteps;
    double lower, upper, sum, k, angle;
    double r_i, x, y;

    int i;

    initialize_polygone(poly, nbpoints);

    // generate n angle steps
    angleSteps = malloc(sizeof(double) * nbpoints);
    lower = (2 * M_PI / nbpoints) - irregularity;
    upper = (2 * M_PI / nbpoints) + irregularity;
    sum = 0;

    for (i = 0; i < nbpoints; ++i) {
        double tmp = random_uniform(lower, upper);
        angleSteps[i] = tmp;
        sum += tmp;
    }

    //normalize the steps so that point 0 and point n+1 are the same
    k = sum / (2 * M_PI);
    for (i = 0; i < nbpoints; ++i) {
        angleSteps[i] = angleSteps[i] / k;
    }

    //now generate the points
    angle = random_uniform(0, 2 * M_PI);

    for (i = 0; i < nbpoints; ++i) {
        r_i = clip(random_uniform(AVERAGE_RADIUS - spikeyness, AVERAGE_RADIUS + spikeyness), 0, 2 * AVERAGE_RADIUS);
        poly->vert[i].x = POLYGON_CENTER_X + r_i * cos(angle);
        poly->vert[i].y = POLYGON_CENTER_Y + r_i * sin(angle);
        angle = angle + angleSteps[i];
    }

    free(angleSteps);
}

//FIXME: English names
void test_with_random_simple_polygon() {
    int i, j = 0;
    int x, y = 0;
    int x0, y0 = 0;
    int res;

    Polygone poly;
    Vertex vert;
    Vertex pointtest;

    srand(time(NULL));

    generate_random_simple_polygone(&poly);
    write_poly(&poly, "../generated_simple_poly.csv");

    // on définie alétoirement le point à tester l'appartenance
    // Vertex *pointttest = NULL;
    generate_random_point(&pointtest);

    // on commence la fct
    printf("Bienvenue au programme: Vérifier appartennance du point au polygone\n");

    res = is_point_inside_polygon(&poly, &pointtest);
    if (res) {
        printf("Super! Le point de coordonnées %lf, %lf appartient à l'intérieur du polygone\n", pointtest.x,
               pointtest.y);
    } else {
        printf("Malheureusement le point de coordonnées %lf, %lf n'appartient pas à l'intérieur du polygone\n",
               pointtest.x, pointtest.y);
    }

    dispose_polygone(&poly);
}