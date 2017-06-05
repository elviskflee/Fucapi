#include "bibliotecaHash.h"

int main(){
	int flag, op= 1, valor, id;
	int i, contaCJ= 0, atualCJ= -1;
	hash *raiz[50];
	
	for(i= 0; i< 50; i++)
		raiz[i]= 0;
	printf("Inicializado\n");
	
	// MENU:
	do{
		do{
			CLR
			printf("HASH:");
			printf("\n1)Criar uma tabela nova");
			printf("\n2)Inserir uma chave");
			printf("\n3)Buscar uma chave");
			printf("\n4)Sobreescrever uma tabela com valores aleatorios");
			printf("\n5)Excluir uma chave");
			printf("\n6)Unir duas tabelas");
			printf("\n7)Listar todas as tabelas existentes");
			printf("\n8)Listar todas as chaves de uma tabela por Bucket");
			printf("\n9)Listar todas as chaves de uma tabela em Ordem Crescente");
			printf("\n0)Sair\n");
			if(op<0 || op > 9)
				printf("\nEntrada invalida");
			printf("\nDigite sua opcao: ");
			scanf(" %d", &op);
		} while(op<0 || op > 9);
		
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
				getchar();
				while(getchar()!='\n');
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
				getchar();
				while(getchar()!='\n');
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
				getchar();
				while(getchar()!='\n');
				break;
				
			case 4:
				CLR
				printf("\n4)Sobreescrever uma tabela com valores aleatorios");
				printf("\nDigite o ID da Tabela: ");
				scanf(" %d", &id);
				GNA(raiz, id);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
				
			case 5:
				CLR
				printf("\n5)Excluir uma chave");
				printf("\nDigite o Valor da Chave e o ID da Tabela: ");
				scanf(" %d %d", &valor, &id);
				flag= excluir(raiz, valor, id, &contaCJ);
				if (flag== -2)
					printf("\nErro: A Tabela %d nao existe", id);
				else if (flag== -1)
					printf("\nErro: A chave %d nao existe", valor);
				else if(flag== 0)
					printf("\nA Tabela %d foi excluida", id);
				else
					printf("\nChave %d removida da posicao %d da Tabela %d", valor, flag, id);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
				
			case 6:
				CLR
				printf("\n6)Unir duas tabelas");
				printf("\nDigite os IDs das Tabelas: ");
				scanf(" %d %d", &valor, &id);
				flag= unir(raiz, &contaCJ, &atualCJ, valor, id);
				if (flag== -2)
					printf("\nErro: Pelo menos uma das Tabelas nao existe");
				else if (flag== -1)
					printf("\nErro: Limite de Tabelas atingido");
				else
					printf("\nTabelas %d e %d unidas na Tabela %d", valor, id, flag);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
				
			case 7:
				CLR
				printf("\n7)Listar todas as tabelas existentes");
				for(i= 0; i<50; i++)
					if(raiz[i]!= 0)
						printf("\nTabela %d", raiz[i]->id);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
				
			case 8:
				CLR
				printf("\n8)Listar todas as chaves de uma tabela por Bucket");
				printf("\nDigite o ID da Tabela: ");
				scanf(" %d", &id);
				listar(raiz, id);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
				
			case 9:
				CLR
				printf("\n9)Listar todas as chaves de uma tabela em Ordem Crescente");
				printf("\nDigite o ID da Tabela: ");
				scanf(" %d", &id);
				ordem(raiz, id);
				printf("\n\nDigite Enter para continuar.. ");
				getchar();
				while(getchar()!='\n');
				break;
		}
	} while(op!= 0);
	
	printf("\n");
	return 0;
}
