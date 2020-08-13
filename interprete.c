#include <stdio.h>
#include <string.h>
#include <conjunto.h>
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
    Conjunto conjunto;
    char buffer[MAX_LINEA];
    int i=0, j=0;
    if (segundoTermino[i] == '{'){
        if (segundoTermino[i+1] >= 'a' && segundoTermino[i+1] <= 'z'){
            // primerConjunto = leer_conjunto_compresion(primerTermino, segundoTermino);
            // insertar_tabla_hash (conjunto, tablaHash);
        } else {
            // primerConjunto = leer_conjunto_extension(primerTermino, segundoTermino);
            // insertar_tabla_hash (conjunto, tablaHash);
        }
    } else if (segundoTermino[i] == '∼'){
        i++;
        while (segundoTermino[i] != '\0'){
            buffer[j] = segundoTermino[i];
            j++;
            i++;
        }
        buffer[j] = '\0';
        // conjunto = buscar_tabla_hash(buffer, tablaHash);
        // insertar_tabla_hash (conjunto_complemento(primerTermino, conjunto), tablaHash);
        
    } else
        operacion_dos_conjuntos (primerTermino, segundoTermino);
}

Conjunto leer_conjunto_compresion(char* primerTermino, char* segundoTermino){
    Conjunto conjunto = NULL;
    char inicioStr[MAX_LINEA], finalStr[MAX_LINEA], letra = segundoTermino[1];
    int i=5, j=0, inicio, final = 0; 
    if (segundoTermino[2] == ' ' && segundoTermino[3] == ':' && segundoTermino[4] == ' '){ // ya sabemos que segundoTermino[0] = '{' y que segundoTermino[1] es una letra
        while (segundoTermino[i] != '<') {
            inicioStr[j] = segundoTermino[i];
            i++;
            j++;
        }
        j = 0;
        if (segundoTermino[i+1] == '='){
            inicio = atoi(inicioStr);   
            i++;
        }
        else if (segundoTermino[i+1] == ' ')
            inicio = atoi(inicioStr) + 1;   
        else
            printf ("sintaxis incorrecta\n");
            return NULL;

        i = i + 2;
        if (segundoTermino[i] != letra){
            printf ("sintaxis incorrecta\n");
            return NULL;
        }
        i = i + 2;

        if (segundoTermino[i] != '<')
            printf ("sintaxis incorrecta\n");
            return NULL;

        if (segundoTermino[i+1] == '='){
            i++;
        }
        else if (segundoTermino[i+1] == ' ')
            final = 1;   
        else
            printf ("sintaxis incorrecta\n");
            return NULL;
        i = i + 2;

        while (segundoTermino[i] != '}') {
            finalStr[j] = segundoTermino[i];
            i++;
            j++;
        }
        final = final + atoi(finalStr);

        conjunto = dlist_crear(primerTermino);
        if (intervalo_valido(inicio, final))
            dlist_insertar_final(conjunto, crear_intervalo(inicio, final));

    } else
        printf ("sintaxis incorrecta\n");
    return conjunto;
}

Conjunto leer_conjunto_extension(char* primerTermino, char* segundoTermino){
    Conjunto conjunto = dlist_crear(primerTermino);
    char numero[MAX_LINEA];
    int i = 1, j = 0;

    while (segundoTermino[i] != '}') {
        while (segundoTermino[i] != ','){
            numero[j] = segundoTermino[i];
            j++;
            i++;
        }
        j = 0;
        dlist_insertar_final(conjunto, crear_intervalo(atoi(numero), atoi(numero)));
    }
    
    return conjunto;
}

int operacion_dos_conjuntos (char* primerTermino, char* segundoTermino){
    char* primerBuffer[MAX_LINEA], segundoBuffer[MAX_LINEA], operacion;
    int i = 0, j = 0;
    Conjunto primerConjunto, segundoConjunto, conjuntoResultante;

    while (segundoTermino[i] != ' '){
        primerBuffer[j] = segundoTermino[i];
        i++;
        j++;
    }
    j = 0;
    i++;
    operacion = segundoTermino[i];
    i++;
    if (segundoTermino[i] == ' '){
        while (segundoTermino[i] != '\0'){
            segundoBuffer[j] = segundoTermino[i];
            i++;
            j++;
        }
        segundoBuffer[j] = '\0';
    } else
        printf ("error\n");

    // primerConjunto = buscar_tabla_hash(primerBuffer, tablaHash);
    // segundoConjunto = buscar_tabla_hash(primerBuffer, tablaHash);
    if (primerConjunto && segundoConjunto){
        switch (operacion) {
            case '|':
                // insertar_tabla_hash (conjunto_union(primerTermino, primerConjunto, segundoConjunto), tabla);
                break;

            case '&':
                // insertar_tabla_hash (conjunto_interseccion(primerTermino, primerConjunto, segundoConjunto), tabla);
                break;
            
            case '-':
                // insertar_tabla_hash (conjunto_resta(primerTermino, primerConjunto, segundoConjunto), tabla);
                break;
            
            default:
                printf ("error\n");
        }

    } else 
        printf ("no se encontro alguno de los conjuntos\n");

}



int main (){
    int codigo;
    char entrada[MAX_LINEA], primerTermino[MAX_LINEA], segundoTermino[MAX_LINEA];
    Conjunto conjunto;
    printf ("ingrese comando\n");
    while (strcmp(leer_entrada(entrada), "salir\0") != 0){
        printf ("entrada: %s \n",entrada);
        codigo = descomponer_entrada(entrada, primerTermino, segundoTermino);
        printf ("codigo: %d\n", codigo);
        switch (codigo) {
            case 1:
                /* imprimo segundo termino */
                printf ("imprimo \n");
                // imprimir_dlist_pantalla(buscar_tabla_hash(segundoTermino, tablaHash), imprimir_intervalo);
                printf ("segundo: %s \n",segundoTermino);
                break;
            
            case 2:
                /* hacer operaciones */
                // realizar_operacion(primerTermino, segundoTermino);
                printf ("primer: %s \n",primerTermino);
                printf ("segundo: %s \n",segundoTermino);
                break;
            default:
                printf ("error\n");
        }
    }

    return 0;
}