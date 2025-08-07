/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 17:51:45 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//START HERE, THEN MAKE SURE THE FT_EAT IS INCREMENTING CORRECTLY

void	*ft_control_turns(void *arg)
{
	t_args *args;
	int		id;

	id = *(int *)arg;
	free(arg);
	args = ft_args();
	while (1)
	{
		pthread_mutex_lock(&args->kill_mutex);
		if (args->kill_waiters == true)
		{
			//printf("exiting\n");
			pthread_mutex_unlock(&args->kill_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&args->kill_mutex);
		sem_wait(args->waiters[id].my_sem);
		sem_post(args->waiters[id].left_sem);
		usleep(1000);
	}
	return (NULL);
}

int	ft_allocate_waiter_arrays(t_args *args)
{
	int 	i;
	char	*id;
	int		j;

	args->waiters = malloc((args->nb_philo) * sizeof(t_waiter));
	if (args->waiters == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		return (1);
	}
	memset(args->waiters, 0, (args->nb_philo) * sizeof(t_waiter));
	args->w_threads = malloc((args->nb_philo) * sizeof(pthread_t));
	if (args->w_threads == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiters);
		return (1);
	}
	memset(args->w_threads, 0, (args->nb_philo) * sizeof(pthread_t));
	
	args->all_philo_sems = malloc((args->nb_philo) * sizeof(sem_t *));
	if (args->all_philo_sems == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiters);
		free(args->w_threads);
		return (1);
	}
	memset(args->all_philo_sems, 0, (args->nb_philo) * sizeof(sem_t *));
 	args->philo_sems_names = malloc((args->nb_philo) * sizeof(char *));
	if (args->philo_sems_names == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiters);
		free(args->w_threads);
		free(args->all_philo_sems);
		return (1);
	}
	i = 0;
	while (i < args->nb_philo)
	{
		args->philo_sems_names[i] = malloc(20 * sizeof(char));
		if (args->philo_sems_names[i] == NULL)
		{
			ft_puterror("Allocation error");
			j = 0;
			while (j < i)
				free(args->philo_sems_names[j++]);
			sem_close(args->print_sem);
			free(args->waiters);
			free(args->w_threads);
			free(args->all_philo_sems);			
			free(args->philo_sems_names);
			return (1);
		}
		i++;
	}

	i = 0;
	args->all_waiter_sems = malloc((args->nb_philo) * sizeof(sem_t *));
	if (args->all_waiter_sems == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiters);
		free(args->w_threads);
		free(args->all_philo_sems);
		while (i < args->nb_philo)	
			free(args->philo_sems_names[i++]);
		free(args->philo_sems_names);
		return (1);
	}
	memset(args->all_waiter_sems, 0, (args->nb_philo) * sizeof(sem_t *));
	i = 0;
 	args->waiter_sems_names = malloc((args->nb_philo) * sizeof(char *));
	if (args->waiter_sems_names == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiters);
		free(args->w_threads);
		free(args->all_philo_sems);
		while (i < args->nb_philo)	
			free(args->philo_sems_names[i++]);
		free(args->philo_sems_names);
		free(args->all_waiter_sems);
		return (1);
	}
	i = 0;
	while (i < args->nb_philo)
	{
		args->waiter_sems_names[i] = malloc(22 * sizeof(char));
		if (args->waiter_sems_names[i] == NULL)
		{
			ft_puterror("Allocation error");
			sem_close(args->print_sem);
			free(args->waiters);
			free(args->w_threads);
			free(args->all_philo_sems);
			while (i < args->nb_philo)	
				free(args->philo_sems_names[i++]);
			free(args->philo_sems_names);
			free(args->all_waiter_sems);
			j = 0;
			while (j < i)
				free(args->waiter_sems_names[j++]);
			free(args->waiter_sems_names);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < args->nb_philo)
	{
		id = ft_itoa(i);
		ft_strlcpy(args->philo_sems_names[i], "/turn_id_", 20);
		ft_strlcat(args->philo_sems_names[i], id, 20);
		ft_strlcpy(args->waiter_sems_names[i], "/waiter_id_", 22);
		ft_strlcat(args->waiter_sems_names[i], id, 22);
		free(id);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		if (i % 2 != 0)
			args->all_philo_sems[i] = sem_open(args->philo_sems_names[i], O_CREAT, 0600, 1);
		else
			args->all_philo_sems[i] = sem_open(args->philo_sems_names[i], O_CREAT, 0600, 0);
		args->all_waiter_sems[i] = sem_open(args->waiter_sems_names[i], O_CREAT, 0600, 0);
		if (args->all_philo_sems[i] == SEM_FAILED || args->all_waiter_sems[i] == SEM_FAILED )
		{
			ft_puterror("sem_open failed\n");
			return(1);
		}
		i++;
	}
	return (0);
}
//int id t_waiter	*ft_init_waiter()
// {
// 	static t_waiter	waiter;

// 	return (&waiter);
// }

int	ft_thread_waiters(t_args *args)
{
	int i;

	i = 0;
	while (i < args->nb_philo)
	{
		int *thread_id = malloc(sizeof(int));
		if (!thread_id)
			return (1); // handle error properly
		*thread_id = i;
		ft_open_waiter_sems(i);
		if (pthread_create(&args->w_threads[i], NULL, ft_control_turns, thread_id) != 0)
		{
			ft_puterror("Could not initialize thread");
			free(thread_id); // prevent memory leak
			return (1);
		}
		i++;
	}
	return (0);
}
int	ft_waiter(t_args *args)
{
	//t_waiter	*waiter;
	
	//waiter = ft_init_waiter();
	//waiter->kill_waiter = false;
	//ft_allocate_waiter_arrays(args, waiter); //error check!!!
	if (pthread_mutex_init(&args->kill_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	ft_thread_waiters(args);
	return (0);
}