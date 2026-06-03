


#include "../include/codexion.h"


bool parser_time_val(char **av, t_config *config)
{
    if ((config->time_to_burnout = ft_atoi(av[2])) == -1)        
        return (error_out_of_range("time_to_burnout",av[2]), false);
    if ((config->time_to_compile = ft_atoi(av[3])) == -1)
        return (error_out_of_range("time_to_compile",av[3]), false);
    if ((config->time_to_debug = ft_atoi(av[4])) == -1)
        return (error_out_of_range("time_to_debug",av[4]), false);
    if ((config->time_to_refactor = ft_atoi(av[5])) == -1)
        return (error_out_of_range("time_to_refactor",av[5]), false);
    if ((config->dongle_cooldown = ft_atoi(av[7])) == -1)
        return (error_out_of_range("dongle_cooldown",av[7]), false);
    return (true);
}