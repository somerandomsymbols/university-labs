#include <bits/stdc++.h>
#include <omp.h>

/**
void thr(Matrix& M, const Matrix& x, const Matrix& y)
{
    if (x.h == y.w)
    {
        M = Matrix(x.w, y.h);

        if (x.w == 1 && y.h == 1)
        {
            M.m[0][0] = 0;

            for (int i = 0; i < x.h; ++i)
            {
                M.m[0][0] += x.m[0][i] * y.m[i][0];
            }
        }

        else if (x.w == 1)
        {

            Matrix M1, M2;
            std::thread thread_obj1(thr, std::ref(M1), x, y.select(0,0,y.w,(y.h + 1)/2));
            std::thread thread_obj2(thr, std::ref(M2), x, y.select(0,(y.h + 1)/2,y.w,y.h));

            thread_obj1.join();
            thread_obj2.join();
            M = M1.merge_right(M2);
        }

        else if (y.h == 1)
        {
            Matrix M1, M2;
            std::thread thread_obj1(thr, std::ref(M1), x.select(0,0,(x.w + 1)/2,x.h), y);
            std::thread thread_obj2(thr, std::ref(M2), x.select((x.w + 1)/2,0,x.w,x.h), y);

            thread_obj1.join();
            thread_obj2.join();
            M = M1.merge_bottom(M2);
        }

        else
        {
            Matrix M1, M2, M3, M4;
            std::thread thread_obj1(thr, std::ref(M1), x.select(0,0,(x.w + 1)/2,x.h), y.select(0,0,y.w,(y.h + 1)/2));
            std::thread thread_obj2(thr, std::ref(M2), x.select((x.w + 1)/2,0,x.w,x.h), y.select(0,0,y.w,(y.h + 1)/2));
            std::thread thread_obj3(thr, std::ref(M3), x.select(0,0,(x.w + 1)/2,x.h), y.select(0,(y.h + 1)/2,y.w,y.h));
            std::thread thread_obj4(thr, std::ref(M4), x.select((x.w + 1)/2,0,x.w,x.h), y.select(0,(y.h + 1)/2,y.w,y.h));

            thread_obj1.join();
            thread_obj2.join();
            thread_obj3.join();
            thread_obj4.join();
            M1 = M1.merge_bottom(M2);
            M3 = M3.merge_bottom(M4);
            M = M1.merge_right(M3);
        }
    }
    else
        throw invalid_argument("x.h != y.w");
}
**/

using namespace std;

class Matrix
{
public:
    int w, h;
    vector<vector<int>> m;

    Matrix()
    {
        w = 1;
        h = 1;
        m.resize(1);
        m.back().resize(1);
        m[0][0] = 0;
    }

    Matrix(int x, int y)
    {
        w = x;
        h = y;
        m.resize(w);

        #pragma omp parallel for
        for (int i = 0; i < w; ++i)
            m[i].resize(h);
    }

    Matrix(vector<vector<int>> v)
    {
        w = v.size();
        h = v.back().size();

        m.resize(w);

        #pragma omp parallel
        {
            #pragma omp for nowait
            for (int i = 0; i < w; ++i)
                m[i].resize(h);

            #pragma omp for nowait
            for (int i = 0; i < w; ++i)
            {
                for (int j = 0; j < h; ++j)
                {
                    m[i][j] = v[i][j];
                }
            }
        }
    }

    Matrix select(int x1, int y1, int x2, int y2) const
    {
        Matrix M(x2-x1, y2-y1);

        #pragma omp parallel for
        for (int i = 0; i < M.w; ++i)
        {
            for (int j = 0; j < M.h; ++j)
            {
                M.m[i][j] = m[x1 + i][y1 + j];
            }
        }

        return M;
    }

    Matrix merge_right(const Matrix& x) const
    {
        Matrix M(w, h + x.h);

        #pragma omp parallel for
        for (int i = 0; i < w; ++i)
        {
            for (int j = 0; j < h; ++j)
            {
                M.m[i][j] = m[i][j];
            }

            for (int j = 0; j < x.h; ++j)
            {
                M.m[i][j + h] = x.m[i][j];
            }
        }

        return M;
    }

    Matrix merge_bottom(const Matrix& x) const
    {
        Matrix M(w + x.w, h);

        #pragma omp parallel for
        for (int j = 0; j < h; ++j)
        {
            for (int i = 0; i < w; ++i)
            {
                M.m[i][j] = m[i][j];
            }

            for (int i = 0; i < x.w; ++i)
            {
                M.m[i + w][j] = x.m[i][j];
            }
        }

        return M;
    }

    void print() const
    {
        for (int i = 0; i < w; ++i)
        {
            cout << "| ";
            for (int j = 0; j < h; ++j)
            {
                cout << m[i][j] << ' ';
            }

            cout << "|\n";
        }
    }
};

Matrix thr(const Matrix& x, const Matrix& y)
{
    cout << omp_get_thread_num() << " start\n";

    if (x.h == y.w)
    {
        if (x.w == 1 && y.h == 1)
        {
            Matrix M(x.w, y.h);
            M.m[0][0] = 0;

            #pragma omp parallel for
            for (int i = 0; i < x.h; ++i)
            {
                M.m[0][0] += x.m[0][i] * y.m[i][0];
            }

            cout << omp_get_thread_num() << " end\n";
            return M;
        }
        else if (x.w == 1)
        {
            Matrix M1, M2;

            #pragma omp parallel sections
            {
                #pragma omp section
                M1 = thr(x, y.select(0,0,y.w,(y.h + 1)/2));
                #pragma omp section
                M2 = thr(x, y.select(0,(y.h + 1)/2,y.w,y.h));
            }

            cout << omp_get_thread_num() << " end\n";
            return M1.merge_right(M2);
        }
        else if (y.h == 1)
        {
            Matrix M1, M2;

            #pragma omp parallel sections
            {
                #pragma omp section
                M1 = thr(x.select(0,0,(x.w + 1)/2,x.h), y);
                #pragma omp section
                M2 = thr(x.select((x.w + 1)/2,0,x.w,x.h), y);
            }

            cout << omp_get_thread_num() << " end\n";
            return M1.merge_bottom(M2);
        }
        else
        {
            Matrix M1, M2, M3, M4;

            #pragma omp parallel sections
            {
                #pragma omp section
                M1 = thr(x.select(0,0,(x.w + 1)/2,x.h), y.select(0,0,y.w,(y.h + 1)/2));
                #pragma omp section
                M2 = thr(x.select((x.w + 1)/2,0,x.w,x.h), y.select(0,0,y.w,(y.h + 1)/2));
                #pragma omp section
                M3 = thr(x.select(0,0,(x.w + 1)/2,x.h), y.select(0,(y.h + 1)/2,y.w,y.h));
                #pragma omp section
                M4 = thr(x.select((x.w + 1)/2,0,x.w,x.h), y.select(0,(y.h + 1)/2,y.w,y.h));
            }

            #pragma omp parallel sections
            {
                #pragma omp section
                M1 = M1.merge_bottom(M2);
                #pragma omp section
                M3 = M3.merge_bottom(M4);
            }

            cout << omp_get_thread_num() << " end\n";
            return M1.merge_right(M3);
        }
    }
    else
        throw invalid_argument("x.h != y.w");
}

int main()
{
    omp_set_nested(3);
    omp_set_num_threads(10);
    int aw, ah, bw, bh;
    vector<vector<int>> va, vb;
    ifstream fi;
    fi.open("input.txt");

    fi >> aw >> ah;
    va.resize(aw);

    for (int i = 0; i < aw; ++i)
    {
        va[i].resize(ah);

        for (int j = 0; j < ah; ++j)
        {
            fi >> va[i][j];
        }
    }

    fi >> bw >> bh;
    vb.resize(bw);

    for (int i = 0; i < bw; ++i)
    {
        vb[i].resize(bh);

        for (int j = 0; j < bh; ++j)
        {
            fi >> vb[i][j];
        }
    }

    Matrix
    A(va),
    B(vb),
    C = thr(A, B);

    cout << endl;
    A.print();
    cout << "X" << endl;
    B.print();
    cout << "=" << endl;
    C.print();
}
