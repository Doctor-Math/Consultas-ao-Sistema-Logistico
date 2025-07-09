#include "eventos.hpp"
#include <iomanip>

// ---------------------- Implementação da classe Evento ----------------------

Evento::Evento() {
    data_hora = -1;
    tipoEvento = "";
    idPac = -1;
    remetente = "";
    destinatario = "";
    idArmOrg = -1;
    idArmDest = -1;
    secaoDestino = -1;
}

Evento::Evento(int dh, std::string tp, int idP, std::string rem, std::string dest,
               int idArmIni, int idArmD, int secaoDest) {
    data_hora = dh;
    tipoEvento = tp;
    idPac = idP;
    remetente = rem;
    destinatario = dest;
    idArmOrg = idArmIni;
    idArmDest = idArmD;
    secaoDestino = secaoDest;
}

void Evento::imprimeEvento() {
    std::cout << std::setfill('0') << std::setw(7) << data_hora << " EV " << tipoEvento << " ";

    if (tipoEvento == "RG") {
        std::cout << std::setw(3) << idPac << " " << remetente << " " << destinatario << " "
                  << std::setw(3) << idArmOrg << " " << std::setw(3) << idArmDest << std::endl;
    } else if (tipoEvento == "AR" || tipoEvento == "RM" || tipoEvento == "UR") {
        std::cout << std::setw(3) << idPac << " " << std::setw(3) << idArmDest << " "
                  << std::setw(3) << secaoDestino << std::endl;
    } else if (tipoEvento == "TR") {
        std::cout << std::setw(3) << idPac << " " << std::setw(3) << idArmOrg << " "
                  << std::setw(3) << idArmDest << std::endl;
    } else if (tipoEvento == "EN") {
        std::cout << std::setw(3) << idPac << " " << std::setw(3) << idArmDest << std::endl;
    }
}

std::string Evento::getTipoEvento() { return tipoEvento; }
int Evento::getDataHora() { return data_hora; }
int Evento::getIdPac() { return idPac; }

// ---------------------- Implementação da classe vetorEventos ----------------------

vetorEventos::vetorEventos(int cap) {
    capacidade = cap;
    quantidade = 0;
    eventos = new Evento*[capacidade];
}

vetorEventos::~vetorEventos() {
    for (int i = 0; i < quantidade; i++) {
        delete eventos[i];
    }
    delete[] eventos;
}

void vetorEventos::insereEvento(Evento* e) {
    if (quantidade >= capacidade) {
        aumentaCapacidade();
    }
    eventos[quantidade++] = e;
}

void vetorEventos::aumentaCapacidade() {
    int novaCapacidade = capacidade * 2;
    Evento** novoVetor = new Evento*[novaCapacidade];

    for (int i = 0; i < capacidade; i++) {
        novoVetor[i] = eventos[i];
    }

    delete[] eventos;
    eventos = novoVetor;
    capacidade = novaCapacidade;
}

Evento* vetorEventos::acessaEvento(int pos) {
    if (pos < 0 || pos >= quantidade) {
        throw "ERRO: Posição inválida!";
    }
    return eventos[pos];
}

int vetorEventos::getQuantidade() {
    return quantidade;
}
