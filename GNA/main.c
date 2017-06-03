#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gerarNA(int multiplicador, int semente, int incremento, int mod){
	semente= (multiplicador * semente + incremento)%mod;
	
	return semente;
}

int main(){
	int quantidade, i;
	char salvar= 'N';
	double multiplicador, semente, incremento,mod;
	double *resultados;
	
	multiplicador= 7727; // 967;
	semente= 5099; // 137;
	incremento= 4759 ;// 55001;
	mod= pow(2, 31)- 1;
	
	
	printf("/nMetodo da Congruencia:");
	printf("\nDigite a quantidade de numeros a serem gerados: ");
	scanf(" %d", &quantidade);
	resultados= (double *) malloc(quantidade * sizeof(double));
	
	for(i= 0; i<quantidade; i++){
		semente= gerarNA(multiplicador, semente, incremento,mod);
		resultados[i]= semente / (mod- 1.0);
		if (resultados[i]< 0)
			resultados[i]= -1*resultados[i];
		printf("\n%7d: %.60f", i+1, resultados[i]);
	}
	
	do{
		printf("\nDeseja gerar um arquivo? (S/N): ");
		scanf(" %c", &salvar);
	} while (salvar!= 'S' && salvar!= 'N');
	if(salvar== 'S'){
		FILE *arquivo= fopen("numerosaleatorios.csv","w");
		if(arquivo== NULL){
			printf("Erro ao abrir arquivo!\n");
			exit(1);
		}
		for(i= 0; i<quantidade; i++)
			fprintf(arquivo, "%.60f\n", resultados[i]);
		fclose(arquivo);
		printf("\nArquivo gerado com sucesso");
	}
	
	
	printf("\n");
	return 0;
}