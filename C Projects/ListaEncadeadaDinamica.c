#include <stdio.h>
#include <stdlib.h>

typedef struct aluno Aluno;
Aluno* cria_lista_null (void);
Aluno* lst_insere_ordenado (Aluno* lst_aluno, int num_var, int val_var);
Aluno* excluir (Aluno* lst_aluno, int excluir_var, int *cont);
void printar(Aluno* lst_aluno, int cont);

struct aluno {
	int num;
	int classific;
	Aluno* prox;
};

int main(){
	
	int val_var, num_var, cont = 0, teste = 1, x, saida = 1, excluir_var;
	
	Aluno* lst_aluno;
	lst_aluno = cria_lista_null();
	
	do{
		
		printf("\n1 - Inserir \n");
		printf("2 - Excluir \n");
		printf("3 - Imprimir \n");
		printf("0 - Sair \n");
		scanf("%d", &x);
		system("cls");
		
		switch(x)
	
		case 1:
		{
			do{
				printf("Digite o numero do aluno: ");
				scanf("%d", &num_var);
				printf("Digite a classificacao do aluno: ");
				scanf("%d", &val_var);
				lst_aluno = lst_insere_ordenado(lst_aluno, num_var, val_var);
				cont++;
				printf("Deseja adicionar outro aluno? (1 - sim, 0 - nao: ) ");
				scanf("%d", &teste);
			}while((cont<=10)&&(teste != 0));
			
			break;
		
		case 2:
			printf("Numero do aluno que deseja excluir: ");
			scanf("%d", &excluir_var);
			excluir(lst_aluno, excluir_var, &cont);
			break;
	
		case 3:
			printar(lst_aluno, cont);
			break;
		
		case 0:
			return 0;
		}	
		
	
		}while(saida != 0);
}

Aluno* cria_lista_null (void){
	return NULL;
}

void printar(Aluno* lst_aluno, int cont){
	
 	Aluno* p;
 	
 	if (cont > 0){
	 	for (p = lst_aluno; p != NULL; p = p->prox){
 			printf("\nNumero do aluno: %d, Classificacao do aluno: %d \n", p->num, p->classific);
	 	}
	}
}

Aluno* lst_insere_ordenado (Aluno* lst_aluno, int num_var, int val_var){
	
 	Aluno* novo;
 	Aluno* a = NULL; 
 	Aluno* p = lst_aluno; 

 	while (p != NULL && p->num < num_var){ 
	a = p; p = p->prox;
	}

 	novo = (Aluno*) malloc(sizeof(Aluno));
 	novo->classific = val_var;
 	novo->num = num_var;
 

 	if (a == NULL){ 
 		novo->prox = lst_aluno; lst_aluno = novo; 
	}
 	else{ 
 			novo->prox = a->prox;
 			a->prox = novo; 
		}
		 
 	return lst_aluno;
}

Aluno* excluir (Aluno* lst_aluno, int excluir_var, int *cont){
	
	Aluno* a = NULL; 
	Aluno* p = lst_aluno; 

	while (p != NULL && p->num != excluir_var) {
 		a = p;
 		p = p->prox;
 	}
 	
 	if (p == NULL)
 		return lst_aluno; 
 	
	if (a == NULL){ 
 		lst_aluno = p->prox; 
	}
	
 	else { 
 		a->prox = p->prox; 
	}
	
	*cont = *cont - 1;
	
	free(p);
 	
 	return lst_aluno;
}
