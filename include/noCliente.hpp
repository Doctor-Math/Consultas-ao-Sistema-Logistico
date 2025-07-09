#ifndef NO_CLIENTE_HPP
#define NO_CLIENTE_HPP

#include <string>
#include <iostream>
#include "noPacote.hpp"

// --------- Célula da lista de índices ---------
// Representa um nó de uma lista ligada simples que armazena a associação
// entre um cliente e os pacotes ligados a ele.
struct CelulaIndice {
    int indicePacote;             // Índice ou ID do pacote na estrutura principal
    Pacote* representante;        // Ponteiro para o objeto Pacote correspondente
    CelulaIndice* prox;           // Ponteiro para a próxima célula na lista

    CelulaIndice(int i, Pacote* p);
};

// --------- Classe noCliente ---------
// Representa um cliente com um nome e uma lista ligada de pacotes associados.
class noCliente {
private:
    std::string nomeCliente;      // Nome identificador do cliente
    CelulaIndice* inicio;         // Ponteiro para o início da lista de pacotes
    CelulaIndice* fim;            // Ponteiro para o final da lista (facilita inserção)
    int qntdPacotes;              // Contador de pacotes associados ao cliente

    // Método auxiliar: copia os dados de outro cliente (para construtor de cópia/atribuição)
    void copia(const noCliente& outro);

    void limpa();

public:
    noCliente(std::string nome);

    // Construtor de cópia
    noCliente(const noCliente& outro);

    noCliente& operator=(const noCliente& outro);

    ~noCliente();

    void adicionaIndice(int idx, Pacote* p); 

    std::string getNome() const;

    // Retorna o ponteiro para o início da lista de índices
    CelulaIndice* getListaIndices() const;

    int getQntdPacotes() const;

    // Operadores de comparação por nome (úteis para ordenação)
    bool operator<(const noCliente& outro) const;
    bool operator>(const noCliente& outro) const;

    // Operador de inserção para saída formatada (impressão)
    friend std::ostream& operator<<(std::ostream& os, const noCliente& cliente);
};

#endif
