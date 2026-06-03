

#include "../include/codexion.h"

void error_out_of_range(const char *arg_name, const char *value)
{
    fprintf(stderr, 
        "Error: '%s' must be between 0 and INT_MAX (got '%s').\n",
        arg_name, value);
}