#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fila de pedidos
//{FIFO}
typedef struct Pedido
{
    int id;
    char prato[50];
    int mesa;
    struct Pedido *proximo;
} Pedido;

// Pilha de lavagem
//{LIFO}
typedef struct Prato
{
    int id_tipo;
    char cor[20];
    struct Prato *proximo;
} Prato;

// Lista de insumos
typedef struct Insumo
{
    char nome[50];
    int quantidade;
    struct Insumo *proximo;
} Insumo;

Prato *inicio_fila = NULL;
Prato *fim_fila = NULL;
int contador_pedidos = 1;

// Adiciona pedidos:
void adicionar_pedido();

// Entrega pedidos:
void entregar_pedido();

// Lista pedidos:
void listar_pedidos();


void adicionar_prato();
void lavar_prato();

// MENU gamer
int main()
{
    int opcao;
    printf("\n***********************\n");
    printf("*** RESTAURANTE FPO ***\n");
    printf("***********************\n");
    printf("(1) Adicionar Pedido (Fila)\n");
    printf("(2) Entregar Pedido (Fila)\n");
    printf("(3) Receber Prato Sujo (Pilha)\n");
    printf("(4) Lavar Prato (Pilha)\n");
    printf("(5) Adicionar Insumo à Lista (Lista)\n");
    printf("(6) Remover Insumo da Lista (Lista)\n");
    printf("(7) Imprimir Pedidos\n");
    printf("(8) Ver Pilha de Pratos\n");
    printf("(9) Imprimir Lista de Ingredientes\n");
    printf("(0) Sair\n");
    printf("Escolha: ");

    scanf("%d", &opcao);
    if (scanf("%d", &opcao) != 1)
    {
        printf("Entrada invalida. Saindo...\n");
    }
    switch (opcao)
    {
    case 1:
        adicionar_pedido();
        break;
    case 2:
        entregar_pedido();
        break;
    case 3:
        adicionar_prato();
        break;
    case 4:
        lavar_prato();
        break;
    case 5:
        adicionar_insumo();
        break;
    case 6:
        remover_insumo();
        break;
    case 7:
        imprimir_pedidos();
        break;
    case 8:
        imprimir_pilha_pratos();
        break;
    case 9:
        imprimir_insumos();
        break;
    case 0:
        printf("Saindo...\n");
        break;
    default:
        printf("Opcao invalida. Tente novamente.\n");
    }

    {
        Insumo *t = lista_insumos;
        lista_insumos = lista_insumos->proximo;
        free(t);
    }
    return 0;
}

//       FILAS
// Adiciona pedidos (FIFO)
void adicionar_pedido()
{
    Pedido *novo_pedido = (Pedido *)malloc(sizeof(Pedido));
    printf("Digite o ID do pedido: ");
    scanf("%d", &novo_pedido->id);

    printf("Digite nome do prato: ");
    scanf("%s", &novo_pedido->prato);

    printf("Mesa do pedido: ");
    scanf("%d", &novo_pedido->mesa);

    novo_pedido->proximo = NULL;
    if (inicio_fila == NULL)
    {
        inicio_fila = fim_fila = novo_pedido;
    }
    else
    {
        fim_fila->proximo = novo_pedido;
        fim_fila = novo_pedido;
    }

    printf("Pedido adicionado com sucesso!\n");
    printf("ID do pedidos: %d\n", novo_pedido->id);
    printf("Prato: %s\n", novo_pedido->prato);
    printf("Mesa: %d\n", novo_pedido->mesa);
    // NAO ESQUECER DE TIRAR->>>
    printf("\nObrigado pelo pedido gamer!");
}
// Entrega pedidos (FIFO)
void entregar_pedido()
{
    if (inicio_fila == NULL)
    {
        printf("Nenhum pedido para entregar.\n");
        return;
    }
    Pedido *pedido_entregue = inicio_fila;
    inicio_fila = inicio_fila->proximo;
    printf("Pedido entregue:\n");
    printf("ID do pedido: %d\n", pedido_entregue->id);
    printf("Prato: %s\n", pedido_entregue->prato);
    printf("Mesa: %d\n", pedido_entregue->mesa);
    free(pedido_entregue);
}
// Lista pedidos (FIFO)
void listar_pedidos()
{
    if (inicio_fila == NULL)
    {
        printf("Nenhum pedido na fila.\n");
        return;
    }

    Pedido *atual = inicio_fila;
    printf("Pedidos na fila:\n");
    while (atual != NULL)
    {
        printf("ID do pedido: %d, Prato: %s, Mesa: %d\n", atual->id, atual->prato, atual->mesa);
        atual = atual->proximo;
    }
}

//       PILHAS gamer
Prato *topo = NULL;
// adiciona prato:
void adicionar_prato()
{
    Prato *novo_prato = (Prato *)malloc(sizeof(Prato));
    printf("Digite a cor do prato:\n 1- Branco\n 2- Azul\n 3- Vermelho\n 4- Verde\n");
    scanf("%s", &novo_prato->cor);

    // verificação gamer pra saber se o cara digitou um numero valido
    if (novo_prato->cor == "Branco")
    {
        novo_prato->id_tipo = 1;
    }
    else if (novo_prato->cor == "Azul")
    {
        novo_prato->id_tipo = 2;
    }
    else if (novo_prato->cor == "Vermelho")
    {
        novo_prato->id_tipo = 3;
    }
    else if (novo_prato->cor == "Verde")
    {
        novo_prato->id_tipo = 4;
    }
    else
    {
        printf("Cor invalida!\n");
        free(novo_prato);
        return;
    }

    novo_prato->proximo = topo;
    topo = novo_prato;
    printf("Prato adicionado para lavagem: %s\n", novo_prato->cor);
}

void lavar_prato()
{
    if (topo == NULL)
    {
        printf("Nenhum prato para lavar.\n");
        return;
    }
    Prato *prato_lavado = topo;
    topo = topo->proximo;
    printf("Prato lavado: %s\n", prato_lavado->cor);
    free(prato_lavado);
}

// ver pilha de prato gamer
void listar_pratos()
{
    if (topo == NULL)
    {
        printf("Nenhum prato na pilha.\n");
        return;
    }

    Prato *atual = topo;
    printf("Pratos na pilha:\n");
    while (atual != NULL)
    {
        printf("Cor do prato: %s\n", atual->cor);
        atual = atual->proximo;
    }
}

// LISTA DE INSUMOS
Insumo *inicio_lista = NULL;
Insumo *fim_lista = NULL;

// adiciona insumo
void novo_insumo()
{
    Insumo *novo_insumo = (Insumo *)malloc(sizeof(Insumo));
    printf("Digite o nome do insumo: ");
    scanf("%s", &novo_insumo->nome);
    printf("Digite a quantidade do insumo: ");
    scanf("%d", &novo_insumo->quantidade);
    novo_insumo->proximo = inicio_lista;
    inicio_lista = novo_insumo;

    printf("Insumo adicionado: %s, Quantidade: %d\n", novo_insumo->nome, novo_insumo->quantidade);
}

// remover insumo
void remover_insumo()
{
    if (inicio_lista == NULL)
    {
        printf("Nenhum insumo para remover.\n");
        return;
    }
    int posicao, i = 1;

    printf("Digite a posicao do insumo a ser removido: ");
    scanf("%d", &posicao);

    Insumo *insumo_atual = inicio_lista;
    Insumo *insumo_anterior = NULL;
    while (insumo_atual != NULL && i < posicao)
    {
        insumo_anterior = insumo_atual;
        insumo_atual = insumo_atual->proximo;
        i++;
    }

    if (insumo_atual == NULL)
    {
        printf("Posicao invalida.\n");
        return;
    }
    if (insumo_anterior == NULL)
    {
        inicio_lista = insumo_atual->proximo;
    }
    else
    {
        insumo_anterior->proximo = insumo_atual->proximo;
    }

    printf("Insumo removido: %s\n", insumo_atual->nome);
    free(insumo_atual);
}

// listar insumos
Insumo *lista_insumos = NULL;
void listar_insumos()
{
    if (inicio_lista == NULL)
    {
        printf("Nenhum insumo na lista.\n");
        return;
    }

    Insumo *atual = inicio_lista;
    int i = 1;
    printf("Insumos na lista:\n");
    while (atual != NULL)
    {
        printf("%d. Nome: %s, Quantidade: %d\n", i, atual->nome, atual->quantidade);
        atual = atual->proximo;
        i++;
    }
}