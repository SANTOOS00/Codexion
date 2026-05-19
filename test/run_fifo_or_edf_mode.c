#include "codexion.h"

void    run_fifo_or_edf_routine(t_simulation *sim)
{
    if(sim->config.scheduler == FIFO)
        run_fifo_routine(sim);
    else if (sim->config.scheduler == EDF)
        run_edf_routine(sim);
}