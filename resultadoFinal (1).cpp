#include <stdio.h>
#include <stdlib.h> // Biblioteca de manipula��o de arquivos
#include <string.h> // Biblioteca de manipula��o de string
#include <windows.h> // Adiciona a fun��o de limpar a tela (promptt)
#include <locale.h> // Inclui a biblioteca para configurar o local e a codifica��o de caracteres.

// Nome: Amanda de Freitas     | 
// Nome: Ana Luiza Guilherme   | 
// Nome: Bruna Sant'Ana        | 

// Estrutura para armazenar registros
struct Registro {
    char nome[50];
    int idade;
};

// Fun��o para incluir um registro em um arquivo de texto
void incluirRegistro(FILE *arquivo) {
    struct Registro registro;
    printf("Digite o nome: ");
    scanf("%s", registro.nome);
    printf("Digite a idade: ");
    scanf("%d", &registro.idade);

    FILE *pont_arq = fopen("registros.txt", "a");

    if (pont_arq == NULL) {
        perror("Erro ao tentar abrir o arquivo");
        return;
    }

    int r = fprintf(pont_arq, "%s %d\n", registro.nome, registro.idade);

    if (r < 0) {
        printf("Erro ao tentar gravar os dados!\n");
    } else {
        printf("Dados gravados com sucesso.\n");
    }

    fclose(pont_arq);
}

// Fun��o para excluir um registro do arquivo
void excluirRegistro(FILE *arquivo) {
    char nome[50];
    printf("Digite o nome a ser exclu�do: ");
    scanf("%s", nome);

    FILE *tempFile = fopen("tempFile.txt", "w");
    struct Registro registro;

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo original");
        fclose(tempFile);
        return;
    }

    if (tempFile == NULL) {
        perror("Erro ao criar o arquivo tempor�rio");
        fclose(arquivo);
        return;
    }

    int registrosExcluidos = 0;

    while (fscanf(arquivo, "%s %d", registro.nome, &registro.idade) == 2) {
        if (strcmp(registro.nome, nome) != 0) {
            fprintf(tempFile, "%s %d\n", registro.nome, registro.idade);
        } else {
            registrosExcluidos++;
        }
    }

    fclose(arquivo);
    fclose(tempFile);

    // Verifica se algum registro foi exclu�do antes de realizar opera��es de remo��o e renomea��o
    if (registrosExcluidos > 0) {
        remove("registros.txt");
        rename("tempFile.txt", "registros.txt");
    } else {
        // Se nenhum registro foi exclu�do, remova o arquivo tempor�rio
        remove("tempFile.txt");
    }

    arquivo = fopen("registros.txt", "r");
}

// Fun��o para gerar um relat�rio e salvar em um arquivo de texto
void gerarRelatorio(FILE *arquivo) {
    struct Registro registro;
    FILE *relatorioFile = fopen("relatorio.txt", "w");

    if (relatorioFile == NULL) {
        perror("Erro ao criar o arquivo de relat�rio");
        return;
    }

    while (fscanf(arquivo, "%s %d", registro.nome, &registro.idade) == 2) {
        fprintf(relatorioFile, "Nome: %s, Idade: %d\n", registro.nome, registro.idade);
    }

    fclose(relatorioFile);
    printf("Relat�rio gerado e salvo em 'registros.txt'\n");
    
    printf("Pressione Enter para retornar ao menu principal...");
    fflush(stdin); //Limpa o buffer (mem�ria temporaria)
    getchar();
}
// Classe Principal
int main() {
	setlocale (LC_ALL, "portuguese"); // Define o idioma 
    FILE *arquivo = fopen("registros.txt", "a+"); // Abre registro.txt

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int opcao;

    do {
        system("cls");  // Limpa a tela no Windows | cmd

        printf("      M E N U    P R I N C I P A L        \n");
        printf("     * * * * * * * * * * * * * * *        \n");
        printf("* * * * * * * * * * * * * * * * * * * * * \n\n\n");

        printf("1 - I N C L U I R \n");
        printf("2 - E X C L U I R \n");
        printf("3 - R E L A T � R I O \n");
        printf("4 - S A I R \n");

        printf("\n\n E s c o l h a   a   o p � � o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirRegistro(arquivo);
                break;
            case 2:
                excluirRegistro(arquivo);
                break;
            case 3:
                gerarRelatorio(arquivo);
                break;
            case 4:
                printf("Saindo do programa. At� mais!\n");
                fclose(arquivo);
                return 0;
            default:
                printf("Op��o inv�lida. Por favor, escolha uma op��o v�lida.\n");
                break;
        }

        system("pause"); // Pausa para que o usu�rio possa ver o resultado
    } while (1);

    return 0;
}

