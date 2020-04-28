typedef enum {
    ND_CLASS,
    ND_CLASS_VAR_DEC,
    ND_TYPE,
    ND_SUBROUTINE_DEC,
    ND_PARAMETER_LIST,
    ND_SUBROUTINE_BODY,
    ND_VAR_DEC,
    ND_CLASS_NAME,
    ND_SUBROUTINE_NAME,
    ND_VAR_NAME,
    ND_STATEMENTS,
    ND_STATEMENT,
    ND_LET_STATEMENT,
    ND_IF_STATEMENT,
    ND_WHILE_STATEMENT,
    ND_DO_STATEMENT,
    ND_RETURN_STATEMENT,
    ND_EXPRESSION,
    ND_TERM,
    ND_SUBROUTINE_CALL,
    ND_EXPRESSION_LIST,
    ND_OP,
    ND_UNARY_OP,
    ND_KEYWORD_CONSTANT
} NodeKind;

typedef struct Node Node;
struct Node {
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    KeyWord word;
    int val;
    char *str;
};

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

void class(){
    printf("<class>\n\t");
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
    return;
}
    
void classVarDec(){
    printf("<classVarDec>\n\t");
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
    printf("</classVarDec>\n\t");
    advance();
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
    if(keyWord() == 'KW_ELSE'){
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
