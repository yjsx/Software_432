//
//  Header.h
//  lab1_final
//
//  Created by apple on 2019/4/1.
//  Copyright © 2019年 apple. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define MAX_WORD_LEN 99
#define MAX_WORD_NUM 100
#define FIND_LEN 1
#define FIND_NUM 2
#define FIND_SPECIFIC_NUM 3

using namespace std;

class Core {
    
public:
    char ** words_;
    int len_;
    
    Core();
    Core(const char * filename) ;
    Core(char * words[], int len) ;
    ~Core();
    int gen_chain_word(char* words[], int len, char* result[], char head, char tail);
    int gen_chain_char(char* words[], int len, char* result[], char head, char tail);
    int* gen_chain_specific_word(char* words[], int len, vector<vector<char *> > &result, char head, char tail, int num);

private:
    int check(char* words[], int len, char head, char tail);
    void Build_Wordlist(char* words[], int len, int type);
    void clean();
    char** Get_word(const char* filename);
    int Find_Wordlist_(const int num,const char begin ,const char end,const int type);
};


typedef struct _EngLex {
    char str[MAX_WORD_LEN+1];
    int len ;
    char first_letter, last_letter;
    _EngLex(){
        len = 0;
    }
} EngLex;


EngLex word_list[MAX_WORD_NUM+1];
int word_num;
int G[MAX_WORD_NUM+1][MAX_WORD_NUM+1] = {0};

int word_count;
int bc[MAX_WORD_NUM+1];
int step;
int max_path_value = 0;
int max_path[MAX_WORD_NUM+1];
int path_value = 0  ;
int path[MAX_WORD_NUM+1];
int end_path_value = 0;
int end_path[MAX_WORD_NUM+1] ;
int spe_path_count =0 ;
int specific_path[8888][MAX_WORD_NUM+1];

int Compare(const char* a, const char* b) ;
int Partition(int p, int r, char* words[]);
void Quick_sort(int p,int r, char * words[]);
int Delete_dup(int num, char* words[]);

#endif /* Header_h */
