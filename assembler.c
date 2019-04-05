#include<stdio.h>
#include<string.h>

void Parser();          //パースするやつ
void hasMoreCommands(); //変換すべきニーモックが残っているか？
void advance();         //次のニーモックを参照する
void commandType();     //現在参照してるニーモックのタイプを調べる ex)A命令 C命令 シンボル
void symbol();          //現在のシンボルを返す [注意]現在仕様を理解していない！！！
void dest();            //C命令のdest部分を返す     
void comp();            //C命令のcomp部分を返す     111a cccc ccdd djjj
void jump();            //C命令のjump部分を返す

void Code();            //ニーモックをバイナリに変換するやつ
void dest_bin();        //C命令のdest部分をバイナリに変換する
void comp_bin();        //C命令のcomp部分をバイナリに変換する
void jump_bin();        //C命令のjump部分をバイナリに変換する

void SymbolTable();     //シンボル扱うやつ
void addEntry();        //テーブルにシンボルとアドレスのペアを追加
void contains();        //与えられたシンボルはテーブルに存在するか？
void getAddress();      //与えられたシンボルに対応するアドレスを返す


int main(){
    return 0;
    }
