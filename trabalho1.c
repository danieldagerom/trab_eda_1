#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Funcionario{
    int idade;
    char *nome, *email;
}funcionario;

funcionario *criafuncionario(int quant, int *check, int *x, funcionario *ptr);
int cadastro(int *quant, int *novo);
void incluifuncionario(funcionario *ptr, int quant, int *x);
void imprimefuncionario(funcionario *ptr, int *quant);
void editar_switch(funcionario *ptr, int *quant);
void exclui_funcionario(funcionario *ptr, int *quant);
void menu();

int main(){
    menu();
    return 0;
}

void menu(){
    funcionario *empregado;
    int opcao = -1, quant = 0, novo = 0, cont = 0, check = 0, x = 0;
    while(opcao != 0){
        //system("clear");
        printf("Seja bem vindo ao primeiro trabalho de EDA1!\n");
        printf("____________________________________________\n");
        printf("________Esse eh o MENU DE OPCOES:___________\n");
        printf("1) *INCLUIR* FUNCIONARIOS:\n");
        printf("2) *LISTAR* FUNCIONARIOS INCLUIDOS:\n");
        printf("3) *EDITAR* FUNCIONARIOS INCLUIDOS:\n");
        printf("4) *EXCLUIR* FUNCIONARIOS INCLUIDOS:\n");
        printf("0) *SAIR*:\n");
        printf("Qual opçao voce deseja? -> ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            quant += cadastro(&quant, &novo);
            empregado = criafuncionario(quant, &check, &x, &empregado[0]);
            incluifuncionario(&empregado[0], quant, &x);
            break;
        case 2:
            imprimefuncionario(empregado, &quant);
            break;
        case 3 :
            editar_switch(empregado, &quant);
            break;
        case 4:
            exclui_funcionario(empregado, &quant);
            break;
        
        default:
            break;
        }
    }
    for(int i = 0; i < quant; i++){
        free(empregado[i].nome);
        free(empregado[i].email);
        printf("Apagou aqui!\n\n");
    }
    free(empregado);    
        printf("Apagou aqui tambem!\n\n");

}

void incluifuncionario(funcionario *ptr, int quant, int *x){
    int i;
    for(i = *x; i < quant; i++){
        printf("\nDigite o nome do funcionario[%d] -> ", i + 1);
        getchar();
        scanf("%[^\n]", ptr[i].nome);
        printf("\nDigite o email do funcionario[%d] -> ", i + 1);
        getchar();
        scanf("%[^\n]", ptr[i].email);
        printf("\nDigite a idade do funcionario[%d] -> ", i + 1);
        scanf("%d", &ptr[i].idade);        
    }
    *x = quant;
    printf("%d Funcionarios foram cadastrados com sucesso!\n", quant);
    sleep(1.0);
}

void imprimefuncionario(funcionario *ptr, int *quant){
    int i;
    printf("quant = %d", *quant);
    for(int i = 0; i < *quant; i++){
        printf("  %s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
    }
    sleep(2.5);
}

int cadastro(int *quant, int *novo){
    *novo = *quant;
    printf("Quantos funcionarios deseja incluir?\n");
    scanf("%d", quant);

    return *novo;
}

funcionario *criafuncionario(int quant, int *check, int *x, funcionario *ptr){
    int i;
    printf("CHEGOU AQUI\n\n\n");
    if(*check == 0){
    printf("CHEGOU AQUI2\n\n\n");

    funcionario *first;
    printf("CHEGOU AQUI2\n\n\n");

    first = (funcionario *) malloc(quant * sizeof(funcionario));


    if(first == NULL){
        printf("ERRO!\n"); 
        exit(2);
    }

        for(i = 0; i < quant; i++){
            first[i].nome = (char *) malloc(50 * sizeof(char));
            printf("deu certo   ");
            if(first[i].nome == NULL){
                printf("ERRO!\n");
                exit(2);
            } 
        }
        for(i = 0; i < quant; i++){
            first[i].email = (char *) malloc(50 * sizeof(char));
            printf("deu certo   ");
            if(first[i].email == NULL){
                printf("ERRO!\n");
                exit(2);
            } 
        }
        *check = 2;
        return first;
    }else{
        ptr = (funcionario *) realloc(ptr, quant * sizeof(funcionario));
        if(ptr == NULL){
            printf("ERRO!\n");
            exit(2);
        }
        for(i = *x; i < quant; i++){
            ptr[i].nome = (char *) malloc (35 * sizeof(char));
            if(ptr[i].nome == NULL){
                printf("ERRO!\n");
                exit(2);
            }
        }
        for(i = *x; i < quant; i++){
            ptr[i].email = (char *) malloc (35 * sizeof(char));
            if(ptr[i].email == NULL){
                printf("ERRO!\n");
                exit(2);
            }
        }
    }
    return ptr;
}

void editar_switch(funcionario *ptr, int *quant){
    int opcao = -1, indice = 0, achou = 0, ret;
    char *nome, *email;
    nome = (char *) malloc(35 * sizeof(char));
    if(nome == NULL) {
        printf("ERRO!\n");
        exit(2);
    }
    email = (char *) malloc(35 * sizeof(char));
    if(email == NULL) {
        printf("ERRO!\n");
        exit(2);
    }

    while (opcao != 0) {
        printf("Como deseja editar o funcionario?\n");
        printf("(1) Procurar com indice\n");
        printf("(2) Procurar com nome\n");
        printf("(3) Procurar com email\n");
        printf("(0) Sair\n");
        printf(" = ");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            printf("Digite o indice do funcionario que deseja editar = ");
            scanf("%d", &indice);
            for(int i = 0; i < *quant; i++){
                if(i == (indice - 1)){
                    printf("Funcionario encontrado!\n");
                    printf("%s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
                    sleep(1.0);
                    printf("____Editar___:\n");
                    printf("Novo nome: ");
                    getchar();
                    scanf("%[^\n]", ptr[i].nome);
                    getchar();
                    printf("Novo email: ");
                    scanf("%[^\n]", ptr[i].email);
                    printf("Nova idade: ");
                    scanf("%d", &ptr[indice - 1].idade);
                    printf("Funcionario %s alterado com sucesso!\n", ptr[indice - 1].nome);
                    sleep(1.0);
                    achou++;
                    printf("chegoiu aqui switch\n\n");
                    break;
                }
            }if(achou == 0){
                printf("Funcionario não encontrado!\n");
                sleep(1.0);
            }
            break;
        case 2:
            printf("Digite o nome do funcionario que deseja editar: ");
            getchar();
            scanf("%[^\n]", nome);
            for(int i = 0; i < *quant; i++){
               // printf("chegou aqui nome\n");
                ret = strcmp(ptr[i].nome, nome);
                if(ret == 0){
                    indice = i;
                    achou++;
                    printf("achou %d\n", i);
                    //break;
                } }
            if(achou == 1){
                    printf("Funcionario encontrado!\n");
                    printf("%s -- %s -- %d\n", ptr[indice].nome, ptr[indice].email, ptr[indice].idade);
                    sleep(1.0);
                    printf("____Editar___:\n");
                    printf("Novo nome: ");
                    getchar();
                    scanf("%[^\n]", ptr[indice].nome);
                    getchar();
                    printf("Novo email: ");
                    scanf("%[^\n]", ptr[indice].email);
                    printf("Nova idade: ");
                    scanf("%d", &ptr[indice].idade);
                    printf("Funcionario %s alterado com sucesso!\n", ptr[indice].nome);
                    sleep(1.0);
                    //achou = 1;
            }else if(achou > 1){
                printf("Mais de um funcionario com esse nome!\n utilize a funcao (3), pelo email, para editar!\n");
                sleep(2.0);
                break;
            }
             if(achou == 0){
                printf("Funcionario não encontrado!\n");
                sleep(1.0);
            } 
            break;
        case 3:
            printf("Digite o email do funcionario que deseja editar: ");
            getchar();
            scanf("%[^\n]", email);
            for(int i = 0; i < *quant; i++){
               // printf("chegou aqui nome\n");
                ret = strcmp(ptr[i].email, email);
                if(ret == 0){
                    printf("Funcionario encontrado!\n");
                    printf("%s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
                    sleep(1.0);
                    printf("____Editar___:\n");
                    printf("Novo nome: ");
                    getchar();
                    scanf("%[^\n]", ptr[i].nome);
                    getchar();
                    printf("Novo email: ");
                    scanf("%[^\n]", ptr[i].email);
                    printf("Nova idade: ");
                    scanf("%d", &ptr[i].idade);
                    printf("Funcionario %s alterado com sucesso!\n", ptr[i].nome);
                    sleep(1.0);
                    achou = 1;
                    break;
                }
             }if(achou == 0){
                printf("Funcionario não encontrado!\n");
                sleep(1.0);
            } 
            break;
        
        default:
            break;
        }
    free(nome);
    printf("limpou nome aux!!\n");
    free(email);
    printf("limpou email!!\n");
    }
}

void exclui_funcionario(funcionario *ptr, int *quant){
    int indice, opcao = -1, certeza, achou = 0, ret;
    char *nome;
    printf("quant = %d\n\n", *quant);

    nome = (char *) malloc(35 * sizeof(char));
    if(nome == NULL) {
        printf("ERRO!\n");
        exit(2);
    }
    while(opcao != 0){
        printf("------Como deseja excluir?------\n");
        printf("(1) Excluir com o indice do funcionario:\n");
        printf("(2) Excluir com o nome do funcionario:\n");
        printf("(0) <- Voltar\n");
        printf(" = ");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            printf("Digite o indice do funcionario que deseja editar = ");
            scanf("%d", &indice);
            for(int i = 0; i < *quant; i++){
                if(i == (indice - 1)){
                    printf("Funcionario encontrado!\n");
                    printf("%s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
                    achou = 2;
                    sleep(1.0);
                    printf("Tem certeza que deseja excluir esse funcionario?\n");
                    printf("(1) = SIM\n(2) = NAO\n = ");
                    scanf("%d", &certeza);
                    if(certeza == 1){
                        for(int i = indice - 1; i < *quant; i++){
                            ptr[i] = ptr[i + 1];
                        }
                        *quant -= 1;
                        ptr = (funcionario *) realloc(ptr, *quant * sizeof(funcionario));
                        if(ptr == NULL) {
                            printf("ERRO!\n");
                            exit(2);
                        }
                        printf("Funcionario excluido com sucesso!\n");
                        break;
                    }else
                        break;
                }
            }
            if(achou == 0){
                printf("Funcionario não encontrado!\n");
                sleep(1.0);
            }
            break;
        case 2:
            printf("Digite o nome completo do funcionario que quer excluir = ");
            scanf("%[^\n[", nome);
            for(int i = 0; i < *quant; i++){
                ret = strcmp(ptr[i].nome, nome);
                if(ret == 0){
                    printf("Funcionario encontrado!\n");
                    printf("%s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
                    achou = 2;
                    indice = i;
                    sleep(1.0);
                    printf("Tem certeza que deseja excluir esse funcionario?\n");
                    printf("(1) = SIM\n(2) = NAO\n = ");
                    scanf("%d", &certeza);
                    if(certeza == 1){
                        for(int i = indice; i < *quant; i++){
                            ptr[i] = ptr[i + 1];
                        }
                        *quant -= 1;
                        ptr = (funcionario *) realloc(ptr, *quant * sizeof(funcionario));
                        if(ptr == NULL) {
                            printf("ERRO!\n");
                            exit(2);
                        }
                        printf("Funcionario excluido com sucesso!\n");
                        break;
                    }else
                        break;
                }
            }
            if(achou == 0){
                printf("Funcionario não encontrado!\n");
                sleep(1.0);
            }
            break;
        
        default:
            break;
        }
    }

}



