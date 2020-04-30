#include"JackTokenizer.h"

int main(int argc, char *argv[]){
    token = tokenize(argv[1]);

    do {
        switch(tokenType()){
            case TT_KEYWORD:
                printf("<keyword> %s </keyword>\n", stringVal());
                break;
            case TT_SYMBOL:
                printf("<symbol> %c </symbol>\n", symbol());
                break;
            case TT_IDENTIFIER:
                printf("<identifier> %s </identifer>\n", identifier());
                break;
            case TT_INT_CONST:
                printf("<intConst> %d </intConst>\n", intVal());
                break;
            case TT_STRING_CONST:
                printf("<stringConst> %s </stringConst>\n", stringVal());
                break;
            }
        advance();
    } while(!at_eof());
}
