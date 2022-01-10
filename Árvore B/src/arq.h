#ifndef ARQ_H
#define ARQ_H

#include "lista.h"
#include "btree.h"

#define PATH_CLIENTES "src/files/clientes/"

#define FALSE 0
#define TRUE 1

typedef struct Cliente Cliente;

struct Cliente {
    int cpf;
    int idade;
    char *nome;
};

void writeArq(int inicio, int fim, char *valor);

void readArqConcatenado(Lista *lista);
void readArqIntervalo(Pagina **p);
void readArqClientes(Record r, Cliente *c, int *aux);

void token(char *str);
void tokenClientes(char *str, Cliente *c, int *aux);

int get_random();
int get_randomIdade();

#endif