#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0);
#define endl "\n"
#define int long long
#define INF 1e9
const int N = 1e3;
vector<int> ans = {1};
void push(int x)
{
    while(x!=0)
    {
        int dig = x%10;
        x/=10;
        ans.push_back(dig); 
    }
}
void shape()
{
    int len = ans.size();
    for(int i=0;i<len;i++)
    {
        int x = ans[i];
        if(x>=10)
        {
            if(i==len-1)
            {
                int dig = x%10;
                x /= 10;
                ans[i] = dig;
                if(x!=0) push(x);
                x=0;
                return;
            }
            int dig = x%10;
            ans[i] = dig;
            x = x/10;
            int idx = i+1;
            ans[idx] += x;
        }
    }
}
void bigFact(int n)
{
    for(int i=2;i<=n;i++)
    {
        int len = ans.size();
        for(int j=0;j<len;j++) ans[j] = ans[j]*i;
        shape();
    }
}
int32_t main()
{
    int n;
    cin>>n;
    bigFact(n);
    int cnt=0;
    for(int i=ans.size()-1;i!=-1;i--)
    {
        cout<<ans[i];
    }
    for(int i=0;i<ans.size();i++)
    {
        if(ans[i] == 0) cnt++;
        else break;
    }
    cout<<endl<<"no of dig: "<<ans.size();
    return 0;
}
