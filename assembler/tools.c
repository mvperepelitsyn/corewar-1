/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerhold <ggerhold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:23:44 by ggerhold          #+#    #+#             */
/*   Updated: 2019/10/16 18:59:16 by ggerhold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_get_type_of_file(char *file_name, char *needle)
{
	int		i;
	int		j;
	char	*file_type;

	if (!file_name || !needle)
		return (0);
	i = 0;
	j = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.')
			j = i;
		i++;
	}
	file_type = ft_strdup(&(file_name[j + 1]));
	if (!ft_strcmp(file_type, needle))
		j = 0;
	else
		j = 1;
	(i > 0) ? free(file_type) : 0;
	return (j);
}

void		ft_lstadd_last(t_list *alst, t_list *new)
{
	if (new == NULL || alst == NULL)
		return ;
	if (alst == NULL)
	{
		new->next = NULL;
		alst = new;
	}
	else
	{
		while ((alst)->next)
			(alst) = (alst)->next;
		(alst)->next = new;
	}
}

char		*ft_strjoin_orig(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(new_str = (char *)ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 2)))
		return (0);
	i = -1;
	j = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	return (new_str);
}

long long	ft_power(long x, long y)
{
	long long	res;

	if (y > 0)
	{
		res = x;
		while (--y > 0)
			res = res * x;
		return (res);
	}
	else
		res = 1;
	return (res);
}
