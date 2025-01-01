#include "ListaDuplamenteLigada.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarLista(LISTA* l) {
  l->inicio = NULL;
}

void exibirLista(LISTA* l) {
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

int tamanho(LISTA* l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

int tamanhoEmBytes(LISTA* l) {
  return (tamanho(l) * sizeof(ELEMENTO)) + sizeof(LISTA);
}

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL) {
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave < ch) {
    *ant = atual;
    atual = atual->prox;
  }
  if (atual != NULL && atual->reg.chave == ch) return atual;
  return NULL;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  PONT i = l->inicio;
  while (i != NULL && i->reg.chave != ch) {
    i = i->prox;
  }
  if (i == NULL) return false; // Elemento não encontrado

  if (i->ant == NULL) { // O elemento é o primeiro
    l->inicio = i->prox;
    if (l->inicio != NULL) l->inicio->ant = NULL; // Atualiza o anterior do novo primeiro elemento
  } else {
    i->ant->prox = i->prox;
    if (i->prox != NULL) i->prox->ant = i->ant; // Atualiza o anterior do próximo elemento
  }

  free(i);
  return true;
}


void reinicializarLista(LISTA* l) {
  PONT end = l->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  PONT i = l->inicio, ant = NULL;

  // Procura a posição correta para inserção
  while (i != NULL && i->reg.chave < reg.chave) {
    ant = i;
    i = i->prox;
  }

  // Cria o novo nó
  PONT novo = (PONT)malloc(sizeof(ELEMENTO));
  if (novo == NULL) return false; // Falha ao alocar memória
  novo->reg = reg;
  novo->prox = i;
  novo->ant = ant;

  // Ajusta os ponteiros
  if (ant == NULL) { // Inserção no início
    l->inicio = novo;
  } else {
    ant->prox = novo;
  }
  if (i != NULL) {
    i->ant = novo;
  }

  return true;
}


PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch) {
  if (l->inicio != NULL) *ch = l->inicio->reg.chave;
  return l->inicio;
}

PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch) {
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
}
