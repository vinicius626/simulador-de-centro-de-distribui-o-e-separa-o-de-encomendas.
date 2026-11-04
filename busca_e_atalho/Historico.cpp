#include "Historico.h"

#include <iostream>

struct Historico::No {
    Encomenda encomenda;
    No* anterior;
    No* proximo;

    explicit No(const Encomenda& valor)
        : encomenda(valor), anterior(nullptr), proximo(nullptr) {}
};

Historico::Historico()
    : inicio(nullptr), fim(nullptr), quantidadeRegistros(0) {}

Historico::~Historico() {
    No* atual = inicio;
    while (atual != nullptr) {
        No* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

void Historico::adicionar(const Encomenda& encomenda) {
    No* novo = new No(encomenda);
    novo->anterior = fim;

    if (fim != nullptr) {
        fim->proximo = novo;
    } else {
        inicio = novo;
    }

    fim = novo;
    ++quantidadeRegistros;
}

bool Historico::vazia() const {
    return inicio == nullptr;
}

std::size_t Historico::quantidade() const {
    return quantidadeRegistros;
}

void Historico::exibirRegistro(const Encomenda& encomenda, std::size_t numero) {
    std::cout << numero << ". Codigo: " << encomenda.codigo
              << " | Destino: " << encomenda.destino
              << " | Status: " << statusParaTexto(encomenda.status)
              << '\n';
}

void Historico::exibirDoMaisAntigo() const {
    if (vazia()) {
        std::cout << "Historico vazio.\n";
        return;
    }

    std::cout << "Historico (mais antigo primeiro):\n";
    std::size_t numero = 1;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo) {
        exibirRegistro(atual->encomenda, numero++);
    }
}

void Historico::exibirDoMaisRecente() const {
    if (vazia()) {
        std::cout << "Historico vazio.\n";
        return;
    }

    std::cout << "Historico (mais recente primeiro):\n";
    std::size_t numero = quantidadeRegistros;
    for (No* atual = fim; atual != nullptr; atual = atual->anterior) {
        exibirRegistro(atual->encomenda, numero--);
    }
}
