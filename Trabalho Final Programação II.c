#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Trabalho final da 3ª etapa de Programação II. Igor Ryan e Luiz Felipe.

typedef struct {   //Feito por Igor
    int codigo;
    char descricao[200];
    char nomeCliente[100];
    char telefone[15];
    int resolvido;
} Problema;

typedef struct {   // Feito por Luiz Felipe
    Problema problemas[100];
    int qtd;
} SistemaSuporte;

int main(); //Feito por Felipe
void cadastrar(SistemaSuporte *suporte);
void imprimir(SistemaSuporte *suporte);
void excluir(SistemaSuporte *suporte);
void status(SistemaSuporte *suporte);
void cDados(SistemaSuporte *suporte);
void salvar(SistemaSuporte *suporte);
int menu();

int main() {                //Feito por Felipe
    setlocale(LC_ALL, "Portuguese");
    SistemaSuporte suporte;
    suporte.qtd = 0;

    cDados(&suporte);

    while (1) {
        fflush(stdin);
        char op = menu();
        if (op == '0') {
            salvar(&suporte); // Salva as informações ao fechar o programa
            break;
        }
        switch (op) {
            case '1':
                cadastrar(&suporte);
                system("pause");
                break;
            case '2':
                imprimir(&suporte);
                system("pause");
                break;
            case '3':
                status(&suporte);
                system("pause");
                break;
            case '4':
                excluir(&suporte);
                system("pause");
                break;
            default:
                printf("\nOpção Inválida!\n");
                system("pause");
        }
    }
    return 0;
}

int menu() {
    system("cls");
    char op;
    printf("=========== SISTEMA DE SUPORTE TECNICO LR SOLUÇÕES DE T.I ===========\n\n");
    printf("1| - CADASTRAR ATENDIMENTO\n");
    printf("2| - CONSULTAR ATENDIMENTOS\n");
    printf("3| - ATUALIZAR STATUS DE ATENDIMENTOS\n");
    printf("4| - EXCLUIR ATENDIMENTOS\n");
    printf("\n=====================================================================\n");
    printf("\n0| - SAIR\n");
    printf("\n>> ");
    scanf("%c", &op);
    return op;
}

void cadastrar(SistemaSuporte *suporte) {               // Feito por Luiz Felipe
    char descricao[200], nomeCliente[100], telefone[15];
    system("cls");
    fflush(stdin);
    printf("=========== CADASTRAR ATENDIMENTO ===========\n\n");
    printf("NOME DO CLIENTE: ");
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

    printf("TELEFONE PARA CONTATO: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    printf("DESCRIÇÃO DO PROBLEMA: ");
    fgets(descricao, sizeof(descricao), stdin);
    descricao[strcspn(descricao, "\n")] = '\0';

    int codigo;
    if (suporte->qtd == 0) {
        codigo = 1;
    } else {
        codigo = suporte->problemas[suporte->qtd - 1].codigo + 1;
    }

    suporte->problemas[suporte->qtd].codigo = codigo;
    strcpy(suporte->problemas[suporte->qtd].descricao, descricao);
    strcpy(suporte->problemas[suporte->qtd].nomeCliente, nomeCliente);
    strcpy(suporte->problemas[suporte->qtd].telefone, telefone);
    suporte->problemas[suporte->qtd].resolvido = 0; // o problema começa como não resolvido
    suporte->qtd++;

    printf("\nAtendimento cadastrado com sucesso!\n");
}

void imprimir(SistemaSuporte *suporte) {      //Feito Igor
    system("cls");
    printf("=========== LISTAGEM DE SUPORTES TECNICOS ===========\n\n");
    printf("---------------------------------------------");
    int i;
    for (i = 0; i < suporte->qtd; i++) {
        printf("\nCÓDIGO: %d", suporte->problemas[i].codigo);
        printf("\nNOME DO CLIENTE: %s", suporte->problemas[i].nomeCliente);
        printf("\nTELEFONE: %s", suporte->problemas[i].telefone);
        printf("\nDESCRIÇÃO: %s", suporte->problemas[i].descricao);
        printf("\nSTATUS: %s", suporte->problemas[i].resolvido ? "Resolvido" : "Não Resolvido");
        printf("\n---------------------------------------------");
    }
    printf("\n");
}

void excluir(SistemaSuporte *suporte) {         //Feito por Igor
    system("cls");
    printf("=========== EXCLUIR ATENDIMENTO ===========\n\n");
    imprimir(suporte);
    int c;
    printf("Qual atendimento você deseja excluir? (Digite o código).\nVoltar para menu principal.Pressione [0]\n");
    printf("\nEscolha uma opção:");
	scanf("%d", &c);

	if(c == 0){
		menu();
	}else{



    int certeza = 0;
    printf("Tem certeza que deseja excluir as informações do atendimento %d? (1 - SIM; 0 - NÃO): ", c);
    scanf("%d", &certeza);
    if (certeza == 1) {
        int i, j, encontrado = 0;
       for (i = 0; i < suporte->qtd; i++) {
            if (suporte->problemas[i].codigo == c) {
                for (j = i; j < suporte->qtd - 1; j++) {
                    suporte->problemas[j] = suporte->problemas[j + 1];
                }
                suporte->qtd--;
                encontrado = 1;
                break;
            }
        }
        //Entrando nos condicionais de saída
        if (encontrado == 0) {
            printf("\nAtendimento não encontrado!");
        } else if(encontrado == 1){
			printf("\nAtendimento excluído com sucesso!");
		}
        printf("\n");
    }
    int continar;
    printf("\n deseja continar? [1]SIM [2]NÃO:");
    scanf("%d",&continar);
    if(continar == 1){
		excluir(suporte);
	}
}
}

void status(SistemaSuporte *suporte) {      // Feito por Luiz Felipe
    system("cls");
    printf("=========== ATUALIZAR STATUS DE ATENDIMENTO===========\n\n");
    imprimir(suporte);
    int codigo;
    printf("Digite o código do atendimento que deseja atualizar o status: ");
    scanf("%d", &codigo);

    int encontrado = 0;
    int i;
    for (i = 0; i < suporte->qtd; i++) {
        if (suporte->problemas[i].codigo == codigo) {
            encontrado = 1;
            printf("O problema %d está atualmente: %s\n", codigo, suporte->problemas[i].resolvido ? "Resolvido" : "Não Resolvido");
            printf("Deseja alterar para: %s? (1 - SIM; 0 - NÃO): ", suporte->problemas[i].resolvido ? "Não Resolvido" : "Resolvido");
            int opcao;
            scanf("%d", &opcao);
            if (opcao == 1) {
                suporte->problemas[i].resolvido = !suporte->problemas[i].resolvido; // Alterna o status
                printf("Status atualizado com sucesso!\n");
            } else {
                printf("Status não alterado.\n");
            }
            break;
        }
    }
    if (encontrado == 0) {
        printf("Problema com código %d não encontrado.\n", codigo);
    }
}

void cDados(SistemaSuporte *suporte) {       //Feito por Luiz Felipe
    FILE *arquivo = fopen("problemas.txt", "r");
    if (arquivo == NULL) {
        return; // Se o arquivo não existe ele inicia vazio
    }

    suporte->qtd = 0;
    while (fscanf(arquivo, "%d\n", &suporte->problemas[suporte->qtd].codigo) != EOF) {
        fgets(suporte->problemas[suporte->qtd].nomeCliente, sizeof(suporte->problemas[suporte->qtd].nomeCliente), arquivo);
        suporte->problemas[suporte->qtd].nomeCliente[strcspn(suporte->problemas[suporte->qtd].nomeCliente, "\n")] = '\0';

        fgets(suporte->problemas[suporte->qtd].telefone, sizeof(suporte->problemas[suporte->qtd].telefone), arquivo);
        suporte->problemas[suporte->qtd].telefone[strcspn(suporte->problemas[suporte->qtd].telefone, "\n")] = '\0';

        fgets(suporte->problemas[suporte->qtd].descricao, sizeof(suporte->problemas[suporte->qtd].descricao), arquivo);
        suporte->problemas[suporte->qtd].descricao[strcspn(suporte->problemas[suporte->qtd].descricao, "\n")] = '\0';

        fscanf(arquivo, "%d\n", &suporte->problemas[suporte->qtd].resolvido);
        suporte->qtd++;
    }

    fclose(arquivo);
}

void salvar(SistemaSuporte *suporte) {      //Feito por Igor
    FILE *arquivo = fopen("problemas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados!\n");
        return;
    }
    int i;
    for (i = 0; i < suporte->qtd; i++) {
        fprintf(arquivo, "%d\n", suporte->problemas[i].codigo);
        fprintf(arquivo, "%s\n", suporte->problemas[i].nomeCliente);
        fprintf(arquivo, "%s\n", suporte->problemas[i].telefone);
        fprintf(arquivo, "%s\n", suporte->problemas[i].descricao);
        fprintf(arquivo, "%d\n", suporte->problemas[i].resolvido);
    }

    fclose(arquivo);
}