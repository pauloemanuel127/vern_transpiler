#ifndef LEXER_H
#define LEXER_H

typedef enum {
    INT_NUM,
    PRINTF_FUNC,
    TEXT,
    ARITMETC_OP,
    NUMBER,
} TOKEN_TYPE;

typedef struct {
    int num;
    char string[50];
    TOKEN_TYPE type;
} TOKEN;

#endif
