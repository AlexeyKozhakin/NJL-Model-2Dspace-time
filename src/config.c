#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>
#include "config.h"

int load_parameter_range(yaml_parser_t *parser, ParameterRange *range) {
    yaml_event_t event;

    while (1) {
        if (!yaml_parser_parse(parser, &event)) {
            return 0;
        }
        if (event.type == YAML_MAPPING_END_EVENT) {
            break;
        }
        if (event.type == YAML_SCALAR_EVENT) {
            char *key = (char *) event.data.scalar.value;
            yaml_event_t value_event;
            if (!yaml_parser_parse(parser, &value_event)) {
                return 0;
            }
            char *value = (char *) value_event.data.scalar.value;
            if (strcmp(key, "start") == 0) {
                range->start = atof(value);
            } else if (strcmp(key, "end") == 0) {
                range->end = atof(value);
            } else if (strcmp(key, "steps") == 0) {
                range->steps = atoi(value);
            }
            yaml_event_delete(&value_event);
        }
        yaml_event_delete(&event);
    }
    return 1;
}

int load_config(const char *filename, Config *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return 0;
    }

    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser\n");
        fclose(file);
        return 0;
    }

    yaml_parser_set_input_file(&parser, file);
    yaml_event_t event;

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            return 0;
        }

        if (event.type == YAML_MAPPING_START_EVENT) {
            continue;
        }

        if (event.type == YAML_MAPPING_END_EVENT) {
            break;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            char *key = (char *) event.data.scalar.value;
            if (!yaml_parser_parse(&parser, &event)) {
                return 0;
            }

            if (strcmp(key, "M") == 0) {
                if (!load_parameter_range(&parser, &config->M)) {
                    return 0;
                }
            } else if (strcmp(key, "b") == 0) {
                if (!load_parameter_range(&parser, &config->b)) {
                    return 0;
                }
            } else if (strcmp(key, "L") == 0) {
                if (!load_parameter_range(&parser, &config->L)) {
                    return 0;
                }
            } else if (strcmp(key, "mu") == 0) {
                if (!load_parameter_range(&parser, &config->mu)) {
                    return 0;
                }
            } else if (strcmp(key, "phi") == 0) {
                if (!load_parameter_range(&parser, &config->phi)) {
                    return 0;
                }
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    fclose(file);
    return 1;
}
