#include "lexer.h"
#include <string.h>
#include <ctype.h>

TOKEN obter_proximo_token(char *codigo) {
    static int pos = 0; //variavel estatica, mantem o valor mesmo com a função sendo finalizada

    TOKEN token;

    while(isspace(codigo[pos])) { //pula pra frente sempre que houver um espaço em branco
        pos++;
    }

    if(codigo[pos] == '\0') { //verifica o fim do arquivo, gera token de end of file
        token.type = TOKEN_EOF;
        return token;
    }

    char char_atual = codigo[pos];

    if(char_atual == '+' || char_atual == '-' || char_atual == '/' || char_atual == '*') { //gera o token de um operador aritmetico
        token.type = TOKEN_ARITMETC_OP;
        token.string[0] = char_atual; token.string[1] = '\0';

        pos++;

        return token;
    }

    if(isdigit(char_atual)) { //gera o token do numero e armazena o valor
        token.type = TOKEN_NUM;
        token.num = 0;

        while(isdigit(codigo[pos])) {
            int digito = codigo[pos] - '0';
            token.num = (token.num * 10) + digito;
            pos++;
        }

        return token;
    }

    if(isalpha(char_atual)) {
        int i = 0;

        while(isalnum(codigo[pos]) || codigo[pos] == '_') {
            token.string[i] = codigo[pos];
            i++;
            pos++;
        }

        token.string[i] = '\0';

        if(strcmp(token.string, "num") == 0) { //gera o token que carateriza o tipo int
            token.type = TOKEN_INT;
            return token;
        }
        else if(strcmp(token.string, "console_ex") == 0) { //gera o token da função printf
            token.type = TOKEN_PRINT;
            return token;
        }
        else { //gera o token do nome da variavel e armazena ele
            token.type = TOKEN_VARNAME;
            return token;
        }
    }

    if(char_atual == ';') { //gera o token de fim de linha
        token.type = TOKEN_EOL;
        pos++;
        return token;
    }

    if(char_atual == '"') { //gera o token da string dentro da função printf
        token.type = TOKEN_TEXT;
        pos++;

        int i = 0;
        while(codigo[pos] != '"' && codigo[pos] != '\0') {
            token.string[i] = codigo[pos];
            i++;
            pos++;
        }
        token.string[i] = '\0';

        if(codigo[pos] == '"') {
            pos++;
        }

        return token;
    }

    token.type = TOKEN_ERROR; //caso não seja encontrado gera um token de erro
    pos++;
    return token;
}
