#include "intervalo.h"
#include <stdlib.h>

Intervalo *llenar_intervalo(int inicio, int final) {
    Intervalo *nuevoIntervalo = malloc(sizeof(Intervalo));
    nuevoIntervalo->inicio = inicio;
    nuevoIntervalo->final = final;

    return nuevoIntervalo;
}

int intervalo_valido(Intervalo dato) {
    if (dato.inicio > dato.final)
        return 0;
    return 1;
}

int intersecar(Intervalo primero, Intervalo segundo) {
    return !(primero.final < segundo.inicio || primero.inicio > segundo.final);
}

void liberar_intervalo(Intervalo *intervalo) {
    free(intervalo);
}