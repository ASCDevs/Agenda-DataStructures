#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto{
    int codigo;
    char descricao[200];
    float preco_compra;
    float preco_venda;
    int qtd_estoque;
    int qtdVendido;
    struct Produto *proximo;
};

int tam;
void inicia(Produto *List);
void menu();
void opcao(Produto *List,char op);
void adiciona( Produto *List);
void excluir(Produto *List);
void consultar(Produto *List);
void alterar(Produto *List);
void vender(Produto *List);
void listaProdutos( Produto *List);
void listaCodigos(Produto *List);
void dadosProdutos(Produto &List);
int verificaCod( Produto *List,int n);
void ordenaProdutos(Produto *List);
void swapNodes(Produto *a,  Produto *b);
void geraArquivo(Produto *List);

int main(){
    Produto *Lista = (Produto *)malloc(sizeof(Produto));
    inicia(Lista);

    char op;

    do{
        menu();
        scanf("%c",&op);
        opcao(Lista,op);

    }while(op!='0');

    geraArquivo(Lista);
    printf("\nArquivo gerado.");

    char resp;
    printf("\nAbrir arquivo (S(sim) ou N(nao))\n> ");
    setbuf(stdin,NULL);
    scanf("%c",&resp);
    if(resp=='S' or resp=='s'){
        system("start lista-produtos.txt");
    }
    
    free(Lista);
}

void inicia(Produto *List){
    List->proximo = NULL;
    tam=0;
}


void menu(){
    system("cls");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Excluir Produto\n");
    printf("3 - Consultar Produto\n");
    printf("4 - Alterar Produto (Estoque, precos, vendas)\n");
    printf("5 - Listar Produtos\n");
    printf("6 - Vender Produto\n");
    printf("0 - Sair\n");
    printf("> ");
}

void opcao(Produto *List,char op){
    switch (op){
        case '1':
            adiciona(List);
            break;
        case '2':
            excluir(List);
            break;
        case '3':
            consultar(List);
            break;
        case '4':
            alterar(List);
            break;
        case '5':
            listaProdutos(List);
            break;
        case '6':
            vender(List);
            break;
    }
}
int verificaCod(Produto *List,int n){
    Produto *temp;
    temp = List->proximo;

    while(temp!=NULL){
        if(temp->codigo==n){
            return 1;
        }
        temp = temp->proximo;
    }
    return 0;
}

//Troca os dados dos nos, quando for ordenado
void swapNodes(Produto *a, Produto *b){
    int auxCod = a->codigo;
    a->codigo = b->codigo;
    b->codigo = auxCod;

    char desc[200];
    strcpy(desc,a->descricao);
    strcpy(a->descricao,b->descricao);
    strcpy(b->descricao,desc);

    float pCompra = a->preco_compra;
    a->preco_compra = b->preco_compra;
    b->preco_compra = pCompra;

    float pVenda = a->preco_venda;
    a->preco_venda = b->preco_venda;
    b->preco_venda = pVenda;

    int qtd = a->qtd_estoque;
    a->qtd_estoque = b->qtd_estoque;
    b->qtd_estoque = qtd;

    int vendidos = a->qtdVendido;
    a->qtdVendido = b->qtdVendido;
    b->qtdVendido = vendidos;
}

void ordenaProdutos(Produto *List){

    int swapped, i; 
	struct Produto *ptr1;

	if (List->proximo == NULL) 
		return; 

	do
	{ 
		swapped = 0; 
		ptr1 = List->proximo; 

		while (ptr1->proximo != NULL) 
		{ 
			if (ptr1->codigo > ptr1->proximo->codigo) 
			{ 
				swapNodes(ptr1, ptr1->proximo); 
				swapped = 1; 
			} 
			ptr1 = ptr1->proximo; 
		} 
		 
	}while (swapped); 

}

//Funcao de cadastro de produto
void adiciona(Produto *List){
    Produto *novo = (Produto *)malloc(sizeof(Produto));
    if(!novo){
        printf("Sem memoria disponivel!\n");
        system("pause");
        exit(1);
    }else{
        
        do{
            system("cls");
            printf("Codigo do produto: ");
            scanf("%d", &novo->codigo);

            if(verificaCod(List,novo->codigo)){
                printf("\nJa existe este Produto!\n");
                system("pause");
            }
        }while (verificaCod(List,novo->codigo));
        
        setbuf(stdin,NULL);
        printf("\nDescricao produto: ");
        scanf("%[^\n]s",novo->descricao);

        printf("\nPreco de compra: R$");
        scanf("%f",&novo->preco_compra);

        printf("\nPreco de venda: R$");
        scanf("%f",&novo->preco_venda);

        printf("\nQuantidade de estoque: ");
        scanf("%d",&novo->qtd_estoque);
        setbuf(stdin,NULL);

        novo->qtdVendido = 0;
        
    }

    novo->proximo = NULL;

    if(List->proximo == NULL){

        List->proximo = novo;
        
    }else{

        Produto *temp = List->proximo;
        while(temp->proximo!=NULL ){
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }

    tam++;
    ordenaProdutos(List);
}

//Funcao de deletar produto
void excluir(Produto *List){
    system("cls");
    
    if(List->proximo==NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }
    int cod_prod;
    listaCodigos(List);
    printf("---------------------\n");
    printf("Digite o codigo do produto para excluir: ");
    scanf("%d",&cod_prod);

    Produto *temp;
    int flag=0, i=0;
    temp = List->proximo;

    while(temp!=NULL and flag==0){
        if(temp->codigo==cod_prod){
            printf("Produto Encontrado!\n");
            flag =1;
            system("pause");

            Produto *atual=List->proximo, *anterior=List;

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
    
    printf("\nProduto Nao Cadastrado!\n");
    system("pause");
}

//Funcao de consulta de produto
void consultar(Produto *List){
    system("cls");
    listaCodigos(List);
    printf("---------------------\n");
    if(List->proximo==NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }

    int cod_prod;
    
    printf("Digite o codigo do produto para consultar: ");
    scanf("%d",&cod_prod);
    if(!verificaCod(List,cod_prod)){
        printf("Produto nao cadastrado!\n");
        system("pause");
        return;
    }

    Produto *temp;
    temp = List->proximo;

    while (temp!=NULL){
        if(temp->codigo==cod_prod){
            
            char opt;
            do{
                system("cls");
                printf("Consultar Produto Codigo: %d\n",temp->codigo);
                printf("1 - Descricao Produto\n");
                printf("2 - Preco Compra\n");
                printf("3 - Preco Venda\n");
                printf("4 - Quantidade em estoque\n");
                printf("5 - Quantidade vendida\n");
                printf("6 - Valor total estocado\n");
                printf("7 - Valor total vendido\n");
                printf("8 - Geral\n");
                printf("0 - voltar\n");
                printf("> ");
                scanf("%c",&opt);

                switch (opt){
                    case '1':
                        system("cls");
                        printf("Descricao Produto: %s\n",temp->descricao);
                        system("pause");
                        break;
                    case '2':
                        system("cls");
                        printf("Preco de compra: %.2f\n",temp->preco_compra);
                        system("pause");
                        break;
                    case '3':
                        system("cls");
                        printf("Preco de venda: %.2f\n",temp->preco_venda);
                        system("pause");
                        break;
                    case '4':
                        system("cls");
                        printf("Quantidade em estoque: %d\n",temp->qtd_estoque);
                        system("pause");
                        break;
                    case '5':
                        system("cls");
                        printf("Quantidade vendida: %d\n",temp->qtdVendido);
                        system("pause");
                        break;
                    case '6':
                        system("cls");
                        printf("\nQuantidade em estoque: %d\nPreco de compra: R$%.2f\n----\nValor total estocado: R$%.2f\n",temp->qtd_estoque,temp->preco_compra,(temp->qtd_estoque*temp->preco_compra));
                        system("pause");
                        break;
                    case '7':
                        system("cls");
                        printf("\nQuantidade vendida: %d\nPreco de venda: R$%.2f\n----\nValor total vendido: R$%.2f\n",temp->qtdVendido,temp->preco_venda,(temp->qtdVendido*temp->preco_venda));
                        system("pause");
                        break;
                    case '8':
                        system("cls");
                        dadosProdutos(*temp);
                        printf("\n");
                        system("pause");
                        break;
                }

            }while(opt!='0');

            return;
        }
        temp = temp->proximo;
    }
}

//Funcao de alterar produto
void alterar(Produto *List){
    system("cls");
    
    if(List->proximo==NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }

    int cod_prod;
    listaCodigos(List);
    printf("---------------------\n");
    printf("Digite o codigo do produto para alterar: ");
    scanf("%d",&cod_prod);
    if(!verificaCod(List,cod_prod)){
        printf("Produto nao cadastrado!\n");
        system("pause");
        return;
    }

    Produto *temp;
    temp = List->proximo;

    while (temp!=NULL){
        if(temp->codigo==cod_prod){
            
            char opt;
            do{
                system("cls");
                printf("Alterar Produto Codigo: %d\n",temp->codigo);
                printf("1 - Descricao Produto\n");
                printf("2 - Preco Compra\n");
                printf("3 - Preco Venda\n");
                printf("4 - Quantidade em estoque\n");
                printf("5 - Quantidade vendida\n");
                printf("0 - voltar\n");
                printf("> ");
                scanf("%c",&opt);

                switch (opt){
                    case '1':
                        system("cls");
                        setbuf(stdin,NULL);
                        printf("\nDescricao produto: ");
                        scanf("%[^\n]s",temp->descricao);
                        system("pause");
                        break;
                    case '2':
                        system("cls");
                        printf("\nPreco de compra: R$");
                        scanf("%f",&temp->preco_compra);
                        system("pause");
                        break;
                    case '3':
                        system("cls");
                        printf("\nPreco de venda: R$");
                        scanf("%f",&temp->preco_venda);
                        system("pause");
                        break;
                    case '4':
                        do{
                            system("cls");
                            printf("\nQuantidade de estoque: ");
                            scanf("%d",&temp->qtd_estoque);
                            if(temp->qtd_estoque<0){
                                printf("\nEstoque nao pode ser negativo!\n");
                                system("pause");
                            }
                        }while(temp->qtd_estoque<0);
                        
                        system("pause");
                        break;
                    case '5':
                        do{
                            system("cls");
                            printf("\nQuantidade de vendas: ");
                            scanf("%d",&temp->qtdVendido);
                            if(temp->qtdVendido<0){
                                printf("\nVendas nao pode ser negativo!\n");
                                system("pause");
                            }
                        }while(temp->qtdVendido<0);
                        system("pause");
                        break;
                }

            }while(opt!='0');

            return;
        }
        temp = temp->proximo;
    }
}

//Simples funcao de vender produtos em estoque
void vender(Produto *List){
    system("cls");
    
    if(List->proximo==NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }
    listaCodigos(List);
    printf("---------------------\n");
    int cod_prod;
    
    printf("Digite o codigo do produto para vender: ");
    scanf("%d",&cod_prod);
    if(!verificaCod(List,cod_prod)){
        printf("Produto nao cadastrado!\n");
        system("pause");
        return;
    }

    Produto *temp;
    temp = List->proximo;

    while (temp!=NULL){
        if(temp->codigo==cod_prod){
        
            if(temp->qtd_estoque==0){
                printf("\nProduto %s (%d) sem estoque!\n",temp->descricao,temp->codigo);
                system("pause");
                return;
            }    
            int qtdItens, flag=0;
            do{
                flag=0;
                system("cls");
                printf("Codigo: %d\n",temp->codigo);
                printf("Produto: %s\n",temp->descricao);
                printf("Preco do produto: R$%.2f\n",temp->preco_venda);
                printf("------\nDigite a quatidade a ser vendida: ");
                scanf("%d",&qtdItens);
                if(qtdItens>temp->qtd_estoque){
                    flag=1;
                    printf("Quantidade maior que estoque!\n");
                    system("pause");
                }
            }while(qtdItens<0||flag);
            
            printf("\n---\nTOTAL DA VENDA: R$%.2f\n",qtdItens*temp->preco_venda);
            system("pause");
            temp->qtdVendido+=qtdItens;
            temp->qtd_estoque-=qtdItens;
            return;
        }
        temp = temp->proximo;
    }
    
}

void listaProdutos(Produto *List){
    system("cls");
    if(List->proximo == NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }
    Produto *temp;
    temp = List->proximo;
    printf("Lista de Produtos:");

    while(temp!=NULL){
        printf("\n------------------------------\n");
        dadosProdutos(*temp);
        temp = temp->proximo;
    }
    printf("\n------------------------------\nQuantidade de Produtos: %d\n",tam);
    system("pause");
}

void listaCodigos(Produto *List){
    system("cls");
    if(List->proximo == NULL){
        printf("Sem produtos cadastrados!\n");
        system("pause");
        return;
    }
    Produto *temp;
    temp = List->proximo;
    printf("Produtos: \n");

    while(temp!=NULL){
        printf("  Codigo: %d\n  Produto: %s\n\n",temp->codigo,temp->descricao);
        temp = temp->proximo;
    }
    printf("Total Produtos cadastrados: %d\n",tam);
}

void dadosProdutos(Produto &List){

    printf("  Codigo: %d",List.codigo);
    printf("\n  Descricao: %s",List.descricao);
    printf("\n  Preco de compra: R$%.2f",List.preco_compra);
    printf("\n  Preco de venda: R$%.2f",List.preco_venda);
    printf("\n  Quantidade em estoque: %d",List.qtd_estoque);
    printf("\n  Quantidade vendida: %d",List.qtdVendido);
    printf("\n  Total em estoque: R$%.2f | Total vendido: R$%.2f",(List.qtd_estoque*List.preco_compra),(List.qtdVendido*List.preco_venda));

}

void geraArquivo(Produto *List){

    FILE *arquivo;
    arquivo = fopen("lista-produtos.txt","w");

    if(List->proximo == NULL){
        fprintf(arquivo,"Sem produtos cadastrados!\n");
        fclose(arquivo);
        return;
    }

    Produto *temp;
    temp = List->proximo;
    fprintf(arquivo,"Lista de Produtos:");

    while(temp!=NULL){
        fprintf(arquivo,"\n------------------------------\n");
        fprintf(arquivo,"  Codigo: %d",temp->codigo);
        fprintf(arquivo,"\n  Descricao: %s",temp->descricao);
        fprintf(arquivo,"\n  Preco de compra: R$%.2f",temp->preco_compra);
        fprintf(arquivo,"\n  Preco de venda: R$%.2f",temp->preco_venda);
        fprintf(arquivo,"\n  Quantidade em estoque: %d",temp->qtd_estoque);
        fprintf(arquivo,"\n  Quantidade vendida: %d",temp->qtdVendido);
        fprintf(arquivo,"\n  Total em estoque: R$%.2f | Total vendido: R$%.2f",(temp->qtd_estoque*temp->preco_compra),(temp->qtdVendido*temp->preco_venda));
        temp = temp->proximo;
    }
    fprintf(arquivo,"\n------------------------------\nQuantidade de Produtos: %d\n",tam);


    fclose(arquivo);
}
