#include "ArvoreBusca.h"
#include "Historico.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

int lerInteiro(const std::string& mensagem) {
    int valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << "Digite um numero inteiro valido.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double lerDouble(const std::string& mensagem) {
    double valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << "Digite um numero valido.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void exibirEncomenda(const Encomenda& encomenda) {
    std::cout << "Codigo: " << encomenda.codigo
              << "\nPeso: " << encomenda.pesoKg << " kg"
              << "\nDestino: " << encomenda.destino
              << "\nPrioridade: " << encomenda.prioridade
              << "\nDistancia: " << encomenda.distanciaKm << " km"
              << "\nOrdem de chegada: " << encomenda.ordemChegada
              << "\nStatus: " << statusParaTexto(encomenda.status) << '\n';
}

void cadastrar(ArvoreBusca& abb, int& proximaOrdem) {
    Encomenda encomenda{};

    encomenda.codigo = lerInteiro("Codigo: ");
    encomenda.pesoKg = lerDouble("Peso (kg): ");
    std::cout << "Destino: ";
    std::getline(std::cin >> std::ws, encomenda.destino);
    encomenda.prioridade = lerInteiro("Prioridade (1 baixa, 2 media, 3 alta): ");
    encomenda.distanciaKm = lerDouble("Distancia (km): ");
    encomenda.ordemChegada = proximaOrdem;
    encomenda.status = Status::Aguardando;

    if (encomenda.pesoKg < 0 || encomenda.distanciaKm < 0 ||
        encomenda.prioridade < 1 || encomenda.prioridade > 3) {
        std::cout << "Peso, distancia ou prioridade fora do intervalo permitido.\n";
        return;
    }

    if (abb.inserir(encomenda)) {
        ++proximaOrdem;
        std::cout << "Encomenda cadastrada na ABB.\n";
    } else {
        std::cout << "Ja existe uma encomenda com esse codigo.\n";
    }
}

void buscarEncomenda(ArvoreBusca& abb) {
    const int codigo = lerInteiro("Informe o codigo para busca: ");
    Encomenda* encomenda = abb.buscar(codigo);
    if (encomenda == nullptr) {
        std::cout << "Encomenda nao encontrada.\n";
        return;
    }
    std::cout << "Encomenda encontrada:\n";
    exibirEncomenda(*encomenda);
}

void atualizarStatus(ArvoreBusca& abb, Historico& historico, Status novoStatus) {
    const int codigo = lerInteiro("Codigo da encomenda: ");
    Encomenda* encomenda = abb.buscar(codigo);
    if (encomenda == nullptr) {
        std::cout << "Encomenda nao encontrada.\n";
        return;
    }

    if (novoStatus == Status::Encaminhada && encomenda->status != Status::Aguardando) {
        std::cout << "Somente encomendas aguardando podem ser encaminhadas.\n";
        return;
    }
    if (novoStatus == Status::Entregue && encomenda->status != Status::Encaminhada) {
        std::cout << "A encomenda precisa estar encaminhada antes da entrega.\n";
        return;
    }

    encomenda->status = novoStatus;
    historico.adicionar(*encomenda);
    std::cout << "Status atualizado e evento registrado no historico.\n";
}

void exibirMenu() {
    std::cout << "\n=== BUSCA E HISTORICO DE ENCOMENDAS ===\n"
              << "1 - Cadastrar encomenda na ABB\n"
              << "2 - Buscar encomenda por codigo\n"
              << "3 - Registrar encaminhamento\n"
              << "4 - Registrar entrega\n"
              << "5 - Exibir ABB por codigo\n"
              << "6 - Exibir historico (antigo para recente)\n"
              << "7 - Exibir historico (recente para antigo)\n"
              << "0 - Sair\n";
}

} // namespace

int main() {
    ArvoreBusca abb;
    Historico historico;
    int proximaOrdem = 1;
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha: ");

        switch (opcao) {
            case 1:
                cadastrar(abb, proximaOrdem);
                break;
            case 2:
                buscarEncomenda(abb);
                break;
            case 3:
                atualizarStatus(abb, historico, Status::Encaminhada);
                break;
            case 4:
                atualizarStatus(abb, historico, Status::Entregue);
                break;
            case 5:
                abb.exibirEmOrdem();
                break;
            case 6:
                historico.exibirDoMaisAntigo();
                break;
            case 7:
                historico.exibirDoMaisRecente();
                break;
            case 0:
                std::cout << "Encerrando.\n";
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);

    return 0;
}
