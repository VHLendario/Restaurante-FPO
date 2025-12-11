#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fila de pedidos
typedef struct Pedido {
    int id;
    char prato[50];
    int mesa;
    struct Pedido *proximo;
} Pedido;

// Pilha de pratos
typedef struct Prato {
    int id_tipo;
    char cor[20];
    struct Prato *proximo;
} Prato;

// Lista de insumos
typedef struct Insumo {
    char nome[50];
    int quantidade;
    struct Insumo *proximo;
} Insumo;

// FILA
Pedido *inicio_fila = NULL;
Pedido *fim_fila = NULL;

// PILHA
Prato *topo = NULL;

// LISTA
Insumo *inicio_lista = NULL;

// FUNÇÕES DECLARADAS
void adicionar_pedido();
void entregar_pedido();
void listar_pedidos();

void adicionar_prato();
void lavar_prato();
void listar_pratos();

void novo_insumo();
void remover_insumo();
void listar_insumos();

// MENU
int main() 
{
    int opcao;

    do {
        printf("\n***********************\n");
        printf("*** RESTAURANTE FPO ***\n");
        printf("***********************\n");

        printf("(1) Adicionar Pedido (Fila)\n");
        printf("(2) Entregar Pedido (Fila)\n");
        printf("(3) Receber Prato Sujo (Pilha)\n");
        printf("(4) Lavar Prato (Pilha)\n");
        printf("(5) Adicionar Insumo (Lista)\n");
        printf("(6) Remover Insumo (Lista)\n");
        printf("(7) Imprimir Pedidos\n");
        printf("(8) Ver Pilha de Pratos\n");
        printf("(9) Imprimir Lista de Ingredientes\n");
        printf("(0) Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionar_pedido(); break;
            case 2: entregar_pedido(); break;
            case 3: adicionar_prato(); break;
            case 4: lavar_prato(); break;
            case 5: novo_insumo(); break;
            case 6: remover_insumo(); break;
            case 7: listar_pedidos(); break;
            case 8: listar_pratos(); break;
            case 9: listar_insumos(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

/* =================
        FILA
====================*/

void adicionar_pedido() {
    Pedido *novo = malloc(sizeof(Pedido));

    printf("Digite o ID do pedido: ");
    scanf("%d", &novo->id);

    printf("Digite o nome do prato: ");
    scanf("%s", &novo->prato);

    printf("Mesa do pedido: ");
    scanf("%d", &novo->mesa);

    novo->proximo = NULL;

    if (inicio_fila == NULL) {
        inicio_fila = fim_fila = novo;
    } else {
        fim_fila->proximo = novo;
        fim_fila = novo;
    }

    printf("Pedido adicionado!\n");
}

void entregar_pedido() {
    if (inicio_fila == NULL) {
        printf("Nenhum pedido.\n");
        return;
    }
    Pedido *aux = inicio_fila;
    inicio_fila = inicio_fila->proximo;

    printf("Pedido entregue: %d - %s (Mesa %d)\n",
           aux->id, aux->prato, aux->mesa);

    free(aux);
}

void listar_pedidos() {
    Pedido *p = inicio_fila;
    if (!p) {
        printf("Nenhum pedido na fila.\n");
        return;
    }

    while (p) {
        printf("ID: %d, Prato: %s, Mesa: %d\n",
               p->id, p->prato, p->mesa);
        p = p->proximo;
    }
}

/* =================
        PILHA
====================*/

void adicionar_prato() {
    Prato *novo = malloc(sizeof(Prato));

    printf("Digite a cor do prato: ");
    scanf("%s", novo->cor);

    if (strcmp(novo->cor, "Branco") == 0) novo->id_tipo = 1;
    else if (strcmp(novo->cor, "Azul") == 0) novo->id_tipo = 2;
    else if (strcmp(novo->cor, "Vermelho") == 0) novo->id_tipo = 3;
    else if (strcmp(novo->cor, "Verde") == 0) novo->id_tipo = 4;
    else {
        printf("Cor inválida.\n");
        free(novo);
        return;
    }

    novo->proximo = topo;
    topo = novo;

    printf("Prato adicionado à pilha.\n");
}

void lavar_prato() {
    if (topo == NULL) {
        printf("Nenhum prato.\n");
        return;
    }

    Prato *aux = topo;
    topo = topo->proximo;

    printf("Prato lavado: %s\n", aux->cor);
    free(aux);
}

void listar_pratos() {
    Prato *p = topo;
    if (!p) {
        printf("Pilha vazia.\n");
        return;
    }

    while (p) {
        printf("Cor: %s\n", p->cor);
        p = p->proximo;
    }
}

/* =================
        LISTA
====================*/

void novo_insumo() {
    Insumo *novo = malloc(sizeof(Insumo));

    printf("Nome do insumo: ");
    scanf("%s", novo->nome);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);

    novo->proximo = inicio_lista;
    inicio_lista = novo;

    printf("Insumo adicionado.\n");
}

void remover_insumo() {
    if (inicio_lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    int pos, i = 1;
    printf("Posição do insumo a remover: ");
    scanf("%d", &pos);

    Insumo *atual = inicio_lista;
    Insumo *anterior = NULL;

    while (atual != NULL && i < pos) {
        anterior = atual;
        atual = atual->proximo;
        i++;
    }

    if (atual == NULL) {
        printf("Posição inválida.\n");
        return;
    }

    if (anterior == NULL) {
        inicio_lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    printf("Removido: %s\n", atual->nome);
    free(atual);
}

void listar_insumos() {
    if (inicio_lista == NULL) {
        printf("Nenhum insumo.\n");
        return;
    }

    Insumo *atual = inicio_lista;
    int i = 1;

    while (atual) {
        printf("%d. Nome: %s, Quantidade: %d\n",
               i, atual->nome, atual->quantidade);
        atual = atual->proximo;
        i++;
    }
}

