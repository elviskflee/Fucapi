#include "bibliotecaHash.h"

int criar(hash **raiz, int *contaCJ, int *atualCJ){
	int i, posicaoLivre;
	if(*contaCJ>50)
		return -1;
	
	*contaCJ+= 1;
	*atualCJ+= 1;
	while(raiz[*atualCJ % 50]!= 0)
		*atualCJ+= 1;
	posicaoLivre= *atualCJ % 50;
	raiz[posicaoLivre]= (hash* ) malloc(sizeof(hash));
	if(raiz[posicaoLivre] == 0)
		return -2;
	
	raiz[posicaoLivre]->id= *atualCJ;
	raiz[posicaoLivre]->numChaves= 0;
	for(i= 0; i< 50; i++){
		raiz[posicaoLivre]->l[i]= (listaEnc* ) malloc(sizeof(listaEnc));
		raiz[posicaoLivre]->l[i]->chave= 0;
		raiz[posicaoLivre]->l[i]->prox= NULL;
	}
	
	return *atualCJ;
}

int inserir(hash **raiz, int valor, int id){
	int duplicado, hashify, conjunto;
	listaEnc *aux, *novo;
	
	conjunto= id%50;
	duplicado= busca(raiz, valor, conjunto);
	if(duplicado == -2)
		return -50;
	if (duplicado > 0)
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

int busca(hash **raiz, int valor, int id){
	int hashify, conjunto, resultado= -1;
	listaEnc *aux;
	
	conjunto= id%50;
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

void GNA(hash **raiz, int id){
	int aleatorio[50];
	int pow16= pow(2,16), i, conjunto= id%50;
	int quantidade= MAXCHAVES;
	
	if(raiz[conjunto]== 0)
		printf("\nA Tabela nao existe");
	else{
		srand(time(NULL));						// semente inicial

		for(i= 0; i<quantidade; i++){
			aleatorio[i]= rand()%131072- pow16; 	// numeros entre -2^16 e +2^16-1
			inserir(raiz, aleatorio[i], conjunto);	// numeros entre -2^16 e +2^16,
													//zero eh reservado p/
													// posicao vazia na tabela hash
		}
		
	}
}

int excluir(hash **raiz,int valor, int id){
	int i, posicao, conjunto;
	listaEnc *exlista, *aux;
	
	conjunto= id%50;
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

void unir(hash **raiz, int *contaCJ, int *atualCJ, int id1, int id2){
	int novoHash= -1, i, conjunto1, conjunto2;
	listaEnc *aux1, *aux2;
	
	conjunto1= id1%50;
	conjunto2= id2%50;
	if(raiz[conjunto1]!= 0 && raiz[conjunto2]!= 0)
		novoHash= criar(raiz, contaCJ, atualCJ);
	else 												// Caso -2
		novoHash= -2;									// uma das listas nao existe
	if(novoHash > -1){					// Se == -1: numero max de conjuntos atingido
		for(i=0; i<50; i++){
			if(raiz[conjunto1]->l[i]->chave!= 0){		// Varre o Conj 1
				aux1= raiz[conjunto1]->l[i];
				inserir(raiz, aux1->chave, novoHash);	// Insere no novo Conj todas as chaves
				aux1= aux1->prox;
				while (aux1!= NULL){					// verifica dentro das listas encadeadas
					inserir(raiz, aux1->chave, novoHash);
					aux1= aux1->prox;
				}
			}
			if(raiz[conjunto2]->l[i]->chave!= 0){		// Varre o Conj 1
				aux2= raiz[conjunto2]->l[i];
				inserir(raiz, aux2->chave, novoHash);	// Insere no novo Conj todas as chaves
				aux2= aux2->prox;
				while (aux2!= NULL){					// verifica dentro das listas encadeadas
					inserir(raiz, aux2->chave, novoHash);
					aux2= aux2->prox;
				}
			}
		}
	}
	
}

void listar(hash **raiz, int id){
	int i, conjunto;
	listaEnc *aux;
	
	conjunto= id%50;
	if(raiz[conjunto]== NULL)
		printf("\nO conjunto %d nao existe", conjunto);
	else{
		printf("\nConjunto %d:", conjunto);
		for(i=0; i<50; i++){					// Lista todos os elementos do conjunto;
			if(raiz[conjunto]->l[i]->chave== 0)	// Por Bucket
				printf("\nPosicao %d: X", i);	// X significa Bucket vazio.
			else{
				aux= raiz[conjunto]->l[i];
				printf("\nPosicao %d: %d", i, aux->chave);
				aux= aux->prox;
				while (aux!= NULL){				// verifica dentro das listas encadeadas
					printf(", %d", aux->chave);
					aux= aux->prox;
				}
			}
		}
	}
}

void ordem(hash **raiz, int id){
	listaEnc *aux;
	int i, v[50], j= 0, temp, conjunto;
	
	conjunto= id%50;
	for(i=0; i<50; i++)
		v[i]= 0;
	for(i=0; i<50; i++){						// Salva as chaves
		if(raiz[conjunto]->l[i]->chave!= 0){	// em um vetor desordenadamente
			aux= raiz[conjunto]->l[i];
			v[j]= aux->chave;
			j++;
			aux= aux->prox;
			while (aux!= NULL){					// verifica dentro das listas encadeadas
				v[j]= aux->chave;
				j++;
				aux= aux->prox;
			}
		}
	}
	printf("\nOrdem do conjunto %d: ", conjunto);
	
	for( i=1; i < 50; i++ ) {			// Ordenamento por insertion sort
		temp = v[i];
		j = i-1;
		while(j >= 0 && v[j] > temp){
			v[j+1] = v[j];
			j--;
		} 
		v[j+1] = temp;
	}

	i= 0;								// Impressao do vetor ordenado
	while(v[i] ==0)
		i++;
	if(v[i]!= 0)
		printf("%d", v[i]);
	for(i++; i<50; i++)
		printf(", %d", v[i]);
}
