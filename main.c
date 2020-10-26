#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    IDENTIFICADOR, IMPRIMIR, PUNTOYCOMA, ASIGNACION, CADENA, CONSTANTE,
    SALTO, PARENIZQ, PARENDER, OPERADORADICION, OPERADORMULTIPLICACION, FDT
} TOKEN;

char programaFuente[50];
int contPrograma;
TOKEN tokens[50];
TOKEN tokensSinSaltos[50];
int contToken;
int contTokenSinSalto;

int columna(char, char[]);
void scanner(char[], int *[]);

int main(){

    compilar("Programa correcto.txt");
    printf("\n\n-------------------------------------\n\n");
    compilar("Programa con error.txt");
    return 0;
}

void compilar(char archivo[]){
    inicializar();
    char proximoCaracter;
    int cont = 0;
    FILE *ptr = fopen(archivo, "r");

    if (!ptr){
        printf("ERROR: No se pudo abrir el archivo");
        exit(1);
    }
    while(fscanf(ptr,"%c", &proximoCaracter) != EOF){
        programaFuente[cont] = proximoCaracter;
        cont ++;
    }
    printf("Programa Fuente():\n");
    for (int i=0;i<strlen(programaFuente);i++){
        printf("%c", programaFuente[i]);
    }

    programa();
    fclose(ptr);
}

void inicializar(){
    int contToken = 0;
    int contTokenSinSalto = 0;
    int contPrograma = 0;

    for(int i=0; i< strlen(programaFuente); i++)
        programaFuente[i] = '\0';

    for(int i=0; i< strlen(tokens); i++)
        tokens[i] = '\0';

    for(int i=0; i< strlen(tokensSinSaltos); i++)
        tokensSinSaltos[i] = '\0';
}

TOKEN proximoToken(){
    return tokensSinSaltos[contTokenSinSalto];
}

void match(TOKEN tokenActual){
    if(tokenActual != proximoToken())
        errorSintactico();
    contTokenSinSalto++;
}
void programa(){
    generarTokens();
    contTokenSinSalto = 0;
    listaSentencias();
    match(FDT);
    printf("\nLa compilacion ha sido EXITOSA");
}

void listaSentencias(){
    sentencia();
    if (proximoToken() == IDENTIFICADOR)
        listaSentencias();
}

void sentencia(){
    match(IDENTIFICADOR);
    match(ASIGNACION);
    expresion();
    match(PUNTOYCOMA);
}

void expresion(){
    if(proximoToken() == CADENA)
        match(CADENA);
    else{
        expMatematica();
    }
}

void expMatematica(){
    termino();
    if (proximoToken() == OPERADORADICION){
        match(OPERADORADICION);
        expMatematica();
    }
}

void termino(){
    factor();
    if (proximoToken() == OPERADORMULTIPLICACION){
        match(OPERADORMULTIPLICACION);
        termino();
    }
}

void factor(){
    switch(proximoToken()){
        case CONSTANTE:
            match(CONSTANTE);
            break;
        case PARENIZQ:
            match(PARENIZQ);
            expMatematica();
            match(PARENDER);
            break;
        default:
            errorSintactico();
    }
}
void convertirEstadosATokens(){
    for (int i=0; i<contTokenSinSalto; i++){
        switch(tokensSinSaltos[i]){
            case 1:
                tokensSinSaltos[i] = IDENTIFICADOR;
                break;
            case 2:
                tokensSinSaltos[i] = OPERADORADICION;
                break;
            case 3:
                tokensSinSaltos[i] = OPERADORMULTIPLICACION;
                break;
            case 4:
                tokensSinSaltos[i] = ASIGNACION;
                break;
            case 5:
                tokensSinSaltos[i] = FDT;
                break;
            case 7:
                tokensSinSaltos[i] = CONSTANTE;
                break;
            case 9:
                tokensSinSaltos[i] = CADENA;
                break;
            case 11:
                tokensSinSaltos[i] = PUNTOYCOMA;
                break;
            case 12:
                tokensSinSaltos[i] = PARENIZQ;
                break;
            case 13:
                tokensSinSaltos[i] = PARENDER;
                break;
        }
    }
}

void ignorarSaltos(){
    for(int i=0; i<contToken+1; i++){
        if(tokens[i] != SALTO){
            tokensSinSaltos[contTokenSinSalto] = tokens[i];
            contTokenSinSalto++;
        }
    }
}

void generarTokens(){
    int tabla[14][50] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 3, 3, 3, 4, 5, 6, 6, 6, 8,11,12,13},
                         { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10,10,10,10,10,10,10,10,10,10, 9,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
                         {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}};
    scanner(programaFuente, tabla);
    ignorarSaltos();
    convertirEstadosATokens();
}

void scanner(char lexema[], int *tabla[]){

    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz0123456789+-/^*=_\ \t\n\";()";

    if(!caracteresPertenecenAlAlfabeto(lexema, alfabeto))
        errorSintactico();

    int cantidadColumnas = strlen(alfabeto);
    int aux;
    int estadoActual = 0;
    int siguienteEstado;
    while(estadoActual != 5){
        aux = 1;
        siguienteEstado = (tabla+(estadoActual*cantidadColumnas))[columna(programaFuente[contPrograma], alfabeto)];

        while(aux){
            if(esEstadoFinal(estadoActual) && esEstadoRechazo(siguienteEstado)){
                tokens[contToken] = estadoActual;
                if(estadoActual == 5)
                    return;
                else{
                    contToken++;
                    estadoActual = 0;
                    aux = 0;
                }
            }
            else{
                estadoActual = siguienteEstado;
                contPrograma++;
                siguienteEstado = (tabla+(siguienteEstado*cantidadColumnas))[columna(programaFuente[contPrograma], alfabeto)];
            }
        }
    }
}

int columna(char elemento, char alfabeto[]){
    for(int cont = 0; cont < strlen(alfabeto); cont++)
        if(elemento == alfabeto[cont])
            return cont;
    return 0;
}

int caracteresPertenecenAlAlfabeto(char cadena[], char alfabeto[]){
    int aux = 0;

    for(int cont1 = 0; cont1 < strlen(cadena); cont1 ++)
        for(int cont2 = 0; cont2 < strlen(alfabeto); cont2 ++)
            if(cadena[cont1] == alfabeto[cont2])
                aux ++;

    if(aux == strlen(cadena))
        return 1;

    return 0;
}

int esEstadoFinal(int estado){
    switch(estado){
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 9: case 11: case 12: case 13:
            return 1;
        default:
            return 0;
    }
}

int esEstadoRechazo(int estado){
    if (estado == 10)
        return 1;
    else
        return 0;
}

void errorSintactico(){
    printf("\nERROR: No se ha podido compilar correctamente");
    exit(1);
}

