#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include <string>
#include <iostream>
#include <iomanip>

// ---------------------- Classe Evento ----------------------
// Representa um evento e seus atributos no sistema
class Evento {
private:
    int data_hora;
    std::string tipoEvento;
    int idPac;
    std::string remetente;
    std::string destinatario;
    int idArmOrg;
    int idArmDest;
    int secaoDestino;

public:
    Evento(); // Construtor padrão
    Evento(int dh, std::string tp, int idP, std::string rem, std::string dest,
           int idArmIni, int idArmD, int secaoDest); // Construtor parametrizado

    void imprimeEvento(); // Imprime o evento formatado

    // Métodos de acesso (getters)
    std::string getTipoEvento();
    int getDataHora();
    int getIdPac();
};

// ---------------------- Classe vetorEventos ----------------------
// Vetor dinâmico que armazena ponteiros para objetos Evento
class vetorEventos {
public:
    vetorEventos(int cap);  // Construtor
    ~vetorEventos();        // Destrutor

    void insereEvento(Evento* e);       // Insere um novo evento no vetor
    Evento* acessaEvento(int pos);      // Acessa um evento por posição
    int getQuantidade();                // Retorna a quantidade atual de eventos

private:
    void aumentaCapacidade();           // Dobra a capacidade do vetor

    int capacidade;      // Capacidade total alocada
    int quantidade;      // Número de eventos atualmente armazenados
    Evento** eventos;    // Vetor de ponteiros para eventos
};


// --------------------------
// Struct que representa a chave usada para indexar eventos em estruturas como AVL
// --------------------------
struct ChaveEvento {
    int idPacote;           // ID do pacote
    int tempoEvento;        // Momento do evento
    int ordemInsercao;      // Ordem relativa entre eventos com mesmo tempo e pacote
    Evento* evento;         // Ponteiro para o evento real

    ChaveEvento(int id = 0, int tempo = 0, int ordem = 0, Evento* ev = nullptr)
        : idPacote(id), tempoEvento(tempo), ordemInsercao(ordem), evento(ev) {}

    // Ordenação por tempo, pacote e ordem de inserção
    bool operator<(const ChaveEvento& outro) const {
        if (tempoEvento != outro.tempoEvento)
            return tempoEvento < outro.tempoEvento;
        if (idPacote != outro.idPacote)
            return idPacote < outro.idPacote;
        return ordemInsercao < outro.ordemInsercao;
    }

    bool operator==(const ChaveEvento& outro) const {
        return tempoEvento == outro.tempoEvento &&
               idPacote == outro.idPacote &&
               ordemInsercao == outro.ordemInsercao;
    }

    bool operator>=(const ChaveEvento& outro) const {
        return !(*this < outro);
    }

    bool operator>(const ChaveEvento& outro) const {
        return outro < *this;
    }

    // Impressão formatada
    friend std::ostream& operator<<(std::ostream& os, const ChaveEvento& c) {
        os << std::setw(3) << std::setfill('0') << c.idPacote
           << ' ' << std::setw(7) << std::setfill('0') << c.tempoEvento;
        return os;
    }
};

#endif
