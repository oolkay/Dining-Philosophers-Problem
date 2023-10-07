/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:45:32 by acepni            #+#    #+#             */
/*   Updated: 2023/10/07 14:16:19 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "../includes/philo.h"

void	my_sleep(long long time)
{
	long long	now;

	now = philo_get_time();
	while (philo_get_time() - now < time)
		usleep(100);
}

int	ft_print(t_philo *philo, char *str)
{
	long	time;

	if (ft_check_dead_philo(philo->table))
		return (-1);
	time = philo_get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("[\033[1;39m%06ld\033[0;39m]  \033[1;96m%d  \033[0;39m%s\n", \
			time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}

static int	find_signs(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = find_signs(str);
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb = nb + (str[i] - '0');
		i++;
	}
	nb *= sign;
	return (nb);
}

long	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
