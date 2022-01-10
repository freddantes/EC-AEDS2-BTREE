#include "arq.h"

int get_random() { return (1000 + rand() % 9999); }

int get_randomIdade() { return (1 + rand() % 90); }

void writeArq(int inicio, int fim, char *valor) {
	FILE *arq;
	char *path = (char*)malloc((strlen(PATH_CLIENTES) + 15) * sizeof(char));

	char aux_inicio[20], aux_fim[20];

	sprintf(aux_inicio, "%d", inicio);
	sprintf(aux_fim, "%d", fim);

	strcpy(path, PATH_CLIENTES);
	strcat(aux_inicio, "...");
	strcat(path, strcat(aux_inicio, strcat(aux_fim, ".txt")));

	arq = fopen(path, "w");

	if(arq == NULL) {
		printf("Erro ao abrir o arquivo %s\n", aux_inicio);
		return;
	} else {
		fputs(valor, arq);
	}
	fclose(arq);
}

void readArqConcatenado(Lista *lista) {
	FILE *arqDados;
	FILE *arqCPF;
	FILE *arqIntervalo;

	Item item;
	item.valor = (char*)malloc(200 * sizeof(char));

	int cpf[1000];
	int cont = 0;

	int controle = TRUE;

	char *pathCPF = (char*)malloc(50 * sizeof(char));
	char *pathDados = (char*)malloc(50 * sizeof(char));
	char *pathIntervalo = (char*)malloc(50 * sizeof(char));

	char text[100], linha[100], intervalo[10];
	char *result;

	strcpy(pathCPF, "src/files/clientes-cpf.txt");
	strcpy(pathDados, "src/files/clientes-original.txt");
	strcpy(pathIntervalo, "src/files/clientes-intervalo.txt");

	arqDados = fopen(pathDados, "r");
	arqCPF = fopen(pathCPF, "r");
	arqIntervalo = fopen(pathIntervalo, "w");

	if(arqIntervalo == NULL) {
		printf("Erro ao abrir arquivo de Intervalos\n");
		return;
	}
	else {
		if(arqCPF == NULL) {
			printf("Erro ao abrir arquivo de CPFs\n");
			return;
		} else {
			while(!feof(arqCPF)) {
				result = fgets(linha, sizeof(linha), arqCPF);

				if(result)
					cpf[cont++] = atoi(linha);
			}
		}

		cont = 0;
		if(arqDados == NULL) {
			printf("Erro ao abrir arquivo dados originais\n");
			return;
		} else {
			while(!feof(arqDados)) {
				result = fgets(linha, sizeof(linha), arqDados);

				if(result) {
					token(linha);

					sprintf(text, "%d", get_randomIdade());

					strcat(linha, ",");
					strcat(linha, text);

					sprintf(text, "%d", cpf[cont++]);
					strcpy(intervalo, text);

					if(controle) {
						item.cpfInicio = cpf[cont-1];
						controle = FALSE;
						
						fputs(strcat(intervalo, "\n"), arqIntervalo);
					}

					strcat(text, ",");
					strcat(item.valor, strcat(text, strcat(linha, "\n")));

					if(cont % 10 == 0) {
						item.cpfFim = cpf[cont-1];

						LInsere(lista, item);
						fputs(strcat(intervalo, "\n"), arqIntervalo);

						item.valor = (char*)malloc(200 * sizeof(char));
						controle = TRUE;
					}
				}
			}
			// printf("cont: %d\n", cont);
		}
	}
	fclose(arqDados);
	fclose(arqCPF);
	fclose(arqIntervalo);

	free(pathCPF);
	free(pathDados);
	free(pathIntervalo);
}

void readArqIntervalo(Pagina **p) {
	FILE *arq;
	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100], text[10];
	Record r;
	int aux = TRUE;

	strcpy(path, "src/files/clientes-intervalo.txt");

	arq = fopen(path, "r");

	if(arq == NULL) {
		printf("Nao foi possivel abrir o arquivo de Intervalo.txt\n");
		return;
	} else {
		while(!feof(arq)) {
			result = fgets(linha, sizeof(linha), arq);

			if(result) {
				if(aux) {
					r.key = atoi(linha);
					aux = FALSE;
				} else {
					r.limite = atoi(linha);
					r.arquivo = (char*)malloc(20 * sizeof(char));					
					Insere(p, r);

					aux = TRUE;
				}
			}
		}
	}

	fclose(arq);
	free(path);
}

void readArqClientes(Record r, Cliente *c, int *aux) {
	FILE *arq;
	char *path = (char*)malloc(50 * sizeof(char));
	c->nome = (char*)malloc(20 * sizeof(char));

	char *result, linha[100];

	strcpy(path, PATH_CLIENTES);
	strcat(path, r.arquivo);
	strcat(path, ".txt");

	arq = fopen(path, "r");

	if(arq == NULL) {
		printf("Nao foi possivel abrir o arquivo %s!\n", r.arquivo);
		return;
	} else {
		while(!feof(arq)) {
			result = fgets(linha, sizeof(linha), arq);

			if(result) {
				tokenClientes(linha, c, aux);
				if(*aux) return;
			}
		}
	}

	fclose(arq);
	free(path);
}

void token(char *str) {
	const char sep[] = "<> , ' '";
	char *tokens;
	int aux = 0;
	
	tokens = strtok(str, sep);
	
	while(tokens != NULL) {
		if(aux == 1) {
			strcpy(str, tokens);
			return;
		}
        aux = 1;
		tokens = strtok(NULL, sep);
	}
}

void tokenClientes(char *str, Cliente *c, int *aux) {
	const char sep[] = ",";
	char *tokens;

	int controle = 0;
	
	tokens = strtok(str, sep);
	
	while(tokens != NULL) {
		if(controle == 0) {
			if((atoi(tokens) != c->cpf)) {
				*aux = FALSE;
				return;
			}
			*aux = TRUE;
		} else if(controle == 1) {
			strcpy(c->nome, tokens);
		} else if(controle == 2) {
			c->idade = atoi(tokens);
		}
		controle++;
		tokens = strtok(NULL, sep);
	}
}