# Parte 3 — Busca e histórico

Arquivos desta parte:

- `modelos.h`: contrato compartilhado de `Encomenda`, `Centro` e `Status`.
- `ArvoreBusca.h/.cpp`: ABB indexada pelo código da encomenda.
- `Historico.h/.cpp`: lista duplamente encadeada de eventos de processamento.

## Executar esta demonstracao

`main.cpp` contém um menu independente para demonstrar cadastro na ABB, busca por código, encaminhamento, entrega e consulta do histórico. No terminal aberto nesta pasta, compile com:

```text
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp ArvoreBusca.cpp Historico.cpp -o busca_e_historico.exe
```

Depois, execute `busca_e_historico.exe`.

## Como integrar ao projeto do grupo

O grupo deve manter **uma única definição** de `Encomenda` e `Centro`. Se a Parte 1 já tiver um `modelos.h`, compare os campos e incorpore nele os que faltarem; não deixe cópias diferentes das structs em módulos distintos.

Ao cadastrar uma encomenda, a Parte 1 deve chamar `abb.inserir(encomenda)`. A busca pode ser feita com `Encomenda* encomenda = abb.buscar(codigo)`. Se o resultado não for `nullptr`, os outros módulos podem atualizar o status e registrar uma cópia no histórico:

```cpp
Encomenda* encomenda = abb.buscar(codigo);
if (encomenda != nullptr) {
    encomenda->status = Status::Encaminhada;
    historico.adicionar(*encomenda);
}
```

Quando a encomenda for entregue, atualize novamente o status para `Status::Entregue` e chame `historico.adicionar(*encomenda)` outra vez. Assim, o histórico guarda cada etapa como um registro separado.

Ao integrar ao projeto do grupo, use o `main.cpp` principal de vocês e não compile dois arquivos que tenham `main`. Inclua `ArvoreBusca.cpp` e `Historico.cpp` na compilação. Esta implementação usa recursos de C++11.
