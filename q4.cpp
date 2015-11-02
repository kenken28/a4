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

void getSha1(char* myPass, char* result) {
    unsigned char hash[20];
    char hexStr[41];
    char tohash[100];
	
    strcpy(tohash, myPass);
    
    sha1::calc(tohash, strlen(tohash), hash);
    sha1::toHexString(hash, hexStr);
    
    strcpy(result, hexStr);
}

void toUpperCase(char* target) {
    for (int i=0; i<strlen(target); i++) {
        target[i] = toupper(target[i]);
    }
}


int main() {
    char hashOut[41];
    ofstream myfile ("37909090.program2.dif");
    
    strcpy(tmp_MY_HASH, MY_HASH);
    toUpperCase(tmp_MY_HASH);
    
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

