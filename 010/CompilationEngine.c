#include"JackTokenizer.h"
#include"CompilationEngine.h"

void consume_symbol(char sym){
    if(symbol() == sym){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
        return;
    } else {
        fprintf(stderr, "%cが不足しています\n", sym);
        exit(1);
    }
}

void compileClass(){
    printf("<class>\n");
    if(keyWord() == KW_CLASS){
        printf("<keyword> %s </keyword>\n", stringVal());
        advance();
    } else {
        exit(1);
    }
    if(tokenType() == TT_IDENTIFIER){
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
    }   
    consume_symbol('{');

    while(1){
        if((keyWord() == KW_STATIC) || (keyWord() == KW_FIELD)){
            classVarDec();
        } else {
            break;
        }
    }
    while(1){
    if((keyWord() == KW_CONSTRUCTOR) || (keyWord() == KW_FUNCTION) || (keyWord() == KW_METHOD)){ 
            subroutineDec();
        } else {
            break;
        }
    }
    consume_symbol('}');
    printf("</class>\n");
    return;
}
    
void classVarDec(){
    printf("<classVarDec>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<identifier> %s </identifier>\n", identifier());
    advance();
    while(symbol() != ';'){
        consume_symbol(',');
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
    }
    consume_symbol(';');
    printf("</classVarDec>\n");
    return;
}

void subroutineDec(){
    printf("<subroutineDec>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<identifier> %s </identifier>\n", identifier());
    advance();
    consume_symbol('(');
    parameterList();
    consume_symbol(')');
    subroutineBody();
    printf("</subroutineDec>\n");
    return;
}

void parameterList(){
    if(symbol() == ')'){
        return;
    } else {
        printf("<parameterList>\n");
        printf("<keyword> %s </keyword>\n", stringVal());
        advance();
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
        while(1){
            if(symbol() == ','){
                printf("<symbol> %c </symbol>\n", symbol());
                advance();
                printf("<keyword> %s </keyword>\n", stringVal());
                advance();
                printf("<identifier> %s </identifier>\n", identifier());
                advance();
            } else {
                break;
            }
        }
        printf("</parameterList>\n");
        return;
    }
}

void subroutineBody(){
    printf("<subroutineBody>\n");
    consume_symbol('{');
    while(keyWord() == KW_VAR){
        varDec();
    }
    statements();
    consume_symbol('}');
    printf("</subroutineBody>\n");
    return;
}
void varDec(){
    printf("<varDec>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<identifier> %s </identifier>\n", identifier());
    advance();
    while(symbol() == ','){
        consume_symbol(',');
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
    }
    consume_symbol(';');
    printf("</varDec>\n");
    return;
}

void statements(){
    printf("<statements>\n");
    while(symbol() != '}'){
        statement();
    }
    printf("</statements>\n");
    return;
}

void statement(){
    printf("<statement>\n");
    if(keyWord() == KW_LET){
        letStatement();
    } else if(keyWord() == KW_IF){
        ifStatement();
    } else if(keyWord() == KW_WHILE){
        whileStatement();
    } else if(keyWord() == KW_DO){
        doStatement();
    } else if(keyWord() == KW_RETURN){
        returnStatement();
    } else {
        exit(1);
    }
    printf("</statement>\n");
    return;
}

void letStatement(){
    printf("<letStatement>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<identifier> %s </identifier>\n", identifier());
    advance();
    if(symbol() == '['){
        consume_symbol('[');
        expression();
        consume_symbol(']');
    }
    consume_symbol('=');
    expression();
    consume_symbol(';');
    printf("</letStatement>\n");
    return;
}

void ifStatement(){
    printf("<ifStatement>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    consume_symbol('(');
    expression();
    consume_symbol(')');
    consume_symbol('{');
    statements();
    consume_symbol('}');
    if(keyWord() == KW_ELSE){
        printf("<keyword> %s </keyword>\n", stringVal());
        advance();
        consume_symbol('{');
        statements();
        consume_symbol('}');
    }
    printf("</ifStatement>\n");
    return;
}

void whileStatement(){
    printf("<whileStatement>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    consume_symbol('(');
    expression();
    consume_symbol(')');
    consume_symbol('{');
    statements();
    consume_symbol('}');
    printf("</whileStatement>\n");
    return;
}

void doStatement(){
    printf("<doStatement>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    printf("<identifier> %s </identifier>\n", identifier());
    advance();
    subroutineCall();
    consume_symbol(';');
    printf("</doStatement>\n");
    return;
}

void returnStatement(){
    printf("<returnStatement>\n");
    printf("<keyword> %s </keyword>\n", stringVal());
    advance();
    if(symbol() != ';'){
        expression();
    }
    consume_symbol(';');
    printf("</returnStatement>\n");
    return;
}

void expression(){
    printf("<expression>\n");
    term();
    while((symbol() == '+') || 
          (symbol() == '-') ||
          (symbol() == '*') ||
          (symbol() == '/') ||
          (symbol() == '&') ||
          (symbol() == '|') ||
          (symbol() == '<') ||
          (symbol() == '>') || 
          (symbol() == '=')){
                consume_symbol(symbol());
                term();
          }
    printf("</expression>\n");
    return;
}

void term(){
    printf("<term>\n");
    if(tokenType() == TT_INT_CONST){
        printf("<integerConstant> %d </integerConstant>\n", intVal());
        advance();
    } else if(tokenType() == TT_STRING_CONST){
        printf("<stringConstant> %s </stringConstant>\n", stringVal());
        advance();
    } else if(tokenType() == TT_KEYWORD) {
        printf("<keyword> %s </keyword>\n", stringVal());
        advance();
    } else if(tokenType() == TT_SYMBOL) {
        if(symbol() == '(') {
            consume_symbol('(');
            expression();
            consume_symbol(')');
        } else if((symbol() == '-') || (symbol() == '~')) {
            consume_symbol(symbol());
            term();
        } else {
            exit(1);
        }
    } else {
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
        if(symbol() == '['){
            consume_symbol('[');
            expression();
            consume_symbol(']');
        } else if((symbol() == '(') || symbol() == '.'){
            subroutineCall();
        } else {
        }
    }
    printf("</term>\n");
    return;
}

void subroutineCall(){
    if(symbol() == '('){
        consume_symbol('(');
        expressionList();
        consume_symbol(')');
    } else {
        consume_symbol('.');
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
        consume_symbol('(');
        expressionList();
        consume_symbol(')');
    }
    return;
}

void expressionList(){
    if(symbol() != ')'){
        expression();
        while(symbol() == ','){
            consume_symbol(',');
            expression();
        }
    }
    return;
}
