#ifndef MODELING_KR_GLOBALS_H
#define MODELING_KR_GLOBALS_H

#include <cstdio>

extern int M;
extern int MAX_CLIENT;
extern int entered;
extern int completed;
extern long int* ro;
extern float serve_ave;
extern float num_ave;
extern float soj_ave;
extern float que1_ave;
extern float orders_ave;
extern float busy_ave;
extern int total_ordered;

extern FILE* sojourn;
extern FILE* num;
extern FILE* order;
extern long int total;

#endif //MODELING_KR_GLOBALS_H
