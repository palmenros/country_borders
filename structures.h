#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED



#endif // STRUCTURES_H_INCLUDED


#include<stdio.h>
#include<math.h>
#include<stdlib.h>


// dans ce fichier type header (.h) on définie les structures qu'on utilisera après dans les fichiers du type .c
// il faut inclure le fichier header dans le fichier.c avec
//                 #include "fct.c"


// on  définie la structure de type vertex, ie les sommets (coordonnées appartenant au plan R+xR+ de la forme (x,y) tq x sont les abcisses et y sont les ordonnées)
typedef struct Vertex Vertex;
struct Vertex
{
    double x;
    double y;
};


// on défini les côtés du polygone, ie l'union entre deux points (sommets)
typedef struct Cotes Cotes;
struct Cotes
{
    Vertex pdepart;
    Vertex parrive;
};



// on définie la structure du polygone comme une liste enchaînée de côtés qui forment le polygone
typedef struct Noeud Noeud;
struct Noeud
{
    int nbpoints;
    Vertex *vert;
    // Noeud *noeud; // pointeur vers la liste enchaînée
};

