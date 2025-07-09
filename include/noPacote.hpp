#ifndef NOPACOTE_HPP
#define NOPACOTE_HPP

#include "eventos.hpp"

// -----------------------------
// Classe que representa um Pacote no sistema
// -----------------------------
class Pacote {
private:
    int idPac;           // Identificador do pacote
    Evento* inicio;      // Ponteiro para o primeiro evento do pacote
    Evento* fim;         // Ponteiro para o último evento do pacote

public:
    // Construtor padrão
    Pacote();

    // Construtor com parâmetros
    Pacote(int id, Evento* ini);

    // Getters
    int getId() const;
    Evento* getInicio() const;
    Evento* getFim() const;

    // Atualiza o evento final do pacote
    void atualizaFim(Evento* e);
};

// -----------------------------
// Estrutura auxiliar para indexar pacotes
// -----------------------------
struct NoPacote {
    int idPacote;        // Identificador do pacote
    int tempoRegistro;   // Tempo em que o pacote foi registrado

    // Construtor
    NoPacote(int id, int tempo);

    // Operadores de comparação (para estruturas de ordenação, como AVL)
    bool operator<(const NoPacote& outro) const;
    bool operator>(const NoPacote& outro) const;
    bool operator==(const NoPacote& outro) const;
};

#endif
