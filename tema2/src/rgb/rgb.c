#include <stdlib.h>
#include <stdio.h>
#include "rgb.h"


void swap(RGB *a, RGB *b){
    RGB aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

RGB** get_pixel_matrix(FILE* file, int *width, int *height){
    char aux[5]; // Vom citi P6
    unsigned short max_val; // Deja 256
    fgets(aux, 5, file); // P6 skipped
    fscanf(file, "%d%d", width, height); // Aflam inaltimea/latimea
    fgetc(file); // Trecem peste un whitespace
    fscanf(file, "%hd", &max_val); // Luam val maxima = 255
    fgetc(file); // Trecem peste whitespace
    RGB** matrix; // Matricea unde vor fi retinuti pixelii imaginii

    matrix = (RGB**)malloc(*height * sizeof(RGB*)); // Se aloca spatiul pentru matrice
    for(int i = 0; i < *height; i++)
        matrix[i] = (RGB*)malloc(*width * sizeof(RGB));

    for(int i = 0; i < *height; i++) // Se citeste matricea efectiva
        fread(matrix[i], sizeof(RGB), (*width), file);
    return matrix;
}

void print_pixel_matrix(RGB** matrix, int width, int height, FILE* file){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            fprintf(file, "%d %d %d  ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
        fprintf(file, "\n");
    }
}

void make_ppm(RGB** matrix, int width, int height, FILE* file){
    fprintf(file, "%s\n", "P6");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%s\n", "255");
    for(int i = 0; i < height; i++)
        fwrite(matrix[i], sizeof(RGB), width, file);
}

RGB get_average_color(RGB** matrix, int startX, int startY, int width, int height){
    BIG_RGB temp; // Variabila temporara pentru a stoca suma tuturor culorilor
    RGB answer;
    temp.red = temp.green = temp.blue = 0;
    for(int y = startY; y < startY + height; y++)
        for(int x = startX; x < startX + width; x++){
            temp.red += matrix[y][x].red;
            temp.green += matrix[y][x].green;
            temp.blue += matrix[y][x].blue;
        }
    answer.red = temp.red / (width * height);
    answer.green = temp.green / (width * height);
    answer.blue = temp.blue / (width * height);
    return answer;
}

