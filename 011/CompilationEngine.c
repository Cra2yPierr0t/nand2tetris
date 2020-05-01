#include"JackTokenizer.h"

typedef enum{
    ND_IF,
    ND_RETURN,
    ND_WHILE,
    ND_FOR,
    ND_BLOCK,
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_EQ,
    ND_NE,
    ND_LT,
    ND_LE,
    ND_ASSIGN,
    ND_LVAR,
    ND_NUM
} NodeType;

typedef struct Node Node;
struct Node {
    NodeType type;
    Node *rhs;
    Node *lhs;
    Node *expr; //condition
    Node *stmt; //stmt
    Stmts_vec *stmts;
    Stmts_vec *args;
    int val;
    char *str;
}
typedef struct Stmts_vec Stmts_vec;
struct Stmts_vec {
    Node *stmt;
    Stmts_vec *next;
}

Stmts_vec *new_ary(){
    Stmts_vec *vec = malloc(sizeof(Stmts_vec));
    vec->next = NULL;
    return vec;
}
void ary_push(Stmts_vec *vec, Node *stmt){
    while(vec->next){
        vec = vec->next;
    }
    vec->next = new_ary();
    vec->next->stmt = stmt;
    return;
}

Node *new_node(NodeType type, Node *lhs, Node *rhs){
    Node *node = malloc(sizeof(Node));
    node->type = type;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val){
    Node *node = malloc(sizeof(Node));
    node->type = NT_NUM;
    node->val = val;
    return node;
}

Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();
Node *num();
Node *ident();

Node *stmt(){
    Node *node;
    if(keyWord() == KW_RETURN){
        advance();
        node->type = ND_RETURN;
        node->expr = expr();
    } else if(keyWord() == KW_IF){
        advance();
        node->type = ND_IF;
        consume_symbol('(');
        node->expr = expr(); 
        consume_symbol(')');
        node->stmt = stmt();
        return node;
    } else if(keyWord() == ND_WHILE){
        advance();
        node->type = ND_WHILE;
        consume_symbol('(');
        node->expr = expr();
        consume_symbol(')');
        node->stmt = stmt();
        return node;
    } else if(keyWord() == ND_FOR){
        //for
    } else if(symbol() == '{'){
        consume_symbol('{');
        node->type = ND_BLOCK;
        node->stmts = new_ary();
        while(symbol() != '}'){
            ary_push(node->stmts, stmt());
        }
        consume_symbol('}');
        return node;
    } else {
        node = expr();
    }
    consume_symbol(';');
    return node;
}
Node *expr(){
    return assign();
}
Node *assign(){
    Node *node = equality();
    if(symbol() == '=')
        node = new_node(ND_ASSIGN, node, assign());
    return node;
}
Node *equality(){
    Node *node = relational();
    while((strncmp("==", identifier(), 2) == 0) || 
          (strncmp("!=", identifier(), 2) == 0)){
        if(strncmp("==", identifier(), 2) == 0){
            advance();
            node = new_node(ND_EQ, node, relational());
        } else if(strncmp("!=", identifier(), 2) == 0){
            advance();
            node = new_node(ND_NE, node, relational());
        } else {
            break;
        }
    }
    return node;
}
Node *relational(){
    Node *node = add();
    while(1){
        if(strncmp("<", identifier, 1) == 0){
            node = new_node(ND_LT, node, add());
            advance();
        } else if(strncmp("<=", identifier, 1) == 0){
            node = new_node(ND_LE, node, add());
            advance();
        } else if(strncmp(">", identifier, 1) == 0){
            node = new_node(ND_LE, node, add());
            advance();
        } else if(strncmp(">=", identifier, 1) == 0){
            node = new_node(ND_LT, node, add());
            advance();
        } else {
            break;
        }
    }
    return node;
}
Node *add(){
    Node *node = mul();
    while(1){
        if(symbol() == '+'){
            node = new_node(ND_ADD, node, mul());
            consume_symbol('+');
        } else if(symbol() == '-'){
            node = new_node(ND_SUB, node, mul());
            consume_symnbol('-');
        } else {
            break;
        }
    }
    return node;
}
Node *mul(){
    Node *node = unary();
    while(1){
        if(symbol() == '*'){
            node = new_node(ND_MUL, node, unary());
            consume_symbol('*');
        } else if(symbol() == '/'){
            node = new_node(ND_DIV, node, unary());
            consume_symbol('/');
        } else {
            break;
        }
    }
    return node;
}
Node *unary(){
    Node *node;
    if(symbol() == '+'){
        node = new_node(ND_ADD, new_node_num(0), primary());
    } else if(symbol() == '-'){
        node = new_node(ND_SUB, new_node_num(0), primary());
    } else {
        node = primary();
    }       
    return node;
}
Node primary(){
    Node *node;
    if(symbol() == '('){
        consume_symbol('(');
        node = expr();
        consume_symbol(')');
    } else if(tokenType() == TT_IDENTIFIER){
        node = new_node_ident(identifier());
        if(symbol() == '('){
            consume_symbol('(');
            consume_symbol(')');
        }
    } else if(tokenType() == TT_INT_CONST){
        node = new_node_num(intVal());
    }
    return node;
}

int main(int argc, char *argv[]){
    token = tokenize(argv[1]);

    int i = 0;
    Node code[100];
    while(!at_eof){
        code[i++] = stmt();
    }

    /*
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
    */
}
