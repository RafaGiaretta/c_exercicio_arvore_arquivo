#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cpf[15];
    long posicao;
} Registro; // "atributos" de registro

typedef struct no {
    Registro reg;
    struct no *esquerda;
    struct no *direita;
} Arvore; // "atributos" da arvore

typedef struct{
	
	char nome[50];
	int idade;
	char cpf[15];	
	
}Pessoa; // "atributos" de pessoa 

Arvore *criarArvore(Registro reg) { // cria arvore anulando tudo
    Arvore *aux = (Arvore*)malloc(sizeof(Arvore));
    if (aux) {
        aux->reg = reg;
        aux->esquerda = NULL;
        aux->direita = NULL;
    }
    return aux;
}

Arvore *inserirArvore(Arvore *a, Registro reg) { // insere na arvore 
    if (a == NULL) // verifica se ja existe 
        return criarArvore(reg); // preenche a "raiz" se nao

    if (strcmp(a->reg.cpf, reg.cpf) > 0) { // se existe compara para ordenar por registro
        a->esquerda = inserirArvore(a->esquerda, reg);
    } else {
        a->direita = inserirArvore(a->direita, reg);
    }
    return a;
}

Arvore *buscarArvore(Arvore *a, char *cpf) { // busca na arvore por CPF
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
    FILE *arq; // ponteiro arqivo
    long posicao; // var para armazenar posicao

    arq = fopen("PessoasBinarie.bin", "rb"); // abre arquivo
    if (arq == NULL) { // teste
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    while (fread(&p, sizeof(Pessoa), 1, arq)) {
        posicao = ftell(arq) - sizeof(Pessoa); // ftell para localizar a posicao no arquivo que comeca os dados da pessoa (por isso o - sizeof(Pessoa))
        strcpy(reg.cpf, p.cpf); // copia 
        reg.posicao = posicao;
        a = inserirArvore(a, reg); // insere na arvore
    }

    fclose(arq); // fecha arquivo
	int opcao = 1; // var para o menu
	
	while(opcao ==1){ // enquanto..
		
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
	        fseek(arq, resultado->reg.posicao, SEEK_SET); // vix
	        fread(&p, sizeof(Pessoa), 1, arq); // le o arquivo por pessoa 
	        fclose(arq);
	
	        printf("\nNome: %s\nIdade: %d\nCPF: %s\n", p.nome, p.idade, p.cpf);
	    } 
		else {
	        printf("CPF não encontrado!\n");
	    }
	    puts("\nDeseja efetuar outra consulta?");
	    puts("[1] - Nova consulta");
	    puts("[2] - SAIR." );
	    scanf("%d", &opcao);
	}
    return 0;
}



