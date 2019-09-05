#include <stdio.h>
#include <stdlib.h>
typedef struct Funcionario{
    int idade;
    char *nome, *email;
}funcionario;
funcionario *criafuncionario(int quant);
int cadastro(int *quant, int *novo);
void incluifuncionario();
void imprimefuncionario(funcionario *ptr, int quant, int comp);
void menu();
int main(){
    menu();
    
    return 0;
}
void menu(){
    funcionario *empregado;
    int opcao = -1, quant = 0, novo = 0;
    while(opcao != 0){
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
            empregado = criafuncionario(quant);
            incluifuncionario(&empregado[0], quant);
            break;
        case 2:
            imprimefuncionario(empregado ,quant, novo);
        
        default:
            break;
        }
    }
    for(int i = 0; i < quant; i++){
        free(empregado[i].nome);
        printf("limpou nome!\n ");
        free(empregado[i].email);
        printf("limpou email!\n ");
    }
    free(empregado);

}
void incluifuncionario(funcionario *ptr, int *quant){
    int i;
    getchar(); 
    for(i = 0; i < quant; i++){
        printf("\nDigite o nome do funcionario[%d] -> ", i + 1);
        scanf("%[^\n]", ptr[i].nome);
        printf("\nDigite o email do funcionario[%d] -> ", i + 1);
        getchar();
        scanf("%[^\n]", ptr[i].email);
        printf("\nDigite a idade do funcionario[%d] -> ", i + 1);
        scanf("%d", &ptr[i].idade);        
    }
}
void imprimefuncionario(funcionario *ptr, int quant, int comp){
    int i;
    for(int i = comp; i < quant; i++){
        printf("     %s -- %s -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
    }
}
int cadastro(int *quant, int *novo){
    *novo = *quant;
    printf("Quantos funcionarios deseja incluir?\n");
    scanf("%d", quant);

    return *novo;
}



funcionario *criafuncionario(int quant){
    int i;
    funcionario *ptr;
    ptr = (funcionario *) malloc(quant * sizeof(funcionario));
    if(ptr == NULL){
        printf("ERRO!\n");
        exit(2);
    }
    for(i = 0; i < quant; i++){
        ptr[i].nome = (char *) malloc(50 * sizeof(char));
        printf("deu certo   ");
        if(ptr[i].nome == NULL){
            printf("ERRO!\n");
            exit(2);
        } 
    }
     for(i = 0; i < quant; i++){
        ptr[i].email = (char *) malloc(50 * sizeof(char));
        printf("deu certo   ");
        if(ptr[i].email == NULL){
            printf("ERRO!\n");
            exit(2);
        } 
    }
    return ptr;
}




