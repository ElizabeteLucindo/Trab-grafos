#ifndef FILA_H
#define FILA_H

#include <iostream>
using namespace std;

template<typename TIPO>
struct TElementoF{
  TIPO dado;
  TElementoF<TIPO> * proximo;
};

template<typename TIPO>
struct TFila{
  TElementoF<TIPO> * inicio;
};

template <typename TIPO> 
bool inicializa_fila(TFila<TIPO> &fila) {
  fila.inicio = NULL;
  return true;
}

template <typename TIPO>
void insere_fila(TFila<TIPO> &fila, TIPO d){
  TElementoF<TIPO> * novo = new TElementoF<TIPO>;
  novo->dado = d;
  novo->proximo = NULL;
  
  if(fila.inicio == NULL){
    fila.inicio = novo;
  }else{
    TElementoF<TIPO> * nav = fila.inicio;
    while(nav->proximo != NULL){
      nav = nav->proximo;
    }
    nav->proximo = novo;
  }
}

template <typename TIPO>
TIPO remove_fila(TFila<TIPO> &fila){
  if(fila.inicio != NULL){
    TElementoF<TIPO> * removido = fila.inicio;
    TIPO dado = removido->dado;
    fila.inicio = fila.inicio->proximo;

    delete removido;
    return dado;
  }

  return TIPO(); 
}

#endif
