#ifndef MODELOS_H
#define MODELOS_H

#include <string>

enum class Status {
    Aguardando,
    Encaminhada,
    Entregue,
    Problema
};

struct Encomenda {
    int codigo;
    double pesoKg;
    std::string destino;
    int prioridade;       // 1 = baixa, 2 = media, 3 = alta
    double distanciaKm;
    int ordemChegada;     // usado para desempatar prioridades iguais
    Status status;
};

struct Centro {
    std::string nome;
    double capacidadeKg;  // peso maximo processado por operacao
    std::string regiao;
};

inline const char* statusParaTexto(Status status) {
    switch (status) {
        case Status::Aguardando: return "Aguardando";
        case Status::Encaminhada: return "Encaminhada";
        case Status::Entregue: return "Entregue";
        case Status::Problema: return "Problema";
    }
    return "Desconhecido";
}

#endif
