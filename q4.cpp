#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream> 
#include "sha1.h"       // from https://code.google.com/p/smallsha1/

using namespace std;

const char oldPass[41] = "5E680C6D1A44D5C68A0175FEB6B750FCD18BE7DE";

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
    char myPass[100];
    char hashOut[41];
    char offset[3];
    string passStr, tmp;
    stringstream offsetSS;
    
    ofstream myfile ("37909090.program2.dif");
    
    cout << "Type new password: " << endl;
    cin >> passStr;
    
    strcpy(myPass, passStr.c_str());
    
    getSha1(myPass, hashOut);
    toUpperCase(hashOut);
    
    myfile << "This difference file has been created by q4 executable" << endl << endl;
    myfile << "37909090.program2.exe" << endl;
    
    for (int i=0; i<20; i++) {
        offsetSS << hex << (i+212);
        tmp = offsetSS.str();
        offsetSS.str("");
        strcpy(offset, tmp.c_str());
        toUpperCase(offset);
        myfile << "000127" << offset << ": " << oldPass[i*2] << oldPass[i*2+1];
        myfile << " " << hashOut[i*2] << hashOut[i*2+1] << endl;
    }

    if (myfile.is_open())
        myfile.close();

    return 0;
}

