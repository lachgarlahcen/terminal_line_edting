/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:13:47 by llachgar          #+#    #+#             */
/*   Updated: 2019/10/29 16:44:03 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		init_term(void)
{
	char			*termtype;
	int				success;
	struct termios	tattr;

	termtype = getenv("TERM");
	if (termtype == 0)
		ft_putstr_fd("Specify a terminal type'.\n", 2);
	success = tgetent(0, termtype);
	if (success < 0)
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
	if (success == 0)
		ft_putstr_fd("Terminal type  is not defined.\n", 2);
	if (termtype == 0 || success <= 0)
		exit(0);
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	/*tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;*/
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
void	default_term_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}
long		read_key(void)
{
	long key;

	key = 0;
	read(0, &key, sizeof(long));
	return (key);
}
void sheft(t_line *l)
{
	int i;

	i  = l->len;
	while (i >= l->cur)
	{
		l->chars[i] = l->chars[i - 1];
		i--;
	}
	l->chars[l->cur] = (int)l->key;
}
void plus(t_point *p, t_line *l, int b)
{
	if (p->c == l->w.ws_col - 1)
	{
		p->c = 0;
		if (p->r == (l->w.ws_row - 1))
		{
			l->init_p->r--;
			b ? l->cur_p->r-- : 1==1;
			ft_putstr_fd(DO, 0);
		}
		else
			p->r++;
	}
	else
		p->c++;
}
void mines(t_point *p, t_line *l)
{
	if (p->c > 0)
	{
		p->c--;
	}
	else
	{
		p->c = l->w.ws_col - 1;
		p->r--;
	}
	
}
void add_at(t_line *l)
{

	if (l->cur == l->len)
		l->chars[l->cur] = (int)l->key;
	else
	{
		sheft(l);
	}
	l->len++;
	l->cur++;
	plus(l->cur_p, l,0);
	l->chars[l->len] = '\0';
}


void	get_cur_pos(t_point *t)
{
	char	pos[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(pos, 20);
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	t->r = ft_atoi(pos + i);
	while (ft_isdigit(pos[i]))
		i++;
	t->c = ft_atoi(pos + i + 1);
}
t_line			*keep_l(t_line **l)
{
	static t_line *tmp;

	if (*l == NULL)
		return (tmp);
	tmp = *l;
	return (*l);
}

void print_cmd(t_line *l)
{
	t_point *p;
	int i;

	i = -1;
	p = (t_point *)malloc(sizeof(t_point));
	p->r = l->init_p->r - 1;
	p->c = 7; 
	ft_putstr_fd(tgoto(CM,0, l->init_p->r - 1), 0);
	ft_putstr_fd(CD, 0);
	ft_putstr_fd("ROOT:#>",0);
	while (++i < l->len)
	{
		ft_putstr_fd(tgoto(CM,p->c, p->r), 0);
		ft_putchar_fd(l->chars[i], 0);
		plus(p, l, 1);
	}
	ft_putstr_fd(tgoto(CM, l->cur_p->c, l->cur_p->r), 0);
}
static void		size_change(int s)
{
	t_line *l;

	(void)s;
	l = NULL;
	l = keep_l(&l);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	print_cmd(l);
}
void match_key(t_line *l)
{
	int i;
	t_key keys[5] = 
	{
		{RIGHT_K, &right_key},
		{LEFT_K , &left_key},
		{ESC_K, &esc_key},
		{DEL_K, &delete},
		{BACK_K, &delete}
	};
	i = -1;
	while (++i < 5)
		if (l->key == keys[i].key)
			keys[i].f(l);
}
int main(int ac, char **av)
{
	t_line *l;
	struct winsize w;
	
    init_term();
	//signal(SIGWINCH, size_change);
	l = (t_line *)malloc(sizeof(t_line));
	l->init_p = (t_point *)malloc(sizeof(t_point));
	l->cur_p = (t_point *)malloc(sizeof(t_point));
	l->len = 0; 
	ft_putstr_fd("ROOT:#>",0);
	get_cur_pos(l->init_p);
	get_cur_pos(l->cur_p);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	l->cur_p->c--;
	l->cur_p->r--;
	l->cur = 0;
	keep_l(&l);
    while (1337)
    {
        l->key = read_key();
		if (ft_isprint((int)l->key))
		{
			add_at(l);
		}
		else
			match_key(l);
		
		// if (l->key == LEFT_K && l->cur > 0)
		// {
		// 	//ft_putstr_fd(LE,0);
		// 	l->cur--;
		// 	mines(l->cur_p, l);
		// }
		// if (l->key == RIGHT_K && l->cur < l->len)
		// {
		// 	//ft_putstr_fd(ND,0);
		// 	l->cur++;
		// 	plus(l->cur_p, l, 0);
		// }
		// if (l->key == ESC_K)
		// {
		// 	default_term_mode();
		// 	printf("\n|| <<%s>> <<init R:%d>> <<init C:%d>> ||\n", l->chars,l->init_p->r, l->init_p->c);
		// 		exit(0);
		// }
		// if ((l->key == DEL_K || l->key == BACK_K) && l->cur > 0)
		// 	delete(l);
		print_cmd(l);
    }
}