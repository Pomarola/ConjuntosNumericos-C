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

int descomponer_entrada(char* entrada, char* primerTermino, char* segundoTermino){
    int i=0, j=0, codigo=0;
    while (entrada[i] != ' '){
        primerTermino[j] = entrada[i];
        j++;
        i++;
    }
    primerTermino[j] = '\0';
    j = 0;
    if (entrada[i] != ' ')
        return 0;
    i++;
    if (strcmp(primerTermino, "imprimir\0") == 0)
        codigo = 1;
    else if (entrada[i] == '=' && entrada[i+1] == ' '){
        i = i + 2;
        codigo = 2;
    }
    while (entrada[i] != '\0'){
        segundoTermino[j] = entrada[i];
        j++;
        i++;
    }
    segundoTermino[j] = '\0';
    return codigo;
    
}

int realizar_operacion (char* primerTermino, char* segundoTermino){
    char primerBuffer[MAX_LINEA], segundoBuffer[MAX_LINEA];
    int i=0, j=0;
    if (segundoTermino[i] == '{'){

    } else if (segundoTermino[i] == '∼'){

    } else {
        while (segundoTermino[i] != ' '){
            primerBuffer[j] = segundoTermino[i];
            i++;
            j++;
        }
        j = 0;
        i++;
        if (segundoTermino[i] == '|'){
            //union
        } else if (segundoTermino[i] == '&'){
            //interseccion
        } else if (segundoTermino[i] == '-'){
            //resta
        } else {
            // comando invalido
        }
        i++;
        if (segundoTermino[i] == ' '){
            while (segundoTermino[i] != '\0'){
                segundoBuffer[j] = segundoTermino[i];
                i++;
                j++;
            }
        }
    }
}



int main (){
    int codigo;
    char entrada[MAX_LINEA], primerTermino[MAX_LINEA], segundoTermino[MAX_LINEA];
    printf ("ingrese comando\n");
    while (strcmp(leer_entrada(entrada), "salir\0") != 0){
        printf ("entrada: %s \n",entrada);
        codigo = descomponer_entrada(entrada, primerTermino, segundoTermino);
        printf ("codigo: %d\n", codigo);
        switch (codigo) {
            case 0:
                printf ("error\n");
                break;
            case 1:
                /* imprimo segundo termino */
                printf ("imprimo \n");
                printf ("segundo: %s \n",segundoTermino);
                break;
            
            case 2:
                /* hacer operaciones */
                printf ("primer: %s \n",primerTermino);
                printf ("segundo: %s \n",segundoTermino);
                break;
        }
    }

    return 0;
}