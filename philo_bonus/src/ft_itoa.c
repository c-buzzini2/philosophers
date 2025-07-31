/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:33:59 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 09:05:27 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*ft_int_zero(void)
{
	char	*final_str;

	final_str = (char *) malloc (2);
	if (final_str == NULL)
		return (NULL);
	ft_bzero(final_str, 2);
	final_str[0] = '0';
	final_str[1] = '\0';
	return (final_str);
}

static char	*ft_convert(int nb, char *num_str)
{
	int		i;
	long	lnb;
	int		neg;

	i = 0;
	lnb = nb;
	neg = 0;
	if (lnb < 0)
	{
		lnb = -lnb;
		neg = 1;
	}
	while (lnb > 0)
	{
		num_str[i] = (lnb % 10) + '0';
		lnb = lnb / 10;
		i++;
	}
	if (neg == 1)
	{
		num_str[i] = '-';
		i++;
	}
	num_str[i] = '\0';
	return (num_str);
}

char	*ft_itoa(int n)
{
	char	*final_str;
	char	num_str[12];
	int		len_str;
	char	*temp_str;
	int		i;

	i = 0;
	if (n == 0)
		return (ft_int_zero());
	temp_str = ft_convert(n, num_str);
	len_str = ft_strlen(temp_str) + 1;
	final_str = (char *) malloc (len_str * sizeof(char));
	if (final_str == NULL)
		return (NULL);
	ft_bzero(final_str, len_str);
	while (temp_str[i] != 0)
	{
		final_str[i] = temp_str[len_str - 2];
		i++;
		len_str--;
	}
	final_str[i] = '\0';
	return (final_str);
}
