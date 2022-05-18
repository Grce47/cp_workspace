class StringHash
{
private:
    map<string, int> hash;
    vector<string> inv_hash;

public:
    void clear()
    {
        hash.clear();
        inv_hash.clear();
    }
    void insert(string &s)
    {
        if (hash.find(s) == hash.end())
        {
            hash.insert({s, (int)inv_hash.size()});
            inv_hash.push_back(s);
        }
    }
    int size()
    {
        return inv_hash.size();
    }
    string getStr(int no)
    {
        if (no >= inv_hash.size())
            return "";
        return inv_hash[no];
    }
    int getNo(string s)
    {
        auto it = hash.find(s);
        return (it == hash.end() ? -1 : it->second);
    }
};
