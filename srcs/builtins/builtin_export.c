/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/07/06 21:00:59 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*skip_symbol(char *argv)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(ft_strlen(argv));
	if (!str)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	i = 0;
	j = 0;
	while (argv[i] != '\0')
	{
		if (argv[i + 1] == '=' && cherche_symbol(argv[i], "+"))
		{
			i++;
			continue ;
		}
		str[j++] = argv[i];
		i++;
	}
	return (str);
}

bool	error_symbol(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
	{
		if (cherche_symbol(argv[i], "!$%'()*+,-./:;<>?@[]^`{|}~"))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_export(int argc, char **argv)
{
	int		status;
	int		i;
	char	*new;

	status = EXIT_SUCCESS;
	if (argc == 1)
		exported_vars();
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			new = skip_symbol(argv[i]);
			status = export_2(argv, new, i);
			i++;
		}
	}
	return (status);
}

bool	check_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '\0' || argv[0] == '=')
		return (false);
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	if (argv[i] == '=' || argv[i] == '\0')
		return (true);
	else
		return (false);
}
