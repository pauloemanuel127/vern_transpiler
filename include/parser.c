#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AST arvore_sintatica[MAX_COMANDOS];
int total_nos = 0;

PARSER_STATUS analisador_sintaxico(char *codigo) {
    TOKEN token_atual;

    do {
        token_atual = obter_proximo_token(codigo);

        //VERIFICAÇÃO DE DECLARAÇÃO DE VARIAVEL INT:
        if(token_atual.type == TOKEN_INT) {
            token_atual = obter_proximo_token(codigo);

            //TESTA O ERRO, SE PASSAR ARMAZENA O VALOR E CHAMA PROXIMO TOKEN
            if(token_atual.type == TOKEN_EOF) return PARSER_ERROR_UNEXPECTED_EOF;
            if(token_atual.type != TOKEN_VARNAME) return PARSER_ERROR_SINTAX;

            strcpy(arvore_sintatica[total_nos].var_name, token_atual.string);
            token_atual = obter_proximo_token(codigo);

            if(token_atual.type == TOKEN_EOF) return PARSER_ERROR_UNEXPECTED_EOF;
            if(token_atual.type != TOKEN_NUM) return PARSER_ERROR_SINTAX;

            arvore_sintatica[total_nos].valor_1 = token_atual.num;
            token_atual = obter_proximo_token(codigo);

            //VERIFICA ERRO DE FIM DE ARQUIVO SEM TER ; PARA FINALIZAR A DECLARAÇÃO DE VARIAVEL
            if(token_atual.type == TOKEN_EOF) return PARSER_ERROR_UNEXPECTED_EOF;

            //VERIFICA SE A LINHA TERMINA COM ; PARA ACABAR E SALVAR O AST
            if(token_atual.type == TOKEN_EOL) {
                arvore_sintatica[total_nos].type = NUMBER_INT;
                total_nos++;
                continue;
            }
            //CASO TENHA UMA OPERAÇÃO MATÉMATICA SEGUE PARA OUTRA BANDA DE VERIFICAÇÕES DE ERRO
            else if(token_atual.type == TOKEN_ARITMETC_OP) {
                arvore_sintatica[total_nos].aritmetic_op = token_atual.string[0];
                arvore_sintatica[total_nos].type = OPERATOR_INT;
                token_atual = obter_proximo_token(codigo);

                if(token_atual.type == TOKEN_EOF) return PARSER_ERROR_UNEXPECTED_EOF;
                if(token_atual.type != TOKEN_NUM) return PARSER_ERROR_SINTAX;

                arvore_sintatica[total_nos].valor_2 = token_atual.num;
                token_atual = obter_proximo_token(codigo);

                if(token_atual.type == TOKEN_EOF) return PARSER_ERROR_UNEXPECTED_EOF;
                if(token_atual.type != TOKEN_EOL) return PARSER_ERROR_SINTAX;

                total_nos++;
                continue;
            }
            //CASO NÃO SEJA EOL OU NOVA OPERAÇÃO, ERRO DE SINTAX
            else {
                return PARSER_ERROR_SINTAX;
            }
        }


    } while(token_atual.type != TOKEN_EOF);

    return PARSER_SUCCESS;
}
