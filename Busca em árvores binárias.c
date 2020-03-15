#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>

// Declara��o da Estrutura Carro
struct Carro {
	char nome[30];
	char marca[30];
	char cor[30];
	int ano;
	float preco;
};

// Declara��o da Estrutura da �rvore
struct No {
	int numero;
	struct Carro x;
	struct No *esquerda;
	struct No *direita;
};
typedef struct No No;

// Cria��o da �rvore
void criarArvore(No **pRaiz) {
	*pRaiz = NULL;
}

// Inser��o de um Elemento
void inserir(No **pRaiz, int numero, struct Carro x) {
	if(*pRaiz == NULL) {
		*pRaiz = (No *) malloc(sizeof(No));
		(*pRaiz)->esquerda = NULL;
		(*pRaiz)->direita = NULL;
		(*pRaiz)->numero = numero;
		(*pRaiz)->x = x;
	}
	else {
		if(numero < (*pRaiz)->numero)
			inserir(&(*pRaiz)->esquerda, numero, x);
		if(numero > (*pRaiz)->numero)
			inserir(&(*pRaiz)->direita, numero, x);
	}
}

// Teste N� Maior Direita
No *MaiorDireita(No **no) {
	if((*no)->direita != NULL)
		return MaiorDireita(&(*no)->direita);
	else {
		No *aux = *no;
		if((*no)->esquerda != NULL)
			*no = (*no)->esquerda;
		else
			*no = NULL;
		return aux;
	}
}

// Remo��o de um Elemento
void remover(No **pRaiz, int numero) {
	if(*pRaiz == NULL) {
		printf("\nN�mero n�o existe na �rvore!\n");
		return;
	}
	if(numero < (*pRaiz)->numero)
		remover(&(*pRaiz)->esquerda, numero);
	else if(numero > (*pRaiz)->numero)
		remover(&(*pRaiz)->direita, numero);
	else {
		No *pAux = *pRaiz;
		if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL)) {
			free(pAux);
			printf("\nRemovido com Sucesso! \n");
			(*pRaiz) = NULL;
		} else {
			if ((*pRaiz)->esquerda == NULL) {
				(*pRaiz) = (*pRaiz)->direita;
				pAux->direita = NULL;
				free(pAux); pAux = NULL;
				printf("\nRemovido com Sucesso! \n");
			} else {
				if ((*pRaiz)->direita == NULL) {
					(*pRaiz) = (*pRaiz)->esquerda;
					pAux->esquerda = NULL;
					free(pAux); pAux = NULL;
					printf("\nRemovido com Sucesso! \n");
				} else {
					pAux = MaiorDireita(&(*pRaiz)->esquerda);
					pAux->esquerda = (*pRaiz)->esquerda;
					pAux->direita = (*pRaiz)->direita;
					(*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
					free((*pRaiz)); *pRaiz = pAux; pAux = NULL;
					printf("\nRemovido com Sucesso! \n");
				}
			}
		}
	}
}

// M�todo para Percurso Pr�-Ordem
void exibirPreOrdem(No **pRaiz) {
	if((*pRaiz) != NULL) {
		printf("%i\n", (*pRaiz)->numero);
		exibirPreOrdem(&(*pRaiz)->esquerda);
		exibirPreOrdem(&(*pRaiz)->direita);
	}
}

// M�todo para Percurso Em Ordem
void exibirEmOrdem(No **pRaiz) {
	if((*pRaiz) != NULL) {
		exibirEmOrdem(&(*pRaiz)->esquerda);
		printf("%i\n", (*pRaiz)->numero);
		exibirEmOrdem(&(*pRaiz)->direita);
	}
}

// M�todo para Percurso P�s-Ordem
void exibirPosOrdem(No **pRaiz) {
	if((*pRaiz) != NULL) {
		exibirPosOrdem(&(*pRaiz)->esquerda);
		exibirPosOrdem(&(*pRaiz)->direita);
		printf("%i\n", (*pRaiz)->numero);
	}
}

// Impress�o da �rvore
int imprimir(No **pRaiz) {
	if((*pRaiz) != NULL) {
		if((*pRaiz) != NULL)
			printf("\nPai %i\n",(*pRaiz)->numero);
		if((*pRaiz)->esquerda != NULL)
			printf("Esq: %i\t",(*pRaiz)->esquerda->numero);
		else
			printf("Esq: NULL\t");
		if((*pRaiz)->direita != NULL)
			printf("Dir: %i\t",(*pRaiz)->direita->numero);
		else
			printf("Dir: NULL\t");
		if((*pRaiz)->esquerda != NULL)
			imprimir(&(*pRaiz)->esquerda);
		if((*pRaiz)->direita != NULL)
			imprimir(&(*pRaiz)->direita);
	} else
		printf("A �rvore est� vazia! \n");
}

// Programa Principal
int main () {
	struct Carro ca;
	int c;
	No *pRaiz;
	criarArvore(&pRaiz);
	setlocale(LC_ALL, "portuguese");
	int op;
	
	do {
		system("CLS");
		printf("* * * MENU DE OP��ES * * *\n\n");
		printf("1. Incluir n�: \n");
		printf("2. Remover n�: \n");
		printf("3. Buscar pr�-ordem: \n");
		printf("4. Buscar em ordem: \n");
		printf("5. Buscar p�s-ordem: \n");
		printf("6. Imprimir �rvore \n");
		printf("\nOp��o [0 para encerrar]: ");
		scanf("%d", &op);
		
		switch(op) {
		case 1:
			system("CLS");
			printf("\nInforme as seguintes caracter�sticas:\n");
			printf("\nCarro: ");
			scanf("%s", &ca.nome);
			printf("\nMarca: ");
			scanf("%s",&ca.marca);
			printf("\nCor: ");
			scanf("%s",&ca.cor);
			printf("\nAno de Fabrica��o: ");
			scanf("%d", &ca.ano);
			printf("\nPre�o do Ve�culo: ");
			scanf("%f", &ca.preco);
			printf("\nDigite um N�mero (Refer�ncia na �rvore): ");
			scanf("%d",&c);
			inserir(&pRaiz,c,ca);
			system("PAUSE");
			break;
		case 2:
			system("CLS");
			printf("\nDigite um N�mero: ");
			scanf("%d",&c);
			remover(&pRaiz,c);
			system("PAUSE");
			break;
		case 3:
			system("CLS");
			exibirPreOrdem(&pRaiz);
			system("PAUSE");
			break;
		case 4:
			system("CLS");
			exibirEmOrdem(&pRaiz);
			system("PAUSE");
			break;
		case 5:
			system("CLS");
			exibirPosOrdem(&pRaiz);
			system("PAUSE");
			break;
		case 6:
			system("CLS");
			imprimir(&pRaiz);
			printf("\n");
			system("PAUSE");
			break;
		case 0:
			break;
		default:
			printf("\n\nOp��o Inv�lida. \n");
			system("PAUSE");
			break;
		}
	} while(op!=0);
	return 0;
}

