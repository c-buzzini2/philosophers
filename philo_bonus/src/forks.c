/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/06 21:13:54 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
//START HERE!!!! Fork processes, wait[id, graceful termination]

void	ft_change_boolean(t_pids *pids, int exited, t_args *args)
{
	int i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].pid == exited)
		{
			pids[i].exited = true;
			break ;
		}
		i++;
	}
}

void	ft_kill_remaining_processes(t_pids *pids, t_args *args)
{
	int i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].exited == false)
			kill(pids[i].pid, SIGKILL);
		i++;
	}
}

int	ft_parent(t_args *args, t_pids *pids)
{
	int		e_status;
	int		exited_pid;
	int		e_code;
	int		exited_count;
	//t_waiter	*waiter;

	exited_count = 0;
	while (exited_count < args->nb_philo)
	{
		exited_pid = waitpid(-1, &e_status, 0);
		if (exited_pid > 0)
		{
			exited_count++;
			ft_change_boolean(pids, exited_pid, args);
			if (WIFEXITED(e_status)) 
			{
				e_code = WEXITSTATUS(e_status);
				if (e_code == 2 || e_code == 3) 
					ft_kill_remaining_processes(pids, args);
			}
		}
	}
	//waiter = ft_init_waiter();
	pthread_mutex_lock(&args->waiter.waiter_mutex);
	args->waiter.kill_waiter = true;
	pthread_mutex_unlock(&args->waiter.waiter_mutex);
	sem_post(args->waiter_sem);
	free(pids);
	ft_close_arr_sems();
	pthread_mutex_destroy(&args->waiter.waiter_mutex);
	pthread_join(args->waiter.w_thread, NULL);
	return (0);
}

t_philo	*ft_create_philo(void)
{
	static t_philo	philo;

	return (&philo);
}

t_pids	*ft_allocate_pids(t_args *args)
{
	t_pids	*pids;
	
	pids = malloc(args->nb_philo * sizeof(t_pids));
	if (pids == NULL)
	{
		perror("Error in allocation");
		sem_close(args->print_sem);
		ft_unlink_semaphores();
		exit(1);
	}
	return (pids);
}

int	ft_forks(t_args *args)
{
	int		id;
	int		forks;
	t_philo	*philo;
	t_pids	*pids;
	int		i;		

	i = 0;
	forks = 0;
	pids = ft_allocate_pids(args);
	ft_allocate_waiter_arrays(args);//error check
	gettimeofday(&args->start_time, NULL);
	while (forks < args->nb_philo)
	{
		id = fork();
		if (id == -1)
		{
			perror("Error in the fork");
			sem_close(args->print_sem);
			ft_unlink_semaphores();
			exit(1);
		}
		if (id == 0)
		{
			free(pids);
			ft_close_arr_sems();
			philo = ft_create_philo();
			philo->id = forks;
			if (ft_mutex_and_thread(philo) == 1)
				return (3);
			ft_open_turn_sems(philo);
			ft_start_routine(philo);
		}
		else
		{
			pids[i].pid = id;
			pids[i].exited = false;
		}
		forks++;
		i++;
	}
	ft_waiter(args);//handle error return 1
	return (ft_parent(args, pids));
}
