#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cpf[15];
    long posicao;
} Registro;

typedef struct no {
    Registro reg;
    struct no *esquerda;
    struct no *direita;
} Arvore;

typedef struct{
	
	char nome[50];
	int idade;
	char cpf[15];	
	
}Pessoa;

Arvore *criarArvore(Registro reg) {
    Arvore *aux = (Arvore*)malloc(sizeof(Arvore));
    if (aux) {
        aux->reg = reg;
        aux->esquerda = NULL;
        aux->direita = NULL;
    }
    return aux;
}

Arvore *inserirArvore(Arvore *a, Registro reg) {
    if (a == NULL)
        return criarArvore(reg);

    if (strcmp(a->reg.cpf, reg.cpf) > 0) {
        a->esquerda = inserirArvore(a->esquerda, reg);
    } else {
        a->direita = inserirArvore(a->direita, reg);
    }
    return a;
}

Arvore *buscarArvore(Arvore *a, char *cpf) {
    if (a == NULL || strcmp(a->reg.cpf, cpf) == 0)
        return a;

    if (strcmp(a->reg.cpf, cpf) > 0)
        return buscarArvore(a->esquerda, cpf);
    else
        return buscarArvore(a->direita, cpf);
}

int main() {
    Arvore *a = NULL;
    Pessoa p;
    Registro reg;
    FILE *arq;
    long posicao;

    arq = fopen("PessoasBinarie.bin", "rb"); 
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    while (fread(&p, sizeof(Pessoa), 1, arq)) {
        posicao = ftell(arq) - sizeof(Pessoa);
        strcpy(reg.cpf, p.cpf);
        reg.posicao = posicao;
        a = inserirArvore(a, reg);
    }

    fclose(arq);


    char cpfBusca[15];
    printf("\nDigite o CPF para buscar: ");
    scanf("%s", cpfBusca);

    Arvore *resultado = buscarArvore(a, cpfBusca);
    
    if (resultado) {
        arq = fopen("PessoasBinarie.bin", "rb");
        if (arq == NULL) {
            printf("Erro ao abrir o arquivo!");
            return 1;
        }
        fseek(arq, resultado->reg.posicao, SEEK_SET);
        fread(&p, sizeof(Pessoa), 1, arq);
        fclose(arq);

        printf("\nNome: %s\nIdade: %d\nCPF: %s\n", p.nome, p.idade, p.cpf);
    } 
	else {
        printf("CPF não encontrado!\n");
    }

    return 0;
}



