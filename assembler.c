//usage ./Assembler filename.asm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void Converter();       //変換器 アセンブラ本体

void Parser();          //パースするやつ
void hasMoreCommands(); //変換すべきコマンドが残っているか？ [注意]いらないかも
void advance();         //次のコマンドを参照する
void commandType();     //現在参照してるコマンドのタイプを調べる ex)A命令 C命令 シンボル
void symbol();          //現在のシンボルを返す [注意]現在仕様を理解していない！！！
void dest();            //C命令のdest部分を返す     
void comp();            //C命令のcomp部分を返す     111a cccc ccdd djjj
void jump();            //C命令のjump部分を返す

void Code();            //コマンドをバイナリに変換するやつ
void dest_bin();        //C命令のdest部分をバイナリに変換する
void comp_bin();        //C命令のcomp部分をバイナリに変換する
void jump_bin();        //C命令のjump部分をバイナリに変換する

void SymbolTable();     //シンボル扱うやつ
void addEntry();        //テーブルにシンボルとアドレスのペアを追加
void contains();        //与えられたシンボルはテーブルに存在するか？
void getAddress();      //与えられたシンボルに対応するアドレスを返す


int main(int argc,char *argv[]){
    FILE *fp;
    char command[1024];     //コマンド[注意]1024文字以上の変数名を使われると死ぬ
    char command_bin[16];   //バイナリ

    if(fp = fopen(argv[1],"r") == NULL){                //ファイル名読み込み
        perror("[usage] ./Assembler filename.asm\n");   //エラー処理
        exit(EXIT_FAILURE);
        }

    while(fgets(command,1024,fp) != NULL){              //コマンドを行ごとに読み込む ファイル終端に達したら終了
        Converter(command,command_bin);

        }
    return 0;
    }


