/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:18:25 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 20:47:05 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		ln;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ln = count_size(n);
	ptr = (char *)malloc(sizeof(char) * (ln + 1));
	if (!ptr)
		return (NULL);
	ptr[ln--] = '\0';
	if (n == 0)
		ptr[0] = '0';
	while (n)
	{
		if (n < 0)
		{
			n *= -1;
			ptr[0] = '-';
		}
		ptr[ln] = (n % 10) + 48;
		n /= 10;
		ln--;
	}
	return (ptr);
}
