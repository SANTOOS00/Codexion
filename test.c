


// #include <sys/time.h>
// #include <stdio.h>
// #include <stdlib.h>

// // unsigned long	ft_gettime_ms(void)
// // {
// 	// 	struct timeval	new;
	
// 	// 	gettimeofday(&new , NULL);
// 	// 	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
// 	// }
	
// 	// unsigned long	ft_gettime(unsigned long time_create_coder)
// 	// {
// 		// 	return (ft_gettime_ms() - time_create_coder);
// 		// }
		
// typedef struct s_data
// {
// 	int val_randm;
// } t_data;


// void swap_pointers(void **ptr_addr_a, void **ptr_addr_b)
// {
//     void *temp_ptr;

//     temp_ptr = *ptr_addr_a;
//     *ptr_addr_a = *ptr_addr_b;
//     *ptr_addr_b = temp_ptr;
// }

// int get_index_parent(int index)
// {
// 	return (index - 1) / 2;
// }

// int left_cheld(int index)
// {
// 	return (index * 2) + 1;
// }

// int right_cheld(int index)
// {
// 	return (index * 2) + 2;
// }

// void test(int index, t_data **arry)
// {
// 	printf("sdsd\n");
// 	while(index != 0 && arry[get_index_parent(index)]->val_randm  > arry[index]->val_randm)
// 	{
// 		printf("sdsd\n");
// 		swap_pointers((void *)&arry[get_index_parent(index)], (void *)&arry[index]);
// 		index = get_index_parent(index);
// 	}
// 	return ;
// }

// int main()
// {
// 	t_data **arry;
	
// 	arry = malloc(sizeof(t_data **) * 9);
// 	int i = 0;
// 	int tb[] = {2, 8, 5, 0, 3, 9, -1, 55};
// 	while(i < 8)
// 	{
// 		arry[i] = malloc(sizeof(t_data));
//     	arry[i]->val_randm = tb[i];
// 		test(i, arry);
// 		i++;
// 	}

// 	arry[i] = malloc(sizeof(t_data));
// 	arry[i]->val_randm = 6.7;
// 	test(i, arry);
// 	i = 0;
// 	while(i < 9)
// 		{printf("%d \n", arry[i]->val_randm);i++;}
// 	return (0);
// }



// // void push_arry(void **point, int index, t_data **arry)
// // {
// // 	arry[index] = *point;
// // 	sort(index, arry);
// // 	return ;
// // }


// #include "codexion.h"

// int main() {
//     struct timespec ts;

//     // Retrieve the current real-time clock value
//     if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) == 0) {
//         printf("Seconds: %ld\n", ts.tv_sec);
//         printf("Nanoseconds: %ld\n", ts.tv_nsec);
//     } else {
//         perror("clock_gettime");
//     }

//     return 0;
// }
