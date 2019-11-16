/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:21:47 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 12:21:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			ft_itoa_base_compute_number_size(long number, size_t radix)
{
	size_t	size;

	size = (number < 0 ? 1 : 0);
	while (1)
	{
		number /= radix;
		size++;
		if (number == 0)
			break ;
	}
	return (size);
}

char			*ft_itoa_base(long n, char *base)
{
	long	number;
	size_t	radix;
	char	*array;
	size_t	size;

	number = n;
	radix = ft_strlen(base);
	size = ft_itoa_base_compute_number_size(n, radix);
	CHECK_MALLOC(array, (size + 1) * sizeof(char));
	if (number < 0)
	{
		array[0] = '-';
		number *= -1;
	}
	array[size] = '\0';
	while (1)
	{
		array[size - 1] = base[(number % radix)];
		number /= radix;
		size--;
		if (number == 0)
			break ;
	}
	return (array);
}
