#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"JackTokenizer.h"

Token *token;

bool see_reserve_beyond(char *beyond){
    if(strchr(" {}()[].,;=^*/&|<>=~", *beyond) != NULL){
        return true;
    } else {
        return false;
    }
}

Token *new_token(TokenType type, Token *cur, char *str, int len){
    Token *tok = calloc(1, sizeof(Token));

    tok->type = type;
    tok->str = (char *)malloc(sizeof(char) * strlen(str));
    strncpy(tok->str, str, len);
    tok->len = len;
    cur->next = tok;
    return tok;
}

Token *tokenize(char *filename){

    char *line_buffer = (char *)malloc(sizeof(char) * 1024);
    char xml_filename[256];
    FILE* fp_jack, fp_xml;
    if((fp_jack = fopen(filename, "r")) == NULL){
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

    char *addr_buffer;
    
    while(fgets(line_buffer, 1024, fp_jack) != NULL){
        while(*line_buffer){

            if(strncmp(line_buffer, "//", 2) == 0)
                continue;
            if(isspace(*line_buffer)){
                line_buffer++;
            } else if((strncmp(line_buffer, "constructor", 11) == 0) && see_reserve_beyond(line_buffer + 11)){
                line_buffer += 11;
                cur = new_token(TT_KEYWORD, cur, "constructor", 11);
            } else if((strncmp(line_buffer, "function", 8) == 0) && see_reserve_beyond(line_buffer + 11)){
                line_buffer += 8;
                cur = new_token(TT_KEYWORD, cur, "function", 8);
            } else if((strncmp(line_buffer, "boolean", 7) == 0) && see_reserve_beyond(line_buffer + 8)){
                line_buffer += 7;
                cur = new_token(TT_KEYWORD, cur, "boolean", 7);
            } else if((strncmp(line_buffer, "static", 6) == 0) && see_reserve_beyond(line_buffer + 7)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "static", 6);
            } else if((strncmp(line_buffer, "return", 6) == 0) && see_reserve_beyond(line_buffer + 6)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "return", 6);
            } else if((strncmp(line_buffer, "method", 6) == 0) && see_reserve_beyond(line_buffer + 6)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "method", 6);
            } else if((strncmp(line_buffer, "field", 5) == 0) && see_reserve_beyond(line_buffer + 6)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "field", 5);
            } else if((strncmp(line_buffer, "class", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "class", 5);
            } else if((strncmp(line_buffer, "false", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "false", 5);
            } else if((strncmp(line_buffer, "while", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "while", 5);
            } else if((strncmp(line_buffer, "char", 4) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "char", 4);
            } else if((strncmp(line_buffer, "void", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "void", 4);
            } else if((strncmp(line_buffer, "true", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "true", 4);
            } else if((strncmp(line_buffer, "null", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "null", 4);
            } else if((strncmp(line_buffer, "this", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "this", 4);
            } else if((strncmp(line_buffer, "else", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "else", 4);
            } else if((strncmp(line_buffer, "var", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "var", 3);
            } else if((strncmp(line_buffer, "int", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "int", 3);
            } else if((strncmp(line_buffer, "let", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                cur = new_token(TT_KEYWORD, cur, line_buffer, 3);
                line_buffer += 3;
            } else if((strncmp(line_buffer, "do", 2) == 0) && see_reserve_beyond(line_buffer + 2)){
                line_buffer += 2;
                cur = new_token(TT_KEYWORD, cur, "do", 2);
            } else if((strncmp(line_buffer, "if", 2) == 0) && see_reserve_beyond(line_buffer + 2)){
                cur = new_token(TT_KEYWORD, cur, line_buffer, 2);
                line_buffer += 2;
            } else if(addr_buffer = strchr("{}()[].,;+-*/&|<>=~", *line_buffer)){
                cur = new_token(TT_SYMBOL, cur, addr_buffer, 1);
                line_buffer++;
            } else if(isdigit(*line_buffer)){
                cur = new_token(TT_INT_CONST, cur, line_buffer, 0);
                cur->val = strtol(line_buffer, &line_buffer, 10);
            } else if(strncmp(line_buffer, "\"", 1) == 0){
                char *q = line_buffer++;
                while(strncmp(++q, "\"", 1) != 0)
                    ;
                cur = new_token(TT_STRING_CONST, cur, line_buffer, q - line_buffer);
                line_buffer = ++q;
            } else {
                char *p = line_buffer;
                while(strchr(" ()]};+-*/&|<>=,.", *p) == NULL){
                    ++p;
                }
                cur = new_token(TT_IDENTIFIER, cur, line_buffer, p - line_buffer);
                line_buffer = p;
            }
        }
    }

    fclose(fp_jack);
    cur->next = NULL;
    return head.next;
}

bool hasMoreTokens(){
    return token->next != NULL;
}
void advance(){
    token = token->next;
}
TokenType tokenType(){
    return token->type;
}
char *keyWord(){
    return token->str;
}
char symbol(){
    return (token->str)[0];
}
char *identifier(){
    return token->str;
}
int intVal(){
    return token->val;
}
char *stringVal(){
    return token->str;
}

int main(int argc, char *argv[]){
    token = tokenize(argv[1]);

    printf("<tokens>\n");
    do{
        switch(tokenType()){
            case TT_KEYWORD:
                printf("\t<keyword> %s </keyword>\n", keyWord());
                break;
            case TT_SYMBOL:
                printf("\t<symbol> %c </symbol>\n", symbol());
                break;
            case TT_IDENTIFIER:
                printf("\t<identifier> %s </identifier>\n", identifier());
                break;
            case TT_INT_CONST:
                printf("\t<integerConstant> %d\n\t</integerConstant>\n", intVal());
                break;
            case TT_STRING_CONST:
                printf("\t<stringConstant> %s\n\t</stringConstant>\n", stringVal());
                break;
        }
        advance();
    }while(hasMoreTokens());
    printf("</tokens>\n");

    return 0;
}
