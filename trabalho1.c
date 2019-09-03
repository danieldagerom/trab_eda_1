#include <stdio.h>
#include <stdlib.h>
typedef struct Funcionario{
    int idade;
    char *nome, *email;
}funcionario;
void criafuncionario(int qtd);
void incluifuncionario();
void imprimefuncionario(int qtd);
void menu();
int main(){
    funcionario *ptr;
    int qtd, i, qtd2;
    menu();
    
    return 0;
}
void menu(){
    int opcao;

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
        incluifuncionario();
        break;
    
    default:
        break;
    }
}
void incluifuncionario(){
    int qtd, i;
    funcionario *ptr;
    printf("Quantos alunos deseja incluir?\n");
    scanf("%d", &qtd);
    criafuncionario(qtd);
    for(i = 0; i < qtd; i++){
        printf("Digite o nome do funcionario[%d] -> ", i);
        scanf("%[^\n", ptr[i].nome);
        printf("\nDigite o email do funcionario[%d] -> ", i);
        scanf("%[^\n", ptr[i].email);
        printf("\nDigite a idade do funcionario[%d] -> ", i);
        scanf("%[^\n", ptr[i].idade);
    }
}
void imprimefuncionario(int qtd){
    funcionario *ptr;
    int i;
    for(int i = 0; i < qtd; i++){
        printf("%[^\n] -- %[^\n] -- %d\n", ptr[i].nome, ptr[i].email, ptr[i].idade);
    }
}

void criafuncionario(int qtd){
    funcionario *ptr;
    int i;

    ptr = (funcionario *) malloc(qtd * sizeof(funcionario));
    if(ptr == NULL){
        printf("ERRO!\n");
        exit(2);
    }
    for(i = 0; i < qtd; i++){
        ptr[i].nome = (char *) malloc(35 * sizeof(char));
        printf("deu certo   ");
        if(ptr[i].nome == NULL){
            printf("ERRO!\n");
            exit(2);
        } 
    }
     for(i = 0; i < qtd; i++){
        ptr[i].email = (char *) malloc(35 * sizeof(char));
        printf("deu certo   ");
        if(ptr[i].email == NULL){
            printf("ERRO!\n");
            exit(2);
        } 
    }
}




