

#include "../include/codexion.h"

bool parse_required_compiles(char **av, t_config *config)
{
    if ((config->number_of_compiles_required = ft_atoi(av[6])) == -1)
    {
        error_out_of_range("number_of_compiles_required", av[6]);
        return (false);
    }
    return (true);
}