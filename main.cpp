#include <iostream>
#include <string>
#include <queue>
#include <vector>

// Enumeração compartilhada para o status da encomenda
enum class Status {
    Aguardando,
    Encaminhada,
    Entregue,
    Problema
};

// Estrutura compartilhada para a Encomenda
struct Encomenda {
    int codigo;
    double pesoKg;
    std::string destino;
    int prioridade;       // 3: Alta, 2: Média, 1: Baixa
    double distanciaKm;   // Distância do centro até o destino
    int ordemChegada;     // Atribuído automaticamente (1, 2, 3...)
    Status status;
};

// Estrutura compartilhada para o Centro de Distribuição
struct Centro {
    std::string nome;
    double capacidadeKg;  // Peso máximo por rodada
    std::string regiao;
};

// Função auxiliar para converter o Status enum em string para exibição
std::string statusParaString(Status s) {
    switch (s) {
        case Status::Aguardando: return "Aguardando";
        case Status::Encaminhada: return "Encaminhada";
        case Status::Entregue: return "Entregue";
        case Status::Problema: return "Problema";
    }
    return "Desconhecido";
}

// Função para cadastrar novas encomendas e colocá-las na fila
void cadastrarEncomenda(std::queue<Encomenda>& fila, int& contadorOrdem) {
    Encomenda nova;
    
    std::cout << "\n--- Cadastro de Nova Encomenda ---\n";
    std::cout << "Codigo da encomenda: ";
    std::cin >> nova.codigo;
    
    std::cout << "Peso (kg): ";
    std::cin >> nova.pesoKg;
    
    std::cout << "Destino: ";
    std::cin.ignore(); // Limpa o buffer do teclado
    std::getline(std::cin, nova.destino);
    
    // Validação da prioridade (1 a 3)
    do {
        std::cout << "Prioridade (3 - Alta, 2 - Media, 1 - Baixa): ";
        std::cin >> nova.prioridade;
        if (nova.prioridade < 1 || nova.prioridade > 3) {
            std::cout << "Prioridade invalida! Digite um valor entre 1 e 3.\n";
        }
    } while (nova.prioridade < 1 || nova.prioridade > 3);
    
    std::cout << "Distancia em km (distanciaKm): ";
    std::cin >> nova.distanciaKm;
    
    // Atribuição automática da ordem de chegada e status inicial
    nova.ordemChegada = contadorOrdem++;
    nova.status = Status::Aguardando;
    
    // Adiciona a encomenda na fila de espera
    fila.push(nova);
    std::cout << "\n[Sucesso] Encomenda cadastrada e adicionada à fila com ordem de chegada #" << nova.ordemChegada << "!\n";
}

// Função para mostrar as encomendas presentes na fila
void mostrarFila(std::queue<Encomenda> fila) {
    if (fila.empty()) {
        std::cout << "\n[Aviso] A fila de encomendas esta vazia no momento.\n";
        return;
    }
    
    std::cout << "\n========================================\n";
    std::cout << "         FILA DE ENCOMENDAS (AGUARDANDO)\n";
    std::cout << "========================================\n";
    
    int posicao = 1;
    while (!fila.empty()) {
        Encomenda enc = fila.front();
        fila.pop();
        
        std::cout << "Posicao na Fila : " << posicao++ << "\n";
        std::cout << "Ordem Chegada   : " << enc.ordemChegada << "\n";
        std::cout << "Codigo          : " << enc.codigo << "\n";
        std::cout << "Peso            : " << enc.pesoKg << " kg\n";
        std::cout << "Destino         : " << enc.destino << "\n";
        std::cout << "Prioridade      : " << enc.prioridade << "\n";
        std::cout << "Distancia       : " << enc.distanciaKm << " km\n";
        std::cout << "Status          : " << statusParaString(enc.status) << "\n";
        std::cout << "----------------------------------------\n";
    }
}

int main() {
    // Inicialização padrão do Centro de Distribuição
    Centro meuCentro = {"Centro de Distribuicao Principal", 150.0, "Recife"};
    
    // Fila que armazenará as encomendas aguardando processamento
    std::queue<Encomenda> filaEncomendas;
    
    // Contador para gerenciar a ordem de chegada de forma incremental (1, 2, 3...)
    int contadorOrdem = 1;
    int opcao;
    
    do {
        std::cout << "\n=== SISTEMA DE GESTAO DE ENCOMENDAS ===\n";
        std::cout << "Centro: " << meuCentro.nome << " | Capacidade Max: " << meuCentro.capacidadeKg << " kg\n";
        std::cout << "1. Cadastrar nova encomenda\n";
        std::cout << "2. Mostrar encomendas na fila\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        
        switch (opcao) {
            case 1:
                cadastrarEncomenda(filaEncomendas, contadorOrdem);
                break;
            case 2:
                mostrarFila(filaEncomendas);
                break;
            case 3:
                std::cout << "Encerrando o programa...\n";
                break;
            default:
                std::cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (opcao != 3);
    
    return 0;
}