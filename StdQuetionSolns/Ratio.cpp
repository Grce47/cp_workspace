
struct Ratio
{
    int64_t num, den;
    Ratio()
    {
        num = 0;
        den = 1;
    }
    Ratio(int64_t NUM, int64_t DEN)
    {
        num = NUM;
        den = DEN;
        normalize();
    }
    Ratio(const Ratio& other)
    {
        num = other.num;
        den = other.den;
        normalize();
    }

    void normalize()
    {
        int64_t gc = __gcd(abs(num), abs(den));
        num /= gc;
        den /= gc;

        if (den < 0)
        {
            num = -num;
            den = -den;
        }
        if (num == 0) den = 1;
    }

    Ratio operator+(Ratio other)
    {
        Ratio res;
        res.den = other.den * den;
        res.num = (num * other.den) + (other.num * den);
        res.normalize();
        return res;
    }
    Ratio operator-(Ratio other)
    {
        Ratio res;
        res.den = other.den * den;
        res.num = (num * other.den) - (other.num * den);
        res.normalize();
        return res;
    }
    Ratio operator*(Ratio other)
    {
        Ratio res;
        res.den = other.den * den;
        res.num = num * other.num;
        res.normalize();
        return res;
    }
    Ratio operator/(Ratio other)
    {
        Ratio res;
        res.den = other.num * den;
        res.num = num * other.den;
        res.normalize();
        return res;
    }
    bool operator<(const Ratio& x) const
    {
        return (x.den * num < x.num* den);
    }

    bool operator==(const Ratio& x) const
    {
        return (num * x.den == den * x.num);
    }
};

