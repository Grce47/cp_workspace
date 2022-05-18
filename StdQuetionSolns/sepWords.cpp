#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    char msg[100];
    cout<<sizeof(msg)<<endl;
    scanf("%[^\n]",msg);
    int cnt = 1;
    for(int i=0; msg[i] != '\0'; i++)
    {
        if(msg[i] == ' ') cnt++;
    }
    char **words = (char**)malloc(cnt*sizeof(char*));
    int id = 0,idx = 0;
    char word[100];
    for(int i=0; msg[i] != '\0'; i++)
    {
        if(msg[i] == ' ')
        {
            words[id] = (char*)malloc(sizeof(char) * (idx+1));
            for(int j=0;j<idx;j++)
            {
                words[id][j] = word[j];
                word[j] = '\0';
            }
            words[id][idx] = '\0';
            idx = 0;
            id++;
        }
        else word[idx++] = msg[i];
    }
    words[id] = (char*)malloc(sizeof(char) * (idx+1));
    for(int j=0;j<idx;j++)
    {
        words[id][j] = word[j];
        word[j] = '\0';
    }
    words[id][idx] = '\0';
    idx = 0;
    id++;
    for(int i=0;i<cnt;i++)
    {
        printf("%s\n",words[i]);
    }
    return 0;
}
