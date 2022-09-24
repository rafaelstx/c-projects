#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void receber_valores_matriz(int altura, int largura, int **matriz);
void criar_arquivo(int altura, int largura, int **matriz, FILE* imagem_padrao);
void limiarizacao(int altura, int largura, int **matriz);
void negativo(int altura, int largura, int **matriz);
void histograma(int altura, int largura, int **matriz);


int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int **matriz;
	int altura, largura, i, j,x;
	FILE* imagem_padrao;
	
	printf("Entre com a largura da matriz: ");
	scanf("%d",&largura);
	printf("Entre com a altura da matriz: ");
	scanf("%d",&altura);
	
	matriz = malloc(largura * sizeof(int *));
	for (i=0;i<largura;i++)
	{
		matriz[i] = malloc(altura * sizeof(int));
	}
	
	receber_valores_matriz(altura, largura, matriz);
	criar_arquivo(altura, largura, matriz, imagem_padrao);
	system("cls");
	
	printf("Imagem criada!!!\n");
	printf("1. Limiarizar a imagem\n");
	printf("2. Negativar a imagem\n");
	printf("3. Gerar o Histograma\n");
	printf("0. Sair\n");

	
	do
	{
		printf("\nO que você deseja fazer com ela?: ");
	    scanf("%d",&x);
	    switch (x)
	    {
	        case 1:
	        {
	            limiarizacao(altura, largura, matriz);
	            break;
		    }
	
	        case 2:
	        {
	            negativo(altura, largura, matriz);
	            break;
	        }
	
	        case 3:
	        {
	            histograma(altura, largura, matriz);
	            break;
	        }
	        
	        case 0:
	        {
	        	printf("Finalizando programa...");
				break;
			}
			default: printf("ERRO: Opcao invalida\n");	
	    }
	}while(x != 0);
	
	for (i=0;i<largura;i++)
	free(matriz[i]);
	free(matriz);
	return 0;
} 


void receber_valores_matriz(int altura, int largura, int **matriz)
{
	int i,j,x;
	
	for(i=0;i<largura;i++)
	{
		printf("Preencha os valores da linha %d (APENAS VALORES ENTRE 0 E 250):\n",i);
		for(j=0;j<altura;j++)
		{
			do
			{
				scanf("%d",&x);
			}while ((x<0)||(x>250));
			
			matriz[i][j] = x;
		}
	}
}


void criar_arquivo(int altura, int largura, int **matriz, FILE* imagem_padrao)
{
	int tons,i,j;
	//Criando arquivo
    imagem_padrao = fopen("imagem_padrão.pgm", "wb");
    
    //Tipo P2
    fprintf(imagem_padrao, "P2\n");
    
    //Colocando largura x altura
    fprintf(imagem_padrao, "%d %d\n", largura, altura);
    
    //Tom máximo de cinza
    fprintf(imagem_padrao, "255\n");
    
    for(i=0;i<largura;i++)
	{
		for(j=0;j<altura;j++)
		{
			tons = matriz[i][j];
			fprintf(imagem_padrao, "%d ", tons);
		}
		
		fprintf(imagem_padrao, "\n");
	}
	fclose(imagem_padrao);
}


void limiarizacao(int altura, int largura, int **matriz)
{
	int tons,i,j;
	
	FILE* imagem_limiarizada;
    imagem_limiarizada = fopen("imagem_limiarizada.pgm", "wb");
    fprintf(imagem_limiarizada, "P2\n");
    fprintf(imagem_limiarizada, "%d %d\n", largura, altura);
    fprintf(imagem_limiarizada, "255\n");
    
    for(i=0;i<largura;i++)
	{
		for(j=0;j<altura;j++)
		{
			if(matriz[i][j] > 150)
			{
				tons = 255;
			    fprintf(imagem_limiarizada, "%d ", tons);
			}
			else
			{
				tons = 0;
			    fprintf(imagem_limiarizada, "%d ", tons);
			}
		}
		
		fprintf(imagem_limiarizada, "\n");
	}
	fclose(imagem_limiarizada);
}


void negativo(int altura, int largura, int **matriz)
{
	int tons,i,j;
	
	FILE* imagem_negativada;
    imagem_negativada = fopen("imagem_negativada.pgm", "wb");
    fprintf(imagem_negativada, "P2\n");
    fprintf(imagem_negativada, "%d %d\n", largura, altura);
    fprintf(imagem_negativada, "255\n");
    
    for(i=0;i<largura;i++)
	{
		for(j=0;j<altura;j++)
		{
			tons = 255 - matriz[i][j];
			fprintf(imagem_negativada, "%d ", tons);
		}
		
		fprintf(imagem_negativada, "\n");
	}
	fclose(imagem_negativada);
}


void histograma(int altura, int largura, int **matriz)
{
	int i,j,cont=0,aux=0;
	int vet[255];
	for(i=0;i<=255;i++)
	vet[i] = 0;
	
	FILE* histograma;
	histograma = fopen("Histograma.txt", "wb");
	
	for(i=0;i<largura;i++)
	{
		for(j=0;j<altura;j++)
		{
			aux = matriz[i][j];
			vet[aux] = vet[aux] + 1;
		}
	}
	
	for(i=0;i<=255;i++)
	fprintf(histograma, "%d ", vet[i]);
	
	fclose(histograma);
}
