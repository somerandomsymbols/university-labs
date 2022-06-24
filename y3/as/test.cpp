#include "LongInt.h"

int tlim = 1;

void t1(string x, LongInt (*f)(LongInt), string cor)
{
    LongInt a(x);
    LongInt ans;

    ans = f(a);

    if (cor != string(ans))
    {
        cout << "false:\n" << "x: " << a << endl << "cor: " << cor << endl << "ans: " << ans << endl;
        cin >> cor;
    }
}

void T1(string name, vector<string> inp, LongInt (*f)(LongInt), string filepath)
{
    cout << name << ":\n";
    vector <string> otp;
    ifstream fi;
    fi.open(filepath);
    while (!fi.eof())
    {
        otp.push_back("");
        getline(fi,otp.back());

        if (otp.back().empty())
            otp.pop_back();
    }
    fi.close();

    time_t dur = time(nullptr);
    int num = 0;

    while (time(nullptr) - dur <= tlim)
    {
        int i = 0;
        for (auto j : inp)
        {
            t1(j,f,otp[i++]);
            ++num;
        }
    }

    cout << 1.0*(time(nullptr) - dur)/num << endl;
    cout << name << "^\n";
}

void t2(string x, string y, LongInt (*f)(LongInt, LongInt), string cor)
{
    LongInt a(x), b(y);
    LongInt ans;

    ans = f(a,b);

    if (cor != string(ans))
    {
        cout << "false:\n" << "x: " << a << endl << "y: " << b << endl << "cor: " << cor << endl << "ans: " << ans << endl;
        cin >> cor;
    }

}

void T2(string name, vector<string> inp, LongInt (*f)(LongInt, LongInt), string filepath)
{
    cout << name << ":\n";
    vector <string> otp;
    ifstream fi;
    fi.open(filepath);
    while (!fi.eof())
    {
        otp.push_back("");
        getline(fi,otp.back());

        if (otp.back().empty())
            otp.pop_back();
    }
    fi.close();

    time_t dur = time(nullptr);
    int num = 0;

    while (time(nullptr) - dur <= tlim)
    {
        int i = 0;
        for (auto j : inp)
        {
            for (auto k : inp)
            {
                t2(j,k,f,otp[i++]);
                ++num;
            }
        }
    }

    cout << 1.0*(time(nullptr) - dur)/num << endl;
    cout << name << "^\n";
}

int main()
{
    vector <string> inp;
    //vector <pair<string,string>> inp2;
    int num;
    time_t dur;

    {
        ifstream fi;
        fi.open("long_data.txt");

        while (!fi.eof())
        {
            inp.push_back("");
            getline(fi,inp.back());

            if (inp.back().empty())
                inp.pop_back();
        }

        fi.close();

        /*for (auto i : inp)
            for (auto j : inp)
                inp2.push_back(pair<string,string>(i,j));*/
    }

    T2("add",inp,[](LongInt x, LongInt y){return x+y;},"long_add.txt");
    T2("sub",inp,[](LongInt x, LongInt y){return x-y;},"long_sub.txt");
    T2("mul",inp,[](LongInt x, LongInt y){return x*y;},"long_mul.txt");
    T2("div",inp,[](LongInt x, LongInt y){return x/y;},"long_div.txt");
    T2("mod",inp,[](LongInt x, LongInt y){return x%y;},"long_mod.txt");
    T1("sqr",inp,[](LongInt x){return x.sqr();},"long_sqr.txt");
    T1("sqrt",inp,[](LongInt x){return x.sqrt();},"long_sqrt.txt");
/*
    cout << "add:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_add.txt");

        for (auto i : inp)
        {
            for (auto j : inp)
            {
                LongInt x(i),y(j);
                LongInt z = x+y;
                string ans;

                getline(fi,ans);

                if (ans != string(z))
                {
                    cout << "false:\n" << x << endl << y << endl << ans << endl << z << endl;
                    cin >> ans;
                }
                ++num;
            }
        }

        fi.close();
    }
    cout << "^add\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    cout << "sub:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_sub.txt");

        for (auto i : inp)
        {
            for (auto j : inp)
            {
                LongInt x(i),y(j);
                LongInt z = x-y;
                string ans;

                getline(fi,ans);

                if (ans != string(z))
                {
                    cout << "false:\n" << x << endl << y << endl << ans << endl << z << endl;
                    cin >> ans;
                }
                ++num;
            }
        }

        fi.close();
    }
    cout << "^sub\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    cout << "mul:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_mul.txt");

        for (auto i : inp)
        {
            for (auto j : inp)
            {
                LongInt x(i),y(j);
                LongInt z = x*y;
                string ans;

                getline(fi,ans);

                if (ans != string(z))
                {
                    cout << "false:\n" << x << endl << y << endl << ans << endl << z << endl;
                    cin >> ans;
                }
                ++num;
            }
        }

        fi.close();
    }
    cout << "^mul\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    cout << "div:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_div.txt");

        for (auto i : inp)
        {
            for (auto j : inp)
            {
                if (j != "0")
                {
                    LongInt x(i),y(j);
                    LongInt z = x/y;
                    string ans;

                    getline(fi,ans);

                    if (ans != string(z))
                    {
                        cout << "false:\n" << x << endl << y << endl << ans << endl << z << endl;
                        cin >> ans;
                    }
                    ++num;
                }
            }
        }

        fi.close();
    }
    cout << "^div\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    cout << "mod:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_mod.txt");

        for (auto i : inp)
        {
            for (auto j : inp)
            {
                if (j != "0")
                {
                    LongInt x(i),y(j);
                    LongInt z = x%y;
                    string ans;

                    getline(fi,ans);

                    if (ans != string(z))
                    {
                        cout << "false:\n" << x << endl << y << endl << ans << endl << z << endl;
                        cin >> ans;
                    }
                    ++num;
                }
            }
        }

        fi.close();
    }
    cout << "^mod\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    /*cout << "sqr:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_sqr.txt");

        for (auto i : inp)
        {
            LongInt x(i);
            LongInt z = x.sqr();
            string ans;

            getline(fi,ans);

            if (ans != string(z))
            {
                cout << "false:\n" << x << endl << ans << endl << z << endl;
                cin >> ans;
            }
            ++num;
        }

        fi.close();
    }
    cout << "^sqr\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;

    cout << "sqrt:\n";
    dur = time(nullptr);
    for (num = 0; time(nullptr) - dur <= tlim;)
    {
        ifstream fi;
        fi.open("long_sqrt.txt");

        for (auto i : inp)
        {
            LongInt x(i);
            LongInt z = x.sqrt();
            string ans;

            getline(fi,ans);

            if (ans != string(z))
            {
                cout << "false:\n" << x << endl << ans << endl << z << endl;
                cin >> ans;
            }
            ++num;
        }

        fi.close();
    }
    cout << "^sqrt\n";
    cout << 1.0*(time(nullptr) - dur)/num << endl;*/


    /*
    vector<string> d1 = {"0", "123456896", "123000000000456", "12345600000000", "10000023456"};
    vector<pair<int64_t,int64_t>> d2 = { {12300456,87654321}, {99999999,99999999},
    {687598,426759}, {107080,809060}, {7080405,30705}, {7563884,23788}, {743464,5205022},
    {639036,7879970}, {18157858,107328}, {97664005,50936578}, {64908478,79417982}, {100000, 1000000},
    {12345,600}, {18157858,107}, {97664005,509}, {64908478,794}, {239,16}, {47483927,6784789},
    {600,12345}, {107,18157858}, {509,97664005}, {794,64908478}, {16,239}, {6784789,47483927} };
    vector<string> d3 = {"00000000000", "123456896", "0000123456", "000012345600000000", "1234560000"};
    {
        cout << "inp:" << endl;
        vector<string> inp = d3;
        vector<string> cor = {"0", "123456896", "123456", "12345600000000", "1234560000"};
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i]);
            string ans = string(X);

            if (cor[i] != ans)
            {
                cout << "false:" << endl;
                cout << "inp: " << X << endl;
                cout << cor[i] << " != " << ans << endl;
            }
        }
    }

    {
        cout << "add:" << endl;
        auto inp = d2;
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i].first), Y(inp[i].second);
            LongInt ans = X+Y;
            int64_t cor = inp[i].first + inp[i].second;

            if (to_string(cor) != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << " " << Y << endl;
                cout << cor << " != " << ans << endl;
            }
        }
    }

    {
        cout << "sub:" << endl;
        auto inp = d2;
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i].first), Y(inp[i].second);
            LongInt ans = X-Y;
            int64_t cor = inp[i].first - inp[i].second;

            if (to_string(cor) != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << " " << Y << endl;
                cout << cor << " != " << ans << endl;
            }
        }
    }

    {
        cout << "mul:" << endl;
        auto inp = d2;
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i].first), Y(inp[i].second);
            LongInt ans = X*Y;
            int64_t cor = inp[i].first * inp[i].second;

            if (to_string(cor) != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << " " << Y << endl;
                cout << cor << " != " << ans << endl;
            }
        }
    }

    {
        cout << "div:" << endl;
        auto inp = d2;
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i].first), Y(inp[i].second);
            LongInt ans = X/Y;
            int64_t cor = inp[i].first / inp[i].second;

            if (to_string(cor) != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << " " << Y << endl;
                cout << cor << " != " << ans << endl;
            }
        }
    }

    {
        cout << "mod:" << endl;
        auto inp = d2;
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i].first), Y(inp[i].second);
            LongInt ans = X%Y;
            int64_t cor = inp[i].first % inp[i].second;

            if (to_string(cor) != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << " " << Y << endl;
                cout << cor << " != " << ans << endl;
            }
        }
    }

    {
        cout << "sqr:" << endl;
        vector<string> inp = d1;
        vector<string> cor = {"0", "15241605169954816", "15129000000112176000000207936", "152413839360000000000000000", "100000469120550183936"};
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i]);
            LongInt ans = X.sqr();

            if (cor[i] != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << endl;
                cout << cor[i] << " != " << ans << endl;
            }
        }
    }

    {
        cout << "sqrt:" << endl;
        vector<string> inp = d1;
        vector<string> cor = {"0", "11111", "11090536", "3513630", "100000"};
        for (int i = 0; i < inp.size(); ++i)
        {
            LongInt X(inp[i]);
            LongInt ans = X.sqrt();

            if (cor[i] != string(ans))
            {
                cout << "false:" << endl;
                cout << "inp: " << X << endl;
                cout << cor[i] << " != " << ans << endl;
            }
        }
    }

    /**/
}
