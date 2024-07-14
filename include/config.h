#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    double start;
    double end;
    int steps;
} ParameterRange;

typedef struct {
    ParameterRange M;
    ParameterRange b;
    ParameterRange L;
    ParameterRange mu;
    ParameterRange phi;
} Config;

int load_config(const char *filename, Config *config);

#endif // CONFIG_H
