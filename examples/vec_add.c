#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <winsock.h>

#define M_PI 3.14159265358979323846

int gettimeofday(struct timeval *tv, struct timezone *tz) {
    // 定义FILETIME结构体
    FILETIME ft;
    // 获取当前系统时间
    GetSystemTimeAsFileTime(&ft);

    // 将FILETIME结构体中的时间值转换为64位整数，单位位100纳秒
    ULARGE_INTEGER uliTime;
    uliTime.LowPart = ft.dwLowDateTime;
    uliTime.HighPart = ft.dwHighDateTime;
    uint64_t ullTime = uliTime.QuadPart;

    // 将时间值转换为自1970年1月1日00:00:00 UTC以来经过的微秒数
    static const uint64_t EPOCH_DIFFERENCE = 1164447360000000000LL;
    ullTime -= EPOCH_DIFFERENCE;
    ullTime /= 10;

    // 将时间值转换为struct timeval结构体
    tv->tv_sec = ullTime / 1000000;
    tv->tv_usec = ullTime % 1000000;

    return 0;
}

double omp_get_time(void) {
    struct timeval tv;
    double t;

    gettimeofday(&tv, (struct timezone*)0);
    t = tv.tv_sec + (double)tv.tv_usec * 1e-8;

    return t;
}

//int main(int argc, char **argv) {
//    int i, len = 10000000;
//    double *x, *y, *z;
//    double va_tm;
//    double t = 0.;
//
//    if(argc == 2) {
//        int tlen = atoi(argv[1]);
//
//        if(tlen > 0) len = tlen;
//    }
//
//    /* malloc memory, no check */
//    x = malloc(sizeof(*x) * len);
//    y = malloc(sizeof(*y) * len);
//    z = malloc(sizeof(*z) * len);
//
//#pragma omp parallel for
//    for(i = 0; i < len; ++i) {
//        x[i] = i + 0.3;
//        y[i] = i + M_PI;
//    }
//
//    va_tm = omp_get_time();
//    for(i = 0; i < len; ++i) t += x[i];
//    va_tm = omp_get_time() - va_tm;
//    printf("Serial result: %g, time: %g s\n", t, va_tm);
//
//    va_tm = omp_get_time();
//
//#pragma omp parallel for
//    for(i = 0; i < len; ++i) {
//        z[i] = x[i] + y[i];
//    }
//
//    va_tm = omp_get_time() - va_tm;
//    printf("OMP time: %g s\n", va_tm);
//
//    free(x);
//    free(y);
//    free(z);
//
//    return 0;
//}

//int main(int argc, char **argv) {
//    int len = 100000000;
//    double *x, *y, *z;
//    double va_tm;
//
//    if(argc == 2) {
//        int tlen = atoi(argv[1]);
//        if(tlen > 0) len = tlen;
//    }
//
//    /* malloc memory, no check */
//    x = malloc(sizeof(*x) * len);
//    y = malloc(sizeof(*y) * len);
//    z = malloc(sizeof(*z) * len);
//
//    va_tm = omp_get_time();
//
//#pragma omp parallel
//    {
//        int i;
//        int num_threads;
//        int id;
//        int blk;
//        int start, end;
//
//        num_threads = omp_get_num_threads();
//        id = omp_get_thread_num();
//
//        /* task division */
//        blk = (len + num_threads - 1) / num_threads;
//
//        /* starting and ending range */
//        start = id * blk;
//        end = start + blk;
//        if(end > len) end = len;
//
//        for(i = start; i < end; ++i) {
//            x[i] = i +0.3;
//            y[i] = i + M_PI;
//        }
//
//        for(i = start; i < end; ++i) {
//            z[i] = x[i] + y[i];
//        }
//    }
//
//    va_tm = omp_get_time() - va_tm;
//    printf("time: %g s\n", va_tm);
//
//    free(x);
//    free(y);
//    free(z);
//
//    return 0;
//}

int main(int argc, char** argv) {
    int i, len = 100000000;
    double *x, *y, *z;
    double va_tm;

    if(argc == 2) {
        int tlen = atoi(argv[1]);
        if(tlen > 0) len = tlen;
    }

    /* malloc memory, no check */
    x = malloc(sizeof(*x) * len);
    y = malloc(sizeof(*y) * len);
    z = malloc(sizeof(*z) * len);

    va_tm = omp_get_time();

#pragma omp parallel
#pragma omp for
    for(i = 0; i < len; ++i) {
        x[i] = i + 0.3;
        y[i] = i + M_PI;
    }

#pragma omp parallel for
    for(i = 0; i < len; ++i) {
        z[i] = x[i] + y[i];
    }

    va_tm = omp_get_time() - va_tm;
    printf("time: %g s\n", va_tm);

    free(x);
    free(y);
    free(z);

    return 0;
}