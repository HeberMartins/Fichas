#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char nome[45];
    char raca[45];
    char classe[45];
    int forca;
    int vigor;
    int destreza;
    int inteligencia;
    int sabedoria;
} ficha;

void ficha_criacao(ficha *pes)
{
    setlocale(LC_ALL, "Portuguese");
    FILE *file = fopen("fichas_teste.ret", "a+");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
    }

    printf("Insira o nome do personagem: ");
    getchar();
    fgets(pes->nome, sizeof(pes->nome), stdin);
    pes->nome[strcspn(pes->nome, "\n")] = '\0';

    printf("Insira a raca do personagem: ");
    fgets(pes->raca, sizeof(pes->raca), stdin);
    pes->raca[strcspn(pes->raca, "\n")] = '\0';

    printf("Insira a classe do personagem: ");
    fgets(pes->classe, sizeof(pes->classe), stdin);
    pes->classe[strcspn(pes->classe, "\n")] = '\0';

    printf("Insira a forca do personagem: ");
    scanf("%d", &pes->forca);

    printf("Insira o vigor do personagem: ");
    scanf("%d", &pes->vigor);

    printf("Insira a destreza do personagem: ");
    scanf("%d", &pes->destreza);

    printf("Insira a inteligencia do personagem: ");
    scanf("%d", &pes->inteligencia);

    printf("Insira a sabedoria do personagem: ");
    scanf("%d", &pes->sabedoria);

    fprintf(file, "Nome: %s\nRaca: %s\nClasse: %s\nForca: %d\nVigor: %d\nDestreza: %d\nInteligencia: %d\nSabedoria: %d\n\n",
            pes->nome, pes->raca, pes->classe, pes->forca, pes->vigor, pes->destreza, pes->inteligencia, pes->sabedoria);

    fclose(file);
}

void ficha_excluir()
{
    FILE *file = fopen("fichas_teste.ret", "r");
    FILE *temp = fopen("temp.ret", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    ficha *pes = (ficha *)malloc(sizeof(ficha));
    char nomeExcluir[45];

    printf("Digite o nome do personagem que deseja excluir: ");
    getchar();
    fgets(nomeExcluir, sizeof(nomeExcluir), stdin);
    nomeExcluir[strcspn(nomeExcluir, "\n")] = '\0';

    int encontrado = 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        if (strncmp(linha, "Nome: ", 6) == 0)
        {

            sscanf(linha, "Nome: %s", pes->nome);

            if (strcmp(pes->nome, nomeExcluir) != 0)
            {
                fprintf(temp, "%s", linha);

                for (int i = 0; i < 7; i++)
                {
                    if (fgets(linha, sizeof(linha), file) != NULL)
                    {
                        fprintf(temp, "%s", linha);
                    }
                }
            }
            else
            {
                encontrado = 1;

                for (int i = 0; i < 7; i++)
                {
                    fgets(linha, sizeof(linha), file);
                }
            }
        }
        else
        {

            fprintf(temp, "%s", linha);
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado)
    {
        remove("fichas_teste.ret");
        rename("temp.ret", "fichas_teste.ret");
        printf("Ficha excluida com sucesso.\n");
    }
    else
    {
        printf("Ficha nao encontrada.\n");
        remove("temp.ret");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *file;
    int escolha = 0;
    int continuar = 1;
    ficha *pes = (ficha *)malloc(sizeof(ficha));

    if (pes == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do
    {
        printf("Ola, seja bem-vindo ao sistema. Por favor, escolha uma das opcoes abaixo:\n");
        printf("1 - Fichas\n2 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            do
            {
                printf("\nMenu de Fichas. Por favor escolha uma das opcoes:\n");
                printf("1 - Visualizar Fichas Criadas\n");
                printf("2 - Criar Nova Ficha\n");
                printf("3 - Excluir Ficha\n");
                printf("4 - Voltar ao Menu Inicial\n");
                scanf("%d", &escolha);

                switch (escolha)
                {
                case 1:
                    file = fopen("fichas_teste.ret", "r");
                    if (file == NULL)
                    {
                        printf("Nenhuma ficha encontrada ou erro ao abrir o arquivo.\n");
                    }
                    else
                    {
                        char linha[100];
                        while (fgets(linha, sizeof(linha), file) != NULL)
                        {
                            printf("%s", linha);
                        }
                        fclose(file);
                    }
                    break;

                case 2:
                    printf("Criador de Fichas.\n");
                    int qt_fichas;
                    printf("Quantas fichas ser�o criadas? Limite maximo: 10 fichas\n");
                    scanf("%d", &qt_fichas);

                    if (qt_fichas < 1 || qt_fichas > 10)
                    {
                        printf("Numero invalido! Insira entre 1 e 10 fichas.\n");
                    }
                    else
                    {
                        for (int i = 0; i < qt_fichas; i++)
                        {
                            ficha_criacao(pes);
                        }
                    }
                    break;

                case 3:
                    ficha_excluir();
                    break;

                case 4:
                    printf("Voltando ao menu inicial...\n");
                    break;

                default:
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while (escolha != 4);
            break;

        case 2:
            printf("Adeus! Ate a proxima!\n");
            continuar = 0;
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (continuar);

    free(pes);
    return 0;
}
