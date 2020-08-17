#include "./THash/thash.h"
#include "./Conjunto/conjunto.h"
#include <ctype.h>

#define MAX_LINEA 1001

int hash_conjunto(void* conjunto){
    return hash_str(((Conjunto) conjunto)->nombre);
}

Conjunto leer_conjunto_compresion(char* primerTermino, char* segundoTermino) {
    Conjunto conjunto = NULL;
    char inicioStr[MAX_LINEA], finalStr[MAX_LINEA], letra = segundoTermino[1];
    int i = 5, j = 0, inicio = 0, final = 0, error = 0; 
    if (segundoTermino[2] == ' ' && segundoTermino[3] == ':' && segundoTermino[4] == ' ') { // ya sabemos que segundoTermino[0] = '{' y que segundoTermino[1] es una letra
        while (segundoTermino[i] != ' ' && error == 0) {
            if (isdigit(segundoTermino[i])) {
                inicioStr[j] = segundoTermino[i];
                i++;
                j++;
            } else 
                error = 1;
        }

        if (error) {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }

        if (segundoTermino[i + 1] != '<') {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }

        i += 2;       
        j = 0;
        if (segundoTermino[i] == '=') {
            i++;
        }
        else if (segundoTermino[i] == ' ')
            inicio = 1;   
        else {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }
        inicio += atoi(inicioStr);

        i += 1;
        if (segundoTermino[i] != letra) {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }

        i += 2;
        if (segundoTermino[i] != '<') {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }

        if (segundoTermino[i + 1] == '=') {
            i++;
        }
        else if (segundoTermino[i + 1] == ' ')
            final = -1;   
        else {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }
        i += 2;

        while (segundoTermino[i] != '}' && error == 0) {
            if (isdigit(segundoTermino[i])) {
                finalStr[j] = segundoTermino[i];
                i++;
                j++;
            } else
                error = 1;
        }

        if (error) {
            printf ("Sintaxis del conjunto incorrecta\n");
            return NULL;
        }

        final += atoi(finalStr);
        conjunto = dlist_crear(primerTermino);

        if (intervalo_valido(inicio, final))
            dlist_insertar_final(conjunto, crear_intervalo(inicio, final));

    } else
        printf ("Sintaxis del conjunto incorrecta\n");
    return conjunto;
}

Conjunto leer_conjunto_extension(char* primerTermino, char* segundoTermino) {
    Conjunto conjunto = dlist_crear(primerTermino);
    int i = 0, error = 0;
    long numero;

    char *buffer = &segundoTermino[0] + 1;
    while (buffer[i] != '}' && error == 0) {
        if (buffer[i] == ',')
            i++;
        else if (!isdigit(buffer[i]))
            error = 1;
        else {
            numero = strtol(buffer + i, &buffer, 10);
            dlist_insertar_final(conjunto, crear_intervalo(numero, numero));
            i = 0;
        }
    }

    if (error) {
        printf ("Sintaxis del conjunto incorrecta\n");
        dlist_destruir(conjunto);
        return NULL;
    }

    return conjunto;
}

void operacion_dos_conjuntos (char* primerTermino, char* segundoTermino, SList* tablaHash){
    char primerBuffer[MAX_LINEA], segundoBuffer[MAX_LINEA], operacion;
    int i = 0, j = 0;
    Conjunto primerConjunto, segundoConjunto;

    while (segundoTermino[i] != ' ') {
        primerBuffer[j] = segundoTermino[i];
        j++; 
        i++;
    }
    primerBuffer[j] = '\0';
    j = 0;
    i++;
    operacion = segundoTermino[i];
    i++;
    if (segundoTermino[i] == ' ') {
        i++;
        while (segundoTermino[i] != '\0'){
            segundoBuffer[j] = segundoTermino[i];
            i++;
            j++;
        }
        segundoBuffer[j] = '\0';
    } else
        printf ("Sintaxis incorrecta\n");

    primerConjunto = ((Conjunto) thash_buscar(primerBuffer, tablaHash, hash_str, conjunto_comparar_string));
    segundoConjunto = ((Conjunto) thash_buscar(segundoBuffer, tablaHash, hash_str, conjunto_comparar_string));

    if (primerConjunto && segundoConjunto) {
        switch (operacion) {
            case '|':
                tablaHash = thash_insertar (conjunto_union(primerTermino, primerConjunto, segundoConjunto), tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
                break;

            case '&':
                tablaHash = thash_insertar (conjunto_interseccion(primerTermino, primerConjunto, segundoConjunto), tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
                break;
            
            case '-':
                tablaHash = thash_insertar (conjunto_resta(primerTermino, primerConjunto, segundoConjunto), tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
                break;
            
            default:
                printf ("Operacion incorrecta\n");
        }

    } else 
        printf ("No se encontro alguno de los conjuntos\n");

}

char* leer_entrada(char* entrada) {
    int largoEntrada;

    fgets(entrada, sizeof(char) * MAX_LINEA, stdin);

    largoEntrada = strlen(entrada) - 1; // -1 por el \n
    if (largoEntrada > 0)
        entrada[largoEntrada] = '\0';     // reemplazo el \n por un \0

    return entrada;
}

int descomponer_entrada(char* entrada, char* primerTermino, char* segundoTermino) {
    int i = 0, j = 0, codigo = 0;
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

    while (entrada[i] != '\0') {
        segundoTermino[j] = entrada[i];
        j++;
        i++;
    }
    segundoTermino[j] = '\0';
    return codigo;    
}

void realizar_operacion (char* primerTermino, char* segundoTermino, SList* tablaHash){
    Conjunto conjunto;
    char buffer[MAX_LINEA];
    int i = 0, j = 0;
    if (segundoTermino[i] == '{'){
        if (segundoTermino[i + 1] >= 'a' && segundoTermino[i + 1] <= 'z'){
            conjunto = leer_conjunto_compresion(primerTermino, segundoTermino);
            if (conjunto)
                tablaHash = thash_insertar (conjunto, tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
        } else {
            conjunto = leer_conjunto_extension(primerTermino, segundoTermino);
            if (conjunto) {
                dlist_merge_sort(conjunto, intervalo_comparar, intervalo_igual);
                tablaHash = thash_insertar (conjunto, tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
            }
        }

    } else if (segundoTermino[i] == '~') {
        i++;
        while (segundoTermino[i] != '\0') {
            buffer[j] = segundoTermino[i];
            j++;
            i++;
        }
        buffer[j] = '\0';
        
        conjunto = thash_buscar(buffer, tablaHash, hash_str, conjunto_comparar_string);
        if (conjunto)
            tablaHash = thash_insertar (conjunto_complemento(primerTermino, conjunto), tablaHash, hash_conjunto, conjunto_comparar_nombre, dlist_destruir);
        else
            printf ("No se encontro el conjunto\n");
        
    } else
        operacion_dos_conjuntos (primerTermino, segundoTermino, tablaHash);
}

int main() {
    int codigo;
    char entrada[MAX_LINEA], primerTermino[MAX_LINEA], segundoTermino[MAX_LINEA];
    SList* tablaHash = thash_crear();

    printf ("Creacion de un conjunto:\n");
    printf ("- Por extension: alias = {k0,k1,...,kn}\n");
    printf ("- Por compresion: alias = {x : k0 (<=,<) x (<=,<) k1}\n");
    printf ("Operaciones con conjuntos:\n");
    printf ("  ~: Complemento, |: Union, &: Interseccion, -: Resta\n");
    printf ("Otras opciones:  imprimir, salir\n");

    while (strcmp(leer_entrada(entrada), "salir\0") != 0) {
        codigo = descomponer_entrada(entrada, primerTermino, segundoTermino);
        switch (codigo) {
            case 1:
                dlist_imprimir(thash_buscar(segundoTermino, tablaHash, hash_str, conjunto_comparar_string), imprimir_intervalo);
                break;
            
            case 2:
                realizar_operacion(primerTermino, segundoTermino, tablaHash);
                break;

            default:
                printf ("Sintaxis incorrecta\n");
        }
    }
    thash_destruir(tablaHash, dlist_destruir);
    return 0;
}