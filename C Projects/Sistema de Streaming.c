#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	OP0 = 0 ,OP1 , OP2, OP3, OP4, OP5, OP6, OP7, OP8, OP9, OP10, OP11, OP12, OP13
}ops;

typedef enum
{
	BASICO, PREMIUM
}planos_enum;

typedef enum
{
	AVENTURA, COMEDIA, DRAMA, TERROR, ACAO, ROMANCE
}genero;

typedef enum
{
	LIVRE, M_10, M_12, M_14, M_16, M_18, 
}classi;

typedef enum
{
	INATIVO, ATIVO
}status;

typedef struct
{
	int cpf;
	char nome[50];
	char email[50];
	char telefone[15];
	status ativ_inativ;
}cliente;

typedef struct
{
	char nome[50];
	int cpf;
	int cod_filme1;       
	int data1;
	genero genero_filme;
}matriz;

typedef struct
{
	int codigo;
	char nome[50];
	genero genero_filme;
	classi classificacao_filme;
	int vezes_carregado;
	char nome_classi[10];
	char nome_genero[15];
}filme_;

typedef struct
{
	int qtd_filme;
	float valor;
	float valor_extra;
}basico;

typedef struct
{
	float valor;
}premium;

typedef struct
{
	int aventura;
	int comedia;
	int drama;
	int terror;
	int acao;
	int romance;
}contagem_gen;

typedef union
{
	basico plano;
	premium plano1;
}uniao;

typedef struct
{
	int num_agencia;
	int num_conta;
}deb;

typedef struct
{
	int num_cartao;
}cred;

typedef union
{
	deb debito;
	cred credito;
}pagamento;

typedef struct
{
	int cpf;
	int plano1;
	pagamento pague;
	int data;
	int mes;
	int data_cancel;
}tipo_contrato;

int checagem_cpf(cliente *pessoa, int pos_cadastro, int cpf, int *ind);
int checagem_contrato(tipo_contrato *contrato, int pos_contrato, int cpf);
void cadastra_cliente(cliente *pessoa, int *pos_cadastro, int cpf);
void cadastra_filme(filme_ *filme, int *pos_filme);
void cadastra_basico(uniao *planos, int *pos_plano, int *ind_b);
void cadastra_premium(uniao *planos, int *pos_plano, int *ind_p);
void cadastra_contrato(tipo_contrato *contrato, int *pos_contrato, cliente *pessoa, int cpf, int ind, float *debito_clientes, int ind_b, int ind_p, uniao *planos, int mes);
int checagem_ativ_inativ(cliente *pessoa,int ind);
void carrega_filme(int *filmes_carregados, filme_ *filme, int *cont_excedentes,int *excedentes, int pos_filme, tipo_contrato *contrato, int pos_contrato, int cpf, int *pos_carregados, matriz historico[][30], int *vet_pos_filmes, int tam2, uniao *planos,int ind_b, int ind_p, float *debito_clientes);
int checagem_data(int ind, int data_cancel, tipo_contrato *contrato, int cpf, int pos_contrato, int mes);
void cancela_contrato(cliente *pessoa, int ind, float *debito_clientes,tipo_contrato *contrato);
int verifica_contrato(int pos_contrato, tipo_contrato *contrato, int cpf);
void fatura_especifico(uniao *planos, int *vet_pos_filmes, matriz historico[][30], float *debito_clientes, int mes, filme_ *filme, int ind, int ind_b, int ind_p, tipo_contrato *contrato);
void fatura_todos(uniao *planos, tipo_contrato *contrato, cliente *pessoa, float *debito_clientes, matriz historico[][30],int *mes, int tam, int tam2, int *vet_pos_filmes, int ind_b, int ind_p);
void listar_dados(cliente *pessoa, int ind);
void listar_historico(int *vet_pos_filmes, filme_ *filme, matriz historico[][30], int tam, int ind, cliente *pessoa, int mes);
void listar_excedentes(int tam, int *cont_excedentes, cliente *pessoa, uniao *planos, int ind_b);
void frequencia_filme(int filmes_carregados, filme_ *filme, int pos_filme, int cod);
void contagem_genero(contagem_gen *cont_genero, int ind, filme_ *filme, matriz historico[][30], int *vet_pos_filmes, int pos_filme);
void recomenda_filme(contagem_gen *cont_genero, int ind, filme_ *filme, matriz historico[][30], int *vet_pos_filmes, int pos_filme);

int main ()
{
	const int tam=10;
	const int tam2=30;
	const int tam_plano=2;
	int vet_pos_filmes[tam];
	float debito_clientes[tam];
	matriz historico[tam][tam2];
	cliente pessoa[tam];
	filme_ filme[tam]; 
	uniao planos[tam_plano];
	tipo_contrato contrato[tam];
	int cont_excedentes[tam];
	contagem_gen cont_genero[tam];
	
	int op, pos_cadastro,pos_filme,ret,cpf,pos_plano,pos_contrato,cliente,achou,ind,pos_carregados,i,ind_b = 0 ,ind_p = 1,mes,data_cancel,chec,cod,op_fatura, excedentes = 0, filmes_carregados = 0;
	ops opcoes;
	
	pos_cadastro = 0;
	cliente = 0;
	pos_filme = 0;
	pos_plano = 0;
	pos_contrato = 0;
	pos_carregados = 0;
	mes = 1;
	planos[ind_p].plano1.valor = 0;
	planos[ind_b].plano.valor = 0;
	planos[ind_b].plano.valor_extra = 0;
	planos[ind_b].plano.qtd_filme = 0;
	
	for (i=0;i<tam;i++)
	{
	   contrato[i].cpf = 0;	
	   vet_pos_filmes[i] = 0;
	   cont_excedentes[i] = 0;
	   filme[i].vezes_carregado = 0;
	   cont_genero[i].acao = 0;
	   cont_genero[i].aventura = 0;
	   cont_genero[i].comedia = 0;
	   cont_genero[i].drama = 0;
	   cont_genero[i].romance = 0;
	   cont_genero[i].terror = 0;
    }
	
	do
	{
		scanf("%d", &op);
		opcoes = (ops)op;
		
		switch(opcoes)
		{
			case OP1:
				{
					if(pos_cadastro == tam)
					{
						printf("ERRO: Numero maximo de clientes no sistema atingido\n");
					}
					else
					{
						scanf("%d", &cpf);
					    ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
					    if (ret)
					    {
					    	printf("ERRO: CPF do cliente ja cadastrado\n");
					    }
					    else 
						{
						cadastra_cliente(pessoa, &pos_cadastro,cpf);
						cliente++;
					    }
				    }
				    break;
				}
			
			case OP2:
				{
					if(pos_filme == tam)
					{
						printf("ERRO: Numero maximo de filmes no sistema atingido\n");
					}
					else
					{
						cadastra_filme(filme, &pos_filme);
					}
					break;
				}
			
			case OP3:
				{
					cadastra_basico(planos, &pos_plano, &ind_b);
					break;
				}
			
			case OP4:
				{
					cadastra_premium(planos, &pos_plano, &ind_p);
					break;
				}
			
			case OP5:
				{
					if(cliente == 0)
					{
						printf("ERRO: Nenhum cliente cadastrado no sistema\n");
					}
					else
					{
					   if (pos_contrato == tam)
					   {
						   printf("ERRO: Numero maximo de contratos no sistema atingido\n");
				       }
					   else
					   {
						   scanf("%d", &cpf);
					       ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
					       achou = checagem_contrato(contrato, pos_contrato, cpf);
					    
					       if (ret==0)
					       {
					    	   printf("ERRO: Cliente nao cadastrado\n");
						   }
						   else
						   {
						       if(achou==1)
						       {
							   printf("ERRO: Cliente com contrato existente\n");
						       }
						       else
						       cadastra_contrato(contrato,&pos_contrato,pessoa,cpf,ind, debito_clientes, ind_b, ind_p, planos, mes);
						   }
					   }
				    }
					break;
				}
			
			case OP6:
				{
					if(cliente == 0)
					{
						printf("ERRO: Nenhum cliente cadastrado no sistema\n");
					}
					else
					{
						scanf("%d", &cpf);
						ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
						
						if(ret)
						{
							achou = checagem_ativ_inativ(pessoa,ind);
							
							if (achou)
							{
							    if (contrato[ind].plano1 == PREMIUM)
	                            {
		                            if (vet_pos_filmes[ind] == tam2)
		                            {
		                            	printf("ERRO: Numero maximo de filmes no sistema atingido\n");
									}
									else
									{
										carrega_filme(&filmes_carregados,filme,cont_excedentes,&excedentes, pos_filme,contrato,pos_contrato,cpf, &pos_carregados, historico,  vet_pos_filmes, tam2, planos, ind_b, ind_p, debito_clientes);
									}
		                        }
		                        else
		                        carrega_filme(&filmes_carregados,filme,cont_excedentes,&excedentes, pos_filme,contrato,pos_contrato,cpf, &pos_carregados, historico,  vet_pos_filmes, tam2, planos, ind_b, ind_p, debito_clientes);
							}
							else
							{
								printf("ERRO: Cliente nao ativo\n");
							}
						}
						else
						{
							printf("ERRO: Cliente nao cadastrado\n");
						}
					}
				break;
				}
				
			case OP7:
				{
					if(pos_contrato == 0)
					{
						printf("ERRO: Nenhum contrato cadastrado no sistema\n");
					}
					else
					{
				    	scanf("%d", &cpf);
				    	ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
					
				    	if (ret)
				    	{
					      	achou = checagem_ativ_inativ(pessoa,ind);
						
						    if(achou)
						    {
                                do
                             	{
                                scanf("%d", &data_cancel);
                                if ((data_cancel>31)||(data_cancel<1))
	                            printf("ERRO: Dia invalido\n");
                                }while ((data_cancel>31)||(data_cancel<1));
								
								chec = checagem_data(ind ,data_cancel, contrato, cpf, pos_contrato, mes);	
								
								if (chec)
								{
								    cancela_contrato(pessoa,ind,debito_clientes,contrato);
								}
								else
								{
									break;
								}
					    	}
					    	else
					    	{
					    		printf("ERRO: Cliente inativo\n");
				     	    }
				    	}
				    	else
				    	{
					    	printf("ERRO: Cliente nao cadastrado\n");
				    	}
				    }
					
				break;	
				}
				
			case OP8:
				{
					do
                    {
                    scanf("%d", &op_fatura);
                    if ((op_fatura>1)||(op_fatura<0))
	                printf("ERRO: Escolha invalida\n");
                    }while ((op_fatura>1)||(op_fatura<0));
                    
                    
					switch (op_fatura)
					{
			    		case 0:
						{
							if (cliente == 0)
					    	{
								printf("ERRO: Nenhum cliente cadastrado no sistema\n");
							}
							else
							{
								if (pos_contrato == 0)
								{
								    printf("ERRO: Nenhum contrato cadastrado no sistema\n");
								}
								else
								{
									scanf("%d", &cpf);
									ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
										
									if (ret)
									{
									    achou = verifica_contrato(pos_contrato, contrato, cpf);
											
									    if (achou)
										{
									 	    fatura_especifico(planos ,vet_pos_filmes, historico, debito_clientes, mes, filme, ind, ind_b, ind_p, contrato);
									    }
										else
									    {
										break;
										}
									}
									else
									{
								        printf("ERRO: Cliente nao cadastrado\n");
								    }
								}
							}
							break;			
						}
								
						case 1:
						{
							fatura_todos(planos, contrato, pessoa, debito_clientes, historico, &mes, tam, tam2, vet_pos_filmes, ind_b, ind_p);
							break;
						}				
			    	}
				break;	
				}
				
			case OP9:
				{
					if (cliente == 0)
                   	{
                    	printf("ERRO: Nenhum cliente cadastrado no sistema\n");
					}
					else
					{
						scanf("%d", &cpf);
						ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
						if (ret)
						{
							listar_dados(pessoa, ind);
						}
						else
						{
							printf("ERRO: Cliente nao cadastrado\n");
						}
					}
				break;
				}
				
			case OP10:
				{
					if (cliente == 0)
                   	{
                    	printf("ERRO: Nenhum cliente cadastrado no sistema\n");
					}
					else
					{
						scanf("%d", &cpf);
						ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
						if (ret)
						{
							listar_historico(vet_pos_filmes, filme, historico, tam, ind, pessoa, mes);
						}
						else
						{
							printf("ERRO: Cliente nao cadastrado\n");
						}
					}
				break;	
				}
				
			case OP11:
				{
					if (excedentes == 0)
					{
						printf("ERRO: Nenhum cliente excedente\n");
					}
					else
					{
						listar_excedentes(tam, cont_excedentes, pessoa, planos, ind_b);
					}
				break;
				}
				
			case OP12:
			{
				if (pos_filme == 0)
				{
					printf("ERRO: Nenhum filme cadastrado no sistema\n");
				}
				else
				{
					scanf("%d", &cod);
					if (filmes_carregados == 0)
					{
						printf("ERRO: Nenhum filme assistido\n");
					}
					else
					{
						frequencia_filme(filmes_carregados, filme, pos_filme,cod);
					}
				}
			break;
			}
			
			case OP13:
				{
				if(cliente == 0)
					{
						printf("ERRO: Nenhum cliente cadastrado no sistema\n");
					}
					else
					{
						scanf("%d", &cpf);
						ret = checagem_cpf(pessoa, pos_cadastro,cpf,&ind);
						
						if(ret)
						{
							achou = checagem_ativ_inativ(pessoa,ind);
							
							if (achou)
							{
								if (vet_pos_filmes[ind] == 0)
								{
									printf("ERRO: Nenhum filme assistido\n");
								}
								else
								{
									contagem_genero(cont_genero, ind, filme, historico, vet_pos_filmes,pos_filme);
									recomenda_filme(cont_genero, ind, filme, historico, vet_pos_filmes,pos_filme);
								}
							}
							else
							{
								printf("ERRO: Cliente nao ativo\n");
							}
						}
						else
						{
							printf("ERRO: Cliente nao cadastrado\n");
						}
			       }
			    break;   
			   }
				
			case OP0:
				{
					printf("Finalizando programa...");
					break;
				}
			default: printf("ERRO: Opcao invalida\n");			
		}	   
	} while (opcoes!=OP0);
}

int checagem_cpf(cliente *pessoa, int pos_cadastro, int cpf, int *ind)
{
	int i,achou = 0;
	
	for (i=0;i<pos_cadastro;i++)
	{
		if(pessoa[i].cpf == cpf)
		{
			*ind = i;
			achou = 1;
			break;
		}
		else achou = 0;
	}
	return achou;
}

void cadastra_cliente(cliente *pessoa, int *pos_cadastro, int cpf)
{
	pessoa[*pos_cadastro].cpf = cpf;
	scanf(" %[^\n]%*c", pessoa[*pos_cadastro].nome);
	scanf(" %s", pessoa[*pos_cadastro].email);
	scanf(" %s", pessoa[*pos_cadastro].telefone);
	pessoa[*pos_cadastro].ativ_inativ = INATIVO;
	
	*pos_cadastro = *pos_cadastro + 1;
	printf("Cliente cadastrado com sucesso\n");
}

void cadastra_filme(filme_ *filme, int *pos_filme)
{
	int x,y;
	filme[*pos_filme].codigo = *pos_filme + 1001;
	scanf(" %[^\n]%*c", filme[*pos_filme].nome);
	
	do
	{
	   scanf("%d", &x);	
	   if ((x<0)||(x>5))
	   printf("ERRO: Genero invalido\n");
	}while((x<0)||(x>5));
	
	filme[*pos_filme].genero_filme = (genero)x;
	
	if (filme[*pos_filme].genero_filme == AVENTURA)
	strcpy(filme[*pos_filme].nome_genero, "aventura");
	if (filme[*pos_filme].genero_filme == COMEDIA)
	strcpy(filme[*pos_filme].nome_genero, "comedia");
	if (filme[*pos_filme].genero_filme == DRAMA)
	strcpy(filme[*pos_filme].nome_genero, "drama");
	if (filme[*pos_filme].genero_filme == TERROR)
	strcpy(filme[*pos_filme].nome_genero, "terror");
	if (filme[*pos_filme].genero_filme == ACAO)
	strcpy(filme[*pos_filme].nome_genero, "acao");
	if (filme[*pos_filme].genero_filme == ROMANCE)
	strcpy(filme[*pos_filme].nome_genero, "romance");
		
	do
	{
	   scanf("%d", &y);	
	   if ((y<0)||(y>5))
	   printf("ERRO: Classificao invalida\n");
	}while((y<0)||(y>5));
	
	filme[*pos_filme].classificacao_filme = (classi)y;
	
	if (filme[*pos_filme].classificacao_filme == LIVRE)
	strcpy(filme[*pos_filme].nome_classi, "livre");
	if (filme[*pos_filme].classificacao_filme == M_10)
	strcpy(filme[*pos_filme].nome_classi, "+10");
	if (filme[*pos_filme].classificacao_filme == M_12)
	strcpy(filme[*pos_filme].nome_classi, "+12");
	if (filme[*pos_filme].classificacao_filme == M_14)
	strcpy(filme[*pos_filme].nome_classi, "+14");
	if (filme[*pos_filme].classificacao_filme == M_16)
	strcpy(filme[*pos_filme].nome_classi, "+16");
	if (filme[*pos_filme].classificacao_filme == M_18)
	strcpy(filme[*pos_filme].nome_classi, "+18");
	
	printf("Filme cadastrado com sucesso\n");
	*pos_filme = *pos_filme + 1;
}

void cadastra_basico(uniao *planos, int *pos_plano, int *ind_b)
{
	scanf("%d", &planos[*pos_plano].plano.qtd_filme);
	scanf("%f", &planos[*pos_plano].plano.valor);   
	scanf("%f", &planos[*pos_plano].plano.valor_extra); 
	printf("Plano Basico cadastrado com sucesso\n");
	*ind_b = *pos_plano;
	*pos_plano = *pos_plano + 1; 
}

void cadastra_premium(uniao *planos, int *pos_plano, int *ind_p)
{
	scanf("%f", &planos[*pos_plano].plano1.valor);
	printf("Plano Premium cadastrado com sucesso\n");
	*ind_p = *pos_plano;
	*pos_plano = *pos_plano + 1; 
}

int checagem_contrato(tipo_contrato *contrato, int pos_contrato, int cpf)
{
	int i, achou_;
	
	for (i=0;i<pos_contrato;i++)
	{
		if(contrato[i].cpf == cpf)
		{
			achou_ = 1;
			break;
		}
		else achou_ = 0;
	}
	if(pos_contrato == 0)
	achou_ = 0;
	
	return achou_;
}

void cadastra_contrato(tipo_contrato *contrato, int *pos_contrato, cliente *pessoa, int cpf, int ind, float *debito_clientes, int ind_b, int ind_p, uniao *planos, int mes)
{
	int pag;
	contrato[ind].cpf = cpf;
	
	do
	{
	scanf("%d", &contrato[ind].plano1);
	if ((contrato[ind].plano1>1)||(contrato[ind].plano1<0))
	printf("ERRO: Tipo de plano invalido\n");
    }while((contrato[ind].plano1>1)||(contrato[ind].plano1<0));
    
    if (contrato[ind].plano1 == PREMIUM)
    debito_clientes[ind] = planos[ind_p].plano1.valor;
    
    if (contrato[ind].plano1 == BASICO)
    debito_clientes[ind] = planos[ind_b].plano.valor;
    
    do
	{
	scanf("%d", &pag);
	if ((pag>1)||(pag<0))
	printf("ERRO: Tipo de pagamento invalido\n");
    }while((pag>1)||(pag<0));
	
	if (pag == 1)
	{
		scanf("%d", &contrato[ind].pague.credito.num_cartao);
	}
	else
	{
		scanf("%d", &contrato[ind].pague.debito.num_agencia);
		scanf("%d", &contrato[ind].pague.debito.num_conta);	
	}
	
	do
	{
	scanf("%d", &contrato[ind].data);
	if ((contrato[ind].data>31)||(contrato[ind].data<1))
	printf("ERRO: Dia invalido\n");
    }while((contrato[ind].data>31)||(contrato[ind].data<1));
    
    contrato[ind].mes = mes;
    contrato[ind].data_cancel = 00;
    pessoa[ind].ativ_inativ = ATIVO;
    *pos_contrato = *pos_contrato + 1;
    printf("Contrato cadastrado com sucesso\n");	
}

int checagem_ativ_inativ(cliente *pessoa,int ind)
{
	int achou;
	if (pessoa[ind].ativ_inativ == ATIVO)
	{
		achou = 1;
	}
	else
	{
		achou = 0;
	}
	
	return achou;
}

void carrega_filme(int *filmes_carregados, filme_ *filme, int *cont_excedentes,int *excedentes, int pos_filme, tipo_contrato *contrato, int pos_contrato, int cpf, int *pos_carregados, matriz historico[][30], int *vet_pos_filmes, int tam2, uniao *planos,int ind_b, int ind_p, float *debito_clientes)
{
	int dia, escolha, genero, classificacao, i, codigo, achou, ind, aux, aux2,x,j,ind_filme;
	achou = 0;
	ind = 0;
	x = 2;
	
	do
	{
	scanf("%d", &dia);
	if ((dia>31)||(dia<1))
	printf("ERRO: Dia invalido\n");
    }while ((dia>31)||(dia<1));
    
    do
	{
	scanf("%d", &escolha);
	if ((escolha>1)||(escolha<0))
	printf("ERRO: Escolha invalida\n");
    }while ((escolha>1)||(escolha<0));
    
    switch (escolha)
    {
    	case 0:
    		{
    			do
    		    {
    		    	scanf("%d", &genero);
    		    	if((genero>5)||(genero<0))
    		    	printf("ERRO: Escolha invalida\n");
				} while ((genero>5)||(genero<0));
				
				for (i=0;i<pos_filme;i++)
				{
					if (filme[i].genero_filme == genero)
					{
						printf("Codigo: %d\n",filme[i].codigo);
						printf("Nome: %s\n", filme[i].nome);
					}
				}
				break;
			}
		case 1:
			{
				do
    		    {
    		    	scanf("%d", &classificacao);
    		    	if((classificacao>5)||(classificacao<0))
    		    	printf("ERRO: Escolha invalida\n");
				} while ((classificacao>5)||(classificacao<0));
				
				for (i=0;i<pos_filme;i++)
				{
					if (filme[i].classificacao_filme == classificacao)
					{
						printf("Codigo: %d\n",filme[i].codigo);
						printf("Nome: %s\n", filme[i].nome);
					}
				}
				break;
			}		
	}
	

	scanf("%d", &codigo);
	for (i=0;i<pos_filme;i++)
	{
		if(filme[i].codigo == codigo)
		{
			achou=1;
			ind_filme = i;
		}
	}
	if (achou)
	{
		for (i=0;i<pos_contrato;i++)
		{
			if(contrato[i].cpf == cpf)
			{
				ind = i;
				aux = vet_pos_filmes[ind];
				break;
			}
		}
		
		aux2 = planos[ind_b].plano.qtd_filme;
		
		if (contrato[ind].plano1 == BASICO)
		{
		    if (vet_pos_filmes[ind] >= aux2)
		    {
			 do
			 {
			 scanf("%d", &x);
			 if ((x<0)||(x>1))
			 printf("ERRO: Escolha invalida\n");
			 }
			 while((x<0)||(x>1));
		    }
		    else
		    {
		    	historico[ind][aux].cpf = cpf;
				historico[ind][aux].cod_filme1 = codigo;
			    historico[ind][aux].data1 = dia;
			    historico[ind][aux].genero_filme = filme[ind_filme].genero_filme;
			    vet_pos_filmes[ind] = vet_pos_filmes[ind] + 1;
			    printf("Filme carregado com sucesso\n");
				debito_clientes[ind] = planos[ind_b].plano.valor;
				filme[ind_filme].vezes_carregado = 	filme[ind_filme].vezes_carregado + 1;
				*filmes_carregados = *filmes_carregados + 1;
			}
		    
		    if (x == 1)
		    {
			    historico[ind][aux].cpf = cpf;
				historico[ind][aux].cod_filme1 = codigo;
			    historico[ind][aux].data1 = dia;
			    historico[ind][aux].genero_filme = filme[ind_filme].genero_filme;
			    vet_pos_filmes[ind] = vet_pos_filmes[ind] + 1;
			    printf("Filme carregado com sucesso\n");
				debito_clientes[ind] = debito_clientes[ind] + planos[ind_b].plano.valor_extra;
				cont_excedentes[ind] = cont_excedentes[ind] + 1;
				*excedentes = *excedentes + 1;
				filme[ind_filme].vezes_carregado = 	filme[ind_filme].vezes_carregado + 1;
				*filmes_carregados = *filmes_carregados + 1;
		    }
		    if (x == 0)
			{
				printf("ERRO: Taxa adicional negada\n");
			}
		}
			   
		if (contrato[ind].plano1 == PREMIUM)
		{
			historico[ind][aux].cpf = cpf;
			historico[ind][aux].cod_filme1 = codigo;
			historico[ind][aux].data1 = dia;
			historico[ind][aux].genero_filme = filme[ind_filme].genero_filme;
			vet_pos_filmes[ind] = vet_pos_filmes[ind] + 1;
			printf("Filme carregado com sucesso\n");
			debito_clientes[ind] = planos[ind_p].plano1.valor;
			filme[ind_filme].vezes_carregado = filme[ind_filme].vezes_carregado + 1;	
			*filmes_carregados = *filmes_carregados + 1;
		}
	}
	else
	{
		printf("ERRO: Filme nao encontrado\n");
	}
	
	aux = vet_pos_filmes[ind];
	for (i=0;i<pos_filme;i++)
	{
		for (j=0;j<aux;j++)
		{
			if (filme[i].codigo == historico[ind][j].cod_filme1)
			{
				strcpy(historico[ind][j].nome, filme[i].nome);
			}
		}
	}	
}

int checagem_data(int ind, int data_cancel, tipo_contrato *contrato, int cpf, int pos_contrato, int mes)
{
	int achou = 0;

	if ((contrato[ind].data > data_cancel)&&(contrato[ind].mes == mes))
	{
		printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
		achou = 0;
	}
	else
	{
		contrato[ind].data_cancel = data_cancel;
		achou = 1;
	}
	return achou;	
}

void cancela_contrato(cliente *pessoa, int ind, float *debito_clientes, tipo_contrato *contrato)
{
	printf("Valor devido: %.2f\n",(float)debito_clientes[ind]);
	printf("Cancelamento feito com sucesso\n");
	pessoa[ind].ativ_inativ = INATIVO;
	contrato[ind].cpf = 0;
}

int verifica_contrato(int pos_contrato, tipo_contrato *contrato, int cpf)
{
	int i,achou=0;
	
	for (i=0; i<pos_contrato;i++)
	{
		if (contrato[i].cpf == cpf)
		{
			achou = 1;
			break;
		}
	}
	if (achou == 0)
	{
		printf("ERRO: Cliente nao possui contrato\n");
	}
	return achou;
}

void fatura_especifico(uniao *planos, int *vet_pos_filmes, matriz historico[][30], float *debito_clientes, int mes, filme_ *filme, int ind, int ind_b, int ind_p, tipo_contrato *contrato)
{
	int aux, i;
	aux = vet_pos_filmes[ind];
	
	
	for(i=0;i<aux;i++)
	{
		printf("Nome: %s\n", historico[ind][i].nome); 
        printf("Data: %d/%d\n", historico[ind][i].data1, mes); 
	}
	printf("Valor devido: %.2f\n", (float)debito_clientes[ind]);
}

void fatura_todos(uniao *planos, tipo_contrato *contrato, cliente *pessoa, float *debito_clientes, matriz historico[][30],int *mes, int tam, int tam2, int *vet_pos_filmes, int ind_b, int ind_p)
{
	int i,j;
	
	for (i=0;i<tam;i++)
	{
		if(contrato[i].cpf != 0)
		{
			printf("CPF: %d\n", contrato[i].cpf);
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Valor devido: %.2f\n", debito_clientes[i]);
            
            if (contrato[i].plano1 == BASICO)
            {
            	debito_clientes[i] = planos[ind_b].plano.valor;
			}
			else debito_clientes[i] = planos[ind_p].plano1.valor;
		}
	}

	*mes = *mes + 1;
	for (i=0;i<tam;i++)
	{
		vet_pos_filmes[i] = 0;
		for(j=0;j<tam2;j++)
		{
			historico[i][j].cpf = 0;
			historico[i][j].cod_filme1 = 0;
			historico[i][j].data1 = 0;
			strcpy(historico[i][j].nome, "");
		}
	}
	printf("Mes vigente apos a fatura: %d\n", *mes);
}

void listar_dados(cliente *pessoa, int ind)
{
	printf("Nome: %s\n", pessoa[ind].nome);
    printf("Email: %s\n", pessoa[ind].email);
    printf("Telefone: %s\n", pessoa[ind].telefone);
    printf("Status: %d\n", pessoa[ind].ativ_inativ);
}

void listar_historico(int *vet_pos_filmes, filme_ *filme, matriz historico[][30], int tam, int ind, cliente *pessoa, int mes)
{
	int i, j, aux;
	aux = vet_pos_filmes[ind];

	if (pessoa[ind].ativ_inativ == ATIVO)
	{
		printf("Estado: Ativo\n");
	}
	else
	{
		printf("Estado: Inativo\n");
	}
	
	if (vet_pos_filmes[ind] == 0)
	{
		printf("ERRO: Nenhum filme assistido\n");
	}
	else
	{
	   for (i=0;i<aux;i++)
	   {
		   for (j=0;j<tam;j++)
		   {
			   if (historico[ind][i].cod_filme1 == filme[j].codigo)
			   {
				   printf("Codigo: %d\n",filme[j].codigo);
		           printf("Nome: %s\n",filme[j].nome);
				   printf("Genero: %s\n", filme[j].nome_genero);
                   printf("Classificacao: %s\n", filme[j].nome_classi);
				   printf("Data do carregamento: %d/%d\n\n",historico[ind][i].data1, mes); 
			   }
		   }
	   }
	}
}

void listar_excedentes(int tam, int *cont_excedentes, cliente *pessoa, uniao *planos, int ind_b)
{
	int i;
	
	for (i=0;i<tam;i++)
	{
		if (cont_excedentes[i] > 0)
		{
			printf("CPF: %d\n", pessoa[i].cpf);
			printf("Nome: %s\n",pessoa[i].nome);
			printf("Valor excedente: %.2f\n\n",cont_excedentes[i] * planos[ind_b].plano.valor_extra);
		}
	}
}

void frequencia_filme(int filmes_carregados, filme_ *filme, int pos_filme, int cod)
{
	int i, achou = 0;
	
	
	for (i=0;i<pos_filme;i++)
	{
		if (filme[i].codigo == cod)
		{
			printf("Frequencia: %.2f%%\n",((float)filme[i].vezes_carregado * 100) / filmes_carregados);
			achou++;
			break;
		}
	}
	if (achou == 0)
	{
		printf("ERRO: Codigo invalido\n");
	}
}

void contagem_genero(contagem_gen *cont_genero, int ind, filme_ *filme, matriz historico[][30], int *vet_pos_filmes, int pos_filme)
{
	int i,aux,j;

aux = vet_pos_filmes[ind];	

	for (i=0;i<aux;i++)
	{
		for(j=0;j<pos_filme;j++)
		{
			if (historico[ind][i].cod_filme1 == filme[j].codigo)
			{
				if (filme[j].genero_filme == AVENTURA)
				{
					cont_genero[ind].aventura = cont_genero[ind].aventura + 1;
				}
				if (filme[j].genero_filme == ACAO)
				{
					cont_genero[ind].acao = cont_genero[ind].acao + 1;
				}
				if (filme[j].genero_filme == DRAMA)
				{
					cont_genero[ind].drama = cont_genero[ind].drama + 1;
				}
				if (filme[j].genero_filme == TERROR)
				{
					cont_genero[ind].terror = cont_genero[ind].terror + 1;
				}
				if (filme[j].genero_filme == ROMANCE)
				{
					cont_genero[ind].romance = cont_genero[ind].romance + 1;
				}
				if (filme[j].genero_filme == COMEDIA)
				{
					cont_genero[ind].comedia = cont_genero[ind].comedia + 1;
				}
			}
		}
	}
}

void recomenda_filme(contagem_gen *cont_genero, int ind, filme_ *filme, matriz historico[][30], int *vet_pos_filmes, int pos_filme)
{
	int aux,i,j,aux2,n_achou,printou,print_erro;
	aux = 0;
	n_achou = 0;
	aux2 = vet_pos_filmes[ind];
	print_erro = 0;
	
	if(cont_genero[ind].acao > aux)
		aux = cont_genero[ind].acao;
	if(cont_genero[ind].aventura > aux)
		aux = cont_genero[ind].aventura;
	if(cont_genero[ind].comedia > aux)
		aux = cont_genero[ind].comedia;
	if(cont_genero[ind].drama > aux)
		aux = cont_genero[ind].drama;
	if(cont_genero[ind].romance > aux)
		aux = cont_genero[ind].romance;
	if(cont_genero[ind].terror > aux)
		aux = cont_genero[ind].terror;	
	///////////////////////////////////////////
	if(cont_genero[ind].acao == aux)
		{
			printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == ACAO)&&(historico[ind][j].genero_filme == ACAO))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);    
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}
		
	if(cont_genero[ind].aventura == aux)
	{
		printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == AVENTURA)&&(historico[ind][j].genero_filme == AVENTURA))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);       
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}
	
	if(cont_genero[ind].comedia == aux)
	{
		printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == COMEDIA)&&(historico[ind][j].genero_filme == COMEDIA))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);      
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}
	
	if(cont_genero[ind].drama == aux)
	{
		printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == DRAMA)&&(historico[ind][j].genero_filme == DRAMA))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);        
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}

	if(cont_genero[ind].romance == aux)
	{
		printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == ROMANCE)&&(historico[ind][j].genero_filme == ROMANCE))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);        
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}
	
	if(cont_genero[ind].terror == aux)
	
	{
			printou = 0;
			for (i=0;i<pos_filme;i++)
			{
				n_achou = 0;
				for (j=0;j<aux2;j++)
				{
					if ((filme[i].genero_filme == TERROR)&&(historico[ind][j].genero_filme == TERROR))
					{
						if (filme[i].codigo != historico[ind][j].cod_filme1)
						{
							n_achou++;
						}
			        }
				}
				
				if (n_achou == aux)
				{
					printou ++;
					printf("Codigo: %d\n",filme[i].codigo);
                    printf("Nome: %s\n",filme[i].nome);
                    printf("Genero: %s\n", filme[i].nome_genero);
                    printf("Classificacao: %s\n", filme[i].nome_classi);       
				}
			}
			if ((printou == 0)&&(print_erro == 0))
			{
				printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
				print_erro++;
			}
	}
	cont_genero[ind].aventura = 0;
	cont_genero[ind].acao = 0;
	cont_genero[ind].comedia = 0;
	cont_genero[ind].drama = 0;
	cont_genero[ind].romance = 0;
	cont_genero[ind].terror = 0;
}
