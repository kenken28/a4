#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <math.h>
#include <time.h>
#include "sha1.h"

using namespace std;

const char MY_SALT[20] = "JC";
const char MY_HASH[41] = "1878DB98593C8CB5DF89E9F91B2C706E4863B74B";
const char LUT[77] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=";
//const char MY_PASS[79] = "Hello";

void getSha1(char* myPass, char* result) {
    unsigned char hash[20];
    char hexStr[41];
    char tohash[100];
    
    strcpy(tohash, MY_SALT);
    strcat(tohash, myPass);
    
    sha1::calc(tohash, strlen(tohash), hash);
    sha1::toHexString(hash, hexStr);
    
    strcpy(result, hexStr);
}

void toLowerCase(char* target) {
    for (int i=0; i<strlen(target); i++) {
        target[i] = tolower(target[i]);
    }
}

int incOne(char* target, int* targetIndex, int i) {
    if (targetIndex[strlen(target)-i] < strlen(LUT)-1) {
        targetIndex[strlen(target)-i]++;
        target[strlen(target)-i] = LUT[ targetIndex[strlen(target)-i] ];
        return 0;
    } else {
        targetIndex[strlen(target)-i] = 0;
        target[strlen(target)-i] = LUT[0];
        return 1;
    }
}

void incAll(char* target, int* targetIndex) {
    int index = 1, flag = 0;
    do {
        flag = incOne(target, targetIndex, index);
        
        if(index == 6){
            cout << target << endl;
        }
        
    } while (index++ <= 6 && flag == 1);
}

void randPass(char* target, int* targetIndex) {
    for (int i=0; i < strlen(target); i++){
        targetIndex[i] = rand() % (strlen(LUT)-1);
        target[i] = LUT[targetIndex[i]];
    }
}

int main() {
    char hashOut[41];
    char tmp_MY_HASH[41];
    char passStr[7] = "aaaaaa";
    int passIndex[6] = {0,0,0,0,0,0};
    stringstream oss;
    ofstream myfile ("q2result.txt");
    
    srand (time(NULL));
    randPass(passStr, passIndex);
    
    strcpy(tmp_MY_HASH, MY_HASH);
    toLowerCase(tmp_MY_HASH);
    
    for (int i=0; i<pow(strlen(LUT),strlen(passStr)); i++) {
        //cout << passStr << endl;
        getSha1(passStr ,hashOut);
        incAll(passStr, passIndex);
        
        //if (i%10000000 == 0) {
        //    cout << "10000000 passed" << endl;
        //}
        
        if (myfile.is_open() && strcmp(hashOut, tmp_MY_HASH) == 0) {
            myfile << passStr << endl << hashOut << endl;
            cout << "Match found" << endl;
            break;
        }
    }

    if (myfile.is_open())
        myfile.close();

    return 0;
}


