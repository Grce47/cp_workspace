#pragma once

#define deb(...) cerr << "Line[" << __LINE__ << "]" << " (" << #__VA_ARGS__ << "): ", _dbg_out(__VA_ARGS__)

void _print(int t) { cerr << t; }
void _print(long long t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(long double t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(bool t) { cerr << t; }
void _print(unsigned long long t) { cerr << t; }

template <typename T, typename V>
void _print(map<T, V> v);
template <typename T>
void _print(multiset<T> v);
template <typename T>
void _print(set<T> v);
template <typename T>
void _print(vector<T> v);
template <typename T, size_t N>
void _print(array<T, N> v);
template <typename T>
void _print(T *v, int N);

template <typename T, typename V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.first);
    cerr << ",";
    _print(p.second);
    cerr << "}";
}

template <typename T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}

template <typename T, size_t N>
void _print(array<T, N> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T, typename V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <typename T>
void _print(T *v, int N)
{
    cerr << "[ ";
    for (int i = 0; i < N; i++)
    {
        _print(v[i]);
        cerr << " ";
    }
    cerr << "]";
}

void _dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void _dbg_out(Head H, Tail... T)
{
    _print(H);
    cerr << " ";
    _dbg_out(T...);
}