#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "tree.h"
#include "rgb.h"


int main(int argc, char **argv){
    // Cele 3 booleene verifica ce cerinta vom rezolva
    bool is_c = FALSE; 
    bool is_d = FALSE;
    bool is_m = FALSE;
    
    // Fisierele input/output
    char *input_file;
    char *output_file;

    // Parametrii pentru c, respectiv m
    int factor;
    char type;

    // Verificam ce comanda am primit si daca am primit corect setam variabilele
    if(argc == 4 && !strcmp(argv[1], "-d")){
        is_d = TRUE;
        input_file = calloc(strlen(argv[2])+1, sizeof(char));
        memcpy(input_file, argv[2], strlen(argv[2]));
        output_file = calloc(strlen(argv[3])+1, sizeof(char));
        memcpy(output_file, argv[3], strlen(argv[3]));
    }
    else if(argc == 5 && (!strcmp(argv[1], "-c"))){
        is_c = TRUE;
        factor = atoi(argv[2]);
        input_file = calloc(strlen(argv[3])+1, sizeof(char));
        memcpy(input_file, argv[3], strlen(argv[3]));
        output_file = calloc(strlen(argv[4])+1, sizeof(char));
        memcpy(output_file, argv[4], strlen(argv[4]));
    }
    else if (argc == 6 && (!strcmp(argv[1], "-m")&& is_valid_for_m(argv[2]))){
        is_m = TRUE;
        type = argv[2][0];
        factor = atoi(argv[3]);
        input_file = calloc(strlen(argv[4]) + 1, sizeof(char));
        memcpy(input_file, argv[4], strlen(argv[4]));
        output_file = calloc(strlen(argv[5]) + 1, sizeof(char));
        memcpy(output_file, argv[5], strlen(argv[5]));
    }
    else{
        printf("Arguments were given in the wrong way! Read the documentation to see how to use the app!\n");
        return 0;
    }

    input_file[strlen(input_file)] = 0;
    output_file[strlen(output_file)] = 0;

    // Daca optiunea introdusa este -d
    if(is_d){
        FILE *input = fopen(input_file, "rb");
        FILE *output = fopen(output_file, "wb");
        
        // Verificam daca a s-au deschis corect fisierele
        if(input == NULL || output == NULL){
            fprintf(stderr, "Fisierul de intrare/iesire nu a fost vazut bine");
            return 0;
        }
        
        // Se citeste vectorul din fisier
        int leaves, nodes;
        QuadtreeNode* vector;
        fread(&leaves, sizeof(int), 1, input);
        fread(&nodes, sizeof(int), 1, input);
        vector = (QuadtreeNode*)malloc(nodes * sizeof(QuadtreeNode));
        fread(vector, sizeof(QuadtreeNode), nodes, input);

        // Se creeaza arborele si matricea
        Quadtree *root = create_quadtree_from_vector(vector, 0);
        RGB** matrix;
        int width, height;
        width = height = sqrt(root->info->area);
        matrix = (RGB**)malloc(sizeof(RGB*) * height);
        for(int i = 0; i < height; i++)
            matrix[i] = (RGB*)malloc(sizeof(RGB) * width);
        make_pixel_matrix_from_tree(&matrix, root, 0, 0, width, height);

        // Se creeaza fisierul ppm
        make_ppm(matrix, width, height, output);
        
        // Curatarea spatiului
        for(int i = 0; i < height; i++)
            free(matrix[i]);
        free(matrix);
        free(vector);
        destroy_tree(&root);
        fclose(input);
        fclose(output);
    }

    // Daca optiunea introdusa este -c
    if(is_c){
        FILE *input = fopen(input_file, "rb");
        FILE *output = fopen(output_file, "wb");

        // Verificam daca a s-au deschis corect fisierele
        if(input == NULL || output == NULL){
            fprintf(stderr, "Fisierul de intrare/iesire nu a fost vazut bine");
            return 0;
        }

        // Se citeste matricea si se creeaza arborele in functie de ea
        int width, height;
        RGB** matrix = get_pixel_matrix(input, &width, &height);
        RGB average = get_average_color(matrix, 0, 0, width, height);
        Quadtree *root = quadtree_alloc(0, average.red, average.green, average.blue, width * height, 1, 2, 3, 4);
        root = create_quadtree(root, matrix, 0, 0, width, height, factor);
        root = index_tree(root);
        root = index_tree_children(root);
        
        // Se creeaza vectorul si se afiseaza binar in fisier
        QuadtreeNode* vector = make_vector(root);
        int leaves = count_leaves(root);
        int nodes = count_nodes(root);
        fwrite(&leaves, sizeof(int), 1, output);
        fwrite(&nodes, sizeof(int), 1, output);
        fwrite(vector, sizeof(QuadtreeNode), nodes, output);

        // Curatarea spatiului
        for(int i = 0; i < height; i++)
            free(matrix[i]);
        free(matrix);
        free(vector);
        destroy_tree(&root);
        fclose(input);
        fclose(output);
    }
    
    // Daca optiunea introdusa este -m
    if(is_m){
        FILE *input = fopen(input_file, "rb");
        FILE *output = fopen(output_file, "wb");

        // Verificam daca a s-au deschis corect fisierele
        if(input == NULL || output == NULL){
            fprintf(stderr, "Fisierul de intrare/iesire nu a fost vazut bine");
            return 0;
        }

        // Se citeste matricea si se creeaza arborele
        int width, height;
        RGB** matrix = get_pixel_matrix(input, &width, &height);
        RGB average = get_average_color(matrix, 0, 0, width, height);
        Quadtree *root = quadtree_alloc(0, average.red, average.green, average.blue, width * height, 1, 2, 3, 4);
        root = create_quadtree(root, matrix, 0, 0, width, height, factor);
        
        // Se roteste arborele in functie de tipul dat
        if(type == 'h')
            horizontal_rotation(&root);
        if(type == 'v')
            vertical_rotation(&root);
        
        // Se reface matricea de pixeli in functie de arborele modificat
        make_pixel_matrix_from_tree(&matrix, root, 0, 0, width, height);

        // Se creeaza fisierul .ppm
        make_ppm(matrix, width, height, output);

        //curatarea spatiului
        for(int i = 0; i < height; i++)
            free(matrix[i]);
        free(matrix);
        destroy_tree(&root);
        fclose(input);
        fclose(output);
    }
    
    //curatarea globala
    free(input_file);
    free(output_file);
        

    return 0;
    
}