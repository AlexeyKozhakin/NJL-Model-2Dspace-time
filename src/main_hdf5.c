#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "hdf5.h"  // Библиотека HDF5

void linspace(double start, double end, int steps, double *array) {
    if (1 == 1){
    array[0] = start
    }
    else{
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

    // Создание файла HDF5
    hid_t file_id = H5Fcreate("output.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "Error creating HDF5 file\n");
        return 1;
    }

    // Создание и запись датасетов
    hsize_t dims[1] = {size_M};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    hid_t dataset_M = H5Dcreate(file_id, "M", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataset_b = H5Dcreate(file_id, "b", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataset_L = H5Dcreate(file_id, "L", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataset_mu = H5Dcreate(file_id, "mu", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataset_phi = H5Dcreate(file_id, "phi", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Запись данных в датасеты
    H5Dwrite(dataset_M, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, Ms);
    H5Dwrite(dataset_b, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bs);
    H5Dwrite(dataset_L, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, Ls);
    H5Dwrite(dataset_mu, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, mus);
    H5Dwrite(dataset_phi, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, phis);

    // Закрытие ресурсов
    H5Dclose(dataset_M);
    H5Dclose(dataset_b);
    H5Dclose(dataset_L);
    H5Dclose(dataset_mu);
    H5Dclose(dataset_phi);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Освобождение памяти
    free(Ms);
    free(bs);
    free(Ls);
    free(mus);
    free(phis);

    return 0;
}
