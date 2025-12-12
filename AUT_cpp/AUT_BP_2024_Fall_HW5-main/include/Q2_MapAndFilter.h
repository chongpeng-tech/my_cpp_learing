void map(double *arr, int size, double (*func)(double));

double *filter(const double *arr, int size, bool (*func)(double));