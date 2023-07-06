#include <omp.h>
#include <stdio.h>

void task_fun(int id, int v) {
    int eid = omp_get_thread_num();

    printf("generated by id: %d, executed by id: %d, i: %d\n", id, eid, v);
}

int main() {
#pragma omp parallel
    {
        int id;
        int i;

        id = omp_get_thread_num();

#pragma omp master
        for(i = 0; i < 200; ++i) {
#pragma omp task untied
            task_fun(id, i);
        }
    }

    return 0;
}