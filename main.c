#include <stdio.h>
#include <stdlib.h>

int main()
{
    char caracterLeido;
    FILE *ptr = fopen("Programa fuente.txt", "r");

    if (!ptr){
        printf("ERROR: No se pudo abrir el archivo");
        exit(1);
    }
    while(fscanf(ptr,"%c", &caracterLeido) != EOF){
        printf("%c", caracterLeido);
    }
    fclose(ptr);
}
