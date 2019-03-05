/*************************************************************************
	> File Name: shiyan.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年02月21日 星期四 10时27分38秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<memory.h>
#include<string>
using namespace std;
int main(){
    vector<string> m;
    m.push_back(string("ewqqwe"));
    m.push_back(string("asasaa"));
    m.push_back(string("asasda"));
    m.push_back(string("qwqw"));
    m.push_back(string("dqwd"));
    m.push_back(string("dsfsd"));
    vector<string>::iterator itor;
    char *p=NULL;
    for(itor = m.begin();itor != m.end();itor ++)

    cout << m[3][2] << endl;
}


