#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void linspace(double start, double end, int steps, double *array) {
if (steps==1){
array[0]=start;
}else{
    double step = (end - start) / (steps - 1);
    for (int i = 0; i < steps; i++) {
        array[i] = start + i * step;
    }
}
}

int main() {
    Config config;
    if (!load_config("input.yaml", &config)) {
        fprintf(stderr, "Failed to load config\n");
        return 1;
    }

    int size_M = config.M.steps;
    int size_b = config.b.steps;
    int size_L = config.L.steps;
    int size_mu = config.mu.steps;
    int size_phi = config.phi.steps;

    double *Ms = (double *)malloc(size_M * sizeof(double));
    double *bs = (double *)malloc(size_b * sizeof(double));
    double *Ls = (double *)malloc(size_L * sizeof(double));
    double *mus = (double *)malloc(size_mu * sizeof(double));
    double *phis = (double *)malloc(size_phi * sizeof(double));

    linspace(config.M.start, config.M.end, config.M.steps, Ms);
    linspace(config.b.start, config.b.end, config.b.steps, bs);
    linspace(config.L.start, config.L.end, config.L.steps, Ls);
    linspace(config.mu.start, config.mu.end, config.mu.steps, mus);
    linspace(config.phi.start, config.phi.end, config.phi.steps, phis);


    FILE *csv_file = fopen("output.csv", "w");
    if (!csv_file) {
        fprintf(stderr, "Failed to open output.csv for writing\n");
        return 1;
    }

    // Запись заголовка CSV файла
    fprintf(csv_file, "M,b,L,mu,phi\n");

    for (int i = 0; i < size_M; i++) {
        for (int j = 0; j < size_b; j++) {
            for (int k = 0; k < size_L; k++) {
                for (int l = 0; l < size_mu; l++) {
                    for (int m = 0; m < size_phi; m++) {
                        double M = Ms[i];
                        double b = bs[j];
                        double L = Ls[k];
                        double mu = mus[l];
                        double phi = phis[m];

                        // Запись значений в CSV файл
                        fprintf(csv_file, "%f,%f,%f,%f,%f\n", M, b, L, mu, phi);
                    }
                }
            }
        }
    }

    fclose(csv_file);

    free(Ms);
    free(bs);
    free(Ls);
    free(mus);
    free(phis);

    return 0;
}
