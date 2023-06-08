/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    /*abb_dump(tree);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }

    tree = abb_destroy(tree);
    */

    unsigned int opcion = 0u;
    while(opcion != 7){
        printf("\nEscribe el numero de la accion que quieres realizar:\n"
        "1) Mostrar árbol por pantalla\n"
        "2) Agregar un elemento\n"
        "3) Eliminar un elemento\n"
        "4) Chequear existencia de elemento\n"
        "5) Mostrar longitud del árbol\n"
        "6) Mostrar raiz, máximo y mínimo del árbol\n"
        "7) Salir\n");
        scanf("%u",&opcion);
        while(opcion>7u || opcion<1u){
            printf("Opcion invalida");
            scanf("%u",&opcion);
        }

        if(opcion == 1u){
            abb_dump(tree);
        } else if(opcion == 2u){
            abb_elem new_elem;
            printf("Escribe el elemento que quieres agregar al arbol\n");
            scanf("%d",&new_elem);
            abb_add(tree,new_elem);
        } else if(opcion == 3u){
            abb_elem remove_elem;
            printf("Escribe el elemento que quieres eliminar del arbol\n");
            scanf("%d",&remove_elem);
            abb_remove(tree,remove_elem);
        } else if(opcion == 4u){
            abb_elem find_elem;
            printf("Escribe el elemento que quieres saber si existe en el arbol\n");
            scanf("%d",&find_elem);
            if(abb_exists(tree,find_elem)){
                printf("El elemento existe en el arbol\n");
            }else{
                printf("El elemento no existe en el arbol\n");
            }
        } else if(opcion == 5u){
            printf("El arbol tiene %d elementos\n", abb_length(tree));
        } else if(opcion == 6u){
            printf("La raiz del arbol es: %d\nEl minimo de arbol es: %d\nEl maximo del arbol es: %d\n", abb_root(tree), abb_min(tree), abb_max(tree));
        }
    }

    tree = abb_destroy(tree);
    
    return (EXIT_SUCCESS);
}
