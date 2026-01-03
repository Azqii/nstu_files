#include "globals.h"

int M = 3;
int MAX_CLIENT = 6;
int entered = 0;
int completed = 0;
long int* ro = nullptr;
float serve_ave = 0;
float num_ave = 0;
float soj_ave = 0;
float que1_ave = 0;
float orders_ave = 0;
float busy_ave = 0;
int total_ordered = 0;

FILE* sojourn = nullptr;
FILE* num = nullptr;
FILE* order = nullptr;
long int total = 0;
