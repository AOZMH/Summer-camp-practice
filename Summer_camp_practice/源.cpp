#define _CRT_SECURE_NO_WARNINGS
#include "2018_big_data.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <math.h>
#include <stack>
using namespace std;


/*vector<string> split(const string& str, const string& delim) {
    vector<string> res;
    char* source = new char[str.length() + 1];
    strcpy(source, str.c_str());
    char* p = strtok(source, delim.c_str());
    while (p) {
        res.push_back(p);
        p = strtok(NULL, delim.c_str());
    }
    delete[] source;
    return res;
}*/



int main()
{   
    solve_8();
    
    return 0;
}
