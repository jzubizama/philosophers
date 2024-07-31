/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:09:44 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/02 21:56:49 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	ft_check_args(char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_input	*ft_fill_input(char **argv, int argc, t_input *input)
{
	if (argc != 4 && argc != 5)
		return (NULL);
	if (!ft_check_args(argv, argc))
		return (NULL);
	input->num_philo = ft_atoi(argv[0]);
	input->t_die = ft_atoi(argv[1]);
	input->t_eat = ft_atoi(argv[2]);
	input->t_sleep = ft_atoi(argv[3]);
	if (argc > 4)
		input->num_times_eat = ft_atoi(argv[4]);
	else
		input->num_times_eat = -1;
	return (input);
}

int	ft_init_monit(t_monitor *monit, t_philo *philos)
{
	if (pthread_mutex_init(&monit->dead_mut, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monit->read_mut, NULL) != 0)
		return (2);
	monit->dead = 0;
	monit->philos = philos;
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_input		input;
	t_philo		*philos;
	t_monitor	monit;

	if (!ft_fill_input(argv + 1, argc - 1, &input))
		return (2);
	philos = malloc(sizeof(t_philo) * input.num_philo);
	if (!philos)
		return (3);
	i = -1;
	ft_init_monit(&monit, philos);
	while (++i < input.num_philo)
		ft_init_philo(i, &philos[i], &monit, input);
	if (pthread_create(&monit.th, NULL, &ft_monit, &monit) != 0)
		return (3);
	i = -1;
	while (++i < input.num_philo)
		if (pthread_join(philos[i].th, NULL) != 0)
			return (4);
	if (pthread_join(monit.th, NULL) != 0)
		return (5);
	ft_destroy_mut(philos, &monit);
	free(philos);
	return (0);
}
