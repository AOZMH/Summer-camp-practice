#define _CRT_SECURE_NO_WARNINGS
#include "2019_big_data.h"


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

inline bool in_array(int cr, int cc, int r, int c, int arr[25][25])
{
    if (arr[cr][cc] != -1 || cr < 0 || cc < 0 || cr >= r || cc >= c)
        return false;
    return true;
}

int main()
{   
    //SOLVE_6();

    return 0;
}