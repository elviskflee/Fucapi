#include "bibliotecaHash.h"

int main(){
	int flag, op= 1, valor, id;
	char c[1];
	int i, contaCJ= -1, atualCJ= -1;
	hash *raiz[50];
	
	for(i= 0; i< 50; i++)
		raiz[i]= 0;
	printf("\nInicializado");

	// MENU:
	do{
		do{
			CLR
			printf("\nHASH:");
			printf("\n1)Criar uma tabela nova");
			printf("\n2)Inserir uma chave");
			printf("\n3)Buscar uma chave");
			printf("\n4)Sobreescrever uma tabela com valores aleatorios");
			printf("\n5)Excluir uma chave");
			printf("\n6)Unir duas tabelas");
			printf("\n7)Listar todas as chaves de uma tabela por Bucket");
			printf("\n8)Listar todas as chaves de uma tabela em Ordem Crescente");
			printf("\n9)Sair\n");
			if(op<1 || op > 9)
				printf("\nEntrada invalida");
			printf("\nDigite sua opcao: ");
			scanf(" %d", &op);
		} while(op<1 || op > 9);
		switch(op){
			case 1:
				CLR
				printf("\n1)Criar uma tabela nova");
				flag= criar(raiz, &contaCJ, &atualCJ);
				if (flag== -1)
					printf("\nErro: Num maximo de conjuntos atingidos");
				else if (flag== -2){
					printf("\nErro: espaço nao alocado. Terminando a execucao\n");
					exit(1);
				}
				else
					printf("\nHash (ID: %d) criado.", atualCJ);
				printf("\n\nDigite Enter para continuar.. ");
				scanf("%c", &c[0]);
				fgets(c, 100, stdin);

				break;
			case 2:
				CLR
				printf("\n2)Inserir uma chave");
				printf("\nDigite o Valor da Chave e o ID da Tabela: ");
				scanf(" %d %d", &valor, &id);
				flag= inserir(raiz, valor, id);
				if (flag== -50)
					printf("\nErro: A Tabela %d nao existe", id);
				else if (flag < 0)
					printf("\nEntrada %d duplicada, posicao: %d da Tabela %d", valor, -flag, id);
				else
					printf("\nEntrada %d inserida na posicao: %d da Tabela %d", valor, flag, id);
				printf("\n\nDigite Enter para continuar.. ");
				scanf("%c", &c[0]);
				fgets(c, 100, stdin);
				break;
			case 3:
				CLR
				printf("\n3)Buscar uma chave");
				printf("\nDigite o Valor da Chave e o ID da Tabela: ");
				scanf(" %d %d", &valor, &id);
				flag= busca(raiz, valor, id);
				if (flag== -2)
					printf("\nErro: A Tabela %d nao existe", id);
				else if (flag ==-1)
					printf("\nA chave %d nao foi encontrada na Tabela %d", valor, id);
				else
					printf("\nA chave %d esta na posicao %d da Tabela %d", valor, flag, id);
				printf("\n\nDigite Enter para continuar.. ");
				scanf("%c", &c[0]);
				fgets(c, 100, stdin);
				break;
			case 4:
				CLR
				printf("\n4)Sobreescrever uma tabela com valores aleatorios");
				printf("\nDigite o ID da Tabela: ");
				scanf(" %d", &id);
				GNA(raiz, id);
				printf("\n\nDigite Enter para continuar.. ");
				scanf("%c", &c[0]);
				fgets(c, 100, stdin);
				break;
			case 5:
				
				break;
			case 6:
				
				break;
			case 7:
				
				break;
			case 8:
				
				break;
		}
		
		
	} while(op!= 9);
	
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
