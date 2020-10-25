#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    IDENTIFICADOR, PALABRARESERVADA, OPERADOR, CONSTANTE, CADENA
} TOKEN;

TOKEN scanner(void);

int main()
{
    char proximoCaracter;
    char programaFuente[500];
    int cont = 0;
    FILE *ptr = fopen("Programa fuente.txt", "r");

    if (!ptr){
        printf("ERROR: No se pudo abrir el archivo");
        exit(1);
    }
    while(fscanf(ptr,"%c", &proximoCaracter) != EOF){
        programaFuente[cont] = proximoCaracter;
        cont ++;
    }
    fclose(ptr);
}

TOKEN scanner(){
}
