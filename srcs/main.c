/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/14 17:39:03 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *age;
	char *nom;

	nom = readline("entre ton nom : ");
	age = readline("entre ton age : ");

	printf ("ok %s tu as %s ans ", nom, age);
	return (1);
}
