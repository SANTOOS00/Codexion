#include "stdio.h"
typedef enum e_arg_type
{
	number_of_coders,
	time_to_burnout,
	time_to_compile,
	time_to_refactor,
	number_of_compiles_required,
	dongle_cooldown,
} t_arg_type;

int main()
{
    t_arg_type *test;

    printf("%s\n", test[3]);
}
