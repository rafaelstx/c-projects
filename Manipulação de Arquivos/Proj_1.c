//////////////// bibliotecas
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//////////////// defines
#define TAM_COD_VEI 8
#define TAM_COD_CLI 12
#define TAM_NOMES 50
#define TAM_CHAVE 19
#define NUM -1
/////////////// Registro
typedef struct Arquivo
{
    char cod_cli[TAM_COD_CLI];
    char cod_vei[TAM_COD_VEI];
    char nome_cli[TAM_NOMES];
    char nome_vei[TAM_NOMES];
    int n_dias;
} arqui;

////////////// prototipos
void inserindo(int campo_deletado, int tam_reg, char *reg, char *chave, FILE *out, FILE *insere);
void removendo(int campo_deletado, char *chave, FILE *out, FILE *remove);
void compactando(FILE *out, char *reg, int tam_reg);
// void compactando();

///////////// Principal
int main()
{
    int campo_deletado, tam_reg, escolha, num;
    char reg[sizeof(arqui)];
    char chave[TAM_CHAVE];
    arqui arquivo;
    FILE *out;
    FILE *insere;
    FILE *remove;

    if ((out = fopen("arq.bin", "r+b")) == NULL)
    {
        num = NUM;
        out = fopen("arq.bin", "w+b");
        fwrite(&num, sizeof(num), 1, out);
    }

    // ABRIR OS ARQUIVOS DO PROFESSOR
    insere = fopen("insere.bin", "rb");
    remove = fopen("remove.bin", "rb");

    do
    {
        printf("\nAdicionar registro(1)\nRemover registro(2)\nCompactar(3)\nSair(0)\n");
        scanf("%d", &escolha);
        fflush(stdin);

        switch (escolha)
        {
        case 1: // Insercao
            inserindo(campo_deletado, tam_reg, reg, chave, out, insere);
            break;

        case 2: // Remocao
            removendo(campo_deletado, chave, out, remove);
            break;

        case 3: // Compactacao
            compactando(out, reg, tam_reg);
            break;

        case 0: // Sair
            fclose(out);
            fclose(insere);
            fclose(remove);
            break;

        default:
            printf("ERRO: Opcao invalida\n");
            system("cls");
        }

    } while (escolha != 0);

    return 0;
}

void inserindo(int campo_deletado, int tam_reg, char *reg, char *chave, FILE *out, FILE *insere)
{

    char del[1] = "";
    int pos_deletado = 0, tam_reg_delet = 0, header = 0, campo_deletado_anterior = 0, indice = 0;

    arqui arquivo;

    fseek(out, 0, SEEK_SET);
    fread(&campo_deletado, sizeof(int), 1, out);
    printf("\n");
    printf("Indice : ");
    scanf("%d", &indice);

    fseek(insere, (indice - 1) * sizeof(arqui), SEEK_SET);

    fread(&arquivo, sizeof(arqui), 1, insere);

    sprintf(reg, "%s|%s|%s|%s|%d|", arquivo.cod_cli, arquivo.cod_vei, arquivo.nome_cli, arquivo.nome_vei, arquivo.n_dias);
    tam_reg = strlen(reg);

    if (campo_deletado == -1)
    {
        fseek(out, 0, SEEK_END);
        fwrite(&tam_reg, 1, 1, out);
        fwrite(reg, sizeof(char), tam_reg, out);
    }
    else
    {

        fseek(out, campo_deletado - 1, SEEK_SET);
        // LE O TAMANHO DO ARQUIVO
        fread(&tam_reg_delet, 1, 1, out);

        fread(&del, sizeof(char), 1, out);

        fread(&pos_deletado, sizeof(int), 1, out);

        //  A PROCURA DO REGISTRO COM POSICAO VALIDA OU ATE CHEGAR NO FIM
        while (tam_reg > tam_reg_delet && pos_deletado != -1)
        {

            campo_deletado_anterior = campo_deletado;
            // SALVANDO A POSICAO NOVA SEM PERDER SEU VALOR
            campo_deletado = pos_deletado;

            // INDO PARA O PROXIMO REGISTGRO
            fseek(out, pos_deletado - 1, SEEK_SET);

            // REFAZ A LEITURA
            fread(&tam_reg_delet, 1, 1, out);

            fread(&del, sizeof(char), 1, out);
            fread(&pos_deletado, sizeof(int), 1, out);
        }
        // VERIFICA SE O ESPACO E VALIDO PARA INSERCAO
        if (tam_reg_delet >= tam_reg)
        {
            fseek(out, campo_deletado, SEEK_SET);

            fwrite(reg, sizeof(char), tam_reg, out);

            // VERIFICA SE O ENDERECO DO HEADER DIFRENCIA DO ENDERECO EXCLUIDO CASO ISSO OCORRA MUDAR O ENDERECO DO REGISTRO EXLCUIDO ATRAS DO REGISTRO MODIFICADO
            fseek(out, 0, SEEK_SET);
            fread(&header, sizeof(int), 1, out);

            if (campo_deletado != header)
            {
                fseek(out, campo_deletado_anterior, SEEK_SET);
                fseek(out, sizeof(char), SEEK_CUR);
                fwrite(&pos_deletado, sizeof(int), 1, out);
            }
            else
            {
                // ALTERANDO O HEADER PARA A PROXIMA A SER INSERIDO Q ESTA EXCLUIDO
                fseek(out, 0, SEEK_SET);
                fwrite(&pos_deletado, sizeof(int), 1, out);
            }
        }
        else
        {
            fseek(out, 0, SEEK_END);
            fwrite(&tam_reg, 1, 1, out);
            fwrite(reg, sizeof(char), tam_reg, out);
        }
    }
}

void removendo(int campo_deletado, char *chave, FILE *out, FILE *remove)
{
    // usuario insere o codigo que quer deletar do registro

    arqui arquivo;
    char chave_usuario[TAM_CHAVE];
    char codigo_veiculo_remove[TAM_COD_VEI];
    char codigo_cliente_remove[TAM_COD_CLI];
    int tam_arqui = 0, tam_agr = 0, vazio = NUM, aux = 0, indice = 0, tam_reg = 0;
    char del[1] = "*";

    // salvando na variavel o tamanho do arquivo
    fseek(out, 0, SEEK_END);
    tam_arqui = ftell(out);

    // pedindo ao usuario o indice
    printf("\nIndice: ");
    scanf("%d", &indice);

    // procurar o codigo no arquivo remove.bin
    fseek(remove, (indice - 1) * (TAM_CHAVE + 1), SEEK_SET);

    // Ler os codigos e juntar
    fread(&codigo_cliente_remove, sizeof(char), TAM_COD_CLI, remove);
    // fseek(remove,1,SEEK_CUR);
    fread(&codigo_veiculo_remove, sizeof(char), TAM_COD_VEI, remove);

    // concatenando
    strcat(strcpy(chave_usuario, codigo_cliente_remove), codigo_veiculo_remove);

    /// Pula o header
    fseek(out, sizeof(int), SEEK_SET);

    while (1)
    {
        // ler o tamanho do registro
        fread(&tam_reg, 1, 1, out);

        // Apontando para o codigo do cliente e lendo
        fread(&arquivo.cod_cli, sizeof(char), TAM_COD_CLI - 1, out);

        // Apontando para o codigo do veiculo e lendo
        fseek(out, 1, SEEK_CUR);
        fread(&arquivo.cod_vei, sizeof(char), TAM_COD_VEI - 1, out);

        // concatenando
        strcat(strcpy(chave, arquivo.cod_cli), arquivo.cod_vei);

        // Compararando
        if (strcmp(chave, chave_usuario) == 0)
        {

            // apontando para o comeco do registro a ser deletado
            fseek(out, -(TAM_CHAVE), SEEK_CUR);
            campo_deletado = ftell(out);

            // mudando header
            fseek(out, 0, SEEK_SET);
            fread(&aux, sizeof(int), 1, out);
            fseek(out, 0, SEEK_SET);
            fwrite(&campo_deletado, sizeof(int), 1, out);
            fseek(out, campo_deletado, SEEK_SET);

            // mudar os numeros na frente de cada registro com o marcador especial '*'
            fwrite(&del, sizeof(char), 1, out);
            fwrite(&aux, sizeof(int), 1, out);

            printf("\nREMOVIDO COM SUCESSO!!!\n");
            break;
        }
        else
        {
            // apontando para o comeco do registro onde mostra o seu tamanho
            fseek(out, -(TAM_CHAVE), SEEK_CUR);
            // apontando para o proximo registro
            fseek(out, tam_reg, SEEK_CUR);

            // verificando se o arquivo nao acabou
            fseek(out, 0, SEEK_CUR);
            tam_agr = ftell(out);

            //  caso tenha passado por todo o arquivo e nao achado
            if (tam_arqui <= tam_agr)
            {
                printf("\nREGISTRO NAO EXISTE!!!\n");
                break;
            }
        }
    }
}
void compactando(FILE *out, char *reg, int tam_reg)
{
    FILE *fpnew;
    char compara_del[1], leitura[sizeof(arqui)], *pt, limite[1] = "|";
    int tam_arqui, tam_agr = 0, tamanho = 0, header = -1;
    char vetor[5][50];
    int dias, i;

    // novo arquivo da compactacao
    fpnew = fopen("arqnovo.bin", "w+b");

    // Salvando na variavel o tamanho total do arquivo
    fseek(out, 0, SEEK_END);
    tam_arqui = ftell(out);

    // Escrevendo o header no novo arquivo
    fwrite(&header, sizeof(int), 1, fpnew);
    fseek(out, sizeof(int), SEEK_SET);

    while (1)
    {
        // Condicao de parada
        if (tam_arqui <= tam_agr)
        {
            break;
        }
        else
        {
            // ler o tamanho do registro
            fread(&tamanho, 1, 1, out);

            // Apontando para o possivel registro removido (onde ficaria o "*")
            fread(&compara_del, sizeof(char), 1, out);
            fseek(out, -1, SEEK_CUR);

            // Compara se o caracter "*"
            if (strncmp(compara_del, "*", 1) == 0)
            {
                // pula para o proximo registro
                fseek(out, tamanho, SEEK_CUR);
                tam_agr = ftell(out);
            }
            else
            {
                // Escreve o registro no novo arquivo
                fseek(out, -1, SEEK_CUR);
                fread(&leitura, tamanho + 1, 1, out);

                // separa os campos em tokens
                pt = strtok(leitura, "|");
                for (i = 0; i < 5; i++)
                {
                    if (i == 4)
                    {
                        dias = atoi(pt);
                    }
                    else
                    {
                        strcpy(vetor[i], pt);
                        pt = strtok(NULL, "|");
                    }
                }

                // salva os tokens em uma string unica
                sprintf(reg, "%s|%s|%s|%s|%d|", vetor[0], vetor[1], vetor[2], vetor[3], dias);
                tam_reg = strlen(reg) - 1;

                // escreve no arquivo novo
                fwrite(reg, sizeof(char), tam_reg + 1, fpnew);
                fseek(fpnew, -(tam_reg+1), SEEK_CUR);
                fwrite(&tam_reg, 1, 1, fpnew);
                fseek(fpnew, 0, SEEK_END);
                tam_agr = ftell(out);
            }
        }
    }
    // Fecha os arquivos para poder apagar o antigo e renomear o novo
    fclose(out);
    fclose(fpnew);

    // remove o arquivo antigo
    remove("arq.bin");

    // renomea o arquivo novo
    rename("arqnovo.bin", "arq.bin");

    printf("\nCOMPACTACAO EFETUADA COM SUCESSO!!!\n");
}