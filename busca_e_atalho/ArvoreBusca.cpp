#include "ArvoreBusca.h"

#include <iostream>

struct ArvoreBusca::No {
    Encomenda encomenda;
    No* esquerda;
    No* direita;

    explicit No(const Encomenda& valor)
        : encomenda(valor), esquerda(nullptr), direita(nullptr) {}
};

ArvoreBusca::ArvoreBusca() : raiz(nullptr) {}

ArvoreBusca::~ArvoreBusca() {
    liberarRec(raiz);
}

ArvoreBusca::No* ArvoreBusca::inserirRec(
    No* atual, const Encomenda& encomenda, bool& inseriu) {
    if (atual == nullptr) {
        inseriu = true;
        return new No(encomenda);
    }

    if (encomenda.codigo < atual->encomenda.codigo) {
        atual->esquerda = inserirRec(atual->esquerda, encomenda, inseriu);
    } else if (encomenda.codigo > atual->encomenda.codigo) {
        atual->direita = inserirRec(atual->direita, encomenda, inseriu);
    }
    // Codigo igual: nao insere duplicata.
    return atual;
}

bool ArvoreBusca::inserir(const Encomenda& encomenda) {
    bool inseriu = false;
    raiz = inserirRec(raiz, encomenda, inseriu);
    return inseriu;
}

Encomenda* ArvoreBusca::buscarRec(No* atual, int codigo) {
    if (atual == nullptr || atual->encomenda.codigo == codigo) {
        return atual == nullptr ? nullptr : &atual->encomenda;
    }

    if (codigo < atual->encomenda.codigo) {
        return buscarRec(atual->esquerda, codigo);
    }
    return buscarRec(atual->direita, codigo);
}

const Encomenda* ArvoreBusca::buscarRec(const No* atual, int codigo) {
    if (atual == nullptr || atual->encomenda.codigo == codigo) {
        return atual == nullptr ? nullptr : &atual->encomenda;
    }

    if (codigo < atual->encomenda.codigo) {
        return buscarRec(atual->esquerda, codigo);
    }
    return buscarRec(atual->direita, codigo);
}

Encomenda* ArvoreBusca::buscar(int codigo) {
    return buscarRec(raiz, codigo);
}

const Encomenda* ArvoreBusca::buscar(int codigo) const {
    return buscarRec(raiz, codigo);
}

void ArvoreBusca::exibirEmOrdemRec(const No* atual) {
    if (atual == nullptr) {
        return;
    }

    exibirEmOrdemRec(atual->esquerda);
    std::cout << "Codigo: " << atual->encomenda.codigo
              << " | Destino: " << atual->encomenda.destino
              << " | Status: " << statusParaTexto(atual->encomenda.status)
              << '\n';
    exibirEmOrdemRec(atual->direita);
}

void ArvoreBusca::exibirEmOrdem() const {
    if (raiz == nullptr) {
        std::cout << "Nenhuma encomenda cadastrada na ABB.\n";
        return;
    }
    exibirEmOrdemRec(raiz);
}

void ArvoreBusca::liberarRec(No* atual) {
    if (atual == nullptr) {
        return;
    }
    liberarRec(atual->esquerda);
    liberarRec(atual->direita);
    delete atual;
}
