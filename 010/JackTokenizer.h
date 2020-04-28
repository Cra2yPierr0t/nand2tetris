typedef enum {
    TT_KEYWORD,
    TT_SYMBOL,
    TT_IDENTIFIER,
    TT_INT_CONST,
    TT_STRING_CONST
} TokenType;

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
    KW_LET,
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

typedef struct Token Token;
struct Token {
    TokenType type;
    KeyWord word;
    Token *next;
    char *str;
    int len;
    int val;
};

bool see_reserve_beyond(char *);
Token *new_token(TokenType, Token *, char *, int);
Token *tokenize(char *);

bool        hasMoreTokens(void);
void        advance(void);
TokenType   tokenType(void);
KeyWord     keyWord(void);
char        symbol(void);
char*       identifier(void);
int         intVal(void);
char*       stringVal(void);
