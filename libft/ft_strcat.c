/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:29:25 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:07:32 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t len_s1;

	i = 0;
	len_s1 = ft_strlen(s1);
	while (s2[i])
		s1[len_s1++] = s2[i++];
	s1[len_s1] = '\0';
	return (s1);
}
