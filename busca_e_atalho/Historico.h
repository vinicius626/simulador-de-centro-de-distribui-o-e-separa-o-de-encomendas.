#ifndef HISTORICO_H
#define HISTORICO_H

#include "modelos.h"

#include <cstddef>

class Historico {
private:
    struct No;
    No* inicio;
    No* fim;
    std::size_t quantidadeRegistros;

    static void exibirRegistro(const Encomenda& encomenda, std::size_t numero);

public:
    Historico();
    ~Historico();

    Historico(const Historico&) = delete;
    Historico& operator=(const Historico&) = delete;

    // Guarda uma copia da encomenda com o status atual.
    void adicionar(const Encomenda& encomenda);
    bool vazia() const;
    std::size_t quantidade() const;

    void exibirDoMaisAntigo() const;
    void exibirDoMaisRecente() const;
};

#endif
