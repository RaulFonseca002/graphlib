#include <string>

using namespace std;

bool isNumeric(string str){

    try{
        stod(str);
        return true;
    }catch(...){
        return false;
    }
}

//codigo de geeksforgeeks
void reverseStr(string& str)
{
    int n = str.length();
 
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
