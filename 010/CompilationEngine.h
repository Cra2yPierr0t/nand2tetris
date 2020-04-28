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

void consume_symbol(char);
void compileClass(void);
void classVarDec(void);
void subroutineDec(void);
void parameterList(void);
void subroutineBody(void);
void varDec(void);
void statements(void);
void statement(void);
void letStatement(void);
void ifStatement(void);
void whileStatement(void);
void doStatement(void);
void returnStatement(void);
void expression(void);
void term(void);
void subroutineCall(void);
void expressionList(void);

