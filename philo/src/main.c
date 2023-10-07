/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oolkay <oolkay@42.tr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:06:34 by omer/baha         #+#    #+#             */
/*   Updated: 2023/10/07 14:51:07 by oolkay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/philo.h"

int	ft_eat_goal(t_table *table)
{
	int	i;
	int	eat_cnt;

	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_lock(&table->nb_eat_mutex);
		eat_cnt = table->philo[i].nb_eat;
		pthread_mutex_unlock(&table->nb_eat_mutex);
		if (eat_cnt < table->nb_eat)
			return (0);
	}
	pthread_mutex_lock(&table->dead_mutex);
	table->dead = 1;
	pthread_mutex_unlock(&table->dead_mutex);
	return (1);
}

static void	ft_exit(int err, t_table *table)
{
	int	i;

	i = -1;
	if (err == 0)
	{
		while (++i < table->nb_philo)
			pthread_mutex_destroy(&table->fork_mutex[i]);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->nb_eat_mutex);
		pthread_mutex_destroy(&table->dead_mutex);
		pthread_mutex_destroy(&table->last_eat_mutex);
		free(table->fork_mutex);
		free(table->philo);
	}
}

static int	ft_isdigit(char ch)
{
	if (ch <= '9' && ch >= '0')
		return (1);
	return (0);
}

static int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (ft_check_args(argc, argv))
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (ft_init_table(&table, argc, argv) == -2)
		return (-1);
	if (ft_init_philo(&table) == -2)
		return (-1);
	ft_exit(0, &table);
	return (0);
}
