# Vern Transpiler

Bem-vindo ao projeto do Transpilador da linguagem **Vern**! Este projeto tem como objetivo traduzir código escrito na nossa linguagem customizada (Vern) para código **C** funcional.

O projeto é dividido em módulos clássicos de construção de compiladores. Este README serve como um guia de orientação para a equipe de desenvolvimento.

---

## 🏗️ Arquitetura e Fases do Projeto

O nosso transpilador segue uma arquitetura em pipeline. O código-fonte entra como texto e passa por diversas transformações até virar o código `.c` final.

### ✅ Fase 1: Analisador Léxico (Lexer) - [CONCLUÍDO]
**Responsável por:** Ler o arquivo texto caractere por caractere e agrupá-los em **Tokens** (unidades lógicas como palavras-chave, números, operadores).
*   **Onde está:** `include/lexer.h` e `src/lexer.c`
*   **Status:** A máquina de estados já sabe ignorar espaços, processar números, strings, variáveis e símbolos matemáticos. 

### 🚧 Fase 2: Analisador Sintático (Parser e AST) - [PRÓXIMO PASSO]
**Responsável por:** Receber os tokens do Lexer e verificar se a ordem deles faz sentido (validação gramatical). Além disso, deve construir a **Árvore de Sintaxe Abstrata (AST)**.
*   **O que a equipe precisa fazer:**
    1.  Criar o arquivo `include/parser.h` contendo as `structs` que representam os nós da árvore. Teremos nós diferentes para "Declaração de Variável", "Comando de Print", etc. Recomenda-se o uso de `union` na struct do nó para economizar memória.
    2.  Criar o arquivo `src/parser.c`. Ele terá funções como `parse_variavel()` ou `parse_print()`.
    3.  A lógica base é consumir um token (chamando `obter_proximo_token()`) e verificar se o próximo token é o esperado. Se não for, emite um *Syntax Error*. Se for, preenche a `struct` da AST e retorna esse nó.
    4.  O resultado final do Parser deve ser uma lista ou um nó raiz da AST, pronta para ser lida pela próxima etapa.
    5. Criar um teste

### 🔍 Fase 3: Analisador Semântico (Opcional, mas recomendado) - [FUTURO]
**Responsável por:** Garantir as lógicas de negócio do código.
*   **O que a equipe precisa fazer:**
    1.  Criar uma **Tabela de Símbolos** (geralmente um array ou hash map) para registrar as variáveis assim que elas são declaradas.
    2.  Fazer uma varredura na AST construída pelo Parser.
    3.  Se encontrar um uso de variável, verificar na tabela se ela foi previamente declarada.
    4.  Se encontrar re-declaração da mesma variável, emitir erro semântico.
    5.  Garantir que a tipagem faça sentido (impedir manipulações inválidas de dados).
    6. Criar um teste

###   Fase 4: Geração de Código (Code Generator) - [FUTURO]
**Responsável por:** Transformar a nossa AST em código **C** puro e funcional.
*   **O que a equipe precisa fazer:**
    1.  Criar o módulo `codegen.c` e `codegen.h`.
    2.  A função principal receberá a lista de nós da AST e um arquivo de saída (`FILE *out`).
    3.  Fazer um laço iterando por todos os nós da AST.
    4.  Usar um bloco `switch(no->type)` para descobrir qual é o comando e traduzi-lo para C.
    5.  Exemplo para `NODE_VAR_DECLARATION` (ex: `num idade 42;`), emitir: `fprintf(out, "int %s = %d;\n", no->nome, no->valor);`.
    6.  Exemplo para `NODE_PRINT` (ex: `console_ex "A idade é: %idade";`), processar a string, converter o padrão das variáveis (ex: de `%idade` para `%d`) e
    emitir um `printf` válido em C.
    7. Criar um teste

###   Fase 5: Organizar o main para receber os arquivos de codigo (Main) - [FUTURO]
**Responsável por:** Receber o arquivo de codigo e usar dos headers criados para fazer o processo de transpilação para **C**.
* **O que o responsavel precisa fazer:**
    1. Criar o main.c na pasta src.
    2. Desenvolver a função main para receber o arquivos na execução.
    3. Criar uma função auxiliar que lê o texto do arquivo e transforma numa string.
    4. Criar um teste

###   Fase 6: Fazer a parte da compilação do arquivo .c para criar o executavel do codigo transpilado (Main) - [FUTURO]
**Responsável por:** Criar uma maneira de compilar diretamente o arquivo.c gerado para assim fazer a transpilação do codigo em vern diretamente para executavel.
*  **Oque o responsavel precisa fazer:**
    **EM CONSTRUÇÃO**

### Fase 7: Atualizar o README para documentar a sintax da linguagem - [FUTURO]
---

## 🛠️ Regras de Colaboração

Para quem vai assumir as próximas tarefas, sigam estas diretrizes:

1.  **Mantenha o Lexer "Burro":** Qualquer validação de contexto ou formatação complexa de strings deve ser feita no Parser ou no Code Generator.
2.  **Documentação:** Usem o padrão **Doxygen** (`/** ... */`) nos arquivos `.h` para documentar structs, enums e funções públicas. Códigos internos nos arquivos `.c` usam comentários padrão (`//`).
3.  **Testes:** Adicionem códigos de testes rápidos na pasta `testes/` sempre que um novo módulo ou funcionalidade complexa for concluída.
4.  **Cuidado com Vazamento de Memória:** Como a construção da Árvore Sintática (AST) exigirá alocações dinâmicas, o Parser precisará usar `malloc`. Certifiquem-se de criar também uma função para liberar a memória de todos os nós (um `free_ast()`) no final do processo para evitar *memory leaks*.

Boa sorte a todos na construção do transpilador da linguagem Vern!
