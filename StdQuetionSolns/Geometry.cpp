// Point Structure
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T dot(P a, P b) const { return (a - *this).dot(b - *this); }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
};
// end

// 1->Inside, 0->outside, -1 -> boundary
// a is array of verictes, b is query point
// O(n)
template <class P>
int point_inside_polygon(vector<P> const &a, P b)
{
    int n = a.size();
    P just_above;
    just_above.x = b.x;
    just_above.y = b.y + 1LL;
    int cnt = 0;
    bool boundary = false;
    rep(i, 0, n)
    {
        int j = (i + 1) % n;
        if (b.cross(a[i], a[j]) == 0)
        {
            if (min(a[i].x, a[j].x) <= b.x && b.x <= max(a[i].x, a[j].x) && min(a[i].y, a[j].y) <= b.y && b.y <= max(a[i].y, a[j].y))
            {
                boundary = true;
                break;
            }
        }

        ll sign1 = b.cross(just_above, a[i]), sign2 = b.cross(just_above, a[j]);
        if ((sign1 >= 0 && sign2 >= 0) || (sign1 < 0 && sign2 < 0))
            continue;
        if (sign1 >= 0)
        {
            ll sign3 = b.cross(a[i], a[j]);
            if (sign3 <= 0)
                cnt++;
        }
        else if (sign2 >= 0)
        {
            ll sign3 = b.cross(a[j], a[i]);
            if (sign3 <= 0)
                cnt++;
        }
    }
    if (boundary)
        return -1;
    else if (cnt & 1)
        return 1;
    return 0;
}
// end


// Convex Hull
template <class P>
vector<P> convex_hull(vector<P> &points)
{
    sort(all(points));
    vector<P> hull;
    { // upper Hull
        for (P C : points)
        {
            while (hull.size() >= 2)
            {
                P A = hull.end()[-2];
                P B = hull.end()[-1];
                if (A.cross(B, C) <= 0)
                    break;
                hull.pop_back();
            }
            hull.push_back(C);
        }
        hull.pop_back();   //removing rightmost point to avoid dubplication
    }
    { // lower Hull
        reverse(all(points));
        const int S = hull.size();
        for (P C : points)
        {
            while (hull.size() - S >= 2)
            {
                P A = hull.end()[-2];
                P B = hull.end()[-1];
                if (A.cross(B, C) <= 0)
                    break;
                hull.pop_back();
            }
            hull.push_back(C);
        }
        hull.pop_back();  //removing leftmost point
    }
    return hull;
}
//end