/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:44:45 by gde-pass          #+#    #+#             */
/*   Updated: 2017/11/16 16:01:01 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_toupper(int c)
{
	int		error;

	error = c;
	if ((c >= 'a') && (c <= 'z'))
	{
		c = c - 32;
		return (c);
	}
	else
		return (error);
}