#include "noPacote.hpp"

// ------------------- Implementação da classe Pacote -------------------

// Construtor padrão
Pacote::Pacote() : idPac(-1), inicio(nullptr), fim(nullptr) {}

// Construtor com ID e ponteiro para evento inicial
Pacote::Pacote(int id, Evento* ini) : idPac(id), inicio(ini), fim(ini) {}

// Getters
int Pacote::getId() const { return idPac; }

Evento* Pacote::getInicio() const { return inicio; }

Evento* Pacote::getFim() const { return fim; }

// Atualiza o ponteiro para o evento final
void Pacote::atualizaFim(Evento* e) { fim = e; }

// ------------------- Implementação do noPacote -------------------


// Construtor
NoPacote::NoPacote(int id, int tempo) : idPacote(id), tempoRegistro(tempo) {}

// Operadores de comparação
bool NoPacote::operator<(const NoPacote& outro) const {
    return idPacote < outro.idPacote;
}

bool NoPacote::operator>(const NoPacote& outro) const {
    return idPacote > outro.idPacote;
}

bool NoPacote::operator==(const NoPacote& outro) const {
    return idPacote == outro.idPacote;
}

