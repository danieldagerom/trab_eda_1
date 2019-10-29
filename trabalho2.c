#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct no {
    int matricula;
    char *nome;
    char *email;
    struct lista_disciplinas *materias;
    struct no *next;
}node;

typedef struct Disciplina{
    char *nome;
    char *mencao;
    struct Disciplina *next;
}disciplina;

typedef struct Lista_Disciplinas{
    disciplina *head;
    int size;
}lista_disciplinas;

typedef struct lista {
    node *head;
    int size;
}list;


list * create_list();
lista_disciplinas * create_list_disciplinas();
void listar_disciplinas(lista_disciplinas *);
void print_list(list *);
int index_of(lista_disciplinas *, disciplina *);
int is_empty(list *);
int is_empty_disciplinas(lista_disciplinas *);
void pop(list *);
void pop_disciplina(lista_disciplinas *);
void tracejado();
void menu_vizualizar(node *);
void altera_string(char *);
void cadastro(list *);
void cadastro_disciplina(node *);
void push(list *, node *);
void push_disciplina(lista_disciplinas *, disciplina *);
void editar_disciplina(node *);
void excluir_disciplina(lista_disciplinas *);
void filtrar_disciplina(lista_disciplinas *);
void relatorio_geral(lista_disciplinas *);
void editar_aluno(list *);
void excluir_aluno(list *);
int mencao_valida(char *);


int main(){
    list *List;
    lista_disciplinas *List_d;
    node *Node;
    node *aux;
    char *nome, *email;
    int matricula;
    int opcao = -1, opcao_visualizar, retorno;
    List = create_list();
    nome = (char *) malloc(35 * sizeof(char));
    if(nome == NULL) {
        printf("ERRO!\n");
        exit(2);
    }

    email = (char *) malloc(50 * sizeof(char));
    if(email == NULL) {
        printf("ERRO!\n");
        exit(2);
    }
    //List_d = create_list_disciplinas();
    while(opcao != 0){
        int achou = 0;
        system("clear");
        printf("Seja bem vindo ao segundo trabalho de EDA1!\n");
        printf("____________________________________________\n");
        printf("________Esse eh o MENU DE OPCOES:___________\n");
        printf("1) *CADASTRAR* ALUNOS:\n");
        printf("2) *LISTAR* ALUNOS:\n");
        printf("3) *VIZUALIZAR* ALUNOS:\n");
        printf("4) *EDITAR* ALUNOS:\n");
        printf("5) *EXCLUIR* ALUNOS:\n");
        printf("0) *SAIR*:\n");
        printf("Qual opçao deseja? -> ");

        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                cadastro(List);
                break;
            case 2:
                print_list(List);
                break;
            case 3 :
                printf("Como deseja visualizar o aluno?\n");
                printf("1) Por Nome\n");
                printf("2) Por email\n");
                printf("2) Por matricula\n");
                printf(" Opcao -> ");
                scanf("%d", &opcao_visualizar);
                //fiz esse switch para saber se o aluno ja existe, se tiver, ele vai ser mandado direto para a função, seu proprio node
                switch (opcao_visualizar){
                    case 1:
                        printf("Digite o nome d@ alun@ -> ");
                        getchar();
                        scanf("%[^\n]", nome);
                        Node = List->head;

                        altera_string(nome);
                        while(Node != NULL){
                            altera_string(Node->nome);
                            retorno = strcmp(Node->nome, nome);
                            if(retorno == 0 || strstr(Node->nome, nome) != NULL){
                                achou++;
                                aux = Node;
                            }       
                            Node = Node->next;
                        }
                        if(achou > 1){
                            printf("Existe mais de um(a) alun@ com esse nome!\n");
                            printf("Digite a matricula do aluno para continuar!\n");
                            sleep(1.5);
                            goto matricula;
                        }else{
                            printf("Alun@ %s encontrado!\n", aux->nome);
                            sleep(1);
                            menu_vizualizar(aux);
                            break;    
                        }
                        
                        break;
                    case 2:
                        printf("Digite o nome d@ Alun@ -> ");
                        getchar();
                        scanf("%[^\n]", email);
                        Node = List->head;

                        altera_string(email);
                        while(Node != NULL){
                            altera_string(Node->email);
                            retorno = strcmp(Node->email, email);
                            if(retorno == 0){
                                achou++;
                                printf("Alun@ %s encontrado!\n", Node->nome);
                                sleep(1);
                                menu_vizualizar(Node);
                                break;    
                            }       
                            Node = Node->next;
                        }
                        break;
                    case 3:
                        matricula:
                        printf("Digite a matricula d@ Alun@ -> ");
                        scanf("%d", &matricula);
                        Node = List->head;
                        while(Node != NULL){
                            //printf("matricula do node = %d\n", Node->matricula);
                                if(Node->matricula == matricula){
                                    achou++;
                                    printf("Alun@ %s encontrado!\n", Node->nome);
                                    sleep(1);
                                    menu_vizualizar(Node);
                                    break;    
                                }       
                            Node = Node->next;
                        }
                        break;
                    default:
                        break;
                    }
                if(achou == 0){
                    printf("Alun@ não cadastrado!\n");
                    sleep(1);
                }
                break;
            case 4:
                editar_aluno(List);                
                break;
            case 5:
                excluir_aluno(List);
                break;
            default:
                break;
        }
    }
}

void tracejado(){
    //função mais complicada do trabalho inteiro, tem que ler com calma
    printf("----------------------------------------------\n");
}


list * create_list(){
    list * List = (list *) malloc(sizeof(list));
    List->head = NULL;
    List->size = 0;

    return List; 
}

lista_disciplinas * create_list_disciplinas(){
    lista_disciplinas * List = (lista_disciplinas *) malloc(sizeof(lista_disciplinas));
    List->head = NULL;
    List->size = 0;

    return List;
}

void print_list(list * List){
    if(is_empty(List)){
        printf("Lista vazia!\n");
        sleep(1);
        return;
    }
    node *pointer = List->head;
    lista_disciplinas *aux;

    while(pointer != NULL) {
        tracejado();
        printf("Nome = %s\n", pointer->nome);
        printf("Email = %s\n", pointer->email);
        printf("Matricula = %d\n", pointer->matricula);
        aux = pointer->materias;
        if(aux->size == 0){
            printf("Aluno sem disciplina\n");
        }else{
            printf("Quantidade de materias: %d\n", aux->size);
        }
        pointer = pointer->next;
    }
    sleep(2);

}


void push(list *List, node *Node) {
    if(Node != NULL) {
        Node->next = List->head;
        List->head = Node;
        List->size++;
    }
}

void push_disciplina(lista_disciplinas *List, disciplina *Node){
    if(Node != NULL) {
        Node->next = List->head;
        List->head = Node;
        List->size++;
    }
}

int is_empty(list *List){
    if(List->size == 0)
        return 1;
    else   
        return 0;
}

int is_empty_disciplinas(lista_disciplinas * List){
    if(List->size == 0)
        return 1;
    else   
        return 0;
}

int mencao_valida(char * mencao){
    while(1){
        //Sei que ta feio, mas ta funcionando 
        if(strcmp(mencao, "tr") == 0 || strcmp(mencao, "TR") == 0 || strcmp(mencao, "sr") == 0
                    ||  strcmp(mencao, "SR") == 0 || strcmp(mencao, "II") == 0 || strcmp(mencao, "ii") == 0
                        ||  strcmp(mencao, "mi") == 0 || strcmp(mencao, "MI") == 0 || strcmp(mencao, "MM") == 0
                            ||  strcmp(mencao, "mm") == 0 || strcmp(mencao, "MS") == 0 || strcmp(mencao, "ms") == 0
                                ||  strcmp(mencao, "SS") == 0 || strcmp(mencao, "ss") == 0) 
            return 1; 
        printf("Mensoes validas: TR - SR - II - MI - MM - MS -SS\n");

        getchar();       
        printf("Digite a mencao do aluno -> ");
        scanf("%[^\n]", mencao);
    }
    return 0;
}

void menu_vizualizar(node * Node){
    int opcao = -1;
        while(opcao != 0){
            system("clear");
            printf("________Menu Vizualizar:_________\n");
            printf("1) *CADASTRAR* DISCIPLINA:\n");
            printf("2) *LISTAR* DISCIPLINAS DO ALUNO:\n");
            printf("3) *EDITAR* DISCIPLINA DO ALUNO:\n");
            printf("4) *EXCLUIR* DISCIPLINA DO ALUNO:\n");
            printf("5) *FILTRAR* DISCIPLINA POR MENCAO:\n");
            printf("6) *APRESENTAR* RELATORIO DO ALUNO:\n");
            printf("0) *VOLTAR*:\n");
            printf("Qual opçao deseja? -> ");

            scanf("%d", &opcao);

            switch (opcao){
                case 1:
                    cadastro_disciplina(Node);
                    break;
                case 2:
                    listar_disciplinas(Node->materias);                   
                    break;
                case 3 :
                    editar_disciplina(Node);
                    break;
                case 4:
                    excluir_disciplina(Node->materias);
                    break;
                case 5:
                    filtrar_disciplina(Node->materias);
                    break;
                case 6:
                    relatorio_geral(Node->materias);
                    break;
                case 0:
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
                }
        }
}

void cadastro(list * Lista){
    //list *List;
    lista_disciplinas *List_d;
    node *Node;
    node *aux;
    char *nome, *email;
    int matricula;

    nome = (char *) malloc(35 * sizeof(char));
    if(nome == NULL) {
        printf("ERRO!\n");
        exit(2);
    }

    email = (char *) malloc(50 * sizeof(char));
    if(email == NULL) {
        printf("ERRO!\n");
        exit(2);
    }

    printf("Digite o nome do aluno -> ");
    getchar();
    scanf("%[^\n]", nome);

    printf("\nDigite o email do aluno -> ");
    getchar();
    scanf("%[^\n]", email);

    printf("\nDigite a matricula do aluno -> ");
    scanf("%d", &matricula);
    


    Node = (node *) malloc(sizeof(node));
    Node->nome = nome;
    Node->email = email;
    Node->matricula = matricula;
    List_d = create_list_disciplinas();
    Node->materias = List_d;
    push(Lista, Node);
    tracejado();
    printf("Aluno, %s cadastrado com sucesso!\n", nome);
    sleep(1);
    tracejado();
}

void altera_string(char *string){
    for(unsigned int i = 0; i < strlen(string); i++){
        string[i] = toupper(string[i]);
    }
    string[strlen(string)] = '\0';
}

void cadastro_disciplina(node * Node){
    disciplina *node_disciplina;
    lista_disciplinas *List_d;
    
    int resp, matricula, achou = 0, indice_aux = 0, valido;
    char *nome, *mencao;
    nome = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    mencao = (char *) malloc(35 * sizeof (char));
    if(mencao == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
   
    printf("Digite o nome da disciplina que deseja cadastrar -> ");
    getchar();
    scanf("%[^\n]", nome);

    printf("Digite a mencao do aluno -> ");
    getchar();
    scanf("%[^\n]", mencao);
        
    valido = mencao_valida(mencao);
    if(valido == 1){
        node_disciplina = (disciplina *) malloc(sizeof(disciplina));
        node_disciplina->nome = nome;
        node_disciplina->mencao = mencao;
        push_disciplina(Node->materias, node_disciplina);

        printf("Disciplina cadastrada com sucesso!\n");
        sleep(1);
    }
}

void listar_disciplinas(lista_disciplinas * List){
    disciplina *pointer = List->head;
    int indice = 1;
    if(is_empty_disciplinas(List)){
        printf("Lista vazia!\n");
        sleep(1);
        return;
    }

    while(pointer != NULL) {
       tracejado();
       printf("materia = %s\n", pointer->nome);
       printf("mencao = %s\n", pointer->mencao);
       printf("indice = %d\n", indice);
       tracejado();
       sleep(0.2);
       pointer = pointer->next;
       indice++;
    }
    sleep(1);
}

void editar_disciplina(node * Node){
    char *nome, *nome_materia, *mencao;
    int achou = 0, valido;
    lista_disciplinas *List;
    disciplina *pointer;
    nome = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    nome_materia = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }

    mencao = (char *) malloc(10 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    printf("Digite o nome completo da disciplina que deseja editar -> ");
    getchar();
    scanf("%[^\n]", nome);

    List = Node->materias;
    pointer = List->head;
    altera_string(nome);
    while(pointer != NULL){
        altera_string(pointer->nome);
        if(strcmp(nome, pointer->nome) == 0){
            achou++;
            printf("Digite o novo nome da materia -> ");
            getchar();
            scanf("%[^\n]", nome_materia);
            printf("Digite a nova mencao da materia -> ");
            getchar();
            scanf("%[^\n]", mencao);
            valido = mencao_valida(mencao);
            break;
        }
        pointer = pointer->next;
    }if(achou > 0 && valido == 1){
        pointer->nome = nome_materia;
        pointer->mencao = mencao;

        printf("Disciplina, %s alterada com sucesso!\n", nome_materia);
        sleep(1);
    }else{
        printf("Materia nao encontrada!\n Por favor, verifique o nome da materia e tente novamente!\n");
        sleep(1.5);
        return;
    }
    free(nome);
}

void excluir_disciplina(lista_disciplinas * List){
    disciplina *Disciplina, *aux;
    char *nome;
    int index = 0, achou = 0, indice;
    Disciplina = List->head;
    aux = List->head;
    nome = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    printf("Digite o nome da disciplina que deseja excluir -> ");
    getchar();
    scanf("%[^\n]", nome);
    altera_string(nome);

    while(Disciplina != NULL){
        altera_string(Disciplina->nome);
        if(strcmp(Disciplina->nome, nome) == 0){
            achou++;
        }
        Disciplina = Disciplina->next;
    }
    if(achou == 1){
        Disciplina = List->head;
        while(Disciplina != NULL){
            if(strcmp(Disciplina->nome, nome) == 0){
                break;
            }
            Disciplina = Disciplina->next;
            index++;
        }
        if(index == 0){
            List->head = aux->next;
            free(aux->nome);
            free(aux->mencao);
            free(aux);
            List->size--;
            printf("Materia %s excluida com sucesso!\n", nome); 
            sleep(1);
        }else{
            aux = List->head;
            for(int i = 0; aux != NULL && i < index - 1; i++) 
                aux = aux->next; 
            disciplina *next = aux->next->next;
            free(aux->next->nome);
            free(aux->next->mencao);
            free(aux->next);
            aux->next = next;
            List->size--;
            printf("Materia %s excluida com sucesso!\n", nome); 
            sleep(1);
        }
    }else if(achou > 1){
        printf("Existe mais de uma materia com esse nome!\n");
        printf("Por favor, digite o indice da materia para continuar -> ");
        scanf("%d", &indice);
        if(indice == 1){
            List->head = aux->next;
            free(aux->nome);
            free(aux->mencao);
            free(aux);
            List->size--;
            printf("Materia %s excluida com sucesso!\n", nome); 
            sleep(1);
        }else{
            for (int i = 0; aux != NULL && i < indice - 2; i++) 
                aux = aux->next; 
            disciplina *next = aux->next->next;
            free(aux->next->nome);
            free(aux->next->mencao);
            free(aux->next);
            aux->next = next;
            List->size--;
            printf("Materia %s excluida com sucesso!\n", nome); 
            sleep(1);
        }
    }else{
        printf("Materia nao encontrada!\n Por favor, verifique o nome da materia e tente novamente!\n");
        sleep(1.5);
        return;
    }
    index = 0;
    free(nome);

    
}
void pop_disciplina(lista_disciplinas * List){
     if(is_empty(List)){
        printf("Lista Vazia!\n");
        return;
    }
    disciplina * aux = List->head;
    List->head = aux->next;
    free(aux->nome);
    free(aux->mencao);
    free(aux);
    List->size--;
}

void filtrar_disciplina(lista_disciplinas * List){
    char *mencao;
    disciplina *pointer = List->head;
    int achou = 0;
    mencao = (char *) malloc(35 * sizeof (char));
    if(mencao == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    printf("Digite a mencao que deseja filtrar -> ");
    getchar();
    scanf("%[^\n]", mencao);
    altera_string(mencao);
    while(pointer != NULL){
        altera_string(pointer->mencao);
        if(strcmp(pointer->mencao, mencao) == 0){
            achou++;
            altera_string(pointer->nome);
            tracejado();
            printf("Displina com mencao %s = %s\n", mencao, pointer->nome);
        }
        pointer = pointer->next;
    }
    if(achou > 0){
        sleep(1);
    }
    if(achou == 0){
        printf("Nenhuma materia com mencao %s!\n", mencao);
        sleep(1);
    }
}

void relatorio_geral(lista_disciplinas * List){
    int aprovadas = 0, reprovadas = 0, trancamentos = 0;
    disciplina *pointer = List->head;

    while(pointer != NULL){
        altera_string(pointer->mencao);
        if(strcmp(pointer->mencao, "MM") == 0 || strcmp(pointer->mencao, "MS") == 0 ||
            strcmp(pointer->mencao, "SS") == 0){
            aprovadas++;
        }else if(strcmp(pointer->mencao, "TR") == 0){
            trancamentos++;
        }else{
            reprovadas++;
        }
        pointer = pointer->next;
    }
    tracejado();
    printf("Alun@ com %d aprovacoes;\n", aprovadas);
    printf("Alun@ com %d reprovacoes;\n", reprovadas);
    printf("Alun@ com %d tracamentos;\n", trancamentos);
    sleep(2);
}

void editar_aluno(list * List){
    node *Node = List->head;
    node *aux;
    char *nome, *novo_nome, *novo_email;
    int achou = 0, matricula, nova_matricula;

    nome = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    novo_nome = (char *) malloc(35 * sizeof (char));
    if(novo_nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    novo_email = (char *) malloc(35 * sizeof (char));
    if(novo_email == NULL){
        printf("ERRO!!\n");
        exit(2);
    }

    printf("Digite o nome do aluno que deseja editar -> ");
    getchar();
    scanf("%[^\n]", nome);
    altera_string(nome);
    while(Node != NULL){
        altera_string(Node->nome);
        if(strcmp(Node->nome, nome) == 0 || strstr(Node->nome, nome) != NULL){
            achou++;
            aux = Node;
        }
        Node = Node->next;
    }
    if(achou > 1){
        printf("Existe mais de um(a) alun@ com esse nome!\n");
        printf("Por favor, digite a matricula do(a) alun@ para continuar -> ");
        scanf("%d", &matricula);
        Node = List->head;
        while(Node != NULL){
            if(Node->matricula == matricula){
                achou++;
                break;
            }
            Node = Node->next;
        }
        if(achou == 0){
            printf("Nenhum(a) alun@ com a matricula %d cadastrad@!\n", matricula);
            sleep(1);
        }else{
            printf("Alun@ %s encontrado!\n", Node->nome);
            sleep(0.5);
            printf("Digite o novo nome d@ alun@ -> ");
            getchar();
            scanf("%[^\n]", novo_nome);
            printf("Digite o novo email d@ alun@ -> ");
            getchar();
            scanf("%[^\n]", novo_email);
            printf("Digite a nova matricula d@ alun@ -> ");
            scanf("%d", &nova_matricula);
            altera_string(novo_nome);
            altera_string(novo_email);

            Node->nome = novo_nome;
            Node->email = novo_email;
            Node->matricula = nova_matricula;

            printf("Alun@, %s editad@ com sucesso!", Node->nome);
            sleep(1); 
        }
    }else if(achou == 1){
        printf("Alun@ %s encontrado!\n", aux->nome);
            sleep(0.5);
            printf("Digite o novo nome d@ alun@ -> ");
            getchar();
            scanf("%[^\n]", novo_nome);
            printf("Digite o novo email d@ alun@ -> ");
            getchar();
            scanf("%[^\n]", novo_email);
            printf("Digite a nova matricula d@ alun@ -> ");
            scanf("%d", &nova_matricula);

            aux->nome = novo_nome;
            aux->email = novo_email;
            aux->matricula = nova_matricula;

            printf("Alun@, %s editad@ com sucesso!\n", novo_nome);
            sleep(1); 
    }else{
        printf("Aluno nao cadastrado!\n");
        sleep(1);
    }
    free(nome);
}

void excluir_aluno(list * List){
    node *Node = List->head, *aux = List->head;
    lista_disciplinas *ListaDisciplinas;
    char *nome;
    int achou = 0, index = 0, matricula;
    nome = (char *) malloc(35 * sizeof (char));
    if(nome == NULL){
        printf("ERRO!!\n");
        exit(2);
    }
    printf("Digite o nome do aluno que deseja excluir -> ");
    getchar();
    scanf("%[^\n]", nome);
    altera_string(nome);
    while(Node != NULL){
        altera_string(Node->nome);
        if(strcmp(Node->nome, nome) == 0 || strstr(Node->nome, nome) != NULL){
            achou++;
        }
        Node = Node->next;
    }
    if(achou > 1){
        printf("Existe mais de um(a) alun@ com esse nome!\n");
        printf("Por favor, digite a matricula do(a) alun@ para continuar -> ");
        scanf("%d", &matricula);
        Node = List->head;
        achou = 0;
        while(Node != NULL){
            if(Node->matricula == matricula){
                achou++;
                break;
            }
            Node = Node->next;
        }
        if(achou == 0){
            printf("Nenhum(a) alun@ com a matricula %d cadastrad@!\n", matricula);
            sleep(1);
        }else{
            Node = List->head;
            while(Node != NULL){
                if(Node->matricula == matricula)
                aux = Node;
                    break;
                Node = Node->next;
                index++;
            }
            if(index == 0){
                ListaDisciplinas = aux->materias;
                List->head = aux->next;
                printf("Alun@ %s excluido!\n", aux->nome);
                free(aux->nome);
                free(aux->email);
                List->size--;
                while(ListaDisciplinas->size != 0){
                    pop_disciplina(ListaDisciplinas);
                    ListaDisciplinas->size--;
                }
                free(aux);
            }else{
                aux = List->head;
                for(int i = 0; aux != NULL && i < index - 1; i++)
                    aux = aux->next;
                node *next = aux->next->next;
                ListaDisciplinas = aux->next->materias;
                printf("ALun@ %s excluido!\n", aux->next->nome);
                free(aux->next->nome);
                free(aux->next->email);
                List->size--;
                while(ListaDisciplinas->size != 0){
                    pop_disciplina(ListaDisciplinas);
                    ListaDisciplinas->size--;
                }
                free(aux);
            }
            sleep(1); 
        }
    }else if(achou == 1){
        Node = List->head;
        while(Node != NULL){
            if(strcmp(Node->nome, nome) == 0 || strstr(Node->nome, nome) != NULL){
                break;
            }
            Node = Node->next;
            index++;
        }if(index == 0){
                aux = Node;          
                ListaDisciplinas = aux->materias;            
                List->head = aux->next;            
                printf("Alun@ %s excluido!\n", aux->nome);
                free(aux->nome);            
                free(aux->email);           
                while(ListaDisciplinas->size != 0){           
                    pop_disciplina(ListaDisciplinas);                            
                }
                free(aux);
                List->size--;
            }else{
                aux = List->head;
                for(int i = 0; aux != NULL && i < index - 1; i++)
                    aux = aux->next;
                node *next = aux->next->next;
                ListaDisciplinas = aux->next->materias;
                printf("ALun@ %s excluido!\n", aux->next->nome);
                free(aux->next->nome);
                free(aux->next->email);
                List->size--;
                while(ListaDisciplinas->size != 0){
                    pop_disciplina(ListaDisciplinas);
                }
                free(aux->next);
                aux->next = next;
            }
            sleep(1); 
    }else{
        printf("Alun@ nao cadastrado!\n");
        sleep(1);
    }
    index = 0;
    achou = 0;
}



