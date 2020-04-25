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

int main(int argc, char *argv[]){
    char line_buffer[256];
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
    while(fgets(line_buffer, sizeof(line_buffer), fp_jack) != NULL){
        

    }

    while(hasMoreTokens()){
        advance();
        switch(tokenType()){
            case TT_KEYWORD:
                cur = new_token(TT_KEYWORD, cur, keyWord(), NULL, NULL, NULL);
                break;
            case TT_SYMBOL:
                cur = new_token(TT_SYMBOL, cur, NULL, symbol(), NULL, NULL);
                break;
            case TT_IDENTIFIER:
                cur = new_token(TT_IDENTIFIER, cur, NULL, NULL, identifier(), NULL);
                break;
            case TT_INT_CONST:
                cur = new_token(TT_INT_CONST, cur, NULL, NULL, NULL, intVal());
                break;
            case TT_STRING_CONST:
                cur = new_token(TT_STRING_CONST, cur, NULL, NULL, NULL, NULL, stringVal());
                break;
            default:
                break;
        }
    }

    fclose(fp_jack);
    return 0;
}
