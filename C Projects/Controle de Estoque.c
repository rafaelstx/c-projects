#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <locale.h>
#define N_MAX 10

typedef struct 
{
   char nome[50];
   int ponteiro;
} chave;

typedef struct 
{
   float v_compra;
   float v_venda;
   int q_estoque;
   int q_venda;
   int deletado;
} estoque_inf;

void cadastra_produto(FILE* chaves, FILE* infos, chave *cod, estoque_inf *info, int *cont);
void ordenar(FILE* chaves, FILE* infos, int cont, chave *cod, estoque_inf *info);
void iniciar(FILE *chaves, FILE *infos, chave *cod, estoque_inf *info, int cont);
void leitura(FILE *chaves, FILE *infos, chave *cod, estoque_inf *info, int *cont);
void quicksort(chave *cod, int n);
void sort(int Esq, int Dir, chave *cod);
void particao(int Esq, int Dir,int *i, int *j, chave *cod);
void mostra_estoque(chave *cod, estoque_inf *info, int cont);
void inserir(FILE* chaves, FILE* infos, chave *cod, estoque_inf *info, int cont);
void remove_estoque(chave *cod, estoque_inf *info, int *cont);
void venda(chave *cod, estoque_inf *info, int cont);
void lucro(chave *cod, estoque_inf *info, int cont);
void repor(chave *cod, estoque_inf *info, int cont);

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int x;
	chave cod[N_MAX];
	estoque_inf info[N_MAX];  
	int cont = 0;
	
	FILE *chaves;
	
	if( access("chave.bin", F_OK ) == 0 ) 
		chaves = fopen("chave.bin", "r+b");
	    
	else 
	{  
		chaves = fopen("chave.bin", "w+b");	
		
	}
	
	FILE *infos;
	
	if( access("infs.bin", F_OK ) == 0 ) 
	{
	    infos = fopen("infs.bin", "r+b");
	    leitura(chaves, infos, cod, info, &cont);
	}
	else 
	{  
		infos = fopen("infs.bin", "w+b");
		iniciar(chaves, infos, cod, info, cont);	
	}
	
	do
	{
		system("cls");
		fflush(stdout);
	    printf(" 1. Vender\n");
	    printf(" 2. Cadastrar novo produto\n");
	    printf(" 3. Remover produto do estoque\n");
	    printf(" 4. Consultar estoque\n");
	    printf(" 5. Consultar lucro\n");
	    printf(" 6. Repor estoque\n");
	    printf(" 0. Sair\n");
	    printf("\n Opção: ");
	    fflush(stdout);
		scanf("%d",&x);
	    switch (x)
	    {
	        case 1:
	        {
	            venda(cod, info, cont);
	            break;
		    }
	
	        case 2:
	        {
	            cadastra_produto(chaves, infos, cod, info, &cont);
	            break;
	        }
	
	        case 3:
	        {
	            remove_estoque(cod, info, &cont);
	            break;
	        }
	        
	        case 4:
	        {
	            mostra_estoque(cod, info, cont);
	            break;
	        }
	        
	        case 5:
	        {
	            lucro(cod, info, cont);
	            break;
	        }
	        
	        case 6:
	        {
	            repor(cod, info, cont);
	            break;
	        }
	        
	        case 0:
	        {
	        	inserir(chaves, infos, cod, info, cont);
				break;
			}
			default: printf("ERRO: Opção invalida\n");	
	    }
	}while(x != 0);
	
	fclose(chaves);
	fclose(infos);
}

void cadastra_produto(FILE* chaves, FILE* infos, chave *cod, estoque_inf *info, int *cont)
{
	int aux, i, op = 1;
	
	do
  {
	aux = *cont;
	
	for(i=0;i<*cont;i++)
	{
		if (info[i].deletado == -1)
		{
			*cont = i;
		}
	}
	cod[*cont].ponteiro = *cont;
	
	system("cls");
	fflush(stdout);
	printf("Nome do produto: ");
	scanf(" %s", &cod[*cont].nome);
	
	printf("Valor de compra: ");
	scanf(" %f", &info[*cont].v_compra);
	
	printf("Valor de venda: ");
	scanf(" %f", &info[*cont].v_venda);
	
	printf("Quantidade em estoque: ");
	scanf(" %d", &info[*cont].q_estoque);
	
	printf("Quantidade vendida: ");
	scanf(" %d", &info[*cont].q_venda);
	info[*cont].deletado = 2;
	printf("\nProduto cadastrado com sucesso!\n");
	fflush(stdout);
	*cont = aux;
	*cont = *cont + 1;
	
	quicksort(cod, *cont);
	
	printf("\nDeseja cadastrar outro produto? \n");
	printf("\nSim(1)  Não(0): ");
	scanf("%d",&op);
  }while(op != 0);
  
}

void ordenar(FILE* chaves, FILE* infos, int cont, chave *cod, estoque_inf *info)
{
	fseek(chaves, 0, SEEK_SET);
	fseek(infos, 0, SEEK_SET);
}

void iniciar(FILE *chaves, FILE *infos, chave *cod, estoque_inf *info, int cont) 
{
	int i;
		
	for(i=0;i<N_MAX;i++)
	{
		cod[i].ponteiro = -1;
		info[i].deletado = -1;
		info[i].q_estoque = -1;
		info[i].q_venda = -1;
		info[i].v_compra = -1;
		info[i].v_venda = -1;
	}
}

void leitura(FILE *chaves, FILE *infos, chave *cod, estoque_inf *info, int *cont)
{
	int i,aux;
		

	fread(&cod[0], sizeof(chave), N_MAX , chaves);
	fread(&info[0], sizeof(estoque_inf), N_MAX , infos);


	for (i=0;i<N_MAX;i++)
	{
		aux = cod[i].ponteiro;
		if((info[i].deletado == 2)&&(aux >= 0))
		{
			*cont = *cont + 1;
		}
	}	
}

void mostra_estoque(chave *cod, estoque_inf *info, int cont)
{
	int i,x,aux=0;
	
	for(i=0;i<N_MAX;i++)
	{
		x = cod[i].ponteiro; 
		
		if((info[x].deletado == 2)&&(x >= 0))
		{
		    fflush(stdout);
		    printf("\nNome: %s\n",cod[i].nome);
		    printf("Valor de Compra: %.2f\n",info[x].v_compra);
		    printf("Valor de Venda: %.2f\n",info[x].v_venda);
		    printf("Quantidade em estoque: %d\n",info[x].q_estoque);
		    printf("Quantidade Vendida: %d\n",info[x].q_venda);
		    fflush(stdout);
		    aux=1;
		}
	}
	if(aux == 0)
	{
		printf("\nNenhum produto em estoque \n");
	}
	
	printf("\nAperte 0 para voltar ao menu: ");
	scanf("%d",&x);
}

void inserir(FILE* chaves, FILE* infos, chave *cod, estoque_inf *info, int cont)
{
	int x;
	x = cont;
	ordenar(chaves,infos,x,cod,info);
	fwrite(&cod[0], sizeof(chave), N_MAX, chaves);
	fwrite(&info[0], sizeof(estoque_inf), N_MAX, infos);
	printf(" Finalizando programa...");
	
}

void quicksort(chave *cod, int n)
{
  sort(0, n-1, cod);
}

void sort(int Esq, int Dir, chave *cod)
{
  int i,j;
  particao(Esq, Dir, &i, &j, cod);
  if (Esq < j)
	 sort(Esq, j, cod);
  if (i < Dir)
     sort(i, Dir, cod);
}

void particao(int Esq, int Dir,int *i, int *j, chave *cod)
{
  chave x, w;
  *i = Esq; *j = Dir;

  x = cod[(*i + *j)/2];

  do
  {         
    while(strcmp(x.nome, cod[*i].nome) > 0)
	     (*i)++;
    while(strcmp(x.nome, cod[*j].nome) < 0)
        (*j)--;

    if (*i <= *j)
    {

      w = cod[*i];
      cod[*i] = cod[*j];
      cod[*j] = w;
      (*i)++;
      (*j)--;
    }

  } while (*i <= *j);
}

void remove_estoque(chave *cod, estoque_inf *info, int *cont)
{
	char x[50];
	int i,aux=0,y,z;
	
	do
	{
	system("cls");
	printf(" Digite o nome do produto que deseja remover: ");
	scanf("%s",&x);
	
	for (i=0;i<N_MAX;i++)
	{
		if(strcmp(x,cod[i].nome) == 0)
		{
			aux = 1;
			break;
		}
	}
	
	if(aux == 0)
	{
	printf(" \nProduto não encontrado no estoque ");
	printf(" \n(0) - Voltar ao menu ");
	printf(" \n(1) - Digitar novamente\n");
	scanf("%d",&y);
	}
	else
	{
		strcpy (cod[i].nome,".");
		z = cod[i].ponteiro;
		info[z].deletado = -1;
		cod[i].ponteiro = -1;
		printf(" \nProduto removido com sucesso\n ");
		printf(" \n(0) - Voltar ao menu ");
		printf(" \n(1) - Digitar novamente\n");
		scanf("%d",&y);
		quicksort(cod, *cont);
	}
	}while(y != 0);
}

void venda(chave *cod, estoque_inf *info, int cont)
{
	int y=0,z,i,aux,p;
	char x[50];
	
	do
	{
		system("cls");
	    printf(" Digite o nome do produto que irá vender: ");
	    scanf("%s",&x);
	    
	    for (i=0;i<cont;i++)
	    {
		    if(strcmp(x,cod[i].nome) == 0)
		    {
			    aux = 1;
			    break;
		    }
	    }
	
	    if(aux == 0)
      	{
         	printf(" \nProduto não encontrado no estoque ");
        	printf(" \n(0) - Voltar ao menu ");
        	printf(" \n(1) - Digitar novamente\n");
        	scanf("%d",&y);
    	}
	    else
	    {
		    z = cod[i].ponteiro;
		    printf(" Valor: %.2f \n",info[z].v_venda);
			printf(" Temos %d unidade(s) disponível do produto %s, quantas você irá vender?: ", info[z].q_estoque, cod[i].nome);
		    scanf("%d",&p);
		    
		    do
		    {
		    	if(p>info[z].q_estoque)
		    	{
		    		printf("\n Quantidade indisponível, digite novamente:  ");
		    		scanf("%d",&p);
				}
			}while(p > info[z].q_estoque);
			
			info[z].q_estoque = info[z].q_estoque - p;
			info[z].q_venda = info[z].q_venda + p;
			printf("\n Produto vendido com sucesso\n");
			printf("\n (0) Voltar ao menu \n");
			printf("\n (1) Vender novamente \n");
			scanf("%d",&y);
	    }
	}while(y != 0);
}

void lucro(chave *cod, estoque_inf *info, int cont)
{
	int i,x,y;
	
	for(i=0;i<N_MAX;i++)
	{
		x = cod[i].ponteiro; 
		
		if((info[x].deletado == 2)&&(x >= 0))
		{
		    fflush(stdout);
		    printf("\nNome: %s\n",cod[i].nome);
		    printf("Valor total de vendas: %.2f\n",info[x].v_venda * info[x].q_venda );
		    printf("Lucro do produto: %.2f\n",(info[x].v_venda * info[x].q_venda) - ((info[x].q_venda + info[x].q_estoque) * (info[x].v_compra)));
		    fflush(stdout);
		}
	}
	
	printf(" \nDigite 0 para voltar ao menu: ");
	scanf("%d",&y);
}
void repor(chave *cod, estoque_inf *info, int cont)
{
	int achou,i,y,z,aux = 0;
	char x[50];
	system("cls");
	printf("Nome do produto: ");
	scanf("%s",&x);
	
    for(i=0;i<N_MAX;i++)
    {
    	if(strcmp(x,cod[i].nome) == 0)
    	{
    		aux = 1;
    		y = cod[i].ponteiro;
    		printf("\nO produto %s tem %d unidades disponíveis em estoque, quanto deseja repor?: ", cod[i].nome,info[y].q_estoque);
    		
    		do
    		{
    			scanf("%d",&z);
    			info[y].q_estoque = info[y].q_estoque +z;
    			printf("\nReposição efetuada com sucesso");
    			printf("\nAgora o produto possui %d unidades disponíveis\n",info[y].q_estoque);
    			
    			if(z<=0)
    			printf("\nValor inválido");
    			
			}while(z<=0);
    		break;
		}
		
	}
	if(aux == 0)
		{
		printf("Produto não encontrado");
		}
	
	
	printf("\nDigite 0 para voltar ao menu: ");
	scanf("%d",&z);
}
