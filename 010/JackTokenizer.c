#include"JackTokenizer.h"

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

            if(isspace(*line_buffer)){
                line_buffer++;
            } else if(strncmp(line_buffer, "//", 2) == 0){
                break;
            } else if((strncmp(line_buffer, "constructor", 11) == 0) && see_reserve_beyond(line_buffer + 11)){
                line_buffer += 11;
                cur = new_token(TT_KEYWORD, cur, "constructor", 11);
                cur->word = KW_CONSTRUCTOR;
            } else if((strncmp(line_buffer, "function", 8) == 0) && see_reserve_beyond(line_buffer + 11)){
                line_buffer += 8;
                cur = new_token(TT_KEYWORD, cur, "function", 8);
                cur->word = KW_FUNCTION;
            } else if((strncmp(line_buffer, "boolean", 7) == 0) && see_reserve_beyond(line_buffer + 8)){
                line_buffer += 7;
                cur = new_token(TT_KEYWORD, cur, "boolean", 7);
                cur->word = KW_BOOLEAN;
            } else if((strncmp(line_buffer, "static", 6) == 0) && see_reserve_beyond(line_buffer + 7)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "static", 6);
                cur->word = KW_STATIC;
            } else if((strncmp(line_buffer, "return", 6) == 0) && see_reserve_beyond(line_buffer + 6)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "return", 6);
                cur->word = KW_RETURN;
            } else if((strncmp(line_buffer, "method", 6) == 0) && see_reserve_beyond(line_buffer + 6)){
                line_buffer += 6;
                cur = new_token(TT_KEYWORD, cur, "method", 6);
                cur->word = KW_METHOD;
            } else if((strncmp(line_buffer, "field", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "field", 5);
                cur->word = KW_FIELD;
            } else if((strncmp(line_buffer, "class", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "class", 5);
                cur->word = KW_CLASS;
            } else if((strncmp(line_buffer, "false", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "false", 5);
                cur->word = KW_FALSE;
            } else if((strncmp(line_buffer, "while", 5) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 5;
                cur = new_token(TT_KEYWORD, cur, "while", 5);
                cur->word = KW_WHILE;
            } else if((strncmp(line_buffer, "char", 4) == 0) && see_reserve_beyond(line_buffer + 5)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "char", 4);
                cur->word = KW_CHAR;
            } else if((strncmp(line_buffer, "void", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "void", 4);
                cur->word = KW_VOID;
            } else if((strncmp(line_buffer, "true", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "true", 4);
                cur->word = KW_TRUE;
            } else if((strncmp(line_buffer, "null", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "null", 4);
                cur->word = KW_NULL;
            } else if((strncmp(line_buffer, "this", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "this", 4);
                cur->word = KW_THIS;
            } else if((strncmp(line_buffer, "else", 4) == 0) && see_reserve_beyond(line_buffer + 4)){
                line_buffer += 4;
                cur = new_token(TT_KEYWORD, cur, "else", 4);
                cur->word = KW_ELSE;
            } else if((strncmp(line_buffer, "var", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "var", 3);
                cur->word = KW_VAR;
            } else if((strncmp(line_buffer, "int", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                line_buffer += 3;
                cur = new_token(TT_KEYWORD, cur, "int", 3);
                cur->word = KW_INT;
            } else if((strncmp(line_buffer, "let", 3) == 0) && see_reserve_beyond(line_buffer + 3)){
                cur = new_token(TT_KEYWORD, cur, line_buffer, 3);
                line_buffer += 3;
                cur->word = KW_LET;
            } else if((strncmp(line_buffer, "do", 2) == 0) && see_reserve_beyond(line_buffer + 2)){
                line_buffer += 2;
                cur = new_token(TT_KEYWORD, cur, "do", 2);
                cur->word = KW_DO;
            } else if((strncmp(line_buffer, "if", 2) == 0) && see_reserve_beyond(line_buffer + 2)){
                cur = new_token(TT_KEYWORD, cur, line_buffer, 2);
                line_buffer += 2;
                cur->word = KW_IF;
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
KeyWord keyWord(){
    return token->word;
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
