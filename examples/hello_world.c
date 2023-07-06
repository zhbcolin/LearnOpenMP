#include <omp.h>
#include <stdio.h>

int main() {
//#pragma omp parallel
//    {
//        printf("Hello World!\n");
//    }

//#pragma omp parallel num_threads(4)
//    {
//        printf("Hello World!\n");
//    }

//    omp_set_num_threads(3);
//
//#pragma omp parallel
//    {
//        printf("Hello World!\n");
//    };

//    omp_set_num_threads(3);
//
//#pragma omp parallel num_threads(6)
//    {
//        printf("Hello World!\n");
//    }

//    printf("serial part, total number of threads: %d\n\n", omp_get_num_threads());
//
//#pragma omp parallel
//    {
//        printf("Hello World, total number of threads: %d\n", omp_get_num_threads());
//    };

#pragma omp parallel
    {
        printf("Hello World, thread number: %d\n", omp_get_thread_num());
    }

    return 0;
}