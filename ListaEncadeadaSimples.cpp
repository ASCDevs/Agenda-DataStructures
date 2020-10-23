#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int elemento;
    struct Node *proximo;
};

int tam;
void inicia(struct Node *List);
void menu();
void opcao(struct Node *List,char op);
void adiciona(struct Node *List);
void listaElementos(struct Node *List);
void excluir(struct Node *List);
int verificaCod(struct Node *List,int n);

int main(){
    Node *Lista = (Node *)malloc(sizeof(Node));
    inicia(Lista);

    char op;

    do{
        menu();
        scanf("%c",&op);
        opcao(Lista,op);

    }while(op!='0');

    free(Lista);
}

void inicia(struct Node *List){
    List->proximo = NULL;
    tam=0;
}


void menu(){
    system("cls");
    printf("1 - Cadastrar elemento\n");
    printf("2 - Excluir elemento\n");
    printf("3 - Consultar elemento\n");
    printf("4 - Listar elementos\n");
    printf("0 - Sair\n");
    printf("> ");
}

void opcao(struct Node *List,char op){
    switch (op){
        case '1':
            adiciona(List);
            break;
        case '2':
            excluir(List);
            break;
        case '3':
            //consultar(List);
            break;
        case '4':
            listaElementos(List);
            break;
    }
}
int verificaCod(struct Node *List,int n){
    Node *temp;
    temp = List->proximo;

    while(temp!=NULL){
        if(temp->elemento==n){
            return 1;
        }
        temp = temp->proximo;
    }
    return 0;
}

void adiciona(Node *List){
    Node *novo = (Node *)malloc(sizeof(Node));
    if(!novo){
        printf("Sem memoria disponivel!\n");
        system("pause");
        exit(1);
    }else{
        
        do{
            system("cls");
            printf("Novo elemento: ");
            scanf("%d", &novo->elemento);

            if(verificaCod(List,novo->elemento)){
                printf("\nJa existe este elemento!");
                system("pause");
            }
        }while (verificaCod(List,novo->elemento));
        
        
    }

    novo->proximo = NULL;

    if(List->proximo == NULL){

        List->proximo = novo;
        
    }else{

        Node *temp = List->proximo;
        while(temp->proximo!=NULL ){
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }

    tam++;
}

void excluir(Node *List){
    system("cls");
    //Pergunta o código do elemento
    if(List->proximo==NULL){
        printf("Sem elementos cadastrados!\n");
        system("pause");
        return;
    }
    int num_elemento;
    printf("Digite o codigo do elemento para excluir: ");
    scanf("%d",&num_elemento);

    Node *temp;
    int flag=0, i=0;
    temp = List->proximo;

    while(temp!=NULL and flag==0){
        if(temp->elemento==num_elemento){
            printf("Elemento Encontrado!\n");
            flag =1;
            system("pause");

            Node *atual=List->proximo, *anterior=List;

            for(int x=0;x<i;x++){
                anterior = atual;
                atual = atual->proximo;
            }
            anterior->proximo=atual->proximo;
            tam--; 
            return;
        }
        temp = temp->proximo;
        i++;
    }
    
    printf("Elemento Nao Cadastrado!\n");
    system("pause");
}

void listaElementos(Node *List){
    system("cls");
    if(List->proximo == NULL){
        printf("Sem elementos cadastrados!\n");
        system("pause");
        return;
    }
    Node *temp;
    temp = List->proximo;
    printf("Elementos: \n");

    while(temp!=NULL){
        printf("%d  ",temp->elemento);

        temp = temp->proximo;
    }
    printf("\nQuantidade de Elementos: %d",tam);
    printf("\n");
    system("pause");
}
