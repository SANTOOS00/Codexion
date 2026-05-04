#include "codexion.h"



int main(int ac, char **av)
{
    t_simulation simulation;

    if (!ft_init_simulation(av, ac, &simulation))
        return (1);
    ft_run_coders_threads(&simulation);
    ft_join_coders_threads(&simulation);
}
