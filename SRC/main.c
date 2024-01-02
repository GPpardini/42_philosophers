/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:00:40 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/22 12:30:36 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	check_inputs(char **argv)
{
	if (check_is_num(argv) == 0)
		return (write(1, "invalid chars as arguments\n", 28), 1);
	if (ft_atoi(argv[1]) < 1)
		return (write(1, "invalid philosophers count\n", 28), 1);
	if (ft_atoi(argv[2]) < 1)
		return (write(1, "invalid survival hungry time \n", 31), 1);
	if (ft_atoi(argv[3]) < 1)
		return (write(1, "invalid eating time\n", 21), 1);
	if (ft_atoi(argv[4]) < 1)
		return (write(1, "invalid sleeping time\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 1))
		return (write(1, "invalid meal count\n", 20), 1);
	return (0);
}

void	end_program(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->finish_lock);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (write(1, "Wrong argument count\n", 22), 1);
	if (check_inputs(argv))
		return (1);
	start_data(argv, &data);
	start_forks(&data);
	philos = start_philos(&data);
	start_threads(philos, &data, data.philo_count);
	end_program(&data);
	free(philos);
	free(data.fork_lock);
	return (0);
}
