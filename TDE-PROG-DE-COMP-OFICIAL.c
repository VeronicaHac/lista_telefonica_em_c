#include <stdio.h>
#include <string.h>


typedef struct {
    char nome[12];
    char telefone[21];
} Catalogo;



void adicionarContato() {
    Catalogo novoContato;

    fflush(stdin);

    printf("\n\nDigite o nome do contato: ");
    fgets(novoContato.nome, 21, stdin);
    novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';

    while (strlen(novoContato.nome) == 0) {
        printf("O nome nao pode estar em branco. Digite novamente: ");
        fgets(novoContato.nome, sizeof(novoContato.nome), stdin);
        novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';
    }

    printf("Digite o telefone do contato: ");
    fgets(novoContato.telefone, 12, stdin);
    novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0';


    while (strlen(novoContato.telefone) == 0) {
        printf("O telefone nao pode estar em branco. Digite novamente: ");
        fgets(novoContato.telefone, sizeof(novoContato.telefone), stdin);
        novoContato.telefone[strcspn(novoContato.telefone, "\n")] = '\0';
    }

    FILE *arquivo = fopen("catalogo.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreve os dados do contato no arquivo
    fprintf(arquivo, "%s;%s\n", novoContato.nome, novoContato.telefone);

    // Fecha o arquivo
    fclose(arquivo);

    printf("Contato adicionado com sucesso!\n\n\n");
}

void pesquisarContato(const char* nome) {
    Catalogo contato;
    int encontrado = 0;


    FILE* arquivo = fopen("catalogo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n\n");
        return;
    }

    while (fscanf(arquivo, "%20[^;];%11[^\n]%*c", contato.nome, contato.telefone) == 2) {
        if (strcmp(nome, contato.nome) == 0) {
            printf("\n\nContato encontrado:\n");
            printf("Nome: %s\nTelefone: %s\n\n\n", contato.nome, contato.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);

    if (!encontrado) {
        printf("Contato nao encontrado.\n\n\n");
    }
}


void pesquisarEExcluirContato(const char* nome) {
    Catalogo contato;
    int encontrado = 0;

    FILE* arquivo = fopen("catalogo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE* arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%11[^;];%20[^\n]%*c", contato.nome, contato.telefone) == 2) {
        if (strcmp(nome, contato.nome) == 0) {
            printf("Contato encontrado e excluido:\n");
            printf("Nome: %s\nTelefone: %s\n\n\n\n", contato.nome, contato.telefone);
            encontrado = 1;
        } else {
            fprintf(arquivoTemp, "%s;%s\n", contato.nome, contato.telefone);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("catalogo.txt");

    rename("temp.txt", "catalogo.txt");

    if (!encontrado) {
        printf("Contato nao encontrado.\n");
    }
}




int main() {

    int op;
    char nome[21] = {'\0'};
    char nomecomp2[21] = {'\0'};
    char nomecomp3[21] = {'\0'};
    char telefone [12] = {0};
    int i;
    int cont = 0;
    int cont2 = 0;
    char nomePesquisa[21];




    while (op != 4){
        printf("[1] Cadastrar telefone\n");
        printf("[2] Consultar telefone\n");
        printf("[3] Excluir telefone\n");
        printf("[4] Sair do Menu\n");
        printf("-------- Digite a opcao desejada --------\n");

        scanf("%i",&op);


        if(op != 4){

                switch(op){
                    case 1:


                         adicionarContato();

                        break;
                    case 2:


                        fflush(stdin);
                        printf("\n\nDigite o nome do contato a ser pesquisado: ");
                        fgets(nomePesquisa, sizeof(nomePesquisa), stdin);
                        nomePesquisa[strcspn(nomePesquisa, "\n")] = '\0';

                        pesquisarContato(nomePesquisa);

                        break;
                    case 3:


                        fflush(stdin);
                        printf("\n\nDigite o nome do contato a ser pesquisado e excluido: \n");
                        fgets(nomePesquisa, sizeof(nomePesquisa), stdin);
                        nomePesquisa[strcspn(nomePesquisa, "\n\n\n")] = '\0';

                        pesquisarEExcluirContato(nomePesquisa);


                        break;

                    default:
                        printf("Opcao invalida, por favor digite uma opcao valida\n\n");

                }

        }else {
            printf("Encerrando o programa, Tchau!\n");

        }

    }








return 0;
}
