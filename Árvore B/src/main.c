#include "arq.h"

#include <stdio.h>



void createFile(Lista *l) {
    Block *aux;
    char str[20];

	aux = l->first->prox;
	while(aux != NULL) {
        writeArq(aux->dado.cpfInicio, aux->dado.cpfFim, aux->dado.valor);
		aux = aux->prox;
	}
}

int main() {
    
    printf("\n\n======= ÁRVORE B =======\n\n");

	Lista l;
	FLVazia(&l);

	readArqConcatenado(&l);
	createFile(&l);


	FILE *file;
	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100], text[10];


	Pagina *p;
	Record r;
	Cliente c;

	int aux;
	int valor;

	p = CreateBTree();

	int op;

	do {
    	printf("\n\n============ MENU ============\n");
    	printf("1 - Incializar arvore\n");
    	printf("2 - Pesquisar Cliente\n");
    	printf("0 - Sair\n\n");
    	printf("Escolha a opção desejada: ");
    	scanf("%d", &op);
		
		switch(op) {
			case 1:
				if(p == NULL) {
					readArqIntervalo(&p);
					printf("Valores de CPF carregados no arquivo conforme parâmetros.\n");
				} else
					printf("Já constam valores carregados na Árvore B!\n");
			break;
			case 2:
				if(p == NULL)
					printf("Arvore B está vazia!\n");
				else {
					printf("Informe o valor do CPF a ser pesquisado: ");
					scanf("%d", &valor);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						c.cpf = valor;
						aux = FALSE;

						readArqClientes(r, &c, &aux);

						if(aux) {
							printf("Cliente: %s\n", c.nome);
							printf("Idade: %d\n", c.idade);
							printf("CPF: %d\n", c.cpf);
						} else {
							printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
						}
					}
				}
			break;
			case 3:
				if(p == NULL)
					printf("Arvore B vazia!\n");
				else {
					printf("Informe o valor do CPF para remover: ");
					scanf("%d", &valor);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						c.cpf = valor;
						aux = FALSE;

						readFileClientes(r, &c, &aux);

						if(aux) {
							printf("Cliente: %s\n", c.nome);
							printf("Idade: %d\n", c.idade);
							printf("CPF: %d\n", c.cpf);
						} else {
							printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
						}
					}
				}
			break;
			case 0:
				printf("Programa finalizado!\n");
				return EXIT_SUCCESS;
			default:
				printf("Opção inválida!\n");
		}
		
	} while (op != 0);

}


