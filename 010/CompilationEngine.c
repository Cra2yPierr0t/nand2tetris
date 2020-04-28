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
        classVarDec();
    }
    while(1){
        subroutineDec();
    }

    if(symbol() == '}'){
        printf("<symbol> %c </symbol>\n", symbol());
        advance();
    } else {
        exit(1);
    }
}
    
void classVarDec(){
        if((keyWord() == KW_STATIC) || (keyWord() == KW_FIELD)){
            
        } else {
            break; 
        }
}
void subroutineDec(){
        if((keyWord() == KW_CONSTRUCTOR) || (keyWord() == KW_FUNCTION) || (keyWord() == KW_METHOD)){

        } else {
            break;
        }
}
