//usage ./Assembler filename.asm
//シンボルは普通変数として利用しないのでアドレスが被ってもいい
char filename[512];

#define COMMAND_SIZE 512

#define A_COMMAND 0
#define C_COMMAND 1
#define SYMBOL 2

#define TRUE 1
#define FAULSE 0

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int command_type;       //A_COMMAND C_COMMAND SYMBOL
    char dest[COMMAND_SIZE];
    char comp[COMMAND_SIZE];
    char jump[COMMAND_SIZE];
    char symbol[COMMAND_SIZE];
    char address[COMMAND_SIZE];
    }parsed;

typedef struct {
    char str[1024];
    }string;

void Converter(char *,char *);       //変換器 アセンブラ本体

parsed Parser(char *);          //パースするやつ
int command_type(char *);     //現在参照してるコマンドのタイプを調べる ex)A命令 C命令 シンボル
string dest(char *);            //C命令のdest部分を返す     
string comp(char *);            //C命令のcomp部分を返す     dest=comp;jump
string jump(char *);            //C命令のjump部分を返す

string Code(parsed);            //コマンドをバイナリに変換するやつ
string dest_bin(char *);        //C命令のdest部分をバイナリに変換する
string comp_bin(char *);        //C命令のcomp部分をバイナリに変換する
string jump_bin(char *);        //C命令のjump部分をバイナリに変換する

string SymbolTable(char *);     //シンボル扱うやつ
void generate_table();
void addEntry(char *);        //テーブルにシンボルとアドレスのペアを追加
int contain(char *);        //与えられたシンボルはテーブルに存在するか？
int getAddress(char *);      //与えられたシンボルに対応するアドレスを返す
string address_binarizer(int);
void generate_symboltableV2();

int main(int argc,char *argv[]){

    strcpy(filename,argv[1]);

    generate_symboltableV2();

    FILE *asm_file,*bin_file;
    char command[1024];     //コマンド[注意]1024文字以上の変数名を使われると死ぬ
    char command_bin[1024]; //バイナリ
    char nullnull[1024];

    strcpy(nullnull,"\0");
    
    asm_file = fopen(argv[1],"r");
    if(asm_file == NULL){          //ファイル名読み込み
        perror("[usage] ./Assembler filename.asm\n");   //エラー処理
        exit(EXIT_FAILURE);
        }

    
    char hackfilename[1024] = {"\0"};
    strcpy(hackfilename,argv[1]);
    hackfilename[strlen(hackfilename) - 3] = 'h';
    hackfilename[strlen(hackfilename) - 2] = 'a';
    hackfilename[strlen(hackfilename) - 1] = 'c';
    hackfilename[strlen(hackfilename)] = 'k';
    hackfilename[strlen(hackfilename) + 1] = '\0';

    bin_file = fopen(hackfilename,"w+");
    if(bin_file == NULL){
        perror("cannot open/make filename.hack file\n");
        exit(EXIT_FAILURE);
        }

    while(fgets(command,1024,asm_file) != NULL){        //コマンドを行ごとに読み込む ファイル終端に達したら終了
        printf("converting...\n");
        Converter(command,command_bin);
        if(strcmp(command_bin,"\0") != 0){
            command_bin[strlen(command_bin)] = '\0';
            fputs(command_bin,bin_file);                    //.hackファイルに書き込む
            }
        }
    
    fclose(asm_file);
    fclose(bin_file);

    return 0;
    }

void Converter(char *command,char *command_bit){
    parsed x;

    x = Parser(command);
    strcpy(command_bit,Code(x).str);
    }

parsed Parser(char *command){     //MEMO ;とか=とかで考えると良さそう
    parsed x;
    x.command_type = command_type(command);

    if(x.command_type == SYMBOL ){
        strcpy(x.symbol,SymbolTable(command).str);
        strcpy(x.dest,"\0");
        strcpy(x.comp,"\0");
        strcpy(x.jump,"\0");
        strcpy(x.address,"\0");
        return x;
    }else if(x.command_type == A_COMMAND){
        strcpy(x.address,SymbolTable(command).str);
        strcpy(x.dest,"\0");
        strcpy(x.comp,"\0");
        strcpy(x.jump,"\0");
        strcpy(x.symbol,"\0");
        return x;
    }else if(x.command_type == C_COMMAND){  //ここはelseで省略可
        strcpy(x.dest,dest(command).str);
        strcpy(x.comp,comp(command).str);
        strcpy(x.jump,jump(command).str);
        strcpy(x.address,"\0");
        strcpy(x.symbol,"\0");
        return x;
        }
    }

int command_type(char *command){
    if(command[0] == '@'){
        return A_COMMAND;
    }else if(command[0] == '('){
        return SYMBOL;
    }else{
        return C_COMMAND;
        }
    }

string dest(char *command){

    int i=0;
    string dest;

    while(command[i] != '=' && command[i] != ';'){  //配列上の=か;の位置を特定する
                i++;
    }

    if(command[i] == '='){                          //;だったらjump命令なのでNULLを挿れる
        for(int j=0;j<i;j++){
            dest.str[j] = command[j];
            }
    }else{
        strcpy(dest.str,"NNN");
    }
        
        return dest;
    }

string comp(char *command){       //;と=で処理を分ける
    int i=0;
    int k=0;
    char null_null[512] = {"\0"};
    string comp;
    strcpy(comp.str,null_null);

    while(command[i] != '=' && command[i] != ';'){
        i++;
    }

    if(command[i] == '='){
        for(int j=i+1;j<=(strlen(command)-1);j++){ 
            comp.str[k]=command[j];
            k++;
            }
        comp.str[strlen(comp.str)-1] = '\0';
    }else{
        for(int j=0;j<i;j++){
            comp.str[j] = command[j];
            }
        comp.str[i] = '\0'; //change
    }
    return comp;
    }

string jump(char *command){
    int i=0;
    int k=0;
    string jump;

    while(command[i] != ';' && command[i] != '='){
        i++;
    }

    if(command[i] == ';'){
        for(int j=i+1;j<=(strlen(command)-1);j++){
            jump.str[k]=command[j];
            k++;
        }
    }
    jump.str[strlen(jump.str)-1] = '\0';
    return jump;
    }

string Code(parsed x){            //111a cccc ccdd djjj
    string bins;
    char bin[COMMAND_SIZE]={"\0"};
    if(x.command_type == C_COMMAND){
        strcpy(bin,"111");
        strcat(bin,comp_bin(x.comp).str);
        strcat(bin,dest_bin(x.dest).str);
        strcat(bin,jump_bin(x.jump).str);
        bin[strlen(bin)] = '\n';            //改行コードをケツに挿れる
    }else if(x.command_type == SYMBOL){
        strcpy(bin,"\0");
    }else if(x.command_type == A_COMMAND){
        strcpy(bin,x.address);
    }
    strcpy(bins.str,bin);
    return bins;
    }

string comp_bin(char *comp){
    char c[9]={"\0"};
    if(strcmp(comp,"0") == 0){
        strcpy(c,"0101010");
    }else if(strcmp(comp,"1") == 0){
        strcpy(c,"0111111");
    }else if(strcmp(comp,"-1") == 0){
        strcpy(c,"0111010");
    }else if(strcmp(comp,"D") == 0){
        strcpy(c,"0001100");
    }else if(strcmp(comp,"A") == 0){
        strcpy(c,"0110000");
    }else if(strcmp(comp,"!D") == 0){
        strcpy(c,"0001101");
    }else if(strcmp(comp,"!A") == 0){
        strcpy(c,"0110001");
    }else if(strcmp(comp,"-D") == 0){
        strcpy(c,"0001111");
    }else if(strcmp(comp,"-A") == 0){
        strcpy(c,"0110011");
    }else if(strcmp(comp,"D+1") == 0){
        strcpy(c,"0011111");
    }else if(strcmp(comp,"A+1") == 0){
        strcpy(c,"0110111");
    }else if(strcmp(comp,"D-1") == 0){
        strcpy(c,"0001110");
    }else if(strcmp(comp,"A-1") == 0){
        strcpy(c,"0110010");
    }else if(strcmp(comp,"D+A") == 0){
        strcpy(c,"0000010");
    }else if(strcmp(comp,"D-A") == 0){
        strcpy(c,"0010011");
    }else if(strcmp(comp,"A-D") == 0){
        strcpy(c,"0000111");
    }else if(strcmp(comp,"D&A") == 0){
        strcpy(c,"0000000");
    }else if(strcmp(comp,"D|A") == 0){
        strcpy(c,"0010101");
    }else if(strcmp(comp,"M") == 0){
        strcpy(c,"1110000");
    }else if(strcmp(comp,"!M") == 0){
        strcpy(c,"1110000");
    }else if(strcmp(comp,"-M") == 0){
        strcpy(c,"1110011");
    }else if(strcmp(comp,"M+1") == 0){
        strcpy(c,"1110111");
    }else if(strcmp(comp,"M-1") == 0){
        strcpy(c,"1110010");
    }else if(strcmp(comp,"D+M") == 0){
        strcpy(c,"1000010");
    }else if(strcmp(comp,"D-M") == 0){
        strcpy(c,"1010011");
    }else if(strcmp(comp,"M-D") == 0){
        strcpy(c,"1000111");
    }else if(strcmp(comp,"D&M") == 0){
        strcpy(c,"1000000");
    }else if(strcmp(comp,"D|M") == 0){
        strcpy(c,"1010101");
    }
    string ac;
    printf("comp = %s\n",comp);
    strcpy(ac.str, c);
    return ac;
}

string dest_bin(char *dest){
    char d[4]={"\0"};
    char A='0';
    char M='0';
    char D='0';
    for(int i=0;i<strlen(dest);i++){
        if(dest[i] == 'A'){
            A = '1';
        }else if(dest[i] == 'M'){
            M = '1';
        }else if(dest[i] == 'D'){
            D = '1';
        }
    }

    d[0] = A;
    d[1] = D;
    d[2] = M;
    d[3] = '\0';
    
    string dstru;
    strcpy(dstru.str,d);
    return dstru;
    }

string jump_bin(char *jump){
    char j[4] = "000";
    
    if(strcmp(jump,"JGT") == 0){
        strcpy(j,"001");
    }else if(strcmp(jump,"JEQ") == 0){
        strcpy(j,"010");
    }else if(strcmp(jump,"JGE") == 0){
        strcpy(j,"011");
    }else if(strcmp(jump,"JLT") == 0){
        strcpy(j,"100");
    }else if(strcmp(jump,"JNE") == 0){
        strcpy(j,"101");
    }else if(strcmp(jump,"JLE") == 0){
        strcpy(j,"110");
    }else if(strcmp(jump,"JMP") == 0){
        strcpy(j,"111");
    }
    string jjjj;
    strcpy(jjjj.str,j);
    return jjjj;
}

string SymbolTable(char *command){
    int address = 0;
    string address_str;
    if(command[0] == '('){
        strcpy(address_str.str,"\0");
        return address_str;
    }else if(command[0] == '@'){
        command[0] = '(';
        command[strlen(command) - 1] = ')';
        if(contain(command) == TRUE){
            address = getAddress(command);
            strcpy(address_str.str,address_binarizer(address).str);
            return address_str;
        }else if(contain(command) == FAULSE){
            perror("[ERROR]unknown\n");
            exit(EXIT_FAILURE);
        }
    }
}

void generate_table(){
    FILE *symboltable;
    symboltable = fopen("symboltable","w+");
    if(symboltable == NULL){
        perror("Can not make/read/write symboltable\n");
        exit(EXIT_FAILURE);
        }
    fclose(symboltable);
}

void addEntry(char *command){
    FILE *asm_file,*symboltable;
    char buffer[1024],command_symbolized[1024];
    int counter = 0;
    asm_file = fopen(filename,"r");
    symboltable = fopen("symboltable","a+");
    if(asm_file == NULL || symboltable == NULL){
        perror("Can not open asm_file/symboltable\n");
        exit(EXIT_FAILURE);
        }

    while(fgets(buffer,1024,asm_file) != NULL){
        if(buffer[0] == '('){
            strcpy(command_symbolized,command);
            command_symbolized[0] = '(';
            command_symbolized[strlen(command_symbolized) - 1] = ')';
            command_symbolized[strlen(command)] = '\n';
            if(strcmp(buffer,command_symbolized) == 0){
                buffer[strlen(buffer)-1] = ' ';
                fprintf(symboltable,"%s%d\n",buffer,counter);
                fclose(asm_file);
                fclose(symboltable);
                return;
                }
            }
        if(buffer[0] != '('){
            counter++;
            }
        }
        fclose(asm_file);
        fclose(symboltable);
        perror("[ERROR]invaid symbol");
        exit(EXIT_FAILURE);
    }

int getAddress(char *command){
    int address;
    char buffer[1024];
    FILE *symboltable;
    symboltable = fopen("symboltable","r");
    if(symboltable == NULL){
        perror("Can not open symboltable\n");
        exit(EXIT_FAILURE); 
        }

    while(fgets(buffer,1024,symboltable) != NULL){
        if(strcmp(command,strtok(buffer," ")) == 0){
            break;
            }
        }
    fclose(symboltable);

    address = atoi(strtok(NULL," "));
    return address; 
    }

int contain(char *command){
    FILE *symboltable;
    char buffer[1024];
    symboltable = fopen("symboltable","r");
    if(symboltable == NULL){
        perror("Can not open symboltable\n");
        exit(EXIT_FAILURE);
        }
    command[strlen(command)] = '\0';
    while(fgets(buffer,1024,symboltable) != NULL){
        if(strcmp(command,strtok(buffer," ")) == 0){
            return TRUE;
            }
        }
    return FAULSE;
    }

string address_binarizer(int address){
    int a,b;
    string address_bin;
    strcpy(address_bin.str,"0000000000000000");
    b = address;
    for(int j=15;j>=0;j--){
        a = b%2;
        if(b == 1){
            address_bin.str[j] = '1';
            break;
            }
        if(a == 1){
            address_bin.str[j] = '1';
            }
        b = b/2;
        }
    address_bin.str[strlen(address_bin.str)] = '\n';
    return address_bin;
    }

void generate_symboltableV2(){
    int counter = 0;
    char buffer[1024];
    FILE *symboltable,*asm_file;
    symboltable = fopen("symboltable","w+");
    asm_file = fopen(filename,"r");
    
    if(symboltable == NULL || asm_file == NULL){
        perror("[ERROR]\n");
        exit(EXIT_FAILURE);
        }
        
    fputs("SP 0\n",symboltable);
    fputs("LCL 1\n",symboltable);
    fputs("ARG 2\n",symboltable);
    fputs("THIS 3\n",symboltable);
    fputs("THAT 4\n",symboltable);
    fputs("SCREEN 16384\n",symboltable);
    fputs("KBD 24576\n",symboltable);
    for(int i=0;i<16;i++){
        fprintf(symboltable,"R%d %d\n",i,i);
    }

    while(fgets(buffer,1024,asm_file) != NULL){
        buffer[strlen(buffer)-1]='\0';
        if(buffer[0] == '('){
            fprintf(symboltable,"%s %d\n",buffer,counter);
        }else{
            counter++;
            }
        }

    fclose(symboltable);
    fclose(asm_file);
    }
