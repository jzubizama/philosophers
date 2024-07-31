/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:36:00 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:56:58 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philobonus.h"

void	ft_eat(t_philo *arg)
{
	sem_wait(arg->input->sem_fork);
	ft_print_change("has taken a fork", arg);
	if (arg->input->num_philo == 1)
	{
		ft_usleep(arg->input->t_die);
		sem_post(arg->input->sem_fork);
		return ;
	}
	sem_wait(arg->input->sem_fork);
	ft_print_change("has taken a fork", arg);
	sem_wait(arg->input->sem_read);
	(*arg).num_eaten++;
	(*arg).last_meal = get_current_time();
	ft_print_change("is eating", arg);
	sem_post(arg->input->sem_read);
	ft_usleep(arg->input->t_eat);
	sem_post(arg->input->sem_fork);
	sem_post(arg->input->sem_fork);
}

int	ft_read_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	sem_wait(philo->input->sem_dead);
	if ((philo->dead) == 1)
		ret = 1;
	sem_post(philo->input->sem_dead);
	return (ret);
}

void	ft_philo(t_philo *arg)
{
	pthread_t	monit;

	pthread_create(&monit, NULL, ft_monit, arg);
	pthread_detach(monit);
	if ((*arg).id % 2 != 0)
		usleep(50);
	while (!ft_read_dead(arg))
	{
		ft_eat(arg);
		sem_wait(arg->input->sem_print);
		ft_print_change("is sleeping", arg);
		sem_post(arg->input->sem_print);
		ft_usleep(arg->input->t_sleep);
		sem_wait(arg->input->sem_print);
		ft_print_change("is thinking", arg);
		sem_post(arg->input->sem_print);
	}
}

t_philo	*ft_philo_init(t_input *in)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * in->num_philo);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < in->num_philo)
	{
		philos[i].input = in;
		philos[i].id = i;
		philos[i].init_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].num_eaten = 0;
		philos[i].dead = 0;
	}
	return (philos);
}
