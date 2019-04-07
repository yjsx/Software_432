//
//  main.cpp
//  lab1_final
//
//  Created by apple on 2019/4/1.
//  Copyright © 2019年 apple. All rights reserved.
//
#include "Header.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

Core::Core(){}

Core::Core(const char *filename) {
    Get_word(filename);
}

Core::Core(char* words[],int len) {
    words_ = words;
    len_ = len;
    
}

Core::~Core(){
    clean();
    cout<< "-------------clean--------------\n";
}

void Core::Build_Wordlist(char* words[], int len, int type){
    for(int i=0; i<len; i++) {
        int word_len = (int)strlen(words[i]);
        word_list[i].len =word_len;
        strcpy(word_list[i].str, words[i]);
        word_list[i].first_letter =  words[i][0];
        word_list[i].last_letter = words[i][word_len-1];
    }
    word_num = len;
    for(int j=0; j< word_num ;j++) {
        for(int i=0; i< word_num ;i++){
            if(word_list[i].first_letter == word_list[j].last_letter
               && i != j){
                if( type == FIND_LEN )
                    G[j][i] = word_list[i].len;
                else if (word_list[i].len > 0)
                    G[j][i] = 1;
            }
        }
    }
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail){
    if(check(words, len, head, tail)== 0)
        return -7;
    Build_Wordlist(words, len, FIND_LEN);
    int t = Find_Wordlist_(-1, head, tail, FIND_LEN);
    if(t != 0)
        return -t;
    int temp=0;
    while(max_path[temp] != -1) {
        result[temp] = new char[MAX_WORD_LEN];
        strcpy(result[temp],word_list[max_path[temp]].str) ;
        temp++;
    }
    return temp;
}

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail){
    if(check(words, len, head, tail)== 0)
        return -7;
    Build_Wordlist(words, len ,FIND_NUM);
    int t = Find_Wordlist_(-1, head, tail, FIND_NUM);
    if(t!= 0)
        return -t;
    int temp=0;
    while(max_path[temp] != -1) {
        result[temp] = new char[MAX_WORD_LEN];
        strcpy(result[temp],word_list[max_path[temp]].str) ;
        temp++;
    }
    return max_path_value;
    
}

int* Core::gen_chain_specific_word(char* words[], int len, vector<vector<char *> > &result, char head, char tail, int num){
    int * k = new int[8888];
    if(check(words, len, head, tail)== 0){
        k[0] = -7;
        return k;
    }
    if(num > len || num <= 0 ){
        cout << "number is invalid\n";
        k[0] = -7;
        return k;
    }
    Build_Wordlist(words, len, FIND_SPECIFIC_NUM);
    int t = Find_Wordlist_(num, head, tail, FIND_SPECIFIC_NUM);
    if(t != 0 ){
        k[0] = -t;
        return k;
    }
    for(int i= 0; i < spe_path_count; i++) {
        int temp = 0;
        while(specific_path[i][temp] != -1) {
            result[i][temp] = new char[MAX_WORD_LEN];
            strcpy(result[i][temp],word_list[specific_path[i][temp]].str );
            temp++;
        }
    }
    k[0] =spe_path_count;
    for(int i=1; i<=spe_path_count; i++){
        int temp =0;
        while(specific_path[i-1][temp] != -1) {
            temp++;
        }
        k[i] = temp;
    }
    return k;
}
//check的错误种类：
//1.head  tail不为小写字母
//2.字符数组中有空字符
//3.字符数组中有错误字符
//4.len为负数
//5.字符数组中有重复字符串
int Core::check(char* words[], int len, char head, char tail){
    int valid = 1;
    if(len <= 0 ){
        try{
            throw("len is smaller than 0!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);                           
        }
        valid = 0;
    }
    if( (head < 'a' || head >'z')&& head!='0') {
        try{
            throw("head is invalid!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);               
        }
        valid = 0;
    }
    if((tail < 'a' || tail >'z')&& tail!='0') {
        try{
            throw("tail is invalid!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);                                                    
        }
        valid = 0;
    }
    int i = 0;
    for(i=0; i< len; i++){
        int word_len;
        word_len = (int)strlen(words[i]);
        if(word_len == 0 ){
            try{
                throw("there is blank word in these words!\n");
            }catch(const char * msg){
                cout<<msg<<endl;
                exit(0);                                                    
            }
            valid = 0;
            break;
        }
        for(int j = 0; j < word_len; j++){
            if(words[i][j] < 'a' || words[i][j] > 'z') {
                try{
                    throw("there is wrong character in words!\n");
                }catch(const char * msg){
                    cout<<msg<<endl;
                    exit(0);                                                    
                }
                valid = 0;
                break;
            }
        }
    }
    if(valid == 0)
        return 1;
    
    int acc_len;
    Quick_sort(0, len-1, words);
    acc_len = Delete_dup(len, words);
    if(acc_len < len) {
        try{
            throw("there is duplicate words in the word array!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);                                                    
        }
        valid = 0;
    }
    
    return valid;
}

void Core::clean(){
    memset(word_list, 0, sizeof(_EngLex)*MAX_WORD_NUM);
    word_num =0;
    memset(G, 0, sizeof(int)*100*100);
    memset(bc, 0, sizeof(int)*100);
    memset(max_path, 0, sizeof(int)*100);
    memset(path, 0, sizeof(int)*100);
    memset(end_path, 0, sizeof(int)*100);
    max_path_value =0;
    path_value = 0;
    end_path_value = 0;
    spe_path_count =0 ;
}

int find(int i,const char end,int type,int num){
    if(spe_path_count >= 8880)
        return 1;
    bc[i]=1;
    for(int j = 0; j < word_num; j++) {
        if (G[i][j] != 0 && bc[j]==0) {
            path_value += G[i][j];
            step++;
            path[step] = j;
            if(type == FIND_SPECIFIC_NUM && num == path_value ){
                if(end == '0'){
                    memcpy(specific_path[spe_path_count], path, sizeof(int)*MAX_WORD_NUM);
                    spe_path_count++;
                }
                else {
                    if(word_list[j].last_letter == end){
                        memcpy(specific_path[spe_path_count], path, sizeof(int)*MAX_WORD_NUM);
                        spe_path_count++;
                    }
                }
            }
            if(word_list[j].last_letter == end) {
                if(end_path_value < path_value) {
                    memcpy(end_path, path, sizeof(int)*MAX_WORD_NUM);
                    end_path_value =path_value;
                }
            }
            if(path_value > max_path_value) {
                memcpy(max_path, path, sizeof(int)*MAX_WORD_NUM);
                max_path_value =path_value;
            }
            find(j,end,type,num);
        }
    }
    if(type == FIND_NUM or type== FIND_SPECIFIC_NUM )
        path_value -= 1;
    else if (type == FIND_LEN)
        path_value -= word_list[i].len;
    
    path[step] =-1;
    step--;
    bc[i]=0;
    return 0;
}

void output_(int type,const char end,const int t){
    int temp=0;
    ofstream out;
    out.open("solution.txt");
    if (t == 1) {
        cout<< "there is no wordlist begin with " << end <<endl;
        return;
    }
    else if (t == 2) {
        cout<< "there is no wordlist ended with " << end <<endl;
        return;
    }
    else if (t == 3) {
        cout<< "there is no wordlist having this number of words" << endl;
        return;
    }
    else if (t == 4) {
        cout<< "there too much wordlist having this number of words(more than 8888)" << endl;
        return;
    }
    else if(type == FIND_SPECIFIC_NUM) {
        for(int i= 0; i < spe_path_count; i++) {
            int temp = 0;
            while(specific_path[i][temp] != -1) {
                out << word_list[specific_path[i][temp]].str << endl;
                temp++;
            }
        }
        cout << "The num of path is " << spe_path_count <<endl;
        return;
    }
    else if(end != '0'){
        memcpy(max_path, end_path, sizeof(int)*MAX_WORD_NUM);
        max_path_value = end_path_value;
    }
    //将end_path的结果复制到max_path作为最后结果
    cout << "The path is: ";
    while(max_path[temp] != -1) {
        cout<< max_path[temp] << " ";
        out<< word_list[max_path[temp]].str << endl;
        temp++;
    }
    cout <<"The value of path is " <<max_path_value<< endl;
}


int Core::Find_Wordlist_(const int num,const char begin ,const char end,const int type){ //遍历
    if(begin != '0') {
        int i;
        for(i=0; i<word_num; i++)
            if(word_list[i].first_letter == begin)
                break;
        if(i == word_num){
            output_(type,end,1);
            return 1;
        }
    }  //提前查看有无指定begin的单词，无 则返回1
    memset(max_path,-1,sizeof(int)*word_num);
    for(int i=0; i<word_num; i++){
        if(begin == '0' || begin == word_list[i].first_letter) {
            word_count = i;
            memset(bc,0,sizeof(int)*word_num);
            for(int k =0 ; k<MAX_WORD_NUM ; k++)
                path[k]=-1;
            if(type == FIND_LEN)
                path_value = word_list[i].len;
            else
                path_value=1;
            step=0;
            path[step]=i;
            if(word_list[i].last_letter == end) {
                if(end_path_value < path_value) {
                    memcpy(end_path, path, sizeof(int)*MAX_WORD_NUM);
                    end_path_value =path_value;
                }
            }
            if(path_value > max_path_value) {
                memcpy(max_path, path, sizeof(int)*MAX_WORD_NUM);
                max_path_value =path_value;
            }
            int k = find(i,end,type,num);
            if(k == 1){
                output_(type,end,4);
                return 4; //-n的条数过多
            }
        }
    }  //遍历 寻找不同单词开头的 最长单词练
    int t;
    if(end != '0'&& end_path_value == 0)
        t = 2;
    else if(type == FIND_SPECIFIC_NUM && spe_path_count == 0)
        t = 3;
    else
        t = 0;
    output_(type,end,t);
    return t;
}




int Compare(const char* a, const char* b) {
     if(a[0] < b[0])
         return 1;
     else if(a[0] > b[0])
         return -1;
     else
         if(strlen(a) > strlen(b))
             return 1;
         else if (strlen(a) < strlen(b))
             return -1;
         else {
             if(strcmp(a,b)==0)
                 return 0;
             else if(strcmp(a,b) < 0)
                 return -1;
             else
                 return 1;
         }
 }
 int Partition(int p, int r, char* words[]) {
     int i= p-1;
     for(int j=p; j<r ; j++) {
         if(Compare(words[j], words[r])>=0) {
             i++;
             swap(words[i],words[j]);
         }
     }
     swap(words[i+1], words[r]);
     return i+1;
 }

 void Quick_sort(int p,int r, char * words[]){
     if(p < r){
         int q= Partition(p, r, words) ;
         Quick_sort(p, q-1, words);
         Quick_sort(q+1, r, words);
     }
 }

 int Delete_dup(int num, char* words[]) {
     for(int i=0; i<num ;i++) {
         if(Compare(words[i], words[i+1])==0) {
             for(int j=i+2; j<num ;j++)
                 swap(words[j-1],words[j]);
             num--;
             i--;
         }
     }
     return num;
 }

char** Core::Get_word(const char* filename) {
     char ** words =new char*[MAX_WORD_NUM];
     string passage;
     ifstream in;
     in.open(filename);
    if (! in.is_open())
        try{
            throw("Error opening file!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);
        }
     int count =0;
     int flag = 0;//用来指示前一个字符是否为字母，1是，0不是
     int word_len = 0;
     in >> passage ;
     words[count] =new char[MAX_WORD_LEN]();
     do {
         int len = (int)passage.length();
         for(int i=0; i<len ;i++) {
             if(passage[i]<='z' && passage[i]>= 'a') {
                 flag =1;
                 words[count][word_len] = passage[i];
                 word_len++;
             }
             else if(passage[i]<='Z' && passage[i]>= 'A') {
                 flag =1;
                 passage[i] = passage[i] +32;
                 words[count][word_len] = passage[i];
                 word_len++;
             }
             else if(flag == 1 ){
                 count ++;
                 word_len = 0 ;
                 words[count] =new char[MAX_WORD_LEN];
                 flag =0;
             }
         }
         if(flag == 1) {
             count++;
             word_len = 0 ;
             words[count] =new char[MAX_WORD_LEN];
             flag =0;
         }
         in >> passage;
     }while( !in.eof() );
    if(count == 0){
        try{
            throw("There is no word in the file!\n");
        }catch(const char * msg){
            cout<<msg<<endl;
            exit(0);
        }
    }
     Quick_sort(0, count-1, words);
     count = Delete_dup(count, words);
     words_ = words;
     len_ = count;
     return words;
 }
