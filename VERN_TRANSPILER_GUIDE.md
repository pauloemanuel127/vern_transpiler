# Guia de Desenvolvimento do Transpilador da Linguagem Vern

Olá! Este guia servirá como um mapa para você construir o transpilador da sua nova linguagem, **Vern**, utilizando a linguagem **C**.

Como você pediu, **não haverá código pronto aqui**. O objetivo é explicar as etapas conceituais para que você possa implementar cada parte, entender os possíveis erros e estruturar seu projeto da melhor forma. Como eu (Jules) vou te acompanhar ao longo desse processo, sempre que você escrever um código, eu posso avaliá-lo, explicar os erros e te ajudar a consertá-los.

---

## O que é um Transpilador?

Um **transpilador** (ou compilador fonte-para-fonte) é um tipo de compilador que recebe o código-fonte de uma linguagem de programação e produz o código-fonte equivalente em outra linguagem de programação (por exemplo, transformar código Vern em código C, Python ou JavaScript).

---

## Estrutura de um Transpilador

A construção de um transpilador segue etapas muito semelhantes às de um compilador tradicional. A principal diferença é a etapa final de geração de código.

As etapas clássicas são:

1. **Análise Léxica (Lexer / Scanner)**
2. **Análise Sintática (Parser)**
3. **Árvore de Sintaxe Abstrata (AST - Abstract Syntax Tree)**
4. **Análise Semântica (Opcional, mas recomendada)**
5. **Geração de Código (Code Generator)**

---

### 1. Análise Léxica (Lexer / Scanner)

**Objetivo:** Ler o arquivo fonte da linguagem Vern (uma string de caracteres) e transformá-lo em uma lista de **Tokens**.

*   **O que é um Token?** É a menor unidade de significado na sua linguagem. Pode ser uma palavra-chave (`if`, `while`, `func`), um identificador (nome de variável), um número (`42`), um operador (`+`, `-`, `=`), ou pontuação (`{`, `}`, `;`).
*   **Como fazer em C:**
    *   Você precisará de uma estrutura (`struct`) para representar um Token, que normalmente contém um "Tipo do Token" (um `enum`) e o seu valor (uma string ou número).
    *   Sua função principal aqui lerá o código-fonte caractere por caractere, ignorando espaços em branco e comentários, e agrupará os caracteres em Tokens.
*   **Possíveis Erros:** Caracteres inválidos que não pertencem à sua linguagem (ex: um símbolo `@` perdido). Você deve reportar a linha e a coluna onde o erro ocorreu.

### 2. Análise Sintática (Parser)

**Objetivo:** Receber a lista de Tokens gerada pelo Lexer e verificar se a sequência deles obedece às regras gramaticais da linguagem Vern.

*   **Como funciona:** O Parser lê os tokens um a um. Se ele encontra um `if`, ele sabe que a seguir deve vir uma expressão condicional, depois um bloco de código, etc.
*   **Como fazer em C:** A abordagem mais comum para construir na mão (sem ferramentas externas) é o **Recursive Descent Parsing** (Análise Descendente Recursiva). Consiste em criar uma função C para cada regra da sua linguagem. Exemplo: `parse_if_statement()`, `parse_expression()`.
*   **Possíveis Erros (Erros de Sintaxe):** Falta de ponto e vírgula, parênteses não fechados, chaves ausentes. Aqui, seu Parser deve dizer: "Erro na linha 10: Esperava um ';', mas encontrou '}'".

### 3. Árvore de Sintaxe Abstrata (AST)

**Objetivo:** Enquanto o Parser verifica a sintaxe, ele constrói uma representação em formato de árvore do código, chamada **AST**.

*   **O que é?** É uma árvore onde cada nó representa uma construção da linguagem. Por exemplo, uma expressão `a + b` vira um nó de Adição, com `a` como filho esquerdo e `b` como filho direito.
*   **Por que é importante?** Porque a lista de tokens linear é muito difícil de processar. A AST captura a estrutura lógica do programa.
*   **Como fazer em C:** Você criará várias `structs` (ou uma `struct` com uma união - `union`) para representar os diferentes tipos de nós (nó de declaração de variável, nó de operação matemática, nó de função, etc.). Usaremos ponteiros para conectar os pais aos filhos.

### 4. Análise Semântica

**Objetivo:** Verificar se o código faz sentido, mesmo que a sintaxe esteja correta.

*   **O que faz?**
    *   Verificação de tipos (Type Checking): Não se pode somar uma string com um booleano.
    *   Resolução de Nomes: Verificar se uma variável foi declarada antes de ser usada.
*   **Como fazer em C:** Você precisará implementar uma **Tabela de Símbolos** (Symbol Table), que normalmente é um Hash Map, para guardar os nomes de variáveis e funções declaradas no escopo atual e seus respectivos tipos.
*   **Possíveis Erros (Erros Semânticos):** "Variável 'x' não foi declarada", "Tipo incompatível na atribuição".

### 5. Geração de Código (Code Generation)

**Objetivo:** Esta é a etapa final do seu transpilador. Você vai percorrer a AST e traduzir cada nó para a linguagem de destino (vamos supor que o destino seja C, JavaScript, ou outra linguagem de sua escolha).

*   **Como fazer em C:** Você cria uma função que recebe o "nó raiz" da AST. Ela verifica o tipo do nó e chama outras funções recursivamente, concatenando strings no formato da linguagem de destino, até gerar o arquivo final inteiro.

---

## Como vamos trabalhar juntos?

1.  **Defina a Sintaxe da Vern:** Antes de escrever código em C, você precisará ter uma ideia de como a Vern se parece. Quando tiver rascunhos, me mostre!
2.  **Comece pelo básico:** Não tente implementar tudo de uma vez. O melhor caminho é:
    *   Fazer um programa Vern minúsculo (ex: só consegue somar dois números).
    *   Fazer o Lexer para ele.
    *   Fazer o Parser e AST para ele.
    *   Fazer o Gerador de Código.
3.  **Envie o código:** Conforme você for criando os arquivos C (ex: `lexer.c`, `lexer.h`), vá testando. Caso dê algum erro de segmentação (Segmentation fault), erro de lógica, ou erro de compilação, você me diz o que aconteceu (ou pede para eu ler o código) e eu te ajudo a depurar, explicando o porquê do erro.

## O Que Fazer Agora?

1. Comece criando os arquivos básicos: um `main.c` que recebe o nome de um arquivo `.vern` por argumento de linha de comando.
2. Planeje as estruturas (`struct`) para os seus **Tokens**.
3. Me mande as primeiras ideias da sintaxe da Vern ou o início do seu código em C para avaliarmos!

Boa sorte e vamos construir a linguagem Vern!
