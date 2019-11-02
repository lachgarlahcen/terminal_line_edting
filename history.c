/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:39:13 by llachgar          #+#    #+#             */
/*   Updated: 2019/10/31 21:50:43 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void    create_hist(t_hist *h, char *cmd)
{
    t_hist *new;

    if((new = (t_hist *)malloc(sizeof(t_hist))))
        return ;
    new->cmd = ft_strdup(cmd);
    new->next = NULL;
    if (h == NULL)
        h = new;
    else
        h->next = new;
}

