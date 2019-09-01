#include <stdio.h>
#include <stdlib.h>
typedef struct Funcionario{
    int idade;
    char *nome, *email;
}funcionario;
void criafuncionario(int qtd);
int main(){
    funcionario *ptr;
    int qtd, i, qtd2;
    printf("Quantos alunos deseja incluir?\n");
    scanf("%d", &qtd);
    criafuncionario(qtd);
    
    return 0;
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




