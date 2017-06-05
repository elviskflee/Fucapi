#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXCHAVES 50

typedef struct ListaEnc{
	int chave;
	struct ListaEnc *prox;
} listaEnc;

typedef struct Hash{
	int id;
	int numChaves;
	listaEnc *l[50];
} hash;

/* CRIAR:
 * Inicializa uma tabela hash nao populada (vetor de 50 posicoes);
 * Sucesso: retorna o numero da nova tabela;
 * Erro: numero maximo atingido, retorna -1.
 */
int criar(hash **raiz, int *contaCJ, int *atualCJ);

/* INSERIR:
 * Insere a chave de entrada no conjunto especificado;
 * Chave repetida: ignora, retorna "- posicao da chave na tabela";
 * Sucesso: insere, retorna "+ posicao da chave na tabela";
 * Erro: Conjunto nao existe, retorna -1.
 */
int inserir(hash **raiz, int valor, int conjunto);

/* BUSCA:
 * Se o conjunto nao existe, retorna -2;
 * se o conjunto existe e a chave nao existe, retorna -1;
 * senao, retorna a posicao na tabela.
 */
int busca(hash **raiz, int valor, int conjunto);

/*Gerar Numeros Aleatorios:
 * Popula um vetor com valores entre -2^16 e +2^16;
 * e insere no conjunto de entrada;
 * zero reservado para indicar posicao vazia na tabela hash.
 */
void GNA(hash **raiz, int conjunto);

/* EXCLUIR:
 * Se o conjunto esta vazio, exclui o conjunto e retorna 0;
 * Se a chave existe, exlui e retorna a posicao na tabela;
 * Erro: se a chave nao existir, retorna -1;
 * Erro: se o conjunto nao existir, retorna -2;
 */
int excluir(hash **raiz, int valor, int conjunto);

/* UNIAO:
 * O novo conjunto3 nao deve ter chaves duplicadas;
 * Sucesso: definido por criar, retorna o numero da nova tabela;
 * Erro: um dos conjuntos nao existe, retorna -2;
 * Erro: definido por criar, retorna -1;
 * o conjunto 1 e 2 permanecem inalterados.
 */
void unir(hash **raiz, int *contaCJ, int *atualCJ, int conjunto1, int conjunto2); 

/* LISTAR:
 * Lista todos os elementos do conjunto;
 * Por Bucket.
 */
void listar(hash **raiz, int conjunto);

/* ORDEM:
 * Lista todos os elementos da tabela de entrada;
 * Por ordem crescente, separados por virgula e em uma unica linha.
 */
 void ordem(hash **raiz, int conjunto);
 
 void quicksort(int *vetor, int tam);