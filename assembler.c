//usage ./Assembler filename.asm
//TODO .hackファイルのオープン

#define COMMAND_SIZE 1024

#define A_COMMAND 0
#define C_COMMAND 1
#define SYMBOL 2

#define TRUE 1
#define FAULSE 0

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct parsed_ {
    int command_type;       //A_COMMAND C_COMMAND SYMBOL
    char dest[COMMAND_SIZE];
    char comp[COMMAND_SIZE];
    char jump[COMMAND_SIZE];
    char symbol[COMMAND_SIZE];
    char address[COMMAND_SIZE];
    }parsed;

typedef struct string_ {
    char str[1024]={'\0'};
    }string;

void Converter(char *,char *);       //変換器 アセンブラ本体

parsed Parser();          //パースするやつ
void hasMoreCommands(); //変換すべきコマンドが残っているか？ [注意]いらないかも
void advance();         //次のコマンドを参照する[注意]いらないかも
void commandType();     //現在参照してるコマンドのタイプを調べる ex)A命令 C命令 シンボル
void symbol();          //現在のシンボルを返す [注意]現在仕様を理解していない！！！
string dest();            //C命令のdest部分を返す     
string comp();            //C命令のcomp部分を返す     dest=comp;jump
string jump();            //C命令のjump部分を返す

string Code();            //コマンドをバイナリに変換するやつ
string dest_bin();        //C命令のdest部分をバイナリに変換する
string comp_bin();        //C命令のcomp部分をバイナリに変換する
string jump_bin();        //C命令のjump部分をバイナリに変換する

void SymbolTable();     //シンボル扱うやつ
void addEntry();        //テーブルにシンボルとアドレスのペアを追加
void contains();        //与えられたシンボルはテーブルに存在するか？
void getAddress();      //与えられたシンボルに対応するアドレスを返す

int main(int argc,char *argv[]){
    FILE *asm_file,*bin_file;
    char command[1024];     //コマンド[注意]1024文字以上の変数名を使われると死ぬ
    char command_bin[1024]; //バイナリ

    if(asm_file = fopen(argv[1],"r") == NULL){          //ファイル名読み込み
        perror("[usage] ./Assembler filename.asm\n");   //エラー処理
        exit(EXIT_FAILURE);
        }

    char hackfilename[1024];
    strcpy(hackfilename,argv[1]);
    hackfilename[strlen(hackfilename) - 3] = 'h';
    hackfilename[strlen(hackfilename) - 2] = 'a';
    hackfilename[strlen(hackfilename) - 1] = 'c';
    hackfilename[strlen(hackfilename)] = 'k';
    hackfilename[strlen(hackfilename) + 1] = '\0';

    if(bin_file = fopen(hackfilename,"w+") == NULL){
        perror("cannot open/make filename.hack file\n");
        exit(EXIT_FAILURE);
        }

    while(fgets(command,1024,asm_file) != NULL){        //コマンドを行ごとに読み込む ファイル終端に達したら終了
        Converter(command,command_bin);
        command_bin[strlen(command_bin)] = '\0';
        fputs(command_bin,bin_file);                    //.hackファイルに書き込む
        }
    
    fclose(asm_file);
    fclose(bin_file);

    return 0;
    }

void Converter(char *command,char *command_bit){
    parsed x;

    x = Parser(command);
    command_bit = Code(x);
    }

parsed Parser(char *command){     //MEMO ;とか=とかで考えると良さそう
    parsed x;
    x.command_type = commandType(command);

    if(x.command_type == SYMBOL ){
        x.symbol = SymbolTable(command);
        x.dest = NULL;
        x.comp = NULL;
        x.jump = NULL;
        x.address = NULL;
        return x;
    }else if(x.command_type == A_COMMAND){
        x.address = SymbolTable(command);
        x.dest = NULL;
        x.comp = NULL;
        x.jump = NULL;
        x.symbol = NULL;
        return x;
    }else if(x.command_type == C_COMMAND){  //ここはelseで省略可
        strcpy(x.dest,dest(command).str);
        strcpy(x.comp,comp(command).str);
        strcpy(x.jump,jump(command).str);
        x.address = NULL;
        x.symbol = NULL;
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

    while(command[i] != '=' && command[i] != ';');  //配列上の=か;の位置を特定する
        i++;

    if(command[i] == '='){                          //;だったらjump命令なのでNULLを挿れる
        for(int j=0;j<i;j++){
            dest.str[j] = command[j];
            }
    }else{
        dest.str = NULL;
    }
        
        return dest;
    }

string comp(char *command){       //;と=で処理を分ける
    int i=0;
    int k=0;
    string comp;

    while(command[i] != '=' && command[i] != ';');
        i++;

    if(command[i] == '='){
        for(int j=i+1;j<=(strlen(command)-1);j++){
            comp.str[k]=command[j];
            }
    }else{
        for(int j=0;j<i;j++){
            comp.str[j] = command[j];
            }
    }
    return comp;
    }

string jump(char *command){
    int i=0;
    int k=0;
    string jump;

    while(command[i] != ';' && command[i] != '=');
        i++;
    if(command[i] == ';'){
        for(int j=i+1;j<=(strlen(command)-1);j++){
            jump.str[k]=command[j];
            k++
        }
    }

    return jump;
    }

string Code(parsed x){            //111a cccc ccdd djjj
    string bins;
    char bin[COMMAND_SIZE];
    strcpy(bin,"111");
    strcat(bin,comp_bin(x.comp).str);
    strcat(bin,dest_bin(x.dest).str);
    strcat(bin,jump_bin(x.jump).str);
    bin[strlen(bin)] = '\n';            //改行コードをケツに挿れる
    strcpy(bins.str,bin);
    return bins;
    }

string comp_bin(char *comp){
    char c[7];
    char a = '0';
    if(strcmp(comp,"0") == 0){
        strcpy(c,"101010");
    }else if(strcmp(comp,"1") == 0){
        strcpy(c,"111111")
    }else if(strcmp(comp,"-1") == 0){
        strcpy(c,"111010");
    }else if(strcmp(comp,"D") == 0){
        strcpy(c,"001100");
    }else if(strcmp(comp,"A") == 0){
        strcpy(c,"110000");
    }else if(strcmp(comp,"!D") == 0){
        strcpy(c,"001101");
    }else if(strcmp(comp,"!A") == 0){
        strcpy(c,"110001");
    }else if(strcmp(comp,"-D") == 0){
        strcpy(c,"001111");
    }else if(strcmp(comp,"-A") == 0){
        strcpy(c,"110011");
    }else if(strcmp(comp,"D+1") == 0){
        strcpy(c,"011111");
    }else if(strcmp(comp,"A+1") == 0){
        strcpy(c,"110111");
    }else if(strcmp(comp,"D-1") == 0){
        strcpy(c,"001110");
    }else if(strcmp(comp,"A-1") == 0){
        strcpy(c,"110010");
    }else if(strcmp(comp,"D+A") == 0){
        strcpy(c,"000010");
    }else if(strcmp(comp,"D-A") == 0){
        strcpy(c,"010011");
    }else if(strcmp(comp,"A-D") == 0){
        strcpy(c,"000111");
    }else if(strcmp(comp,"D&A") == 0){
        strcpy(c,"000000");
    }else if(strcmp(comp,"D|A") == 0){
        strcpy(c,"010101");
    }else if(strcmp(comp,"M") == 0){
        strcpy(c,"110000");
        a = '1';
    }else if(strcmp(comp,"!M") == 0){
        strcpy(c,"110000");
        a = '1';
    }else if(strcmp(comp,"-M") == 0){
        strcpy(c,"110011");
        a = '1';
    }else if(strcmp(comp,"M+1") == 0){
        strcpy(c,"110111");
        a = '1';
    }else if(strcmp(comp,"M-1") == 0){
        strcpy(c,"110010");
        a = '1';
    }else if(strcmp(comp,"D+M") == 0){
        strcpy(c,"000010");
        a = '1';
    }else if(strcmp(comp,"D-M") == 0){
        strcpy(c,"010011");
        a = '1';
    }else if(strcmp(comp,"M-D") == 0){
        strcpy(c,"000111");
        a = '1';
    }else if(strcmp(comp,"D&M") == 0){
        strcpy(c,"000000");
        a = '1';
    }else if(strcmp(comp,"D|M") == 0){
        strcpy(c,"010101");
        a = '1';
    }
    string ac;
    strcpy(ac.str,a);
    strcat(ac.str,c);
    
    return ac;
}

string dest_bin(char *dest){
    char d[4]={'\0'};
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

    string dstru;
    strcpy(dstru.str,d);
    return dstru;
    }

string jump_bin(char &jump){
    char j[4];
    if(jump[0] == '\0'){
        strcpy(j,"000");
    }else if(strcmp(jump,"JGT") == 0){
        strcpy(j,"001");
    }else if(strcmp(jump,"JEQ") == 0){
        strcpy(j,"010");
    }else if(strcpy(jump,"JGE") == 0){
        strcpy(j,"011");
    }else if(strcpy(jump,"JLT") == 0){
        strcpy(j,"100");
    }else if(strcpy(jump,"JNE") == 0){
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

void SymbolTable(){
    
    }
