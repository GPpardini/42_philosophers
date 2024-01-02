/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:54:22 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/15 13:26:53 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	check_is_num(char **str)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	while (str[i])
	{
		while (str[i][y])
		{
			if (str[i][y] > '9' || str[i][y] < '0')
				return (0);
			y++;
		}
		i++;
		y = 0;
	}
	return (1);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(200);
	return (0);
}

void	msg(t_philo *philo, char *msg)
{
	size_t	time;

	time = get_time() - philo->start_time;
	if (!philo_dead_flag(philo))
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%zu %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(philo->write_lock);
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
