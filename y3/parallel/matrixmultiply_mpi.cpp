#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char** argv)
{
    int rank, n_ranks;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&n_ranks);

    struct timeval tstart, tstop;
    int *ma, *mb, *mc;
    int ha, hb, wa, wb;
    int *p = NULL, *s = NULL, *g = NULL, *w = NULL;

    if (rank == 0)
    {
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
        g = (int*) malloc(sizeof(int) * ha);
    }

    MPI_Bcast(&ha, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&hb, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&wa, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&wb, 1, MPI_INT, 0, MPI_COMM_WORLD);

    p = (int*) malloc(sizeof(int) * ha * wa / n_ranks);
    s = (int*) malloc(sizeof(int) * hb);
    w = (int*) malloc(sizeof(int) * ha / n_ranks);

    MPI_Scatter(ma, ha * wa / n_ranks, MPI_INT, p, ha * wa / n_ranks, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < wb; ++i)
    {
        if (rank == 0)
        {
            for (int j = 0; j < hb; ++j)
                s[j] = mb[j * wb + i];
        }

        MPI_Bcast(s, hb, MPI_INT, 0, MPI_COMM_WORLD);

        for (int j = 0; j < ha / n_ranks; ++j)
        {
            w[j] = 0;

            for (int k = 0; k < wa; ++k)
            {
                w[j] += p[j * wa + k] * s[k];
            }
        }

        MPI_Gather(w, ha / n_ranks, MPI_INT, g, ha / n_ranks, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0)
            for (int j = 0; j < ha; ++j)
                mc[j * wb + i] = g[j];

        MPI_Barrier(MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
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
    }

    // Call finalize at the end
    return MPI_Finalize();
}
