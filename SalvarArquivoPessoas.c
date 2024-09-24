#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


typedef struct{
	
	char nome[50];
	int idade;
	char cpf[15];	
	
}Pessoa;

typedef struct no{
	
	Pessoa p;
	struct no * esquerda;
	struct no * direita;	
	
}Arvore;


Arvore * inserirArvore(Arvore * a, Pessoa p){
	if(a == NULL){
		Arvore * aux = (Arvore*)malloc(sizeof(Arvore));
		aux->p = p;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;		
	}
	else{
		if(a->p.idade > p.idade){
			a->esquerda = inserirArvore(a->esquerda, p);
		}
		else{
			a->direita = inserirArvore(a->direita, p);
		}
		return a;
	}
}

void mostrarArvore(Arvore * a){
	if(a){
		mostrarArvore(a->esquerda);
		printf("\n\n**********************************");
		printf("\n\nNome: %s", a->p.nome);
		printf("\n\nIdade: %d", a->p.idade);
		printf("\n\nCPF: %s", a->p.cpf);

		mostrarArvore(a->direita);
	}
	
}

void salvarEmArquivo(Arvore * a, FILE  * arq){
	if (a != NULL) {
		fwrite(&(a->p),sizeof(Pessoa),1, arq); //(variavel, sizeof(do tipo), tamanho, nome da variavel do arquivo)
		salvarEmArquivo(a->esquerda, arq);
		salvarEmArquivo(a->direita, arq);
	}		
}
	
void abrirArquivo(Arvore  * a){
	FILE * arq; // ponteiro para arquivo
	arq = fopen("PessoasBinarie.bin", "wb"); // abrir "arq" com fopen("nomedoarquivo", "wb" para sobreescrever se existente ou criar)
	
	if(arq !=NULL){
		puts("\n\nArquivo criado com sucesso");
		salvarEmArquivo(a, arq); // chama funcao de salvar a arvore no arquivo arq
		fclose(arq); // fechar arquivo
	}
}


int main(){
	Arvore * a = NULL;

	
	Pessoa p1 = {"Rafael", 31, "555.666.777-88"};
	Pessoa p2 = {"Thiago", 14, "123.456.789-09"};
	Pessoa p3 = {"Maria", 51, "987.654.321-00"};
	Pessoa p4 = {"Guilherme", 87, "111.222.333-44"};
	Pessoa p5 = {"Marcelo", 45,"555.666.777-88"};
	Pessoa p6 = {"Carlos", 21, "999.888.777-66"};	
	a = inserirArvore(a, p1);
	a = inserirArvore(a, p2);
	a = inserirArvore(a, p3);
	a = inserirArvore(a, p4);
	a = inserirArvore(a, p5);
	a = inserirArvore(a, p6);
	
	mostrarArvore(a);
	abrirArquivo(a);	
	
	
	
	return 0;
}
// referencia https://www.youtube.com/watch?v=Bi6kP0vwH0c //
