#include "noCliente.hpp"

// ------------------- Implementação da CelulaIndice -------------------

CelulaIndice::CelulaIndice(int i, Pacote* p)
    : indicePacote(i), representante(p), prox(nullptr) {}

// ------------------- Implementação da classe noCliente -------------------

noCliente::noCliente(std::string nome)
    : nomeCliente(std::move(nome)), inicio(nullptr), fim(nullptr), qntdPacotes(0) {}

noCliente::noCliente(const noCliente& outro)
    : nomeCliente(outro.nomeCliente) {
    copia(outro);
}

noCliente& noCliente::operator=(const noCliente& outro) {
    if (this != &outro) {
        nomeCliente = outro.nomeCliente;
        limpa();
        copia(outro);
    }
    return *this;
}

noCliente::~noCliente() {
    limpa();
}

void noCliente::copia(const noCliente& outro) {
    inicio = fim = nullptr;
    qntdPacotes = 0;

    CelulaIndice* atualOutro = outro.inicio;
    while (atualOutro) {
        adicionaIndice(atualOutro->indicePacote, atualOutro->representante);
        atualOutro = atualOutro->prox;
    }
}

void noCliente::limpa() {
    while (inicio) {
        CelulaIndice* temp = inicio;
        inicio = inicio->prox;
        delete temp;
    }
    fim = nullptr;
    qntdPacotes = 0;
}

void noCliente::adicionaIndice(int idx, Pacote* p) {
    CelulaIndice* nova = new CelulaIndice(idx, p);

    if (!inicio) {
        // Lista vazia
        inicio = fim = nova;
    } else if (idx > fim->indicePacote) {
        // Inserir no fim (O(1))
        fim->prox = nova;
        fim = nova;
    } else if (idx < inicio->indicePacote) {
        // Inserir no início
        nova->prox = inicio;
        inicio = nova;
    } else {
        // Inserir no meio (ordenado)
        CelulaIndice* atual = inicio;
        while (atual->prox && atual->prox->indicePacote < idx)
            atual = atual->prox;

        nova->prox = atual->prox;
        atual->prox = nova;

        if (!nova->prox) fim = nova;  // Se foi o último, atualiza fim
    }

    ++qntdPacotes;
}

// ------------------- Getters -------------------

std::string noCliente::getNome() const {
    return nomeCliente;
}

CelulaIndice* noCliente::getListaIndices() const {
    return inicio;
}

int noCliente::getQntdPacotes() const {
    return qntdPacotes;
}

// ------------------- Operadores -------------------

bool noCliente::operator<(const noCliente& outro) const {
    return nomeCliente < outro.nomeCliente;
}

bool noCliente::operator>(const noCliente& outro) const {
    return nomeCliente > outro.nomeCliente;
}

std::ostream& operator<<(std::ostream& os, const noCliente& cliente) {
    os << cliente.getNome();
    return os;
}