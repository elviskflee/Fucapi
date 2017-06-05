#include "bibliotecaHash.h"

int criar(hash **raiz, int *contaCJ, int *atualCJ){
	int i;
	if(*contaCJ>50)
		return -1;
	
	*contaCJ+= 1;
	*atualCJ+= 1;
	
	raiz[*atualCJ]= (hash* ) malloc(sizeof(hash));
	if(raiz[*atualCJ] == 0)
		return -2;
	
	raiz[*atualCJ]->id= *atualCJ;
	raiz[*atualCJ]->numChaves= 0;
	for(i= 0; i< 50; i++){
		raiz[*atualCJ]->l[i]= (listaEnc* ) malloc(sizeof(listaEnc));
		raiz[*atualCJ]->l[i]->chave= 0;
		raiz[*atualCJ]->l[i]->prox= NULL;
	}
	
	return *atualCJ;
}

int inserir(hash **raiz, int valor, int conjunto){
	int duplicado, hashify;
	listaEnc *aux, *novo;
	duplicado= busca(raiz, valor, conjunto);
	if (duplicado > -1)
		return -duplicado;
	hashify= (16183*valor)%199;
	hashify%= MAXCHAVES;
	if(hashify<0)
		hashify= -hashify;
	if(raiz[conjunto]->l[hashify]->chave == 0)
		raiz[conjunto]->l[hashify]->chave = valor;
	else{
		novo = (listaEnc *) malloc(sizeof(listaEnc));
		novo->chave= valor;
		novo->prox= NULL;
		aux= raiz[conjunto]->l[hashify];
		while(aux->prox!= 0)
			aux= aux->prox;
		aux->prox= novo;
	}
	raiz[conjunto]->numChaves+= 1;
	return hashify;
}

int busca(hash **raiz, int valor, int conjunto){
	int hashify, resultado= -1;
	listaEnc *aux;
	if(raiz[conjunto]== NULL)
		return -2;
	hashify= (16183*valor)%199;
	hashify%= MAXCHAVES;
	if(hashify<0)
		hashify= -hashify;
	aux= raiz[conjunto]->l[hashify];
	while(aux!= 0){
		if(aux->chave == valor)
			resultado= hashify;
		aux= aux->prox;
	}
	return resultado;
}

void GNA(hash **raiz, int conjunto){
	int aleatorio[50];
	int pow16= pow(2,16), i;
	int quantidade= MAXCHAVES;
	srand(time(NULL));						// semente inicial

	for(i= 0; i<quantidade; i++){
		aleatorio[i]= rand()%131072- pow16; 	// numeros entre -2^16 e +2^16-1
		inserir(raiz, aleatorio[i], conjunto);	// numeros entre -2^16 e +2^16,
												//zero eh reservado p/
												// posicao vazia na tabela hash
	}
}

int excluir(hash **raiz,int valor, int conjunto){
	int i, posicao;
	listaEnc *exlista, *aux;

	if(raiz[conjunto]== 0)
		return -2;
	else if(raiz[conjunto]->numChaves== 0){
		for(i=0; i<50; i++){
			exlista= raiz[conjunto]->l[i];
			free(exlista);
		}
		raiz[conjunto]= 0;
		return 0;
	}
	else if((posicao= busca(raiz, valor, conjunto))== -1)
		return -1;
	else{
		aux= raiz[conjunto]->l[posicao];
		if(aux->chave== valor){
			raiz[conjunto]->l[posicao]= aux->prox;
			free(aux);
			if(raiz[conjunto]->l[posicao]==0){
				raiz[conjunto]->l[posicao]= (listaEnc* ) malloc(sizeof(listaEnc));
				raiz[conjunto]->l[posicao]->chave= 0;
				raiz[conjunto]->l[posicao]->prox= NULL;
			}
			raiz[conjunto]->numChaves-= 1;
			return posicao;
		}
		else {
			exlista= aux->prox;
			while(exlista->chave!= valor){
				aux= aux->prox;
				exlista= aux->prox;
			}
			aux->prox= exlista->prox;
			free(exlista);
		}
		raiz[conjunto]->numChaves-= 1;
	}
	return posicao;
}

void unir(hash **raiz, int *contaCJ, int *atualCJ, int conjunto1, int conjunto2){
	int novoHash, i;
	listaEnc *aux1, *aux2;
	novoHash= criar(raiz, contaCJ, atualCJ);
	if(novoHash!= -1){
		for(i=0; i<50; i++){
			if(raiz[conjunto1]->l[i]->chave!= 0){
				aux1= raiz[conjunto1]->l[i];
				inserir(raiz, aux1->chave, novoHash);
				aux1= aux1->prox;
				while (aux1!= NULL){
					inserir(raiz, aux1->chave, novoHash);
					aux1= aux1->prox;
				}
			}
			if(raiz[conjunto2]->l[i]->chave!= 0){
				aux2= raiz[conjunto2]->l[i];
				inserir(raiz, aux2->chave, novoHash);
				aux2= aux2->prox;
				while (aux2!= NULL){
					inserir(raiz, aux2->chave, novoHash);
					aux2= aux2->prox;
				}
			}
		}
	}
	
}

void listar(hash **raiz, int conjunto){
	int i;
	listaEnc *aux;
	if(raiz[conjunto]== NULL)
		printf("\nO conjunto %d nao existe", conjunto);
	else{
		printf("\nConjunto %d:", conjunto);
		for(i=0; i<50; i++){
			if(raiz[conjunto]->l[i]->chave== 0)
				printf("\nPosicao %d: X", i);
			else{
				aux= raiz[conjunto]->l[i];
				printf("\nPosicao %d: %d", i, aux->chave);
				aux= aux->prox;
				while (aux!= NULL){
					printf(", %d", aux->chave);
					aux= aux->prox;
				}
			}
		}
	}
}


void ordem(hash **raiz, int conjunto){
	listaEnc *aux;
	int i, v[50], j= 0;
	
	for(i=0; i<50; i++)
		v[i]= 0;
	for(i=0; i<50; i++){
		if(raiz[conjunto]->l[i]->chave!= 0){
			aux= raiz[conjunto]->l[i];
			v[j]= aux->chave;
			j++;
			aux= aux->prox;
			while (aux!= NULL){
				v[j]= aux->chave;
				j++;
				aux= aux->prox;
			}
		}
	}
	printf("\nOrdem do conjunto %d: ", conjunto);
	
	quicksort(v,(sizeof v / sizeof v[0]));
	i= 0;
	while(v[i] ==0);
	if(v[i]!= 0)
		printf("%d", v[i]);
	for(i++; i<49; i++)
		if(v[i]!= 0)
			printf(", %d", v[i]);

}

void quicksort(int *vetor, int tam){
	if (tam < 2) return;
 
	int pivot = vetor[tam / 2];

	int i, j;
	for (i = 0, j = tam - 1; ; i++, j--)
	{
	while (vetor[i] < pivot) i++;
	while (vetor[j] > pivot) j--;

	if (i >= j) break;

	int temp = vetor[i];
	vetor[i]     = vetor[j];
	vetor[j]     = temp;
	}

	quicksort(vetor, i);
	quicksort(vetor + i, tam - i);

}