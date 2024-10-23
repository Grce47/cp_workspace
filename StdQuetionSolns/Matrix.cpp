// usesase:-
// Matrix<ll, 2, MOD> mat({array<ll, 2>{1, 0}, array<ll, 2>{0, 2}});
// mat.power(10).print();
template <class T, size_t N, long long MOD = -1>
class Matrix : public array<array<T, N>, N>
{
private:
    static void multipy_add(T &a, const T &x, const T &y)
    {
        if (MOD == -1)
            a += (x * y);
        else
        {
            a += (x * y) % MOD;
            if (a >= MOD)
                a -= MOD;
        }
    }

public:
    Matrix(bool identity = false) : array<array<T, N>, N>()
    {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                (*this)[i][j] = (identity && i == j ? 1 : 0);
    }

    Matrix(const array<array<T, N>, N> &a) : array<array<T, N>, N>(a) {}

    void print()
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
                cout << (*this)[i][j] << " ";
            cout << "\n";
        }
    }

    Matrix<T, N, MOD> operator*(const Matrix<T, N, MOD> &other) const
    {
        Matrix<T, N, MOD> res;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                for (size_t k = 0; k < N; k++)
                    multipy_add(res[i][j], (*this)[i][k], other[k][j]);
        return res;
    }

    template <size_t M>
    array<array<T, M>, N> matrix_mult(const array<array<T, M>, N> &other)
    {
        array<array<T, M>, N> res;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
            {
                res[i][j] = 0;
                for (size_t k = 0; k < N; k++)
                    multipy_add(res[i][j], (*this)[i][k], other[k][j]);
            }
        return res;
    }
    array<T, N> matrix_mult(const array<T, N> &other)
    {
        array<T, N> res;
        for (size_t i = 0; i < N; i++)
        {
            res[i] = 0;
            for (size_t k = 0; k < N; k++)
                multipy_add(res[i], (*this)[i][k], other[k]);
        }
        return res;
    }

    Matrix<T, N, MOD> power(long long n) const
    {
        Matrix<T, N, MOD> a(*this), res(true);
        while (n)
        {
            if (n & 1)
                res = (res * a);
            a = (a * a);
            n >>= 1;
        }
        return res;
    }
};



// easy
typedef long long ll;
const long long MOD = 1000000007;
 
using Row = vector<ll>;
using Matrix = vector<vector<ll>>;
 
Matrix mul(const Matrix &a, const Matrix &b)
{
    int n = a.size();
    Matrix res(n, Row(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                (res[i][j] += a[i][k] * b[k][j]) %= MOD;
    return res;
}
 
Matrix power(Matrix a, long long n)
{
    Matrix res(a.size(), Row(a.size(), 0));
    for (int i = 0; i < a.size(); i++)
        res[i][i] = 1;
 
    while (n)
    {
        if (n & 1)
            res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}