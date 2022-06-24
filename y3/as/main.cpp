#include "EllipticCurve.h"

using namespace std;

int main()
{
    //1336000
    Primes::LoadAmount(10000);
    cout << "Primes loaded : " << Primes::Count() << endl;
    cout << Primes::Count() << "th prime is " << Primes::Last() << endl;

    /*LongInt l(1009),n(104729);
    Primes::Sieve(n);



    cout << l.log10() << endl;
    cout << n.log10() << endl;*/

    cout << endl << "----------------" << endl;

    /*for (int64_t i = 1700000; true; i += 100000)
    {
        Primes::LoadAmount(i);
        cout << "Primes loaded : " << Primes::Count() << endl;
        cout << Primes::Count() << "th prime is " << Primes::Last() << endl;
    }*/

    /*{
        LongInt m("123456"),x("-765784943598563900875"),y("3859643905634205869560324623659"),q,r;

        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "m: " << m << endl;
        cout << "x%m: " << mod(x,m) << endl;
        cout << "y%m: " << mod(y,m) << endl;
        cout << "mod_add: " << mod_add(x,y,m) << endl;
        cout << "mod_sub: " << mod_sub(x,y,m) << endl;
        cout << "mod_mul: " << mod_mul(x,y,m) << endl;
        cout << "mod_div: " << mod_div(x,y,m) << endl;
        cout << "mod_pow: " << mod_pow(x,y,m) << endl;
    }*/

    /*LongInt x(18);
    LongInt y(6);
    LongInt z(40);
    LinearCongruence lin(x,y,z);
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
    cout << lin << endl;
    cout << lin.solve() << endl;*/

    {
        LinearCongruence lin1(1,1,6),lin2(1,17,39),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,8,12),lin2(1,6,9),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,8,12),lin2(1,6,13),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,3,7),lin2(1,7,12),lin3(1,4,17),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,1,2),lin2(1,3,6),lin3(1,3,7),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(5,8,2),lin2(7,3,5),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,2,3),lin2(1,3,5),lin3(1,2,7),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,3,10),lin2(1,8,15),lin3(1,5,84),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << "{" << lin3 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << "{" << lin3.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2&lin3;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin3;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin1(1,3,15),lin2(1,4,5),lin;
        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {
        LinearCongruence lin(100,41,65537);
        cout << lin << endl;
        cout << endl << lin.solve() << endl << endl;
    }

    {

        LinearCongruence
        lin1(LongInt("118747878"),LongInt("235252"),LongInt("236259578763785")),
        lin2(LongInt("436747867"),LongInt("32222"),LongInt("36528235667")),
        lin;

        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    {

        LinearCongruence
        lin1(LongInt("5454353"),LongInt("6846348"),LongInt("8757857872879823443")),
        lin2(LongInt("543242354"),LongInt("755453"),LongInt("87456843756857473")),
        lin3(LongInt("23423432533"),LongInt("6775754"),LongInt("35875938591025723")),
        lin;

        cout << "{" << lin1 << endl;
        cout << "{" << lin2 << endl;
        cout << "{" << lin3 << endl;
        cout << endl;

        cout << "{" << lin1.solve() << endl;
        cout << "{" << lin2.solve() << endl;
        cout << "{" << lin3.solve() << endl;
        cout << endl;

        LinearCongruence s = lin1&lin2&lin3;
        cout << s << endl << endl;

        if (!s.isNaN())
        {
            lin = lin1;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin2;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            lin = lin3;
            cout << lin.GetA() << " * " << s.GetB() << " (mod " << lin.GetM() << ") = " << mod_mul(lin.GetA(),s.GetB(),lin.GetM()) << endl;
            cout << endl;
        }
    }

    cout << endl << "----------------" << endl;

    {
        LongInt a("535524234"), b("2453");
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        LongInt c = a^b;

        cout << "a^b = " << c << endl;
        cout << "log10(a^b) = " << c.log10() << endl;
    }

    cout << endl << "----------------" << endl;

    {
        //LongInt a("8051");
        LongInt a = Primes::GetPrime(1234) * Primes::GetPrime(4321);
        cout << "a = " << a << ":" << endl;
        auto v = PollardRho(a);

        for (auto& i : v)
            cout << i << ' ';
        cout << endl;
    }

    cout << endl << "----------------" << endl;

    //cout << (LongInt(29) % LongInt(29)) << endl;

    //Primes::LoadAmount(10050);

    //string A="8051",B="21";
    //cin >> A;
    //cin >> B;
    /*for (int i = 1; i < 200; ++i)
    {
        LongInt a(i), b(B);
    //cout << b << " % " << PollardRho_Factor(b) << " != 0\n";
    vector<LongInt> v = PollardRho(a);
    cout << a << " = ";
    for (auto& i : v)
        cout << i << " * ";
    cout << "1\n";
    }*/

    /*{
        for (int i = 0; i < 100; ++i)
            cout << Rand_Long(1,10) << " ";
    }

    cout << endl << "----------------" << endl;*/

    {
        //1299709
        //1299721
        LongInt n("1689259081189");
        cout << "n = " << n << " = ";
        vector<LongInt> v = PollardRho(n);

        for (auto& i : v)
            cout << i << " * ";
        cout << "1\n";
    }

    cout << endl << "----------------" << endl;

    {
        LongInt a("38"), b("47"), m("101");
        LongInt x = BGStep(a,b,m);
        cout << "a^x=b(mod m) a=" << a << " b=" << b << " m=" << m << endl;
        cout << "x=loga(b)=" << x << " a^x=" << mod_pow(a,x,m) << endl;
    }

    cout << endl << "----------------" << endl;cout << endl << "----------------" << endl;

    {
        //LongInt e = 245738;
        LongInt e("475546576567");
        cout << "e=" << e << " phi(e)=" << Euler(e) << endl;
    }

    cout << endl << "----------------" << endl;

    {
        LongInt u("475546576567");
        cout << "u=" << u << " mu(u)=" << Mobius(u) << endl;
    }

    cout << endl << "----------------" << endl;

    {
        for (int i = 2; i <= 6; ++i)
        {
            LongInt p = Primes::GetPrime(i);
            for (int j = 0; p > j; ++j)
            {
                LongInt a = j;
                cout << "a=" << a << " p=" << p << endl;
                cout << "(a/p)=" << Legendre(a,p) << endl;
            }
        }
    }

    cout << endl << "----------------" << endl;

    {
        for (int i = 3; i < 10; i += 2)
        {
            for (int j = 0; j < 10; ++j)
            {
                LongInt a = j, n = i;
                cout << "a=" << a << " n=" << n << endl;
                cout << "[a/n]=" << Jacobi(a,n) << endl;
            }
        }
    }

    cout << endl << "----------------" << endl;

    {
        LongInt n("56"), p("101");
        cout << "x^2 = "<< n << " (mod " << p <<")\n";
        LongInt x = Cipolla(n,p);
        cout << "x = " << x << endl;
        cout << "x*x = " << mod_mul(x,x,p) << endl;
    }

    cout << endl << "----------------" << endl;

    {
        LongInt a("23463688124878"), p("29996224275833");
        cout << "( " << a << " | " << p << " ) = " << Legendre(a,p) << endl;
    }

    cout << endl << "----------------" << endl;

    {
        //899773470805713030576533893-
        //29996224275835-
        //29996224275833+
        //29996224275831-
        //29996224275821+
        //982451653+
        LongInt n("29996224275833");
        int k = 25;

        //cout << Jacobi(127,199) << endl;

        if (Solovay_Strassen(n,k))
            cout << n << " is prime (p = 1-2^-" << k << " = 1-" << pow(2,-k) << ")\n";
        else
            cout << n << " is not prime\n";
    }

    cout << endl << "----------------" << endl;

    /*{
        EllipticCurve E(1,1,23,0,0,point(0,0));
        point p(3,10), q(9,7);
        cout << "p: " << p.first << " " << p.second << endl;
        cout << "q: " << q.first << " " << q.second << endl;
        point r = E.Add(p,q);

        cout << "p+q: " << r.first << " " << r.second << endl;

    }

    cout << endl << "----------------" << endl;

    {
        EllipticCurve E(2,3,67,0,0,point(0,0));
        point e(2,22);
        cout << "e: " << e.first << " " << e.second << endl;
        LongInt d = 4;
        cout << "d: " << d << endl;
        point ei = E.Mul(e,d);

        cout << "d*e: " << ei.first << " " << ei.second << endl;

    }

    cout << endl << "----------------" << endl;*/

    {
        //1
        //1170244908728626138608688645279825
        //5
        //4294111829665782682720180854550727
        //6
        //2884156751491678244964697911030604
        //8
        //3056825142281162274735037408304164

        EllipticCurve E;
        LongInt k = Rand_Long(1, E.GetOrder()-1);
        point Y = E.Mul(E.GetGenerator(),k);
        /*LongInt x("8");
        cout << "x=" << x << endl;
        LongInt y = Cipolla(mod_add(mod_mul(E.GetA()+x*x,x,E.GetModulo()),E.GetB(),E.GetModulo()),E.GetModulo());
        cout << "y=" << y << endl;*/
        LongInt x("5"), y("4294111829665782682720180854550727");

        point M = point(x,y);
        cout << "M: (" << M.first << "; " << M.second << ")" << endl;

        if (M.second.isNaN() || !E.IsPoint(M))
        {
            cout << "M in E: false" << endl;
        }
        else
        {
            cout << "M in E: true" << endl;

            auto code = ElGamal_encrypt(E,Y,M);

            cout << "c: (" << code.first.first << "; " << code.first.second << "),";
            cout << "(" << code.second.first << "; " << code.second.second << ")" << endl;

            point decoded = ElGamal_decrypt(E,k,code);
            cout << "dM: (" << decoded.first << "; " << decoded.second << ")" << endl;
        }
    }

    /*{
        int r = 110;
        cout << "remainders of " << r << ": ";
        set<int> s;
        for (int i = 4; i < 1000; ++i)
        {
            s.insert((Primes::GetPrime(i)%r).to_int64());
        }
        for (auto i : s)
            cout << i << ' ';
        cout << endl;
        cout << s.size();
    }*/


/**/
}
