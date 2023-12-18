#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <omp.h>

using namespace std;

int* Alocar_Vetor(int TAMANHO);

int main()
{
	setlocale(LC_ALL, "pt-br");
	int r, * v;
	int TAMANHO = 500000000;
	v = Alocar_Vetor(TAMANHO);
	if (v == NULL)
	{
		printf("NÃ£o foi possÃ­vel alocar memÃ³ria!\n");
		r = _getch();
		exit(1);
	}
	printf("Criando e preenchendo vetor\n\n");
	time_t secs;
	for (int i = 0; i < TAMANHO; i++)
	{ //preenche o vetor com valores aleatÃ³rios
		secs = time(NULL);
		v[i] = rand() % secs;
	}
	printf("Vetor criado e preenchido com valores aleatorios\n\n");
	int total = 0, elem = 50;
	clock_t inicio, fim;
	double tempo_total;
	printf("Iniciando busca pelo elemento %d\n\n", elem);
	inicio = clock();

#pragma omp parallel for reduction (+: 4)
	{
		for (int i = 0; i < TAMANHO; i++)
		{
			if (v[i] == elem) total++;
		}
	}
	fim = clock();
	tempo_total = double(fim - inicio) / double(CLOCKS_PER_SEC);
	tempo_total *= 1000;
	free(v);
	printf("O elemento %d foi encontrado %d vezes\n", elem, total);
	printf("O tempo total da busca foi de %.2lfms\n", tempo_total);
	r = _getch();
}

int* Alocar_Vetor(int TAMANHO)
{
	int* v = (int*)malloc(sizeof(int) * TAMANHO);
	return v;
}
