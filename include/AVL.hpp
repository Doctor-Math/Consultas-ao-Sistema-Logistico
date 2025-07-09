#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP
#include "noCliente.hpp"

// Classe template para árvore AVL genérica
template <typename T>
class arvoreAVL {
private:
    struct No {
        T chave;
        int altura;
        No* filhoEsquerda;
        No* filhoDireita;

        No(const T& c)
            : chave(c), altura(1), filhoEsquerda(nullptr), filhoDireita(nullptr) {}
    };

    No* raiz;

    // Métodos auxiliares internos
    int altura(No* no) const;
    int fatorBalanceamento(No* no);
    void atualizarAltura(No* no);
    No* rotacaoDireita(No* y);
    No* rotacaoEsquerda(No* x);
    No* insere(No* no, const T& chave);
    T* busca(No* no, const T& chave) const;
    void limpa(No* no);

    // Métodos específicos a depender do tipo de célula
    void emOrdemApartirDe(No* no, const T& chaveRef, int idPacoteAlvo) const;
    void imprimeInOrderPacoteAte(No* no, const T& chaveInicial, int dataLimite) const;
    void contaEventosPacoteAte(No* no, const T& chaveInicial, int dataLimite, int& contador) const;

    void contaEventosDeChegadaClienteAte(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente, int& contador) const;
    void imprimeEventosDeChegadaClienteAte(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente) const;
    void imprimeEventosFinaisClienteFiltrados(No* no, const T& chaveInicial, int dataLimite, const noCliente& cliente) const;

public:
    arvoreAVL();
    ~arvoreAVL();

    // Interface pública
    T* busca(const T& chave) const;
    void insere(const T& chave);
    void emOrdemApartirDe(const T& chaveRef, int idPacoteAlvo) const;
    void imprimeInOrderPacoteAte(const T& chaveInicial, int dataLimite) const;
    void contaEventosPacoteAte(const T& chaveInicial, int dataLimite, int& contador) const;

    // Operações específicas com cliente
    void contaEventosDeChegadaClienteAte(const T& chaveInicial, int dataLimite, const noCliente& cliente, int& contador) const;
    void imprimeEventosDeChegadaClienteAte(const T& chaveInicial, int dataLimite, const noCliente& cliente) const;
    void imprimeEventosFinaisClienteAteInOrder(const T& chaveInicial, int dataLimite, const noCliente& cliente) const;
};

#include "../src/AVL.tpp"

#endif // ARVORE_AVL_HPP