#include <stdio.h>
#include "../include/lexer.h"

int main() {
    char *meu_programa = "num idade 42;\n console_ex \"A idade e:\";"; //string simulando o input do arquivo

    printf("Analisando o codigo VERN:\n%s\n\n", meu_programa);

    TOKEN t; //token base

    do {
        t = obter_proximo_token(meu_programa); //gerando os tokens reais

        printf("Tipo: %d", t.type); //exibe o tipo(numerico) do token

        if (t.type == TOKEN_NUM) {
            printf(" | Valor NUMERICO: %d\n", t.num); //exibe o valor numero demonstrando o funcionamento
        } else if (t.type == TOKEN_TEXT) {
            printf(" | Valor TEXTO: %s\n", t.string); //exibe o valor interno da string pra demonstrar o funcionamento
        } else if (t.type == TOKEN_VARNAME) {
            printf(" | Nome da VARIAVEL: %s\n", t.string); //exibe o nome da variavel
        } else {
            printf("\n");
        }

    } while (t.type != TOKEN_EOF); //para se o token gerado for o fim do arquivo

    return 0;
}
