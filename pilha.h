#ifndef PILHA_H
#define PILHA_H


template<typename TIPO>
struct TElementoP{
  TIPO dado;
  TElementoP<TIPO> * proximo;
};

template<typename TIPO>
struct TPilha{
  TElementoP<TIPO> * topo;
};

template <typename TIPO> 
bool inicializa_pilha(TPilha<TIPO> &pilha) {
  pilha.topo = NULL;
  return true;
}

template <typename TIPO>
void insere_pilha(TPilha<TIPO> &pilha, TIPO d){
  TElementoP<TIPO> * novo = new TElementoP<TIPO>;
  novo->dado = d;
  novo->proximo = pilha.topo;
  pilha.topo = novo;
}

template <typename TIPO>
TIPO remove_pilha(TPilha<TIPO> &pilha){
  if(pilha.topo != NULL){
    TElementoP<TIPO> * removido = pilha.topo;
    TIPO dado = pilha.topo->dado;
    pilha.topo = pilha.topo->proximo;
    delete removido;
    return dado;
  }
    return '\0';
}

template <typename TIPO>
bool vazia_pilha(TPilha<TIPO> pilha){
  if(pilha.topo == NULL){
    return true;
  }
  return false;
}

#endif