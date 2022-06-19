#include <bits/stdc++.h>
using namespace std;

void getInp(vector<string> &a,ifstream &input_file)
{
    string line;
     if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            a.push_back(line);
        }
        input_file.close();
    }
    else
        cout << "Unable to open file" << endl;
}

int32_t main()
{
    freopen("error.txt", "w", stdout);
    vector<string> brute;
    vector<string> mySol;
    ifstream bruteInp("b_output.txt");
    ifstream myInp("output.txt");
    getInp(brute,bruteInp);
    getInp(mySol,myInp);
    if(brute.size() != mySol.size())
    {
        cout<<"Size NOT Same !!\n";
        // return 0;
    }
    int ok = 0;
    for(int i=0;i<brute.size();i++)
    {
        // if(ok > 0) break;
        if(brute[i] != mySol[i])
        {
            ok++;
            cout<<"CASE : "<<i+1<<"\n";
            cout<<"BRUTE : "<<brute[i]<<"\nMYSOL : "<<mySol[i]<<"\n\n";
        }
    }
    if(ok == 0) cout<<"ALL OK!!";
    else cout<<"PROBLEM : "<<ok;
    return 0;
}