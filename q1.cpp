#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include "sha1.h"

using namespace std;

const char MY_SALT[20] = "Rv";
const char MY_HASH[41] = "F53903931C9B4593D856B08C47E0783E59D55F03";
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

void append0infront(char* target) {
    char tmp_target[10];
    strcpy(tmp_target, target);
    strcpy(target, "0");
    strcat(target, tmp_target);
}

void toLowerCase(char* target) {
    for (int i=0; i<strlen(target); i++) {
        target[i] = tolower(target[i]);
    }
}

int main() {
    char hashOut[41];
    char tmp_MY_HASH[41];
    char passStr[10];
    stringstream oss;
    ofstream myfile ("q1result.txt");
    
    strcpy(tmp_MY_HASH, MY_HASH);
    toLowerCase(tmp_MY_HASH);
    
    for (int i=0; i<10000; i++) {
        oss << i;
        strcpy(passStr, oss.str().c_str());
        oss.str("");
        oss.clear();
        
        while (strlen(passStr) < 4)
            append0infront(passStr);
        
        getSha1(passStr ,hashOut);
        //cout << passStr << endl << hashOut << endl;
        
        if (myfile.is_open() && strcmp(hashOut, tmp_MY_HASH) == 0)
            myfile << passStr << endl << hashOut << endl;
    }

    if (myfile.is_open())
        myfile.close();

    return 0;
}


