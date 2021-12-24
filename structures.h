#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

// dans ce fichier type header (.h) on définie les structures qu'on utilisera après dans les fichiers du type .c
// il faut inclure le fichier header dans le fichier.c avec
//                 #include "fct.c"


// on  définie la structure de type vertex, ie les sommets (coordonnées appartenant au plan R+xR+ de la forme (x,y) tq x sont les abcisses et y sont les ordonnées)
typedef struct Vertex Vertex;
struct Vertex {
    double x;
    double y;
};

// on défini les côtés du polygone, ie l'union entre deux points (sommets)
typedef struct Cotes Cotes;
struct Cotes {
    Vertex pdepart;
    Vertex parrive;
};

// on définie la structure du polygone comme une nombre de côtés et une liste de points
typedef struct Polygone Polygone;
struct Polygone {
    int nbpoints;
    Vertex *vert;
};

// FIXME: Polygone functions

void initialize_polygone(Polygone *poly, int nbpoints);

void dispose_polygone(Polygone *poly);

// FIXME: I/O functions

void write_poly(Polygone *poly, const char *f);

// FIXME: English name
int is_point_inside_polygon(Polygone *poly, Vertex *pointtest);

#endif // STRUCTURES_H_INCLUDED