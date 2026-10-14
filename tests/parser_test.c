#include "../include/parser.h"
#include <stdio.h>

int main(void) {
    char *source = "num test1 10;\n num test2 25 + 5;\n console_ex \"testando o funcionamento\"; "; //codigo de teste na linguagem Vern

    analisador_sintaxico(source); //chamando a função com o codigo como parametro

    for(int i = 0; i < total_nos; i++) {
        if(arvore_sintatica[i].type == NUMBER_INT) {
            printf("nome da variavel: %s \n", arvore_sintatica[i].var_name);
            printf("valor interno: %d\n", arvore_sintatica[i].valor_1);//printa verificando se os valores estão indo para o lugar certo
        }
        if(arvore_sintatica[i].type == OPERATOR_INT) {
            printf("nome da variavel: %s \n", arvore_sintatica[i].var_name);//printa verificando se os valores estão indo para o lugar certo
            printf("valor interno: %d %c %d\n", arvore_sintatica[i].valor_1, arvore_sintatica[i].aritmetic_op, arvore_sintatica[i].valor_2);
        }
        if(arvore_sintatica[i].type == CONSOLE_TEXT) {
            printf("texto interno: %s\n", arvore_sintatica[i].text);//printa verificando se os valores estão indo para o lugar certo
        }
    }

    return 0;
}
