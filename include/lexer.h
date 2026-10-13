/**
 * @file lexer.h
 * @brief analisador lexico da linguagem fictia vern(criada por mim)
 * @author pauloemanuel127
 * @date 08/10/2026
    */
#ifndef LEXER_H
#define LEXER_H

/**
 * @brief Tipos de tokens que a linguagem reconhece no seu analisador lexico
 */
typedef enum {
    TOKEN_INT, /*!< palavra-chave 'num' para declarar inteiros */
    TOKEN_PRINT, /*< palavra-chave 'console_ex' para declarar printf */
    TOKEN_TEXT, /*!< texto literal delimitado pelas aspas */
    TOKEN_ARITMETC_OP, /*!< operadores matematicos aritmeticos  */
    TOKEN_NUM, /*!< valor numerico literal da variavel */
    TOKEN_EOF, /*!< token representante do fim do arquivo */
    TOKEN_VARNAME, /*!< nome da variavel criada */
    TOKEN_EOL, /*!< palavra-chave ';' representa o fim de uma linha */
    TOKEN_ERROR /*!< token representando sintax não reconhecida */
} TOKEN_TYPE;

/**
 * @brief estrutura que armazena os tokens lidos do codigo,
 *  caso seja uma string ou valor numerico armazena também o valor
 */
typedef struct {
    int num; /*!< valor numerico da variavel, armazenado quando type = TOKEN_NUM */
    char string[200]; /*!< texto literal quando type = TOKEN_TEXT */
    TOKEN_TYPE type; /*!< tipo do token, define sua funcionalidade no codigo já alterado */
} TOKEN;

/**
 * @brief Cria o novo token com base no codigo original, segue sempre de onde parou por ter a variavel pos como estatica.
 * @param codigo A string contendo todo o codigo fonte .vern
 * @return O proximo token gerado de acordo como o codigo
 */
TOKEN obter_proximo_token(char *codigo);

#endif
