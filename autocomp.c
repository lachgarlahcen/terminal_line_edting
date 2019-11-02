/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:50:58 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/01 15:55:45 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void    create_comp(t_tab *tab, char *data)
{
    t_hist *new;

    if((new = (t_hist *)malloc(sizeof(t_hist))))
        return ;
    new->cmd = ft_strdup(data);
    new->next = NULL;
    if (tab == NULL)
        tab = new;
    else
        tab->next = new;
}