/**
 * @file parser.h
 * @brief criador de struturas AST e analisador de ordem da sintax
 * @author pauloemanue127
 * @date 12/10/2026
    */
#ifndef PARSER_H
#define PARSER_H
#define MAX_COMANDOS 1000

typedef enum {
    NUMBER_INT,
    CONSOLE_TEXT,
} COMPLETE_TOKEN;

typedef struct {
    int valor;
    char aritmetic_op;
    char var_name[50];
    char text[200];
    COMPLETE_TOKEN type;
} AST;

extern AST arvore_sintatica[MAX_COMANDOS];
extern int total_nos;

void analisador_sintaxico(char *codigo);

#endif
