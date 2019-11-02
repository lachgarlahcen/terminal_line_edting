/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:13:47 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/02 17:33:01 by llachgar         ###   ########.fr       */
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
	int key;
	int res;
	key = 0;
	res = read(0, &key,sizeof(int));
	//printf("{%c}\n", key);
	/*if (res != 0)
	{
		read(0, c,READ_SIZE);
		ft_putstr_fd("{", 0);
		ft_putstr_fd(c, 0);
		ft_putstr_fd("}", 0);
	}*/

	return (key);
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
	t_point p;
	int i;

	i = l->b_p - 1;
	p.r = l->init_p->r - 1;
	p.c = 7; 
	ft_putstr_fd(tgoto(CM,0, l->init_p->r - 1), 0);
	ft_putstr_fd(CD, 0);
	ft_putstr_fd(l->prompt,0);
	while (++i < l->len)
	{
		//ft_putstr_fd(tgoto(CM,p.c, p.r), 0);
		ft_putchar_fd(l->chars[i], 0);
		plus(&p, l, 1);
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
	t_key keys[10] = 
	{
		{RIGHT_K, &right_key},
		{LEFT_K , &left_key},
		{ESC_K, &esc_key},
		{DEL_K, &delete},
		{BACK_K, &delete},
		{END_K, &end_k},
		{HOME_K, &home_k},
		{INTER_k, &return_k},
		{CTL_B, &ctl_left},
		{CTL_F, &ctl_right}

	};
	i = -1;
	while (++i < 10)
		if (l->key == keys[i].key)
			keys[i].f(l);
}
t_line *init_line(void)
{
	t_line *l;
	l = (t_line *)malloc(sizeof(t_line));
	l->init_p = (t_point *)malloc(sizeof(t_point));
	l->cur_p = (t_point *)malloc(sizeof(t_point));
	if (l == NULL || l->init_p == NULL || l->cur_p == NULL)
		return (NULL);
	l->len = 0;
	l->b_p = 0;
	l->prompt = "ROOT:#>";
	ft_putstr_fd(l->prompt,0);
	get_cur_pos(l->init_p);
	get_cur_pos(l->cur_p);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	l->cur_p->c--;
	l->cur_p->r--;
	l->cur = 0;
	l->hist = NULL;
	keep_l(&l);
	return (l);
}
int main(int ac, char **av)
{
	t_line *l;
	struct winsize w;
	
    init_term();
	signal(SIGWINCH, size_change);
	if ((l = init_line()) == NULL)
		return (0);
    while (1337)
    {
		l->key = read_key();
		//printf("--%ld--|\n",l->key);
		if (ft_isprint(l->key))
			add_at(l);
		else
			match_key(l);
		print_cmd(l);
    }
}