# TP3 - Consultas ao Sistema Logístico dos Armazéns Hanói

**Disciplina**: Estruturas de Dados (DCC205/DCC221) — UFMG  
**Autor**: Matheus Soares dos Santos de Freitas  
**Matrícula**: 2024080043  
**Email**: matheussdsf@ufmg.br

---

## 🧾 Descrição

Este projeto implementa um sistema para consultas logísticas em uma rede de armazéns, com foco em desempenho e organização modular. Ele permite:

- Consultar o **histórico de eventos de um pacote**;
- Consultar os **eventos associados a um cliente**, respeitando restrições temporais.

Utiliza-se a estrutura de árvore **AVL** para garantir eficiência nas buscas e inserções, além de um **vetor dinâmico** para armazenar eventos em ordem cronológica.

---

## 🛠️ Organização do Projeto

- `include/`: Arquivos de cabeçalho (.hpp)
- `src/`: Implementações das classes e funções (.cpp)
- `obj/`: Arquivos objeto gerados durante a compilação
- `bin/`: Executável final (`tp3.out`)
- `Makefile`: Script de automação da compilação

---

## 📦 Principais Estruturas

- **arvoreAVL<T>**: Árvore AVL genérica para armazenar eventos, pacotes e clientes.
- **Evento**: Representa um evento logístico (registro, entrega, transferência...).
- **vetorEventos**: Vetor dinâmico que armazena os eventos na ordem de chegada.
- **Pacote**: Guarda informações e histórico de eventos de um pacote.
- **noCliente**: Armazena os dados e pacotes associados a um cliente.
- **CelulaIndice**: Nó de lista ligada para indexar pacotes de clientes.
- **ChaveEvento / NoPacote**: Estruturas auxiliares para organização das árvores.

---

## ⚙️ Execução

### 🔧 Compilação

Para compilar o projeto, execute na raiz do diretório:

```bash
make
```

O executável será gerado em `bin/tp3.out`.

### ▶️ Execução

Após a compilação, rode o programa da seguinte forma:

```bash
./bin/tp3.out < entrada.txt > saida.txt
```

- `entrada.txt`: Arquivo de entrada contendo os eventos e consultas.
- `saida.txt`: Arquivo de saída com os resultados das consultas.

---

## 📈 Complexidade

A estrutura do projeto foi projetada com foco em desempenho:

- Inserções e buscas: `O(log n)` (graças às árvores AVL)
- Armazenamento de eventos: `O(n)` com inserções `O(1)` amortizadas
- Consultas a clientes: `O(c · k · m)`
- Consultas a pacotes: `O(p · k)`

**Onde:**

- `k` = número de eventos  
- `c` = número de clientes  
- `m` = média de pacotes por cliente  
- `p` = número de pacotes

---

## 🧪 Resultados Experimentais

O desempenho foi avaliado sob três perspectivas:

1. **Número de pacotes**: crescimento quadrático no tempo de processamento (`O(p²)`).
2. **Número de clientes**: tempo de execução cai conforme aumenta o número de clientes, devido à menor carga por cliente.
3. **Número de eventos**: aumento proporcional ao número de armazéns, devido ao maior número de rotas e movimentações.

---

## 🧱 Estratégias de Robustez

O projeto implementa diversas práticas para garantir a estabilidade do sistema:

- Verificação da abertura de arquivos
- Prevenção contra ponteiros nulos e duplicações
- Balanceamento automático das árvores AVL
- Redimensionamento seguro do vetor de eventos
- Destrutores recursivos para liberação de memória

---

## 📚 Referências

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., Stein, C. *Algoritmos: Teoria e Prática*. 3ª Edição. Elsevier, 2012.
- Slides da disciplina **DCC205/DCC221 – Estruturas de Dados**, UFMG, 2025/1.

---

## ✅ Conclusão

Este trabalho demonstrou a aplicação prática de estruturas balanceadas, modularização e análise assintótica em C++, resultando em um sistema robusto e eficiente para consultas logísticas de pacotes e clientes em um ambiente simulado de armazéns.

A utilização de árvores AVL e vetores dinâmicos permitiu que o sistema mantivesse desempenho consistente mesmo sob grande volume de dados, comprovado pela análise experimental.
