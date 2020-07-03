#include <stdio.h>
#include <string.h>
#define MAX_LINEA 1001

char* leer_entrada(char* entrada){
    int largoEntrada;

    fgets(entrada, sizeof(char) * MAX_LINEA, stdin);

    largoEntrada = strlen(entrada) - 1; // -1 por el \n
    if (largoEntrada > 0)
        entrada[largoEntrada] = '\0';     // reemplazo el \n por un \0

    return entrada;
}

int main (){
    char entrada[MAX_LINEA];
    printf ("ingrese comando\n");
    while (strcmp(leer_entrada(entrada), "salir\0") != 0){
        printf ("%s \n",entrada);
    }

    return 0;
}