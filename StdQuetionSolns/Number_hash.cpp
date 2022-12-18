template <typename T = long long int>
class NumberHash
{
private:
    map<T, int> hash_map;
    vector<T> inv_hash_map;
    int hash_size;

public:
    NumberHash()
    {
        this->hash_size = 0;
    }

    // returns size of hash
    int size()
    {
        return this->hash_size;
    }

    void clear()
    {
        this->hash_map.clear();
        this->inv_hash_map.clear();
        this->hash_size = 0;
    }

    // returns number which is assigned this hash value
    T actual_value(int hash_value)
    {
        assert(hash_value < this->hash_size);
        return this->inv_hash_map[hash_value];
    }

    // gets or creates hash value for given value
    int hash_value(T value)
    {
        if (this->hash_map.find(value) == this->hash_map.end())
        {
            this->hash_map[value] = this->inv_hash_map.size();
            this->inv_hash_map.push_back(value);
        }
        return this->hash_map[value];
    }
};