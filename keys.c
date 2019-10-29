/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:29:11 by llachgar          #+#    #+#             */
/*   Updated: 2019/10/29 16:43:30 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void right_key(t_line *l)
{
    if (l->cur >= l->len)
        return ;
    l->cur++;
	plus(l->cur_p, l, 0);
}
void left_key(t_line *l)
{
    if (l->cur <= 0)
        return ;
    l->cur--;
    mines(l->cur_p, l);
}
void esc_key(t_line *l)
{
    default_term_mode();
    printf("\n|| <<%s>> <<init R:%d>> <<init C:%d>> ||\n", l->chars,l->init_p->r, l->init_p->c);
    exit(0);
}

void delete(t_line *l)
{
	int i;

    if (l->cur <= 0)
        return ;
	i = l->cur - 1;
	while (i < l->len)
	{
		l->chars[i] = l->chars[i + 1];
		i++;
	}
	l->len--;
	l->cur--;
	mines(l->cur_p, l);
}