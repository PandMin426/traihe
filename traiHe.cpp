#include <bits/stdc++.h>
#include <string>
using namespace std;

int main(){//LÀM LẠI THEO CÁCH HAY HƠN
    
    string s1 = "This is the main string";
    string s2 = "main2";

    // using contains() function, checking if the given substring is present in the main string or not
    int isFound = s1.find(s2) != string::npos;
    if(isFound){
        cout << "Ton tai";
    }else{
        cout << "Khong Ton tai";
    }
}
