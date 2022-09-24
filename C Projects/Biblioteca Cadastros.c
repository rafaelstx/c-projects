#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	LIVROS = 1, TESES = 2, PERIODICOS = 3, OP1 = 1, OP2 = 2, OP3 = 3
}ops;

typedef struct
{
	char autor[30];
	char titulo[30];
	int ano;
	char editora[30];
	char cidade[30];
	int chec;
}t_livro;


typedef struct
{
	char autor[30];
	char titulo[30];
	int mes;
	int ano;
	char universidade[30];
	char programa[30];
	char orientador[30];
	int valor;
	int chec;
}t_tese;

typedef struct
{
	char titulo[30];
	int volume;
	int mes;
	int ano;
	char editora[30];
	char cidade[30];
	int num_pag;
	int chec;
}t_peri;

typedef union
{
	t_livro livro;
	t_tese tese;
	t_peri periodico;
}acervo;

void cadastra(acervo *obras, int *posi, int  tam, ops opcoes);
void consulta(acervo *obras, ops opcoes, int tam);

int main ()
{
	const int tam=5;
	acervo obras[tam];
	int i, op, posi;
	ops opcoes, opcoes1;
	
	for (i=0;i<tam;i++)
	
	
	posi = 0;
	do
	{
	   scanf("%d",&op);
	   opcoes1 = (ops)op;
	   switch(opcoes1)
	   {
		   case OP1:
		    {
		   	    if(posi==tam)
		   	   {
		   	  	  printf("Limite de cadastros excedido!\n");
			   }  
			   else
			   {
			   	  scanf("%d",&op);
	              opcoes = (ops)op;
	              cadastra(obras,&posi,tam,opcoes);
			   }
			   break;
		    }
		   
		   case OP2:
		   	{
		   		scanf("%d",&op);
	            opcoes = (ops)op;
	            consulta(obras,opcoes,tam);
	            break;
			}
			
		   case OP3:
		   	{
			    printf("Fim de execucao\n");
			    break;
			}
	   }
	}while (opcoes1!=3);
}

void cadastra(acervo *obras, int *posi, int  tam, ops opcoes)
{
	switch (opcoes)
	{
		case LIVROS:
			{
				scanf(" %[^\n]",obras[*posi].livro.autor);
				scanf(" %[^\n]",obras[*posi].livro.titulo);
				scanf("%d",& obras[*posi].livro.ano);
				scanf(" %[^\n]",obras[*posi].livro.editora);
				scanf(" %[^\n]",obras[*posi].livro.cidade);
				printf("-----Livro Cadastrado!-----\n");
				obras[*posi].livro.chec = 1;
				*posi = *posi + 1;
				break;
			}
	  	
		case TESES:
	  		{
	  		    scanf(" %[^\n]",obras[*posi].tese.autor);
				scanf(" %[^\n]",obras[*posi].tese.titulo);
				scanf("%d",& obras[*posi].tese.mes);
				scanf("%d",& obras[*posi].tese.ano);
				scanf(" %[^\n]",obras[*posi].tese.universidade);
				scanf(" %[^\n]",obras[*posi].tese.programa);	
				scanf(" %[^\n]",obras[*posi].tese.orientador);	
				scanf("%d",& obras[*posi].tese.valor);	
				printf("-----Tese Cadastrada!-----\n");
				obras[*posi].tese.chec = 2;
				*posi = *posi + 1;
				break;
			}
		
		case PERIODICOS:
			{
				scanf(" %[^\n]",obras[*posi].periodico.titulo);
				scanf("%d",& obras[*posi].periodico.volume);
				scanf("%d",& obras[*posi].periodico.mes);
				scanf("%d",& obras[*posi].periodico.ano);
				scanf(" %[^\n]",obras[*posi].periodico.editora);
				scanf(" %[^\n]",obras[*posi].periodico.cidade);
				scanf("%d",& obras[*posi].periodico.num_pag);
				printf("-----Periodico Cadastrado!-----\n");
				obras[*posi].periodico.chec = 3;
				*posi = *posi + 1; 
				break;
			}	
	}		
}

void consulta(acervo *obras, ops opcoes, int tam)
{
	int i;
	
	switch(opcoes)
	{
		case LIVROS:
			{
				for (i=0;i<tam;i++)
				if (obras[i].livro.chec == 1)
				{
					printf("Autor: %s\n", obras[i].livro.autor);
                    printf("Titulo: %s\n", obras[i].livro.titulo);
                    printf("Ano: %d\n", obras[i].livro.ano);
                    printf("Editora: %s\n", obras[i].livro.editora);
                    printf("Cidade: %s\n", obras[i].livro.cidade);
                    printf("-----------------\n");;
				}
				break;
			}
		case TESES:
			{
				for (i=0;i<tam;i++)
				if (obras[i].tese.chec == 2)
				{
					printf("Autor: %s\n", obras[i].tese.autor);
                    printf("Titulo: %s\n", obras[i].tese.titulo);
                    printf("Mes: %d\n", obras[i].tese.mes);
                    printf("Ano: %d\n", obras[i].tese.ano);
                    printf("Universidade: %s\n", obras[i].tese.universidade);
                    printf("Programa: %s\n", obras[i].tese.programa);
                    printf("Orientador: %s\n", obras[i].tese.orientador);
                    printf("Graduacao: %d\n", obras[i].tese.valor);
                    printf("-----------------\n");
				}
				break;
			}
		case PERIODICOS:
			{
				for (i=0;i<tam;i++)
				if (obras[i].periodico.chec == 3)
				{
					printf("Titulo: %s\n", obras[i].periodico.titulo);
                    printf("Volume: %d\n", obras[i].periodico.volume);
                    printf("Mes: %d\n", obras[i].periodico.mes);
                    printf("Ano: %d\n", obras[i].periodico.ano);
                    printf("Editora: %s\n", obras[i].periodico.editora);
                    printf("Cidade: %s\n", obras[i].periodico.cidade);
                    printf("Numero de paginas: %d\n", obras[i].periodico.num_pag);
                    printf("-----------------\n"); 
				}
				break;
			}		
	}
}
