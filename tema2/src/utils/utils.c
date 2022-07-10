#include "utils.h"
#include "rgb.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool is_valid_for_m(char* string){
    if(strlen(string) != 1) // Daca sirul nu este doar o litera
        return FALSE;
    if(string[0] == 'h' || string[0] == 'v')
        return TRUE;
    return FALSE;
}

int square(int a){
    return a*a;
}

int64_t determinate_mean(RGB** matrix, int startX, int startY, int width, int height){
    int64_t sum = 0;
    RGB average = get_average_color(matrix, startX, startY, width, height); // culoarea medie pe zona cautata
    for(int y = startY; y < startY + height; y++)
        for(int x = startX; x < startX + width; x++)
            sum += square(average.red - matrix[y][x].red) + square(average.green - matrix[y][x].green) + square(average.blue - matrix[y][x].blue);
    sum /= 3*square(width);
    return sum;
}


void make_pixel_matrix_from_tree(RGB*** matrix, Quadtree *node, int startX, int startY, int width, int height){
    // Daca suntem intr-un nod frunza, atunci avem informatia utila de culoare si putem seta pixelii
    if(node->first == NULL && node->second == NULL && node->third == NULL && node->fourth == NULL){
        for(int y = startY; y < startY + height; y++)
            for(int x = startX; x < startX + width; x++){
                (*matrix)[y][x].red = node->info->red;
                (*matrix)[y][x].green = node->info->green;
                (*matrix)[y][x].blue = node->info->blue;
            }
    }

    else{
        // Cautam nodurile frunza
        make_pixel_matrix_from_tree(matrix, node->first, startX, startY, width/2, height/2);
        make_pixel_matrix_from_tree(matrix, node->second, startX + width/2, startY, width/2, height/2);
        make_pixel_matrix_from_tree(matrix, node->third, startX + width/2, startY + height/2, width/2, height/2);
        make_pixel_matrix_from_tree(matrix, node->fourth, startX, startY + height/2, width/2, height/2);
    }
}

