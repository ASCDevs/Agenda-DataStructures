#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato{
    char nome[80];
    int telefone;
    char email[80];
    struct contato *proximo;
}Agenda;

int tamanho;
void iniciaAgenda(Agenda *contatos);
void menu();
void opcao(Agenda *contatos, char op);
void addContato(Agenda *contatos);
void deletaContato(Agenda *contatos);
void listaContatos(Agenda *contatos);
void consultar(Agenda *contatos);

int main(){
    Agenda *contatos = (Agenda *)malloc(sizeof(Agenda));
    iniciaAgenda(contatos);

    char op;
    do{
        system("cls");
        menu();
        scanf("%c",&op);
        opcao(contatos,op);

    }while(op!='5');

}

void iniciaAgenda(Agenda *contatos){
    contatos->proximo = NULL;
    tamanho = 0;
}

void menu(){
    printf("1. Incluir um Contato\n");
    printf("2. Remover um Contato\n");
    printf("3. Listar todos os Contatos\n");
    printf("4. Pesquisar um Contato pelo telefone\n");
    printf("5. Sair do Programa\n");
    printf("> ");
}

void opcao(Agenda *contatos, char op){
    switch (op){

        case '1':
            system("cls");
            addContato(contatos);
            system("pause");
            break;
        case '2':
            system("cls");
            deletaContato(contatos);
            system("pause");
            break;
        case '3':
            system("cls");
            listaContatos(contatos);
            system("pause");
            break;
        case '4':
            system("cls");
            consultar(contatos);
            system("pause");
            break;
    }
}

void addContato(Agenda *contatos){
    Agenda *novo = (Agenda *)malloc(sizeof(Agenda));
    if(novo==NULL){
        printf("Memoria indisponivel\n");
        return;
    }else{

        setbuf(stdin,NULL); //Limpa o buffer
        printf("Digite o nome do contato: ");
        scanf("%[^\n]s",novo->nome);
        
        setbuf(stdin,NULL); //Limpa o buffer
        printf("\nDigite o telefone: ");
        scanf("%d",&novo->telefone);

        setbuf(stdin,NULL); //Limpa o buffer
        printf("\nDigite o email do contato: ");
        scanf("%[^\n]s",novo->email);
    }

    novo->proximo = NULL;

    if(contatos->proximo == NULL){
        contatos->proximo = novo;
    }else{
        Agenda *temp = contatos->proximo;
        while (temp->proximo!=NULL){
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
    tamanho++;
}

void deletaContato(Agenda *contatos){
    if(contatos->proximo==NULL){
        printf("Lista sem contatos cadastrados!\n");
        return;
    }
    listaContatos(contatos);
    
    int posicao;
    
    printf("Digite a posicao (1 ate %d) para excluir o contato: ",tamanho);
    scanf("%d",&posicao);
    if(posicao>0 && posicao <=tamanho){
        Agenda *temp = contatos->proximo;
        
        if(posicao==1){
            contatos->proximo = temp->proximo;
            tamanho--;
            printf("\nContato excluido!\n");
            return;
        }

        Agenda *anterior = contatos;
        for(int i=1;i<posicao;i++){
            anterior = temp;
            temp = temp->proximo;
        }
        anterior->proximo = temp->proximo;
        tamanho--;
        printf("\nContato excluido!\n");
    }else{
        printf("Posicao invalida!\n");
    }

}

void listaContatos(Agenda *contatos){
    if(contatos->proximo==NULL){
        printf("Lista sem contatos cadastrados!\n");
        return;
    }
    Agenda *temp;
    temp = contatos->proximo;
    printf("LISTA DE CONTATOS: ");

    int posicao=0;
    while(temp!=NULL){
        printf("\n--------------------------------\n");
        printf("%3d.  Nome: %s\n",posicao+1,temp->nome);
        printf("      Telefone: %d\n",temp->telefone);
        printf("      Email: %s\n",temp->email);
        temp = temp->proximo;
        posicao++;
    }
    printf("\n--------------------------------\nTotal de contatos: %d\n",tamanho);
}

void consultar(Agenda *contatos){
    if(contatos->proximo==NULL){
        printf("Lista sem contatos cadastrados!\n");
        return;
    }
    int telefone, flag=0, posicao=1;
    printf("Digite o numero de telefone do contato: ");
    scanf("%d",&telefone);

    Agenda *temp;
    temp = contatos->proximo;

    printf("\n--------------------------------\n");
    printf("RESULTADOS DE BUSCA POR TELEFONE");

    while(temp!=NULL){
        if(temp->telefone==telefone){
            printf("\n--------------------------------\n");
            printf("%3d.  Nome: %s\n",posicao,temp->nome);
            printf("      Telefone: %d\n",temp->telefone);
            printf("      Email: %s\n",temp->email);
            flag=1;
        }
        temp = temp->proximo;
        posicao++;
    }
    if(flag==0){
        printf("\n--------------------------------\n");
        printf("Sem contatos com este telefone (%d)\n",telefone);
    }


}