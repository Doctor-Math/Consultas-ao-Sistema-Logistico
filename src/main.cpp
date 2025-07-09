#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "eventos.hpp"
#include "noCliente.hpp"
#include "AVL.hpp"

#define MAXTAM 10000          // Capacidade inicial para o vetor de eventos
#define MAX_PACOTES 10000     // Número máximo de pacotes suportados

// Vetor que armazena todos os pacotes registrados
Pacote listaPacotes[MAX_PACOTES];
// Vetor auxiliar para indicar se um pacote já foi usado
bool usado[MAX_PACOTES] = {};  // Inicializa tudo como false

int main(int argc, char* argv[]) {

    int ordemGlobal = 0; // Garantir unicidade das chaves (tempo+ordem) mesmo para eventos com tempo repetido
    arvoreAVL<ChaveEvento> avlChavesEventos;       // Índice principal de eventos (ordenado por tempo)
    arvoreAVL<NoPacote> avlPacotesRegistrados;     // Índice auxiliar para evitar duplicações de pacotes

    // Verifica se o nome do arquivo foi passado como argumento
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>" << std::endl;
        return 1;
    }

    // Tenta abrir o arquivo fornecido
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    // Variáveis auxiliares para leitura dos dados
    int data_hora, idPac, idArmOrg, idArmDest, secaoDest;
    std::string str, tipoEvento, remetente, destinatario;

    vetorEventos v(MAXTAM);               // Armazena os eventos dinamicamente
    arvoreAVL<noCliente> avlClientes;     // Índice AVL de clientes únicos

    // Processamento linha a linha do arquivo de entrada
    while (infile >> data_hora >> str) {
        
        if (str == "EV") {
            // Evento padrão
            infile >> tipoEvento >> idPac;
            Evento* novoEvento = nullptr;

            // Evento de registro (remetente e destinatário envolvidos)
            if (tipoEvento == "RG") {
                infile >> remetente >> destinatario >> idArmOrg >> idArmDest;
                novoEvento = new Evento(data_hora, tipoEvento, idPac, remetente, destinatario, idArmOrg, idArmDest, -1);

                // Criação do pacote associado, se ainda não registrado
                if (!usado[idPac]) {
                    listaPacotes[idPac] = Pacote(idPac, novoEvento);
                    usado[idPac] = true;
                }

                // Associar remetente ao pacote
                noCliente* clienteRem = avlClientes.busca(noCliente(remetente));
                if (clienteRem)
                    clienteRem->adicionaIndice(idPac, &listaPacotes[idPac]);
                else {
                    noCliente novo(remetente);
                    novo.adicionaIndice(idPac, &listaPacotes[idPac]);
                    avlClientes.insere(novo);
                }

                // Associar destinatário ao pacote
                noCliente* clienteDest = avlClientes.busca(noCliente(destinatario));
                if (clienteDest)
                    clienteDest->adicionaIndice(idPac, &listaPacotes[idPac]);
                else {
                    noCliente novo(destinatario);
                    novo.adicionaIndice(idPac, &listaPacotes[idPac]);
                    avlClientes.insere(novo);
                }

            } else if (tipoEvento == "AR" || tipoEvento == "RM" || tipoEvento == "UR") {
                infile >> idArmDest >> secaoDest;
                novoEvento = new Evento(data_hora, tipoEvento, idPac, "", "", -1, idArmDest, secaoDest);
            } else if (tipoEvento == "TR") {
                infile >> idArmOrg >> idArmDest;
                novoEvento = new Evento(data_hora, tipoEvento, idPac, "", "", idArmOrg, idArmDest, -1);
            } else if (tipoEvento == "EN") {
                infile >> idArmDest;
                novoEvento = new Evento(data_hora, tipoEvento, idPac, "", "", -1, idArmDest, -1);
            }

            // Se evento criado com sucesso:
            if (novoEvento) {
                // Criação do pacote caso ainda não feito
                if (!usado[idPac]) {
                    listaPacotes[idPac] = Pacote(idPac, novoEvento);
                    usado[idPac] = true;
                } else {
                    // Atualiza evento final do pacote
                    listaPacotes[idPac].atualizaFim(novoEvento);
                }

                // Cria chave e insere evento no índice AVL
                ChaveEvento chave(idPac, data_hora, ordemGlobal++, novoEvento);
                avlChavesEventos.insere(chave);
            }

        } else if (str == "CL") {
            // Consulta por cliente
            std::string nomeCliente;
            infile >> nomeCliente;

            std::cout << std::setfill('0') << std::setw(6) << data_hora << " CL " << nomeCliente << "\n";

            noCliente* cliente = avlClientes.busca(noCliente(nomeCliente));
            int contador = 0;

            if (cliente) {
                ChaveEvento chaveInicial;
                chaveInicial.idPacote = 0;
                chaveInicial.tempoEvento = 0;

                // Conta quantos pacotes estão associados ao cliente
                avlChavesEventos.contaEventosDeChegadaClienteAte(chaveInicial, data_hora, *cliente, contador);
                std::cout << contador * 2 << '\n'; // Cada pacote gera dois eventos: chegada + final

                // Imprime eventos de chegada em ordem cronológica
                avlChavesEventos.imprimeEventosDeChegadaClienteAte(chaveInicial, data_hora, *cliente);

                // Imprime eventos finais (últimos) em ordem cronológica
                avlChavesEventos.imprimeEventosFinaisClienteAteInOrder(chaveInicial, data_hora, *cliente);
            } else {
                std::cout << "0\n"; // Cliente não encontrado
            }

        } else if (str == "PC") {
            // Consulta por pacote
            infile >> idPac;

            std::cout << std::setfill('0') << std::setw(6) << data_hora << " PC "
                      << std::setw(3) << std::setfill('0') << idPac << '\n';

            int contador = 0;

            if (usado[idPac]) {
                // Cria chave de busca inicial
                ChaveEvento chaveInicial(idPac, 0, 0, nullptr);

                // Conta e imprime eventos do pacote até o tempo atual
                avlChavesEventos.contaEventosPacoteAte(chaveInicial, data_hora, contador);
                std::cout << contador << '\n';

                avlChavesEventos.imprimeInOrderPacoteAte(chaveInicial, data_hora);
            } else {
                std::cout << "0\n"; // Pacote não existente
            }
        }
    }

    return 0;
}