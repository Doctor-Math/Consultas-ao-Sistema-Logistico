#include "AVL.hpp"
#include <iostream>

// Construtor e destrutor
template <typename T>
arvoreAVL<T>::arvoreAVL() : raiz(nullptr) {}

template <typename T>
arvoreAVL<T>::~arvoreAVL() {
    limpa(raiz);
}

// Altura do nó
template <typename T>
int arvoreAVL<T>::altura(No* no) const {
    return no ? no->altura : 0;
}

// Fator de balanceamento
template <typename T>
int arvoreAVL<T>::fatorBalanceamento(No* no) {
    return no ? altura(no->filhoDireita) - altura(no->filhoEsquerda) : 0;
}

// Atualiza altura de um nó
template <typename T>
void arvoreAVL<T>::atualizarAltura(No* no) {
    if (no)
        no->altura = 1 + std::max(altura(no->filhoEsquerda), altura(no->filhoDireita));
}

// Rotações
template <typename T>
typename arvoreAVL<T>::No* arvoreAVL<T>::rotacaoDireita(No* y) {
    No* x = y->filhoEsquerda;
    No* T2 = x->filhoDireita;

    x->filhoDireita = y;
    y->filhoEsquerda = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

template <typename T>
typename arvoreAVL<T>::No* arvoreAVL<T>::rotacaoEsquerda(No* x) {
    No* y = x->filhoDireita;
    No* T2 = y->filhoEsquerda;

    y->filhoEsquerda = x;
    x->filhoDireita = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

// Inserção AVL
template <typename T>
typename arvoreAVL<T>::No* arvoreAVL<T>::insere(No* no, const T& chave) {
    if (!no) return new No(chave);

    if (chave < no->chave)
        no->filhoEsquerda = insere(no->filhoEsquerda, chave);
    else if (chave > no->chave)
        no->filhoDireita = insere(no->filhoDireita, chave);
    else
        return no; // Evita duplicatas

    atualizarAltura(no);
    int balanceamento = fatorBalanceamento(no);

    // Casos de rotação
    if (balanceamento > 1 && chave > no->filhoDireita->chave)
        return rotacaoEsquerda(no);
    if (balanceamento < -1 && chave < no->filhoEsquerda->chave)
        return rotacaoDireita(no);
    if (balanceamento > 1 && chave < no->filhoDireita->chave) {
        no->filhoDireita = rotacaoDireita(no->filhoDireita);
        return rotacaoEsquerda(no);
    }
    if (balanceamento < -1 && chave > no->filhoEsquerda->chave) {
        no->filhoEsquerda = rotacaoEsquerda(no->filhoEsquerda);
        return rotacaoDireita(no);
    }

    return no;
}

template <typename T>
void arvoreAVL<T>::insere(const T& chave) {
    raiz = insere(raiz, chave);
}

// Busca
template <typename T>
T* arvoreAVL<T>::busca(const T& chave) const {
    return busca(raiz, chave);
}

template <typename T>
T* arvoreAVL<T>::busca(No* no, const T& chave) const {
    if (!no) return nullptr;
    if (chave < no->chave) return busca(no->filhoEsquerda, chave);
    if (chave > no->chave) return busca(no->filhoDireita, chave);
    return &(no->chave);
}

// Liberação de memória
template <typename T>
void arvoreAVL<T>::limpa(No* no) {
    if (!no) return;
    limpa(no->filhoEsquerda);
    limpa(no->filhoDireita);
    delete no;
}

// Impressão por pacote até tempo
template <typename T>
void arvoreAVL<T>::imprimeInOrderPacoteAte(const T& chaveInicial, int dataLimite) const {
    imprimeInOrderPacoteAte(raiz, chaveInicial, dataLimite);
}

template <typename T>
void arvoreAVL<T>::imprimeInOrderPacoteAte(No* no, const T& chaveInicial, int dataLimite) const {
    if (!no) return;

    imprimeInOrderPacoteAte(no->filhoEsquerda, chaveInicial, dataLimite);

    if (no->chave.idPacote == chaveInicial.idPacote && no->chave.tempoEvento <= dataLimite && no->chave.evento)
        no->chave.evento->imprimeEvento();

    imprimeInOrderPacoteAte(no->filhoDireita, chaveInicial, dataLimite);
}

// Impressão a partir de chave e id
template <typename T>
void arvoreAVL<T>::emOrdemApartirDe(const T& chaveRef, int idPacoteAlvo) const {
    emOrdemApartirDe(raiz, chaveRef, idPacoteAlvo);
}

template <typename T>
void arvoreAVL<T>::emOrdemApartirDe(No* no, const T& chaveRef, int idPacoteAlvo) const {
    if (!no) return;

    if (!(no->chave < chaveRef))
        emOrdemApartirDe(no->filhoEsquerda, chaveRef, idPacoteAlvo);

    if (!(no->chave < chaveRef) && no->chave.idPacote == idPacoteAlvo)
        std::cout << no->chave << "\n";

    emOrdemApartirDe(no->filhoDireita, chaveRef, idPacoteAlvo);
}

// Contagem eventos pacote até tempo
template <typename T>
void arvoreAVL<T>::contaEventosPacoteAte(const T& chaveInicial, int dataLimite, int& contador) const {
    contaEventosPacoteAte(raiz, chaveInicial, dataLimite, contador);
}

template <typename T>
void arvoreAVL<T>::contaEventosPacoteAte(No* no, const T& chaveInicial, int dataLimite, int& contador) const {
    if (!no) return;

    contaEventosPacoteAte(no->filhoEsquerda, chaveInicial, dataLimite, contador);

    if (no->chave.idPacote == chaveInicial.idPacote && no->chave.tempoEvento <= dataLimite)
        contador++;

    contaEventosPacoteAte(no->filhoDireita, chaveInicial, dataLimite, contador);
}

// Contagem eventos RG de cliente
template <typename T>
void arvoreAVL<T>::contaEventosDeChegadaClienteAte(const T& chaveInicial, int dataLimite, const noCliente& cliente, int& contador) const {
    contaEventosDeChegadaClienteAte(raiz, chaveInicial, dataLimite, cliente, contador);
}

template <typename T>
void arvoreAVL<T>::contaEventosDeChegadaClienteAte(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente, int& contador) const {
    if (!no) return;

    if (no->chave >= chaveInicial)
        contaEventosDeChegadaClienteAte(no->filhoEsquerda, chaveInicial, dataLimite, cliente, contador);

    if (no->chave.tempoEvento <= dataLimite && no->chave.evento && no->chave.evento->getTipoEvento() == "RG") {
        CelulaIndice* atual = cliente.getListaIndices();
        while (atual) {
            if (atual->indicePacote == no->chave.idPacote) {
                contador++;
                break;
            }
            atual = atual->prox;
        }
    }

    if (no->chave >= chaveInicial)
        contaEventosDeChegadaClienteAte(no->filhoDireita, chaveInicial, dataLimite, cliente, contador);
}

// Impressão eventos RG de cliente
template <typename T>
void arvoreAVL<T>::imprimeEventosDeChegadaClienteAte(const T& chaveInicial, int dataLimite, const noCliente& cliente) const {
    imprimeEventosDeChegadaClienteAte(raiz, chaveInicial, dataLimite, cliente);
}

template <typename T>
void arvoreAVL<T>::imprimeEventosDeChegadaClienteAte(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente) const {
    if (!no) return;

    if (no->chave >= chaveInicial)
        imprimeEventosDeChegadaClienteAte(no->filhoEsquerda, chaveInicial, dataLimite, cliente);

    if (no->chave.tempoEvento <= dataLimite && no->chave.evento && no->chave.evento->getTipoEvento() == "RG") {
        CelulaIndice* atual = cliente.getListaIndices();
        while (atual) {
            if (atual->indicePacote == no->chave.idPacote) {
                no->chave.evento->imprimeEvento();
                break;
            }
            atual = atual->prox;
        }
    }

    if (no->chave >= chaveInicial)
        imprimeEventosDeChegadaClienteAte(no->filhoDireita, chaveInicial, dataLimite, cliente);
}

// Impressão eventos finais
template <typename T>
void arvoreAVL<T>::imprimeEventosFinaisClienteAteInOrder(const T& chaveInicial, int dataLimite, const noCliente& cliente) const {
    imprimeEventosFinaisClienteFiltrados(raiz, chaveInicial, dataLimite, cliente);
}

template <typename T>
void arvoreAVL<T>::imprimeEventosFinaisClienteFiltrados(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente) const {
    if (!no) return;

    imprimeEventosFinaisClienteFiltrados(no->filhoEsquerda, chaveInicial, dataLimite, cliente);

    if (no->chave >= chaveInicial && no->chave.tempoEvento <= dataLimite) {
        Evento* eventoNaArvore = no->chave.evento;

        CelulaIndice* atual = cliente.getListaIndices();
        while (atual) {
            if (atual->representante && atual->representante->getFim() == eventoNaArvore) {
                eventoNaArvore->imprimeEvento();
                break;
            }
            atual = atual->prox;
        }
    }

    imprimeEventosFinaisClienteFiltrados(no->filhoDireita, chaveInicial, dataLimite, cliente);
}

