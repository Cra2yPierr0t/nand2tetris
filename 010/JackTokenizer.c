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
        while(*line_buffer){
            while(isspace(line_buffer))
                line_buffer++;

            if(strncmp(line_buffer, "//", 2) == 0)
                continue;
            if(strncmp(line_buffer, "constructor", 11) == 0){
                line_buffer += 11;
                cur = new_token();
            }
            if(strncmp(line_buffer, "function", 8) == 0){
                line_buffer += 8;
                cur = new_token();
            }
            if(strncmp(line_buffer, "boolean", 7) == 0){
                line_buffer += 7;
                cur = new_token();
            }
            if(strncmp(line_buffer, "static", 6) == 0){
                line_buffer += 6;
                cur = new_token();
            }
            if(strncmp(line_buffer, "return", 6) == 0){
                line_buffer += 6;
                cur = new_token();
            }
            if(strncmp(line_buffer, "method", 6) == 0){
                line_buffer += 6;
                cur = new_token();
            }
            if(strncmp(line_buffer, "field", 5) == 0){
                line_buffer += 5;
                cur = new_token();
            }
            if(strncmp(line_buffer, "class", 5) == 0){
                line_buffer += 5;
                cur = new_token();
            }
            if(strncmp(line_buffer, "false", 5) == 0){
                line_buffer += 5;
                cur = new_token();
            }
            if(strncmp(line_buffer, "while", 5) == 0){
                line_buffer += 5;
                cur = new_token();
            }
            if(strncmp(line_buffer, "char", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "void", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "true", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "null", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "this", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "else", 4) == 0){
                line_buffer += 4;
                cur = new_token();
            }
            if(strncmp(line_buffer, "var", 3) == 0){
                line_buffer += 3;
                cur = new_token();
            }
            if(strncmp(line_buffer, "int", 3) == 0){
                line_buffer += 3;
                cur = new_token();
            }
            if(strncmp(line_buffer, "let", 3) == 0){
                line_buffer += 3;
                cur = new_token();
            }
            if(strncmp(line_buffer, "do", 2) == 0){
                line_buffer += 2;
                cur = new_token();
            }
            if(strncmp(line_buffer, "if", 2) == 0){
                line_buffer += 2;
                cur = new_token();
            }
        }
    }

    fclose(fp_jack);
    return 0;
}
