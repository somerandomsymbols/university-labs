#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char** argv)
{
    struct timeval tstart, tstop;
    int *ma, *mb, *mc;
    int ha, hb, wa, wb;
    int *p = NULL, *s = NULL, *g = NULL, *w = NULL;
    FILE *fi;

    fi = fopen("input10X.txt", "r");
    fscanf(fi, "%d", &ha);
    fscanf(fi, "%d", &wa);
    ma = (int*) malloc(sizeof(int) * ha * wa);

    for (int i = 0; i < ha; ++i)
    {
        for (int j = 0; j < wa; ++j)
        {
            fscanf(fi, "%d", &ma[i * wa + j]);
        }
    }

    fscanf(fi, "%d", &hb);
    fscanf(fi, "%d", &wb);
    mb = (int*) malloc(sizeof(int) * hb * wb);

    for (int i = 0; i < hb; ++i)
    {
        for (int j = 0; j < wb; ++j)
        {
            fscanf(fi, "%d", &mb[i * wb + j]);
        }
    }

    fclose(fi);

    if (wa != hb)
        exit(1);

    mc = (int*) malloc(sizeof(int) * ha * wb);
    gettimeofday(&tstart, NULL);

    #pragma omp parallel for num_threads(12)
    for (int i = 0; i < ha; ++i)
    {
        for (int j = 0; j < wb; ++j)
        {
            mc[i * wb + j] = 0;

            for (int k = 0; k < wa; ++k)
                mc[i * wb + j] += ma[i * wa + k] * mb[k * wb + j];
        }
    }

    gettimeofday(&tstop, NULL);
    printf("time %dmcs\n", tstop.tv_sec*1000000LL + tstop.tv_usec - tstart.tv_sec*1000000LL - tstart.tv_usec);

    /*for (int i = 0; i < ha; ++i)
    {
        for (int j = 0; j < wb; ++j)
        {
            printf("%d ", mc[i * wb + j]);
        }

        printf("\n");
    }*/

    return 0;
}
