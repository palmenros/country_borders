#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

//FIXME: Translate to french
void read_country_data(int* npolys, Polygone** polys, const char *f) {
    FILE *file;
    int i, j;

    file = fopen(f, "r");  // "r" = read file

    //FIXME: We read the number of polygons (patches that form the country)
    fscanf(file, "%d\n", npolys);

    *polys = malloc(sizeof(Polygone) * *npolys);

    for(i = 0; i < *npolys; ++i) {
        int nbpoints;
        //FIXME: Read one polygon
        Polygone* currentPoly = &((*polys)[i]);

        fscanf(file, "%d\n", &nbpoints);

        initialize_polygone(currentPoly, nbpoints);

        for(j = 0; j < nbpoints; ++j) {
            double x, y;
            fscanf(file, "%lf,%lf\n", &x, &y);
            currentPoly->vert[j].x = x;
            currentPoly->vert[j].y = y;
        }
    }

    fclose(file);
}

//FIXME: Translate
int is_point_in_country(int npolys, Polygone* polys, double longitude, double latitude)
{
    int i;
    Vertex point;
    point.x = longitude;
    point.y = latitude;

    for(i = 0; i < npolys; i++) {
        if(is_point_inside_polygon(&polys[i], &point)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    Polygone* polys;
    int npolys, i;
    double longitude, latitude;

    read_country_data(&npolys, &polys, "../spain_country_data.data");

    //FIXME: Translate
    printf("Let's check if a point is inside Spanish territory. \nEnter a longitude: ");
    scanf("%lf", &longitude);
    printf("Enter a latitude: ");
    scanf("%lf", &latitude);

    if(is_point_in_country(npolys, polys, longitude, latitude)) {
        printf("The point %lf, %lf *IS* inside the country \n", longitude, latitude);
    } else {
        printf("The point %lf, %lf is *NOT* inside the country \n", longitude, latitude);
    }

    for(i = 0; i < npolys; i++) {
        dispose_polygone(&polys[i]);
    }

    free(polys);
    return 0;
}
