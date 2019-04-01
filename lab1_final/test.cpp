//
//  test.cpp
//  lab1_final
//
//  Created by apple on 2019/4/1.
//  Copyright © 2019年 apple. All rights reserved.
//

#include "Header.h"
#include <iostream>
#include <string.h>
#include <string>
#include "main.cpp"

using namespace std;
//错误说明
//1.-x ，x不对
//2.完全不对
//3.-x 后没跟参数
int fake_main(int argc, char * argv[]){
    char begin = '0', end = '0';
    const char * file ={0};
    int type =1;
    int num =-1;
    int argindex = 1;
    while (argindex < argc && argv[argindex][0] == '-') {
        if(strcmp(argv[argindex],"-w") == 0) {
            argindex++;
            if (argindex >= argc) {
                cout<< "Command wrong, there need parament after -w\n\n";
                exit(0);
            }
            file = argv[argindex];
            if(num == -1)
                type = FIND_NUM;
            else
                type = FIND_SPECIFIC_NUM;
            argindex++;
        }
        else if(strcmp(argv[argindex],"-c") == 0){
            argindex++;
            if (argindex >= argc) {
                cout<< "Command wrong, there need parament after -c\n\n";
                return 1;
            }
            file = argv[argindex];
            type = FIND_LEN;
            argindex++;
        }
        else if(strcmp(argv[argindex],"-n") == 0){
            argindex++;
            if (argindex >= argc) {
                cout<< "Command wrong, there need parament after -n\n\n";
                return 1;
            }
            num = argv[argindex][0] - '0';
            argindex++;
        }
        else if(strcmp(argv[argindex],"-h") == 0){
            argindex++;
            if (argindex >= argc) {
                cout<< "Command wrong, there need parament after -h\n\n";
                return 1;
            }
            begin = argv[argindex][0];
            argindex++;
        }
        else if(strcmp(argv[argindex],"-t") == 0){
            argindex++;
            if (argindex >= argc) {
                cout<< "Command wrong, there need parament after -t\n\n";
                return 1;
            }
            cout <<argv[argindex+1][0]<<endl;
            if(argv[argindex+1][0] == 'v') {
                cout<< " ------" <<endl;
            }
            end = argv[argindex][0];
            cout << "end :"<< end<<endl;
            argindex++;
        }
        else {
            cout << "Command wrong,-n,-h,-t,-w,-c is needed\n\n";
            return 1;
        }
    }
    if(argc > argindex) {
        cout << "Command wrong,-n,-h,-t,-w,-c is needed\n\n";
        return 1;
    }
   // cout << file << endl;
    Core* core = new Core(file);
    if(type == FIND_NUM) {
        char* result[20] = {0};
        int len;
        len = core->gen_chain_word(core->words_, core->len_, result, begin, end);
        if(len > 0){
            for(int i=0; i<len; i++)
                cout << result[i] << endl;
        }
    }
    else if(type == FIND_LEN) {
        char* result[20] = {0};
        int len;
        len = core->gen_chain_char(core->words_, core->len_, result, begin, end);
        if(len > 0){
            for(int i=0; i<len; i++)
                cout << result[i] << endl;
        }
    }
    else if(type == FIND_SPECIFIC_NUM) {
        vector<vector<char *> > result(8888, vector<char *>(99));
        int* len = core->gen_chain_specific_word(core->words_, core->len_, result, begin, end, num);
        if(len[0] > 0) {
            for(int i=0; i<len[0]; i++) {
                for(int j=0; j< len[i+1]; j++)
                    cout << result[i][j] <<" ";
                cout << endl;
            }
        }
    }
    delete core;
    return 0;
}





int main(int argc, const char * argv[]){
  
 //---------测试方法1---------
    string passage;
    ifstream in;
    in.open("./test/cmd.txt");
    getline(in, passage);
    cout << "1\n";
    do{
        int num = 0 ;
        char *arg[30] = {0};
        int len = (int)passage.length();
        int flag = 0;
        int site = 0;
        arg[num] = new char[40]();
        cout <<passage;
        for(int i=0; i<len ;i++) {
            if(passage[i]== ' ' ){
                if(flag == 1) {
                    flag = 0;
                    num ++;
                    arg[num] = new char[20]();
                    site = 0;
                }
            }
            else {
                arg[num][site] = passage[i];
                site++;
                flag = 1;
            }
        }
        num++;
        for(int i=0 ;i<num ;i++){
            cout << arg[i]<<endl;
        }
        fake_main(num, arg);
        getline(in, passage);
    }while(!(in.eof()));
//
    
    
 // ---------测试方法2---------
//    const char *filename = "./test/example.txt";
//    Core* core =new Core(filename);
//    char* result1[20] = {0};
//    int len1;
//    len1 = core->gen_chain_word(core->words_, core->len_, result1, '0', '0');
//    if(len1 > 0){
//        for(int i=0; i<len1; i++)
//            cout << result1[i] << endl;
//    }
//    delete core;
    
    
    
 // ----------测试方法3---------
//    int arrnum = 50;
//    char* input[50] =  {"due","to","pose","uncertainty","merely","executing","a","plannedtobe","stable","grasp","usually","results","in","an","unstable","grasp","in","the","physical","world","in","our","previous","work","k","we","proposed","a","tactile","experience","based","grasping","pipeline","which","utilizes","tactile","feedback","to","adjust","hand","posture","during","the","grasping","task","of","known","objects","and","improves"};
//    core = new Core(input,arrnum);
//    vector<vector<char *> > result3(8888, vector<char *>(99));
//    /* 调用 Core 中封装好的函数 */
//    int* len3 = core->gen_chain_specific_word(core->words_, core->len_, result3, 'd', '0', 4);
//    if(len3[0] > 0) {
//        for(int i=0; i<len3[0]; i++) {
//            for(int j=0; j< len3[i+1]; j++)
//                cout << result3[i][j] <<" ";
//            cout << endl;
//        }
//    }
//    delete core;
}
