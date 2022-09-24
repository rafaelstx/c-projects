#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int cod_serv;
	char descr[20];
} serv;

typedef struct
{
	int cod_serv1;
	int num_serv;
	float valor_serv;
	int cod_cliente;
} serv1;

int busca_cad1(serv *tipos, int cont_tipos, int codigo);
void cad1(serv *tipos, int *cont_tipos, int codigo, char *descricao);
int busca2(serv1 prestados[][3], int *cont_prest, int dia,int servicos_dia);
void cad_serv(serv1 prestados[][3], int *cont_prest, int codserv, int num1, float valor, int codcliente, int dia);
int checagem(int cont_tipos, int codserv, serv *tipos);
void checagem2(float valor_min, float valor_max, serv1 prestados[][3], int servicos_dia, int dias);
void todos_serv(serv1 prestados[][3], serv *tipos, int dias, int servicos_dia, int cont_tipos);



int main (void)

{
	const int tam1 = 4;
	const int dias = 30;
	const int servicos_dia = 3;
	serv1 prestados[dias][servicos_dia];
	serv tipos[tam1];            //variaveis
	int cont_tipos,j,dia,codigo,op,i,achou=0,codserv,num1,codcliente,k;
	int cont_prest;
	float valor, valor_min, valor_max;
	char descricao[20];
	
	/////////////////////////
	for (i=0;i<tam1;i++)
	{                          
	tipos[i].cod_serv=0;
	strcpy(tipos[i].descr,"");
    }
                                        //zerando dados
    for (i=0;i<dias;i++)
    {
    	for(j=0;j<servicos_dia;j++)
    	{
		prestados[i][j].cod_serv1 = 0;
    	prestados[i][j].num_serv = 0;
    	prestados[i][j].valor_serv = 0;
    	prestados[i][j].cod_cliente = 0;
        }
	}
    //////////////////////////
    
	cont_tipos = 0;
	do
	{
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				{
					scanf("%d",&codigo);
					if (cont_tipos==tam1)
					{
						printf("Cadastro de tipos de servicos lotado\n");
					}
					else
					{
						achou = busca_cad1(tipos,cont_tipos,codigo);
						
						if(achou)
						{
							printf("Ja existe tipo de servico cadastrado com esse codigo\n");
						}
						else
						{
							int clear;
                            while ((clear = getchar()) != '\n' && clear != EOF) {} 
                            fgets(descricao, 20, stdin); 
							cad1(tipos,&cont_tipos,codigo,descricao);
							printf("Tipo de servico cadastrado com sucesso\n");
						}
					}
					break;
				}
			case 2:
				{
					dia=0;
					scanf("%d",&dia);
					achou = busca2(prestados,&cont_prest,dia,servicos_dia);
					
					if(achou)
					{
						printf("Todos os servicos prestados neste dia ja foram cadastrados\n");
					}
					else
					{
						scanf("%d",&codserv);
						achou = checagem(cont_tipos,codserv,tipos);
						
						if(achou)
						{
							scanf("%d",&num1);
	                        scanf("%f",&valor);
	                        scanf("%d",&codcliente);
							cad_serv(prestados, &cont_prest, codserv, num1, valor, codcliente, dia);
							printf("Servico cadastrado com sucesso\n");
						}
						else
						{
							printf("Codigo de servico invalido\n");
						}
					}
					break;
				}
			case 3:
				{
					scanf("%d",&dia);
					achou = busca2(prestados,&cont_prest,dia,servicos_dia);
					k = dia - 1;
					
					if(cont_prest > 0)
					{
						for (j=0;j<cont_prest;j++)
						printf("%d %d %.2f\n", prestados[k][j].cod_serv1, prestados[k][j].num_serv, prestados[k][j].valor_serv);
					}
					else
					{
						printf("Nenhum servico foi prestado neste dia\n");
					}
					break;
				}
			case 4:
				{
					scanf("%f",&valor_min);
					scanf("%f",&valor_max);
					checagem2(valor_min, valor_max, prestados, servicos_dia, dias);
					break;
				}
			case 5:
				{
					todos_serv( prestados, tipos, dias, servicos_dia, cont_tipos);
					break;
				}
			case 6:
			    {
			    	printf("Fim de execucao\n");
			    	break;
				}
			default: printf("Opcao invalida\n");		
		}
		
	}while(op != 6);
	
}



int busca_cad1(serv *tipos, int cont_tipos, int codigo)    //BUSCA CADASTRO
{
	int achou,i;
	achou=0;
	for(i=0;i<cont_tipos;i++)
	{
		if(codigo == tipos[i].cod_serv)
		{
			achou=1;
			break;
		}
	}
	return achou;
}

void cad1(serv *tipos, int *cont_tipos, int codigo, char *descricao)  //CADASTRO TIPOS
{
	tipos[*cont_tipos].cod_serv = codigo;
	strcpy(tipos[*cont_tipos].descr,descricao);
	*cont_tipos = *cont_tipos + 1;
}

int busca2(serv1 prestados[][3], int *cont_prest, int dia,int servicos_dia)  //BUSCA 2
{
	int j,aux,conta;
	conta=0;
	aux = dia - 1;
	
	for(j=0;j<servicos_dia;j++)
	{
		if (prestados[aux][j].valor_serv != 0)
		{
		conta++;
	    }
	*cont_prest = conta;    
	}
    if (conta == servicos_dia)
    {
    	return 1;
	}
	else
	{
		return 0;
	}
}

int checagem(int cont_tipos, int codserv, serv *tipos)     // CHECAGEM CASE 2
{
	int i,achou;
	achou = 0;
	for (i=0;i<cont_tipos;i++)
	{
		if (codserv == tipos[i].cod_serv)
		{
			achou = 1;
			break;
		}
   
	}
	return achou;
}

void cad_serv(serv1 prestados[][3], int *cont_prest, int codserv, int num1, float valor, int codcliente, int dia)  //CADASTRO MATRIZ
{
	int aux1,aux2;
	aux1 = *cont_prest;
	aux2 = dia - 1;
	prestados[aux2][aux1].cod_serv1 = codserv;
	prestados[aux2][aux1].num_serv = num1;
	prestados[aux2][aux1].valor_serv = valor;
	prestados[aux2][aux1].cod_cliente = codcliente;
}

void checagem2(float valor_min, float valor_max, serv1 prestados[][3], int servicos_dia, int dias)  //CADASTRO CASE 4
{
	int i,j;
	float achou=0;
	
	for(i=0;i<dias;i++)
	{
		for(j=0;j<servicos_dia;j++)
		{
			if((prestados[i][j].valor_serv >= valor_min)&&(prestados[i][j].valor_serv <= valor_max)&&(prestados[i][j].cod_serv1 != 0))
			{
				printf("%d %d %.2f\n", prestados[i][j].cod_serv1, prestados[i][j].num_serv, prestados[i][j].valor_serv);
				achou++;
			}
			
		}
	}
	
	if (achou==0)
	printf("Nenhum servico prestado esta entre os valores citados\n");
}

void todos_serv(serv1 prestados[][3], serv *tipos, int dias, int servicos_dia, int cont_tipos) //PRINT TODOS SERVIÇOS CASE 5
{
	int i,j,k,achou=0;
	
	for (i=0;i<dias;i++)
	{
		for(j=0;j<servicos_dia;j++)
		{
			if (prestados[i][j].cod_serv1 != 0)
			{
				for(k=0;k<cont_tipos;k++)
				{
					if (prestados[i][j].cod_serv1 == tipos[k].cod_serv)
					{
					printf("Dia: %d | %d | %d | %.2f | %d | %s", i+1, tipos[k].cod_serv, prestados[i][j].num_serv, prestados[i][j].valor_serv, prestados[i][j].cod_cliente, tipos[k].descr);
					achou++;
				    }
				}
			}
		}
	}
	
	if(achou == 0)
	{
		printf("Nenhum servico prestado foi cadastrado\n");
	}
	
}


