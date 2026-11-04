#ifndef ARVORE_BUSCA_H
#define ARVORE_BUSCA_H

#include "modelos.h"

class ArvoreBusca {
private:
    struct No;
    No* raiz;

    static No* inserirRec(No* atual, const Encomenda& encomenda, bool& inseriu);
    static Encomenda* buscarRec(No* atual, int codigo);
    static const Encomenda* buscarRec(const No* atual, int codigo);
    static void exibirEmOrdemRec(const No* atual);
    static void liberarRec(No* atual);

public:
    ArvoreBusca();
    ~ArvoreBusca();

    ArvoreBusca(const ArvoreBusca&) = delete;
    ArvoreBusca& operator=(const ArvoreBusca&) = delete;

    // Retorna false se ja existir uma encomenda com o mesmo codigo.
    bool inserir(const Encomenda& encomenda);

    // Retorna nullptr quando o codigo nao estiver cadastrado.
    Encomenda* buscar(int codigo);
    const Encomenda* buscar(int codigo) const;

    // Exibe os registros em ordem crescente de codigo.
    void exibirEmOrdem() const;
};

#endif
