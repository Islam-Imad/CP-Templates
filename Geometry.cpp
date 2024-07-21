
#include <bits/stdc++.h>
using namespace std;
const double OO = 1e8;
#define ll long long int
#define ld long double
#define X first
#define Y second
#define EPS 1e-9
#define PI acos(-1)
#define vec(a,b) (b-a)
#define dotp(a,b) (conj(a)*b).real()
#define crossp(a,b) (conj(a)*b).imag()
#define same(a,b) (abs(a-b) < EPS)
#define normalize(a) (a/abs(a))
#define rotateA(p,ang,about) ((p-about)*exp(P(0,ang)) + about)
#define rotate0(p,ang) (p*exp(P(0,ang)))
#define reflect0(v, m) (conj(v / m) * m)
#define reflectA(v, a, m) (reflect0(vec(m, v), vec(m, rotateA(v, a, m)) + m))

typedef complex<ld> P;


int dcmp(ld x, ld y){
    if(fabs(x - y) < 1e-9) return 0;
    return x < y ? -1 : 1;
}

P pointToLine(P a, P b, P c){
    // answer is the projection of point c on line ab
    return a + ((dotp(vec(a,b), vec(a, c)) / norm(vec(a,b))) * (vec(a, b)));
}

ld from_deg_to_rad(ld deg){
    ld ret =  deg * PI / 180.0;
    if(ret < 0) ret += 2 * PI;
    return ret;
}

ld from_rad_to_deg(ld rad){
    ld ret =  rad * 180.0 / PI;
    if(ret < 0) ret += 360;
    return ret;
}

ld distToLine(P a, P b, P c){
    return abs(crossp(vec(a, b), vec(a, c))) / abs(b - a);
}

bool isCollinear(P a, P b, P c){
    return dcmp(crossp(vec(a, b), vec(a, c)), 0) == 0;
}

bool isPointOnRay(P a, P b, P c){
    if (!isCollinear(a, b, c))
        return false;
    return dcmp(dotp(vec(a, b), vec(a, c)), 0) == 1;
    // return same(normalize(b - a), normalize(c - a));
}

bool isPointOnSegment(P a, P b, P c){
    // ld d1 = abs(b - a), d2 = abs(c - a);
    // return same(d1+d2,abs(a-b));
    return isPointOnRay(a, b, c) && isPointOnRay(b, a, c);
}

ld CircleArea(ld r){
    return PI * r * r;
}

// Triangle Area two sides and angle between them
ld TriangleArea(ld a, ld b, ld angle){
    return 0.5 * a * b * sin(angle);
}
// Triangle Area three sides
// ld TriangleArea(ld a, ld b, ld c){
//     ld s = (a + b + c) / 2;
//     return sqrt(s * (s - a) * (s - b) * (s - c));
// }
// Triangle Area three points
ld TriangleArea3(P a, P b, P c){
    return abs(crossp(vec(a, b), vec(a, c))) / 2.0;
}

void solve(){
    
}

int main()
{
ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for(int i=1;i<=tc;++i){
        solve();
    }
}
/*
P p = {1 , 1};
p *= polar(1.0, from_deg_to_rad(90)); // polar(r, theta) = r * (cos(theta) + i * sin(theta))
cout << "Real part: " << p.real() << " Imaginary part: " << p.imag() << endl;
cout << "Magnitude: " << abs(p)  << '\n'; // abs = sqrt(x^2 + y^2)
cout << "Argument: " << arg(p) << '\n'; // arg = atan2(y, x)
cout << "Conjugate: " << conj(p) << '\n'; // conjugate = x - iy
cout << "Polar: " << polar(abs(p), arg(p)) << '\n'; // polar(r, theta)
cout << "Norm: " << norm(p) << '\n'; // NORM = x^2 + y^2


cross product = a.x * b.y - a.y * b.x = |a| * |b| * sin(theta)
dot product = a.x * b.x + a.y * b.y = |a| * |b| * cos(theta)

// ans triangle the length of the hypotenuse is the magnitude of the vector
*/
