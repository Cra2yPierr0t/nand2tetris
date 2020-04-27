typedef enum {
    KW_CLASS,
    KW_METHOD,
    KW_FUNCTION,
    KW_CONSTRUCTOR,
    KW_INT,
    KW_BOOLEAN,
    KW_CHAR,
    KW_VOID,
    KW_VAR,
    KW_STATIC,
    KW_FIELD,
    KW_KET,
    KW_DO,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_RETURN,
    KW_TRUE,
    KW_FALSE,
    KW_NULL,
    KW_THIS
} KeyWord;

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

typedef enum {
    TT_KEYWORD,
    TT_SYMBOL,
    TT_IDENTIFIER,
    TT_INT_CONST,
    TT_STRING_CONST
} TokenType;

typedef struct Token Token;
struct Token {
    TokenType type;
    Token *next;
    char *str;
    int len;
    int val;
};

Token *token;

bool        hasMoreTokens(void);
void        advance(void);
TokenType   tokenType(void);
KeyWord     keyWord(void);
char        symbol(void);
char*       identifier(void);
int         intVal(void);
char*       stringVal(void);

Token *new_token(TokenType type, Token *cur, char *str, int len){
    Token *tok = calloc(1, sizeof(Token));

    tok->type = type;
    tok->str = (char *)malloc(sizeof(char) * strlen(str));
    strncpy(tok->str, str, len);
    tok->len = len;
    cur->next = tok;
    return tok;
}

int main(int argc, char *argv[]){
    char *line_buffer = (char *)malloc(sizeof(char) * 1024);
    char xml_filename[256];
    FILE* fp_jack, fp_xml;
    if((fp_jack = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "ファイルを開けません\n");
        exit(1);
    }
    /*
    xml_filename = strtok(argv[1], ".");
    strcat(xml_filename, ".xml");
    if((fp_xml = fopen(xml_filename, "w")) == NULL){
        fprintf(stderr, "ファイルを開けません\n");
        exit(1);
    }
    */

    Token head;
    head.next = NULL;
    Token *cur = &head;

    while(fgets(line_buffer, sizeof(line_buffer), fp_jack) != NULL){
        while(*line_buffer){
            if(isspace(*line_buffer))
                line_buffer++;

            if(strncmp(line_buffer, "//", 2) == 0)
                continue;
            if(strncmp(line_buffer, "constructor", 11) == 0){
                line_buffer += 11;
                cur = new_token(TT_KEYWORD, cur, "constructor", 11);
            }
            if(strncmp(line_buffer, "function", 8) == 0){
                line_buffer += 8;
                cur = new_token(TT_KEYWORD, cur, "function", 8);
            }
            if(strncmp(line_buffer, "boolean", 7) == 0){
                line_buffer += 7;
                cur = new_token(TT_KEYWORD, cur, "boolean", 7);
            }
            if(strncmp(line_buffer, "static", 6) == 0){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "static", 6);
            }
            if(strncmp(line_buffer, "return", 6) == 0){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "return", 6);
            }
            if(strncmp(line_buffer, "method", 6) == 0){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "method", 6);
            }
            if(strncmp(line_buffer, "field", 5) == 0){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "field", 5);
            }
            if(strncmp(line_buffer, "class", 5) == 0){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "class", 5);
            }
            if(strncmp(line_buffer, "false", 5) == 0){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "false", 5);
            }
            if(strncmp(line_buffer, "while", 5) == 0){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "while", 5);
            }
            if(strncmp(line_buffer, "char", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "char", 4);
            }
            if(strncmp(line_buffer, "void", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "void", 4);
            }
            if(strncmp(line_buffer, "true", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "true", 4);
            }
            if(strncmp(line_buffer, "null", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "null", 4);
            }
            if(strncmp(line_buffer, "this", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "this", 4);
            }
            if(strncmp(line_buffer, "else", 4) == 0){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "else", 4);
            }
            if(strncmp(line_buffer, "var", 3) == 0){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "var", 3);
            }
            if(strncmp(line_buffer, "int", 3) == 0){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "int", 3);
            }
            if(strncmp(line_buffer, "let", 3) == 0){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "let", 3);
            }
            if(strncmp(line_buffer, "do", 2) == 0){
                line_buffer += 2;
                cur = new_token(TT_KEYWORD, cur, "do", 2);
            }
            if(strncmp(line_buffer, "if", 2) == 0){
                line_buffer += 2;
                cur = new_token(TT_KEYWORD, cur, "if", 2);
            }
            char *addr_buffer;
            if(addr_buffer = strchr("{}()[].,;+-*/&|<>=~", *line_buffer++)){
                cur = new_token(TT_SYMBOL, cur, addr_buffer, 1);
            }
            if(isdigit(*line_buffer)){
                cur = new_token(TT_INT_CONST, cur, line_buffer, 0);
                cur->val = strtol(line_buffer, &line_buffer, 10);
            }
            if(strncmp(line_buffer, "\"", 1) == 0){
                char *q = line_buffer++;
                while(strncmp(++q, "\"", 1) != 0)
                    ;
                cur = new_token(TT_STRING_CONST, cur, line_buffer, q - line_buffer);
                line_buffer = ++q;
            }
        }
    }

    fclose(fp_jack);
    return 0;
}
