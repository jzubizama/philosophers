/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:09:44 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:57:30 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

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
	input->sem_fork = NULL;
	input->sem_dead = NULL;
	input->sem_read = NULL;
	input->sem_print = NULL;
	input->sem_meal = NULL;
	return (input);
}

void	ft_finish(t_input *d, t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < d->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < d->num_philo)
				kill(philos[i++].pid, SIGKILL);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_input		input;
	t_philo		*philos;

	if (!ft_fill_input(argv + 1, argc - 1, &input))
		return (2);
	philos = ft_philo_init(&input);
	ft_sem_create(&input);
	i = -1;
	while (++i < input.num_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			ft_philo(philos + i);
			exit (0);
		}
	}
	ft_finish(&input, philos);
	ft_destroy_sem(&input);
	free(philos);
	return (0);
}
