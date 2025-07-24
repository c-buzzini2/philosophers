/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:06 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 18:21:03 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static unsigned int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * neg);
}

static int ft_check_args(int argc, char **argv)
{
	int	i;
	int j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_puterror("You need 4 or 5 arguments");
		exit (1);
	}
    while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-') //corrigir, NENHUM NUMERO DEVE SER NEGATIVO
		{
			if (argv[i][j] == '-' || !argv[i][++j])
				return (1);
		}
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j++]) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void ft_allocate_philos(t_arrays *arrays, t_args *args)
{
	int		i;
	
	arrays->philos = malloc((args->nb_philo) * sizeof(t_philo));
	if (arrays->philos == NULL)
	{
		ft_puterror("Allocation error");
		exit (1);
	}
	i = 0;
    while (i < args->nb_philo)
	{
		arrays->philos[i].id = i;
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
		arrays->philos[i++].last_meal = 0;
}

int ft_parse_args(t_args *args, int argc, char **argv)
{
	if (ft_check_args(argc, argv) == 1)
	{
		ft_puterror("Arguments must be positive numbers");
		exit (1);
	}
	args->nb_philo = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->should_eat = ft_atoi(argv[5]);
	return (0);
}