/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:29:11 by llachgar          #+#    #+#             */
/*   Updated: 2019/10/31 14:59:37 by llachgar         ###   ########.fr       */
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
    free(l);
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
void end_k(t_line *l)
{
    int i;

    i = -1;
    home_k(l);
    while (++i < l->len)
        plus(l->cur_p, l, 0);
    l->cur = l->len;
}
void home_k(t_line *l)
{
    l->cur_p->c = l->init_p->c - 1;
    l->cur_p->r = l->init_p->r - 1;
    l->cur = 0;
}

void return_k(t_line *l)
{
    default_term_mode();
    printf("\n||%s||\n", l->chars);
    free(l);
    exit(0);
}

void 		ctl_left(t_line *l)
{
    int c;
    int s;

    c = 0;
    s = 0;

    while (--l->cur >= 0)
    {
        if (ft_isalnum(l->chars[l->cur]))
        {
            c = 1;
            s = 0;
        }
        else
            s = 1;
        mines(l->cur_p,l);
        if (c && s)
        {
            plus(l->cur_p,l, 0);
            l->cur++;
            return ;
        }
    }
    l->cur++;
}
void 		ctl_right(t_line *l)
{
    int c;
    int s;

    c = 0;
    s = 0;

    while (l->cur < l->len)
    {
        if (!ft_isalnum(l->chars[l->cur]))
        {
            c = 0;
            s = 1;
        }
        else
            c = 1;
        if (c && s)
            return ;
        plus(l->cur_p,l, 0);
        l->cur++;
    }
}