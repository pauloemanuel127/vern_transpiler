/**
 * @file parser.h
 * @brief criador de struturas AST e analisador de ordem da sintax
 * @author pauloemanue127
 * @date 12/10/2026
    */
#ifndef PARSER_H
#define PARSER_H
#define MAX_COMANDOS 1000 /** define o tamanho maximo de tamanhos reconhecidos */

/**
 * @brief Tipos de saida para a função analisador sintaxico
 */
typedef enum {
    PARSER_SUCCESS = 0, /*!< Indicador de sucesso da função */
    PARSER_ERROR_SINTAX, /*!< Indicador de sintaxe  */
    PARSER_ERROR_UNEXPECTED_EOF, /*!< Indicador de erro de EOF efora do momento esperado */
} PARSER_STATUS;

/**
 * @brief Token completo para a struct AST
 */
typedef enum { //Util para o gerador de codigo em C, apagar quando o gerador tiver pronto
    NUMBER_INT, /*!< Token que indica o tipo do ast como int */
    OPERATOR_INT, /*!< Token que indica o tipo do ast como int, e avisa que ocorrerá uma operação aritimetica */
    CONSOLE_TEXT, /*!< Token que indica o tipo do ast como mensagem de terminarl (printf()) */
} COMPLETE_TOKEN;

/**
 * @brief Estrutura responsavel por guardar todas as informações importantes dos tokens, une tudo em blocos maiores
 */
typedef struct { //Vai ser utilizado para a geração em codigo em C, dá o varname, valores, textos e etc.
    int valor_1; /*!<  */
    int valor_2;
    char aritmetic_op;
    char var_name[50];
    char text[200];
    COMPLETE_TOKEN type;
} AST;

extern AST arvore_sintatica[MAX_COMANDOS]; /** Array que armazena os comandos AST */ //Base do gerador de codigo em C
extern int total_nos; /** representa quantidade de comandos feitos e serve para coordenar a organização do array */ //representa indiretamente a quantidade de comandos +1

/**
 * @brief Verifica se o codigo está seguindo o caminho correto, e cria as estruturas AST para o gerador de codigo em C
 * @param codigo A string contendo todo o codigo fonte .vern
 * @return Retorna o status do processo, sendo ele sucesso, erro de sintax ou erro de EOF inesperado
 */
PARSER_STATUS analisador_sintaxico(char *codigo);

#endif
