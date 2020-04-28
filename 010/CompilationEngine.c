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
    if(symbol() == '{'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }

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

    if(symbol() == '}'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
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
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
    }
    printf("<symbol> %c </symbol>\n", symbol());
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
    if(symbol() == '('){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
        parameterList();
    } else {
        exit(1);
    }
    if(symbol() == ')'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
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
    if(symbol() == '{'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
    while(keyWord() == KW_VAR){
        varDec();
    }
    statements();
    if(symbol() == '}'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
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
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
        printf("<identifier> %s </identifier>\n", identifier());
        advance();
    }
    if(symbol() == ';'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
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
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
        expression();
        if(symbol() == ']'){
            printf("<symbol> %c </symbol>\n", symbol());
            advance();
        } else {
            exit(1);
        }
    }
    if(symbol() == '='){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
    expression();
    if(symbol() == ';'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
    printf("</letStatement>\n");
    return;
}
