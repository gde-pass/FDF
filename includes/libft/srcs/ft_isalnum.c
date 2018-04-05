/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:07:29 by gde-pass          #+#    #+#             */
/*   Updated: 2017/11/16 15:58:15 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isalnum(int c)
{
	if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) \
		|| ((c >= 'a') && (c <= 'z')))
		return (1);
	else
		return (0);
}
