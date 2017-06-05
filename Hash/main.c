#include "bibliotecaHash.h"

int main(){
	int flag;
	int i, contaCJ= -1, atualCJ= -1;
	hash *raiz[50];
	
	for(i= 0; i< 50; i++)
		raiz[i]= 0;
	printf("\nInicializado");
		
		
	flag= criar(raiz, &contaCJ, &atualCJ);
	if (flag== -1)
		printf("\nErro: Num maximo de conjuntos atingidos");
	else if (flag== -2){
		printf("\nErro: espaço nao alocado. Terminando a execucao\n");
		exit(1);
	}
	else
		printf("\nHash (ID: %d) criado.", atualCJ);
	scanf("%d",&i);
	
	
	flag= inserir(raiz, 10, 0);
	if (flag== -1)
		printf("\nErro: O conjunto nao existe");
	else if (flag < 0)
		printf("\nEntrada %d duplicada, posicao: %d", 10, -flag);
	else
		printf("\nEntrada %d inserida na posicao: %d", 10, flag);
	
	flag= inserir(raiz, 10, 0);
	if (flag== -1)
		printf("\nErro: O conjunto nao existe");
	else if (flag < 0)
		printf("\nEntrada %d duplicada, posicao: %d", 10, -flag);
	else
		printf("\nEntrada %d inserida na posicao: %d", 10, flag);
	
	flag= inserir(raiz, 12753, 0);
	if (flag== -1)
		printf("\nErro: O conjunto nao existe");
	else if (flag < 0)
		printf("\nEntrada %d duplicada, posicao: %d", 12753, -flag);
	else
		printf("\nEntrada %d inserida na posicao: %d", 12753, flag);
	
	
	
	flag= inserir(raiz, 100, 0);
	if (flag== -1)
		printf("\nErro: O conjunto nao existe");
	else if (flag < 0)
		printf("\nEntrada %d duplicada, posicao: %d", 100, -flag);
	else
		printf("\nEntrada %d inserida na posicao: %d", 100, flag);
		
	flag= excluir(raiz, 10, 0);
	if (flag== -2)
		printf("\nErro: O conjunto %d nao existe", 0);
	else if (flag== -1)
		printf("\nErro: A chave %d nao existe", 10);
	else if(flag== 0)
		printf("\nO conjunto %d foi excluido", 0);
	else
		printf("\nChave %d removida da posicao: %d", 10, flag);
	
	flag= criar(raiz, &contaCJ, &atualCJ);
	flag= inserir(raiz, 100, 1);
	flag= inserir(raiz, 90, 1);
	unir(raiz, &contaCJ, &atualCJ, 0, 1);
	//GNA(raiz, 0);
	
	ordem(raiz, 0);
	ordem(raiz, 1);
	ordem(raiz, 2);
	if(raiz[0]!= 0){
		flag= 0;
		for(i= 0;i<50; i++){
			if(raiz[0]->l[i]->chave==0)
				flag++;
		}
		printf("\nNo de listas vazias: %d", flag);
	}
	
	printf("\n");
	return 0;
}
